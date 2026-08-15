
SHELL := bash
MAKEFLAGS += --no-builtin-rules --no-print-directory

# Set OS variable to 'Windows', 'Linux', or 'Apple' (cross-platform robust)
config_path := $(abspath .)
source_path := astrea
examples_path := examples
arch := x86_64
cxx := g++
cc := gcc
cxx_std := 26
cxx_name := $(shell echo $(cxx) | sed 's/g++/gcc/; s/clang++/clang/' | sed 's/-[0-9.]*$$//')
cxx_ver := $(shell $(cxx) -dumpversion | cut -d. -f1)
comp := $(cxx_name)-$(cxx_ver)-$(cxx_std)
tests_path := tests

ifneq (,$(wildcard $(config_path)/.venv/bin/activate))
	venv_activate := $(config_path)/.venv/bin/activate
else ifneq (,$(wildcard $(config_path)/.venv/Scripts/activate))
	venv_activate := $(config_path)/.venv/Scripts/activate
else
	venv_activate :=
endif
# Compiler configuration - can be 'gcc' or 'clang' or 'mingw'
compiler := gcc
toolchain_file :=
toolchain_make := -G Ninja
extra_cmake_args :=

# Set toolchain file for mingw cross-compilation
ifeq ($(compiler),mingw)
	venv_activate := $(config_path)/.venv/Scripts/activate
	toolchain_file := -DCMAKE_TOOLCHAIN_FILE=$(abspath cmake/windows_toolchain.cmake)
	toolchain_make := -G "MinGW Makefiles"
else ifeq ($(compiler),msvc)
	venv_activate := $(config_path)/.venv/Scripts/activate
	toolchain_make := -G "Visual Studio 18 2026" -A x64
endif

CMAKE := source $(venv_activate) && cmake
CONAN := source $(venv_activate) && conan
build_type := Release
build_type_lower := $(shell echo $(build_type) | tr A-Z a-z)
build_path := $(abspath ./build/$(compiler)/$(comp)/$(build_type))
install_path := $(abspath ./install/$(compiler)/$(comp)/$(build_type))
build_tests := OFF
build_benchmarks := OFF
build_examples := OFF
build_profilers := OFF
build_checkcase_db := OFF
build_static := OFF
run_6dof_checkcases := OFF
verbose_makefile := OFF
warnings_as_errors := OFF
username := $(shell whoami)
eop_file := $(abspath ./astrea/astro/data/earth_orientation_parameters/eop.long)
rebuild_eop := ON

.DEFAULT_GOAL := install

.PHONY: all
all: examples tests

.PHONY: checkcases
checkcases: checkcase_db 6dof_checkcases tests

.PHONY: profile
profile: profiling install

.PHONY: install
install: build
	$(CMAKE) --build $(build_path) --target install -j10

.PHONY: conan-install
conan-install:
	mkdir -p $(build_path)
	$(CONAN) install . \
	--output-folder=$(build_path) \
	--build=missing \
	-s build_type=$(build_type)
	rm -f $(build_path)/CMakeCache.txt

.PHONY: build
build: conan-install
	cmake -S . -B $(build_path) \
	$(toolchain_make) \
	-DCMAKE_TOOLCHAIN_FILE=$(build_path)/conan_toolchain.cmake \
	$(toolchain_file) \
	-DCMAKE_CXX_COMPILER=$(cxx) \
	-DCMAKE_C_COMPILER=$(shell echo $(cxx) | sed 's/g++/gcc/;s/clang++/clang/') \
	-DCMAKE_BUILD_TYPE=$(build_type) \
	-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
	-DCMAKE_INSTALL_PREFIX:PATH=$(install_path) \
	-DCPM_SOURCE_CACHE=$(config_path)/.cpm-cache \
	-DCMAKE_POLICY_VERSION_MINIMUM=3.5 \
	-DCMAKE_CXX_COMPILER=$(cxx) \
	-DCMAKE_C_COMPILER=$(cc) \
	-DBUILD_TESTS=$(build_tests) \
	-DBUILD_BENCHMARKS=$(build_benchmarks) \
	-DBUILD_EXAMPLES=$(build_examples) \
	-DBUILD_STATIC=$(build_static) \
	-DBUILD_PROFILERS=$(build_profilers) \
	-DBUILD_CHECKCASE_DATABASE=$(build_checkcase_db) \
	-DBUILD_6DOF_CHECKCASES=$(run_6dof_checkcases) \
	-DEOP_FILE=$(eop_file) \
	-DREBUILD_EOP=$(rebuild_eop) \

.PHONY: build-gcc
build-gcc: gcc build

.PHONY: build-mingw
build-mingw: mingw build

.PHONY: debug
debug:
	$(eval build_type = Debug)
	$(eval build_type_lower := $(shell echo $(build_type) | tr A-Z a-z))
	$(eval build_path := $(abspath ./build/$(compiler)/$(comp)/$(build_type)))
	$(eval install_path := $(abspath ./install/$(compiler)/$(comp)/$(build_type)))

.PHONY: release
release:
	$(eval build_type = Release)
	$(eval build_type_lower := $(shell echo $(build_type) | tr A-Z a-z))
	$(eval build_path := $(abspath ./build/$(compiler)/$(comp)/$(build_type)))
	$(eval install_path := $(abspath ./install/$(compiler)/$(comp)/$(build_type)))

.PHONY: relwithdebinfo
relwithdebinfo:
	$(eval build_type = RelWithDebInfo)
	$(eval build_type_lower := $(shell echo $(build_type) | tr A-Z a-z))
	$(eval build_path := $(abspath ./build/$(compiler)/$(comp)/$(build_type)))
	$(eval install_path := $(abspath ./install/$(compiler)/$(comp)/$(build_type)))

# Compiler selection targets
.PHONY: gcc
gcc:
	$(eval cc := gcc)
	$(eval cxx := g++)
	$(eval compiler = gcc)
	$(eval toolchain_file = )
	$(eval toolchain_make = -G Ninja)
	$(eval build_path := $(abspath ./build/$(compiler)/$(comp)/$(build_type)))
	$(eval install_path := $(abspath ./install/$(compiler)/$(comp)/$(build_type)))

.PHONY: clang
clang:
	$(eval cc := clang)
	$(eval cxx := clang++)
	$(eval compiler = clang)
	$(eval toolchain_file = )
	$(eval toolchain_make = -G Ninja)
	$(eval build_path := $(abspath ./build/$(compiler)/$(comp)/$(build_type)))
	$(eval install_path := $(abspath ./install/$(compiler)/$(comp)/$(build_type)))

.PHONY: msvc
msvc:
	$(eval compiler = msvc)
	$(eval toolchain_file = )
	$(eval toolchain_make = -G "Visual Studio 18 2026" -A x64)
	$(eval build_path := $(abspath ./build/$(compiler)/$(comp)/$(build_type)))
	$(eval install_path := $(abspath ./install/$(compiler)/$(comp)/$(build_type)))

.PHONY: mingw
mingw:
	$(eval compiler = mingw)
	$(eval toolchain_file = -DCMAKE_TOOLCHAIN_FILE=$(abspath cmake/windows_toolchain.cmake))
	$(eval toolchain_make = -G "MinGW Makefiles")
	$(eval build_path := $(abspath ./build/$(compiler)/$(comp)/$(build_type)))
	$(eval install_path := $(abspath ./install/$(compiler)/$(comp)/$(build_type)))

.PHONY: tests
tests:
	$(eval build_tests = ON)

.PHONY: examples
examples:
	$(eval build_examples = ON)

.PHONY: benchmarks
benchmarks:
	$(eval build_benchmarks = ON)

.PHONY: profiling
profiling:
	$(eval build_profilers = ON)

.PHONY: checkcase_db
checkcase_db:
	$(eval build_checkcase_db = ON)

.PHONY: 6dof_checkcases
6dof_checkcases:
	$(eval run_6dof_checkcases = ON)

.PHONY: verbose
verbose:
	$(eval verbose_makefile = ON)

.PHONY: static
static:
	$(eval build_static = ON)

.PHONY: run_tests
run_tests:
	cd $(build_path)/astrea/math/tests && ctest --output-on-failure
	cd $(build_path)/astrea/utilities/tests && ctest --output-on-failure
	cd $(build_path)/astrea/astro/tests && ctest --output-on-failure
	cd $(build_path)/astrea/trace/tests && ctest --output-on-failure

.PHONY: rerun_tests
rerun_tests:
	cd $(build_path)/astrea/math/tests && ctest --rerun-failed --output-on-failure
	cd $(build_path)/astrea/utilities/tests && ctest --rerun-failed --output-on-failure
	cd $(build_path)/astrea/astro/tests && ctest --rerun-failed --output-on-failure
	cd $(build_path)/astrea/trace/tests && ctest --rerun-failed --output-on-failure

.PHONY: run_benchmarks
run_benchmarks:
	sh ./scripts/run_benchmarks.sh

.PHONY: run_examples
run_examples:
	sh ./scripts/run_examples.sh

.PHONY: run_checkcases
run_checkcases:
	cd $(install_path)/bin/regression/ && ./orbital.test --gtest_filter=*.Checkcase* --gtest_catch_exceptions=0 2> /dev/null

.PHONY: build_report
build_report: run_checkcases
	cd astrea/astro/pyastro/6dof_report && python3 nasa_6dof_report.py

.PHONY: docker
docker:
	docker build -t astrea:latest -f ./docker/Dockerfile.dev . --build-arg USER=$(username)

# .PHONY: docker-windows
# docker-windows:
# 	docker build -t astrea:latest-windows -f ./docker/windows/Dockerfile.dev . --build-arg USER=$(username)

.PHONY: clean
clean:
	@cmake --build $(build_path) --target clean

.PHONY: clean-ephem
clean-ephem:
	rm -f $(shell find . -type f | grep './build/.*/ephemerides/.*.hpp')
	rm -f $(shell find . -type f | grep './build/.*/ephemerides/.*.cpp')

.PHONY: new
new:
	rm -rf build
	rm -rf install

CLANG_TIDY_CMD = clang-tidy -p=$(build_path) --extra-arg=-Who-unknown-warning-option --extra-arg=-std=c++26
.PHONY: check
check: build
	find $(source_path) -regex '.*\.\(cpp\|hpp\|c\|h\)' | xargs $(CLANG_TIDY_CMD)
	find $(examples_path) -regex '.*\.\(cpp\|hpp\|c\|h\)' | xargs $(CLANG_TIDY_CMD)

.PHONY: coverage-html
coverage-html: debug run_tests run_examples
	cd build && \
	gcovr -r .. --html-nested \
	-o ../.gcovr/coverage.html \
	--merge-mode-functions=separate \
	--filter ".*/astrea/" \
	--exclude ".*.test.cpp|.*/tests/.*|.*/snapshot/.*|.*plotting.*|.*/plots/.*|.*SpatialIndex.*" \
	--exclude-unreachable-branches -s \
	--gcov-ignore-errors=no_working_dir_found \
	--gcov-ignore-parse-errors=suspicious_hits.warn_once_per_file \
	--gcov-executable gcov-15

.PHONY: coverage
coverage: debug run_tests run_examples
	cd build && \
	gcovr -r .. --cobertura-pretty \
	-o ../.gcovr/coverage.xml  \
	--merge-mode-functions=separate \
	--filter ".*/astrea/" \
	--exclude ".*.test.cpp|.*/tests/.*|.*/snapshot/.*|.*plotting.*|.*/plots/.*|.*SpatialIndex.*" \
	--exclude-unreachable-branches -s \
	--gcov-ignore-errors=no_working_dir_found \
	--gcov-ignore-parse-errors=suspicious_hits.warn_once_per_file \
	--gcov-executable gcov-15

.PHONY: build_env
build_env:
	uv venv .venv

.PHONY: activate_env
activate_env:
	@if [ -f .venv/bin/activate ]; then \
		. .venv/bin/activate; \
	elif [ -f .venv/Scripts/activate ]; then \
		. .venv/Scripts/activate; \
	else \
		echo "No virtual environment found!"; \
		exit 1; \
	fi

.PHONY: install_deps
install_deps:
	uv sync --no-dev

.PHONY: python_env
python_env: build_env activate_env install_deps

.PHONY: clean-env
clean-env:
	rm -rf .venv