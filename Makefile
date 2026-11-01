.DEFAULT_GOAL := all

CONFIG_FILE := config.mk
-include $(CONFIG_FILE)

TOOLS := x86-as x86-cc x86-ld x86-ar x86-nm x86-objdump x86-disk
CONFIG_PYTHON ?= python

.PHONY: all help install test clean config-show config-set config-reset show-config set-config $(TOOLS)

all: $(TOOLS)

$(TOOLS):
	$(MAKE) -C $@ all

help:
	@echo x86-toolchain targets:
	@echo   make                 Build all toolchain components
	@echo   make test            Run component test suites
	@echo   make install         Install all toolchain components
	@echo   make clean           Clean components with clean targets
	@echo   make config-show     Display saved configuration
	@echo   make config-set KEY=NAME VALUE=VALUE
	@echo   make config-reset    Remove saved overrides
	@echo   make set-config / show-config  Compatibility aliases
	@echo Configuration is saved in config.mk.

config-show show-config:
	@$(CONFIG_PYTHON) scripts/config.py show

config-set set-config:
	@$(CONFIG_PYTHON) scripts/config.py set "$(KEY)" "$(VALUE)"

config-reset:
	@$(CONFIG_PYTHON) scripts/config.py reset

install:
	@$(MAKE) -C x86-as install
	@$(MAKE) -C x86-cc install
	@$(MAKE) -C x86-ld install
	@$(MAKE) -C x86-ar install
	@$(MAKE) -C x86-nm install
	@$(MAKE) -C x86-objdump install
	@$(MAKE) -C x86-disk install
	@echo Installation finished.

test:
	@$(foreach tool,$(TOOLS),$(MAKE) -C $(tool) test &&) echo Tests finished.

clean:
	@$(CONFIG_PYTHON) scripts/config.py clean
