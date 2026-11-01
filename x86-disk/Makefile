CC = gcc
CFLAGS ?= -std=c11 -Wall -Wextra -O2
TARGET := x86-disk

ifeq ($(OS),Windows_NT)
TARGET := x86-disk.exe
PREFIX ?= $(USERPROFILE)/.local
BINDIR ?= $(PREFIX)/bin
CP = copy /Y
else
PREFIX ?= $(HOME)/.local
BINDIR ?= $(PREFIX)/bin
CP = cp -f
endif

.PHONY: all clean install
all: $(TARGET)

$(TARGET): x86-disk.c
	$(CC) $(CFLAGS) -o $@ $<

install: $(TARGET)
ifeq ($(OS),Windows_NT)
	@if not exist "$(subst /,\,$(BINDIR))" mkdir "$(subst /,\,$(BINDIR))"
	@$(CP) "$(TARGET)" "$(subst /,\,$(BINDIR))" >NUL
else
	@mkdir -p "$(BINDIR)"
	@$(CP) "$(TARGET)" "$(BINDIR)/x86-disk"
endif
	@echo Installed x86-disk to $(BINDIR)

clean:
ifeq ($(OS),Windows_NT)
	@if exist "$(TARGET)" del /Q "$(TARGET)"
else
	rm -f $(TARGET)
endif

# Shared toolchain configuration (root config.mk).
-include ../config.mk
