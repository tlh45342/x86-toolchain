# BJO2 object format (current v0 and planned multi-section extension)

All integer fields are unsigned little-endian. Strings occupy exactly 64 bytes,
zero-padded and terminated where possible. Do not assume host structure packing.

## Currently implemented (single TEXT section)

| Offset | Width | Field |
|---|---:|---|
| 0 | 4 | ASCII `BJO2` |
| 4 | 2 | section count (currently exactly 1) |
| 6 | 2 | symbol count |
| 8 | 2 | relocation count |
| 10 | 2 | reserved, zero |
| 12 | 2 | section kind (1 = TEXT) |
| 14 | 4 | section byte count |
| 18 | 2 | section alignment (16) |

Immediately following the 20-byte header are symbol records (71 bytes each),
then relocation records (71 bytes each), then the TEXT bytes.

Symbol record: name[64], section:u16, value:u32, defined:u8.
Relocation record: target_name[64], source_section:u16, offset:u32,
relocation_type:u8. Section 0 means undefined; section 1 means TEXT.

Relocation types: 1 PC16, 2 ABS16 (ambiguous; forbidden in Medium),
3 FAR32. DATA16/CODE16/SEG16 (types 4/5/6) are reserved and MUST NOT be
emitted or linked until their semantics and addend handling are implemented.

The `__bjo_origin` symbol is a compatibility marker and is not a runtime
symbol. This is not yet a full sectioned object format.

## Multi-section evolution (NOT YET IMPLEMENTED)

The existing 20-byte layout only describes one section; do not increment
section_count without revising the header layout and versioning it. A future
revision must specify a table of section descriptors, including file offsets,
logical sizes, alignment, section kinds TEXT/DATA/BSS, and BSS no-file-bytes
semantics. It must also identify both source and target sections and retain
signed relocation addends. Older readers should reject new revisions rather
than misinterpret payloads.

Medium-model link rules: TEXT may occupy multiple CS segments; DATA and BSS
must fit into one DS segment; SS remains independent. Startup must set DS,
initialize DATA, and zero BSS before invoking C. Cross-segment near calls
must fail. The VM execution tests verify far calls beyond physical 64 KiB,
but do not yet verify shared DS.
