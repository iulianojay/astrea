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
build_tests := OFF
build_examples := OFF
build_static := OFF
cxx := g++-13
verbose_makefile := OFF
warnings_as_errors := OFF

.DEFAULT_GOAL := all

.PHONY: all
all: examples tests install

# Conan commands - for now
.PHONY: install
install: build
	cmake --build --preset conan-gcc-13-23-$(build_type_lower) -DINSTALL_GTEST=OFF --target install -j20

.PHONY: build
build: setup
	cmake -S . --preset conan-gcc-13-23-$(build_type_lower) -DBUILD_TESTS=$(build_tests) -DBUILD_EXAMPLES=$(build_examples) -DBUILD_STATIC=$(build_static)

.PHONY: setup
setup:
	conan install . -pr ./.conan2/profiles/gcc13-$(build_type_lower) -b=missing 

.PHONY: debug
debug: 
	$(eval build_type = Debug)
	$(eval build_type_lower := $(shell echo $(build_type) | tr A-Z a-z))
	$(eval build_path := $(abspath ./build/gcc-13-23/$(build_type)))
	
.PHONY: release
release: 
	$(eval build_type = Release)
	$(eval build_type_lower := $(shell echo $(build_type) | tr A-Z a-z))
	$(eval build_path := $(abspath ./build/gcc-13-23/$(build_type)))
	
.PHONY: relwithdebinfo
relwithdebinfo: 
	$(eval build_type = RelWithDebInfo)
	$(eval build_type_lower := $(shell echo $(build_type) | tr A-Z a-z))
	$(eval build_path := $(abspath $(ASTREA_ROOT)/build/gcc-13-23/$(build_type)))
	
.PHONY: tests
tests:
	$(eval build_tests = ON)

.PHONY: examples
examples:
	$(eval build_examples = ON)

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
	sh $(ASTREA_ROOT)/scripts/run_examples.sh

.PHONY: docker
docker:
	docker build -t astrea:latest -f ./docker/devcontainer/Dockerfile .

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
coverage-html: debug run_tests run_examples
	cd build && gcovr -r .. --html-nested -o $(ASTREA_ROOT)/.gcovr/coverage.html --merge-mode-functions=separate --filter ".*/astrea/" --exclude-unreachable-branches && cd ..

.PHONY: coverage
coverage: debug run_tests run_examples
	cd build && gcovr -r .. --cobertura-pretty -o $(ASTREA_ROOT)/.gcovr/coverage.xml  --merge-mode-functions=separate --filter ".*/astrea/" --exclude-unreachable-branches -s && cd ..

.PHONY: build_env
build_env: 
	rm -rf .venv
	python3 -m venv .venv

.PHONY: activate_env
activate_env:
	source .venv/bin/activate

.PHONY: install_deps
install_deps:
	.venv/bin/pip install -r requirements.txt

.PHONY: python_env
python_env: build_env activate_env install_deps