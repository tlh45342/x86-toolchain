"""ELF16 ABI bootstrap fixture: standard ELF32 container with 8086 payload.

This tests the proposed on-disk load contract independently of x86-ld.
It is NOT a claim that x86-ld emits ELF16 yet.
"""
import struct
import unittest

ELF_HEADER = '<16sHHIIIIIHHHHHH'
PROGRAM_HEADER = '<IIIIIIII'
LOAD = 1


def make_fixture():
    ident = b'\x7fELF' + bytes([1, 1, 1, 0]) + bytes(8)
    # e_machine=0 deliberately denotes a prototype fixture, NOT a registered ABI.
    header = struct.pack(ELF_HEADER, ident, 2, 0, 1, 0x8000, 52, 0,
                         0, 52, 32, 2, 0, 0, 0)
    program = bytes([0xB8, 0x34, 0x12, 0xF4])  # mov ax,1234h; hlt
    data = b'BJ16'
    ph1 = struct.pack(PROGRAM_HEADER, LOAD, 0x100, 0x8000, 0x8000,
                      len(program), len(program), 5, 16)
    ph2 = struct.pack(PROGRAM_HEADER, LOAD, 0x200, 0x11000, 0x11000,
                      len(data), 16, 6, 16)
    image = bytearray(0x200 + len(data))
    image[:52] = header
    image[52:116] = ph1 + ph2
    image[0x100:0x104] = program
    image[0x200:0x204] = data
    return bytes(image)


def validate_loads(image, allowed_start=0x8000, allowed_end=0xA0000):
    if len(image) < 52 or image[:7] != b'\x7fELF\x01\x01\x01':
        raise ValueError('invalid ELF32 header')
    fields = struct.unpack_from(ELF_HEADER, image)
    entry, phoff, phsize, count = fields[4], fields[5], fields[9], fields[10]
    if phsize != 32 or phoff + phsize * count > len(image):
        raise ValueError('invalid program header table')
    regions = []
    memory = {}
    for i in range(count):
        typ, offset, vaddr, physical, filesz, memsz, flags, align = struct.unpack_from(
            PROGRAM_HEADER, image, phoff + i * phsize)
        if typ != LOAD:
            continue
        end = physical + memsz
        if filesz > memsz or offset + filesz > len(image):
            raise ValueError('invalid segment size')
        if physical < allowed_start or end > allowed_end or end < physical:
            raise ValueError('unsafe physical destination')
        if any(physical < hi and lo < end for lo, hi in regions):
            raise ValueError('overlapping load segments')
        regions.append((physical, end))
        memory[physical] = image[offset:offset + filesz] + bytes(memsz - filesz)
    if not any(lo <= entry < hi for lo, hi in regions):
        raise ValueError('entry is not loadable')
    return memory


class ELF16FixtureTests(unittest.TestCase):
    def test_two_segments_and_bss(self):
        memory = validate_loads(make_fixture())
        self.assertEqual(memory[0x8000], b'\xb8\x34\x12\xf4')
        self.assertEqual(memory[0x11000], b'BJ16' + bytes(12))

    def test_reject_truncated_program_headers(self):
        with self.assertRaises(ValueError):
            validate_loads(make_fixture()[:60])

    def test_reject_overlapping_segments(self):
        image = bytearray(make_fixture())
        struct.pack_into('<I', image, 52 + 32 + 12, 0x8002)
        with self.assertRaises(ValueError):
            validate_loads(image)

    def test_reject_outside_memory(self):
        image = bytearray(make_fixture())
        struct.pack_into('<I', image, 52 + 32 + 12, 0xA0000)
        with self.assertRaises(ValueError):
            validate_loads(image)


if __name__ == '__main__':
    unittest.main()
