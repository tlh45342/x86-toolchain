CC = gcc
CFLAGS ?= -std=c11 -Wall -Wextra -O2
TARGET := x86-objdump
ifeq ($(OS),Windows_NT)
TARGET := x86-objdump.exe
PREFIX ?= $(USERPROFILE)/.local
BINDIR ?= $(PREFIX)/bin
else
PREFIX ?= $(HOME)/.local
BINDIR ?= $(PREFIX)/bin
endif
.PHONY: all install test clean
all: $(TARGET)
$(TARGET): x86-objdump.c omf_dump.h disasm/x86_disasm.c disasm/x86_disasm.h
	$(CC) $(CFLAGS) -I. -o $@ x86-objdump.c disasm/x86_disasm.c
test: $(TARGET)
	python tests/run_tests.py
	python tests/test_bjo3.py
	python tests/test_omf.py
install: $(TARGET)
ifeq ($(OS),Windows_NT)
	@if not exist "$(subst /,\,$(BINDIR))" mkdir "$(subst /,\,$(BINDIR))"
	@copy /Y "$(TARGET)" "$(subst /,\,$(BINDIR))" >NUL
else
	@mkdir -p "$(BINDIR)"
	@cp -f "$(TARGET)" "$(BINDIR)/x86-objdump"
endif
	@echo Installed x86-objdump to $(BINDIR)
clean:
ifeq ($(OS),Windows_NT)
	@if exist "$(TARGET)" del /Q "$(TARGET)"
else
	rm -f $(TARGET)
endif

# Shared toolchain configuration (root config.mk).
-include ../config.mk
