CC = gcc
CFLAGS ?= -std=c11 -Wall -Wextra -O2
TARGET := x86-ld

ifeq ($(OS),Windows_NT)
TARGET := x86-ld.exe
PREFIX ?= $(USERPROFILE)/.local
BINDIR ?= $(PREFIX)/bin
CP = copy /Y
else
PREFIX ?= $(HOME)/.local
BINDIR ?= $(PREFIX)/bin
CP = cp -f
endif

.PHONY: all clean install test test-blackjack16
all: $(TARGET)

$(TARGET): x86-ld.c bjo3_link.h
	$(CC) $(CFLAGS) -o $@ $<

install: $(TARGET)
ifeq ($(OS),Windows_NT)
	@if not exist "$(subst /,\,$(BINDIR))" mkdir "$(subst /,\,$(BINDIR))"
	@$(CP) "$(TARGET)" "$(subst /,\,$(BINDIR))" >NUL
else
	@mkdir -p "$(BINDIR)"
	@$(CP) "$(TARGET)" "$(BINDIR)/x86-ld"
endif
	@echo Installed x86-ld to $(BINDIR)

test: $(TARGET)
	python tests/run_tests.py
	python tests/run_blackjack16.py
	python tests/medium/bjo3_far32_module_cs.py

test-blackjack16: $(TARGET)
	python tests/run_blackjack16.py
	python tests/medium/bjo3_link_smoke.py
	python tests/medium/bjo3_cross_symbol.py
	python tests/medium/bjo3_multisection_link.py
	python tests/medium/bjo3_far32_module_cs.py

clean:
ifeq ($(OS),Windows_NT)
	@if exist "$(TARGET)" del /Q "$(TARGET)"
	@if exist tests\build rmdir /S /Q tests\build
else
	rm -f $(TARGET)
	rm -rf tests/build
endif

# Shared toolchain configuration (root config.mk).
-include ../config.mk
