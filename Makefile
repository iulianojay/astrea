DFLAG = Release
C_COMP = gcc
CXX_COMP = g++
VERBOSE = OFF

.PHONY: all
all: build

.PHONY: debug
debug:
	${eval DFLAG = Debug}

.PHONY: release
release: 
	${eval DFLAG = Release}

.PHONY: verbose
verbose: 
	${eval VERBOSE = ON}

.PHONY: build
build: CMakeLists.txt
	mkdir -p build
	cmake -S . -B build -DCMAKE_BUILD_TYPE=${DFLAG} -DCMAKE_C_COMPILER=$(C_COMP) -DCMAKE_CXX_COMPILER=${CXX_COMP} -DCMAKE_VERBOSE_MAKEFILE::BOOL=${VERBOSE}
	cd build && make --no-print-directory -j 10

.PHONY: clean
clean:
	[-d "build" ] && cd build && make clean --no-print-directory && cd .. && rm -rf build || echo "build directory does not exist. Nothing to clean."

.PHONY: cleanAll
cleanAll:
	rm -rf ./build/*
	rm -f ./lib/libastro*
	rm -rf ./bin/*