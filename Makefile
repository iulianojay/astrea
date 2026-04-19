SHELL := bash
MAKEFLAGS += --no-builtin-rules --no-print-directory

config_path := $(abspath .)
source_path := astrea
examples_path := examples
arch := x86_64
os := Linux
comp := GNU-13.1.0
tests_path := tests

build_type := Release
build_type_lower := $(shell echo $(build_type) | tr A-Z a-z)
build_path := $(abspath ./build/gcc-13-23/$(build_type))
install_path := $(abspath ./install/gcc-13-23/$(build_type))
build_tests := OFF
build_examples := OFF
build_profilers := OFF
build_checkcase_db := OFF
build_static := OFF
run_6dof_checkcases := OFF
cxx := g++-13
verbose_makefile := OFF
warnings_as_errors := OFF

.DEFAULT_GOAL := install

.PHONY: all
all: examples tests

.PHONY: checkcases
checkcases: checkcase_db 6dof_checkcases tests

.PHONY: profile
profile: profiling install

.PHONY: install
install: build
	cmake --build $(build_path) --target install -j10

.PHONY: build
build:
	cmake -S . -B $(build_path) \
	-DCMAKE_BUILD_TYPE=$(build_type) \
	-DCMAKE_INSTALL_PREFIX:PATH=$(install_path) \
	-DBUILD_TESTS=$(build_tests) \
	-DBUILD_EXAMPLES=$(build_examples) \
	-DBUILD_STATIC=$(build_static) \
	-DBUILD_PROFILERS=$(build_profilers) \
	-DBUILD_CHECKCASE_DATABASE=$(build_checkcase_db) \
	-DRUN_6DOF_CHECKCASES=$(run_6dof_checkcases)

.PHONY: debug
debug:
	$(eval build_type = Debug)
	$(eval build_type_lower := $(shell echo $(build_type) | tr A-Z a-z))
	$(eval build_path := $(abspath ./build/gcc-13-23/$(build_type)))
	$(eval install_path := $(abspath ./install/gcc-13-23/$(build_type)))

.PHONY: release
release:
	$(eval build_type = Release)
	$(eval build_type_lower := $(shell echo $(build_type) | tr A-Z a-z))
	$(eval build_path := $(abspath ./build/gcc-13-23/$(build_type)))
	$(eval install_path := $(abspath ./install/gcc-13-23/$(build_type)))

.PHONY: relwithdebinfo
relwithdebinfo:
	$(eval build_type = RelWithDebInfo)
	$(eval build_type_lower := $(shell echo $(build_type) | tr A-Z a-z))
	$(eval build_path := $(abspath ./build/gcc-13-23/$(build_type)))
	$(eval install_path := $(abspath ./install/gcc-13-23/$(build_type)))

.PHONY: tests
tests:
	$(eval build_tests = ON)

.PHONY: examples
examples:
	$(eval build_examples = ON)

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
	docker build -t astrea:latest -f ./docker/devcontainer/Dockerfile . --build-arg USER=$(username)

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

CLANG_TIDY_CMD = clang-tidy -p=$(build_path) --extra-arg=-Who-unknown-warning-option --extra-arg=-std=c++23
.PHONY: check
check: build
	find $(source_path) -regex '.*\.\(cpp\|hpp\|c\|h\)' | xargs $(CLANG_TIDY_CMD)
	find $(examples_path) -regex '.*\.\(cpp\|hpp\|c\|h\)' | xargs $(CLANG_TIDY_CMD)

.PHONY: coverage-html
coverage-html: #debug run_tests run_examples
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
	. .venv/bin/activate

.PHONY: install_deps
install_deps:
	uv pip install -r pyproject.toml

.PHONY: python_env
python_env: build_env activate_env install_deps

.PHONY: clean-env
clean-env:
	rm -rf .venv