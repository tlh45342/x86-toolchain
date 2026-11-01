CC = gcc
CFLAGS ?= -std=c11 -Wall -Wextra -Werror -O2
PREFIX ?= $(USERPROFILE)/.local
BINDIR ?= $(PREFIX)/bin
-include ../config.mk

.PHONY: all install test clean
all: x86-ar.exe
x86-ar.exe: x86-ar.c
	$(CC) $(CFLAGS) -o $@ $<
install: x86-ar.exe
	@if not exist "$(subst /,\,$(BINDIR))" mkdir "$(subst /,\,$(BINDIR))"
	@copy /Y x86-ar.exe "$(subst /,\,$(BINDIR))\x86-ar.exe" >NUL
	@echo Installed x86-ar to $(BINDIR)
test: x86-ar.exe
	python tests/test_duplicate_symbols.py
clean:
	@if exist x86-ar.exe del /Q x86-ar.exe
