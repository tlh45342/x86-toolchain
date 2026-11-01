CC = gcc
CFLAGS ?= -std=c11 -Wall -Wextra -Werror -O2
PREFIX ?= $(USERPROFILE)/.local
BINDIR ?= $(PREFIX)/bin
-include ../config.mk

.PHONY: all install test clean
all: x86-nm.exe
x86-nm.exe: x86-nm.c
	$(CC) $(CFLAGS) -o $@ $<
install: x86-nm.exe
	@if not exist "$(subst /,\,$(BINDIR))" mkdir "$(subst /,\,$(BINDIR))"
	@copy /Y x86-nm.exe "$(subst /,\,$(BINDIR))\x86-nm.exe" >NUL
	@echo Installed x86-nm to $(BINDIR)
test: x86-nm.exe
	@x86-nm.exe --help
clean:
	@if exist x86-nm.exe del /Q x86-nm.exe
