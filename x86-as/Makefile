CC = gcc
CFLAGS ?= -std=c11 -Wall -Wextra -O2
TARGET := x86-as

# Host detection.  Do not require callers to pass OS=Windows_NT:
# cmd.exe exports OS, but Unix-like shells on Windows may not.
ifeq ($(OS),Windows_NT)
HOST_WINDOWS := 1
else ifneq ($(findstring .exe,$(notdir $(SHELL))),)
HOST_WINDOWS := 1
else
HOST_WINDOWS := 0
endif

ifeq ($(HOST_WINDOWS),1)
TARGET := x86-as.exe
PREFIX ?= $(USERPROFILE)/.local
BINDIR ?= $(PREFIX)/bin
else
TARGET := x86-as
PREFIX ?= $(HOME)/.local
BINDIR ?= $(PREFIX)/bin
endif

.PHONY: all clean install test test-sections test-x86 test-bjobj-reloc test-nasm test-compare
all: $(TARGET)

$(TARGET): x86-as.c omf_writer.h bj_sections.h bj_section_object.h bj_section_symbols.h
	$(CC) $(CFLAGS) -o $@ $<

install: $(TARGET)
ifeq ($(HOST_WINDOWS),1)
	@if not exist "$(subst /,\,$(BINDIR))" mkdir "$(subst /,\,$(BINDIR))"
	@copy /Y "$(TARGET)" "$(subst /,\,$(BINDIR))\x86-as.exe" >NUL
else
	@mkdir -p "$(BINDIR)"
	@cp -f "$(TARGET)" "$(BINDIR)/x86-as"
endif
	@echo Installed x86-as to $(BINDIR)

test: test-x86 test-bjobj-reloc test-sections
	python tests/test_omf.py

# Section-storage regression; future integration tests will extend this target.
test-sections: $(TARGET)
	$(CC) $(CFLAGS) -Werror -o tests/bj_sections_test.exe tests/bj_sections_test.c
	./tests/bj_sections_test.exe
	$(CC) $(CFLAGS) -Werror -o tests/bj_section_object_test.exe tests/bj_section_object_test.c
	./tests/bj_section_object_test.exe
	$(CC) $(CFLAGS) -Werror -o tests/bj_section_symbols_test.exe tests/bj_section_symbols_test.c
	./tests/bj_section_symbols_test.exe
	python tests/test_bjobj3_writer.py
	python tests/test_bjo3_multisection.py
	python ../x86-ld/tests/medium/bjo2_sections_test.py ./$(TARGET)

test-bjobj-reloc: $(TARGET)
	python tests/test_bjobj_abs16.py
	python tests/test_bjobj_abs16_matrix.py

test-x86: $(TARGET)
	python tests/run_tests.py --assembler x86

test-nasm:
	python tests/run_tests.py --assembler nasm

test-compare: $(TARGET)
	python tests/run_tests.py --assembler compare

clean:
ifeq ($(HOST_WINDOWS),1)
	@if exist x86-as del /Q x86-as
	@if exist x86-as.exe del /Q x86-as.exe
	@if exist tests\build rmdir /S /Q tests\build
else
	rm -f x86-as x86-as.exe
	rm -rf tests/build
endif

# Shared toolchain configuration (root config.mk).
-include ../config.mk
