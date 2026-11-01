

## README

This is my 16bit x86 toolchain project

There is no real reason for this.  You are most likely better off using NASM or MASM.
This is a vanity project - to check a box and say I played in that pool.

| Component | Note |
| --- | --- |
| x86-as | Assembler |
| x86-ld | Linker |
| x86-disk | Similarities to mtools. |
| x86-cc | yet another compiler |
| x86-objdump | Yup, a tool to dump out the guts of something |
| x86-ar | yet another archiver |
| x86-nm | The toolchains namer - might as well of called it the "table of contents" |

if you are using x86-disk... I strongly suggest you leave it alone and look at my project named "Guppy"  You will probably be happier.  x86-disk deals in raw format and was pretty much designed to build a floppy.  mtools has more file manipulating utilities than x86-disk.  Guppy brings the kitchen sink; is platform agnostic; and can work with virtual disk formats.

Note To Self: 

yes... Tom we are revisiting the 90's  Back to using MASM and from Borland TASM and Turbo C.
So get over it.  Yes OMF = the OBJ files you are used to.  You just didn't call it OMF - you just knew them as OBJ files.



---

## License

This project and it's code is released under the **MIT License**.

Copyright (c) 2026 Tom Hamilton.

See `LICENSE` for the license text.

---

## Author

**Tom Hamilton**
