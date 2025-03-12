SHELL := bash
MAKEFLAGS += --no-builtin-rules --no-print-directory

config_path := .
source_path := source
include_path := include
examples_path := examples
os := linux
tests_path := tests

build_type = Debug
cxx = g++-13
verbose_makefile = OFF
warnings_as_errors = OFF

build_path := $(abspath $(shell pwd)/build/$(os)/$(cxx)/$(build_type))
install_path := $(abspath $(shell pwd)/install/$(os)/$(cxx)/$(build_type))
lib_path :=  $(install_path)/lib
exec_path :=  $(install_path)/bin

OPTIONS = debug release relwdebug verbose
OPTIONS_INPUT = $(filter $(OPTIONS), $(MAKECMDGOALS))

.DEFAULT_GOAL := all

.PHONY: all
all: install

.PHONY: install
install: build
	cmake --install $(build_path)

.PHONY: build
build: configure
	$(MAKE) -C $(build_path) -j 20

.PHONY: configure
configure: $(build_path)/Makefile

$(build_path)/Makefile: CMakeLists.txt $(OPTIONS_INPUT)
	CXX=$(cxx) cmake -S $(config_path) -B $(build_path) \
		-DCMAKE_BUILD_TYPE=$(build_type) \
		-DCMAKE_INSTALL_PREFIX=$(install_path) \
		-DCMAKE_VERBOSE_MAKEFILE:BOOL=$(verbose_makefile) \
		-DWARNINGS_AS_ERRORS:BOOL=$(warnings_as_errors) \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=OPTIONS

.PHONY: examples
examples: install
	$(MAKE) -C $(build_path)/$(examples_path) install
	
.PHONY: tests
tests: install
	$(MAKE) -C $(build_path)/$(tests_path) install

.PHONY: debug
debug: 
	$(eval build_type = Debug)
	$(eval build_path = $(abspath $(shell pwd)/build/$(os)/$(cxx)/$(build_type)))
	$(eval install_path = $(abspath $(shell pwd)/install/$(os)/$(cxx)/$(build_type)))
	$(eval lib_path = $(install_path)/lib)
	$(eval exec_path = $(install_path)/bin)
	
.PHONY: release
release: 
	$(eval build_type = Release)
	$(eval build_path = $(abspath $(shell pwd)/build/$(os)/$(cxx)/$(build_type)))
	$(eval install_path = $(abspath $(shell pwd)/install/$(os)/$(cxx)/$(build_type)))
	$(eval lib_path = $(install_path)/lib)
	$(eval exec_path = $(install_path)/bin)
	
.PHONY: relwdebug
relwdebug: 
	$(eval build_type = RelWithDebInfo)
	$(eval build_path = $(abspath $(shell pwd)/build/$(os)/$(cxx)/$(build_type)))
	$(eval install_path = $(abspath $(shell pwd)/install/$(os)/$(cxx)/$(build_type)))
	$(eval lib_path = $(install_path)/lib)
	$(eval exec_path = $(install_path)/bin)

.PHONY: verbose
verbose:
	$(eval verbose_makefile = ON)

.PHONY: clean
clean:
	@cmake --build $(build_path) --target clean

.PHONY: new
new: 
	rm -rf build
	rm -rf install

CLANG_TIDY_CMD = clang-tidy -p=$(build_path) --extra-arg=-Who-unknown-warning-option --extra-arg=-std=c++23
.PHONY: check
check: build
	command find $(source_path) -type f -name '*.cpp' | xargs $(CLANG_TIDY_CMD)
	command find $(include_path) -type f -name '*.hpp' | xargs $(CLANG_TIDY_CMD)
	command find $(examples_path) -type f -name '*.cpp' | xargs $(CLANG_TIDY_CMD)
	command find $(tests_path) -type f -name '*.cpp' | xargs $(CLANG_TIDY_CMD)