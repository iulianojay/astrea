SHELL := bash
MAKEFLAGS += --no-builtin-rules --no-print-directory

config_path := $(abspath $(shell pwd))
source_path := waveguide
examples_path := examples
arch := x86_64
os := Linux
comp := GNU-13.1.0
tests_path := tests

build_type = Debug
cxx = g++-13
verbose_makefile = OFF
warnings_as_errors = OFF

# build_path := $(abspath $(shell pwd)/build/$(arch)-$(os)/$(comp)/$(build_type))
build_path := $(abspath $(shell pwd)/build/gcc-13-23/$(build_type))

OPTIONS = debug release relwdebug verbose
OPTIONS_INPUT = $(filter $(OPTIONS), $(MAKECMDGOALS))

.DEFAULT_GOAL := conan-debug

# THESE DON"T WORK AND WILL BREAK THINGS IF YOU USE THEM
# .DEFAULT_GOAL := all

# .PHONY: all
# all: install

# .PHONY: install
# install: build
# 	cmake --install $(build_path)

# .PHONY: build
# build: configure
# 	$(MAKE) -C $(build_path) -j 20

# .PHONY: configure
# configure: $(build_path)/Makefile

# $(build_path)/Makefile: CMakeLists.txt
# 	cmake -S $(config_path) -B $(build_path) \
# 		-DCMAKE_BUILD_TYPE=$(build_type) \
# 		-DCMAKE_VERBOSE_MAKEFILE:BOOL=$(verbose_makefile) \
# 		-DWARNINGS_AS_ERRORS:BOOL=$(warnings_as_errors) \
# 		-DCMAKE_EXPORT_COMPILE_COMMANDS=ON  

# .PHONY: examples
# examples: install
# 	$(MAKE) -C $(build_path)/$(examples_path) install
	
# .PHONY: tests
# tests: install
# 	$(MAKE) -C $(build_path)/waveguide/math/$(tests_path) install 
# 	$(MAKE) -C $(build_path)/waveguide/astro/$(tests_path) install 
	
.PHONY: run_tests
run_tests: conan-debug
	cd $(build_path)/waveguide/math/tests && ctest
	cd $(build_path)/waveguide/astro/tests && ctest
	cd $(build_path)/waveguide/access/tests && ctest

.PHONY: debug
debug: 
	$(eval build_type = Debug)
	$(eval build_path = $(abspath $(shell pwd)/build/$(arch)-$(os)/$(comp)/$(build_type)))
	
.PHONY: release
release: 
	$(eval build_type = Release)
	$(eval build_path = $(abspath $(shell pwd)/build/$(arch)-$(os)/$(comp)/$(build_type)))
	
.PHONY: relwdebug
relwdebug: 
	$(eval build_type = RelWithDebInfo)
	$(eval build_path = $(abspath $(shell pwd)/build/$(arch)-$(os)/$(comp)/$(build_type)))

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
	find $(source_path) -regex '.*\.\(cpp\|hpp\|c\|h\)' | xargs $(CLANG_TIDY_CMD)
	find $(examples_path) -regex '.*\.\(cpp\|hpp\|c\|h\)' | xargs $(CLANG_TIDY_CMD)

# Conan commands - for now
.PHONY: conan-setup-debug
conan-setup-debug: 
	conan install . -pr ~/.conan2/profiles/gcc13-debug -b=missing 

.PHONY: conan-build-debug
conan-build-debug: conan-setup-debug
	cmake -S . --preset conan-gcc-13-23-debug

.PHONY: conan-debug
conan-debug: conan-build-debug
	cmake --build --preset conan-gcc-13-23-debug -DINSTALL_GTEST=OFF --target install
	
	
.PHONY: conan-setup-release
conan-setup-release: 
	conan install . -pr ~/.conan2/profiles/gcc13-release -b=missing 

.PHONY: conan-build-release
conan-build-release: conan-setup-release
	cmake -S . --preset conan-gcc-13-23-release

.PHONY: conan-release
conan-release: conan-build-release
	cmake --build --preset conan-gcc-13-23-release -DINSTALL_GTEST=OFF --target install
	
	
.PHONY: conan-setup-relwithdebinfo
conan-setup-relwithdebinfo: 
	conan install . -pr ~/.conan2/profiles/gcc13-relwithdebinfo -b=missing 

.PHONY: conan-build-relwithdebinfo
conan-build-relwithdebinfo: conan-setup-relwithdebinfo
	cmake -S . --preset conan-gcc-13-23-relwithdebinfo

.PHONY: conan-relwithdebinfo
conan-relwithdebinfo: conan-build-relwithdebinfo
	cmake --build --preset conan-gcc-13-23-relwithdebinfo -DINSTALL_GTEST=OFF --target install