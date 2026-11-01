CC = gcc
CFLAGS ?= -std=c11 -Wall -Wextra -O2
LDFLAGS :=
TARGET := x86-cc

# Some Windows cmd environments do not export OS=Windows_NT. GNU make on
# Windows provides ComSpec, so accept either signal.
HOST_WINDOWS := $(if $(filter Windows_NT,$(OS)),1,$(if $(COMSPEC),1,))
ifeq ($(HOST_WINDOWS),1)
TARGET := x86-cc.exe
LDFLAGS += -Wl,--stack,8388608
PREFIX ?= $(subst \,/,$(USERPROFILE))/.local
CP := copy /Y
else
PREFIX ?= $(HOME)/.local
CP := cp -f
endif
BINDIR ?= $(PREFIX)/bin
LIBDIR ?= $(PREFIX)/lib/x86-cc
INCLUDEDIR ?= $(LIBDIR)/include
CONFIG := config.mk

-include $(CONFIG)

CFLAGS += -DX86CC_DEFAULT_INCLUDEDIR=\"$(INCLUDEDIR)\"

.PHONY: test-global-struct-enum
test-global-struct-enum: $(TARGET)
	./$(TARGET) -c tests/global_struct_array_member.c -o tests/global_struct_array_member.o

.PHONY: test-struct-address
# Structure-address and structure-pointer-address regression (LACC-inspired).
test-struct-address: $(TARGET)
	./$(TARGET) -c tests/struct_address_call.c -o tests/struct_address_call.o
	./$(TARGET) -c tests/function_pointer_struct_member_lacc.c -o tests/function_pointer_struct_member_lacc.o
	./$(TARGET) -c tests/function_pointer_typedef_member_lacc.c -o tests/function_pointer_typedef_member_lacc.o
	./$(TARGET) -c tests/function_pointer_typedef_cast_lacc.c -o tests/function_pointer_typedef_cast_lacc.o
	./$(TARGET) -c tests/frame_slots_typedef_cast_followed_by_local.c -o tests/frame_slots_typedef_cast_followed_by_local.o

.PHONY: all clean install test test-optimization test-asm test-far-pointer test-corpus test-peephole measure-peephole config-set show-config
all: $(TARGET)

$(TARGET): x86-cc.c peephole.h long_branches.h
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

install: $(TARGET)
ifeq ($(HOST_WINDOWS),1)
	@if not exist "$(subst /,\,$(BINDIR))" mkdir "$(subst /,\,$(BINDIR))"
	@$(CP) "$(TARGET)" "$(subst /,\,$(BINDIR))" >NUL
	@if not exist "$(subst /,\,$(INCLUDEDIR))" mkdir "$(subst /,\,$(INCLUDEDIR))"
	@xcopy /E /I /Y "include" "$(subst /,\,$(INCLUDEDIR))" >NUL
	@if exist "..\libc\include" xcopy /E /I /Y "..\libc\include" "$(subst /,\,$(INCLUDEDIR))" >NUL
else
	@mkdir -p "$(BINDIR)"
	@mkdir -p "$(INCLUDEDIR)"
	@$(CP) "$(TARGET)" "$(BINDIR)/x86-cc"
	@cp -R include/. "$(INCLUDEDIR)/"
	@if [ -d ../libc/include ]; then cp -R ../libc/include/. "$(INCLUDEDIR)/"; fi
endif
	@echo Installed x86-cc to $(BINDIR)
	@echo Installed x86-cc headers to $(INCLUDEDIR)

config-set:
	@python config-set.py config.mk PREFIX=$(PREFIX) BINDIR=$(BINDIR) LIBDIR=$(LIBDIR) INCLUDEDIR=$(INCLUDEDIR)

show-config:
	@echo x86-cc build configuration
	@echo ------------------------------------------------------------
	@echo PREFIX      $(PREFIX)
	@echo BINDIR      $(BINDIR)
	@echo LIBDIR      $(LIBDIR)
	@echo INCLUDEDIR  $(INCLUDEDIR)
	@echo CONFIG      $(CONFIG)

test: $(TARGET)
	python tests/run_tests.py
	python tests/test_wide32.py
	python tests/test_inline_asm.py
	python tests/test_far_pointer_local.py
	python tests/test_peephole_sprint2.py
	python tests/test_peephole_production.py
	python tests/test_peephole_analyzer.py
	python tests/test_sprint34.py
	python tests/test_sprint56.py
	python tests/test_optimization_gate.py
	python tests/test_optimization_execution.py
	$(TARGET) -c --blackjack tests/stdlib_atoi_prototype.c -o tests/stdlib_atoi_prototype.o

test-optimization: $(TARGET)
	python tests/test_peephole_sprint2.py
	python tests/test_peephole_production.py
	python tests/test_peephole_analyzer.py
	python tests/test_sprint34.py
	python tests/test_sprint56.py
	python tests/test_optimization_gate.py
	python tests/test_optimization_execution.py

test-peephole:
	python tests/test_peephole_sprint2.py

measure-peephole:
	python tests/measure_peephole.py

test-wide32: $(TARGET)
	python tests/test_wide32.py

test-asm: $(TARGET)
	python tests/test_inline_asm.py

test-far-pointer: $(TARGET)
	python tests/test_far_pointer_local.py

test-corpus: $(TARGET)
	python tests/run_corpus.py

.PHONY: test-lacc
test-lacc: $(TARGET)
	$(TARGET) -c tests/typedef_order_lacc.c -o tests/build/typedef_order_lacc.o
	$(TARGET) -c tests/function_typedef_lacc.c -o tests/build/function_typedef_lacc.o
	$(TARGET) -c tests/function_typedef_chain_lacc.c -o tests/build/function_typedef_chain_lacc.o
	$(TARGET) -c tests/global_string_pointer_lacc.c -o tests/build/global_string_pointer_lacc.o
	$(TARGET) -c tests/conditional_global_string.c -o tests/build/conditional_global_string.o
	python tests/run_lacc_baseline.py

clean:
ifeq ($(HOST_WINDOWS),1)
	@if exist "$(TARGET)" del /Q "$(TARGET)"
	@if exist tests\build rmdir /S /Q tests\build
else
	rm -f $(TARGET)
	rm -rf tests/build
endif

# Shared toolchain configuration (root config.mk).
-include ../config.mk
