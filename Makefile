DFLAG = Release
C_COMP = gcc
CXX_COMP = g++

.PHONY: all
all: build

.PHONY: debug
debug:
	${eval DFLAG = Debug}

.PHONY: release
release: 
	${eval DFLAG = Release}

.PHONY: build
build: CMakeLists.txt
	mkdir -p build
	CXX=$(CXX_COMP) cmake -S . -B build -DCMAKE_C_COMPILER=$(C_COMP) -DCMAKE_CXX_COMPILER=${CXX_COMP}
	cd build && make --no-print-directory -j 10

.PHONY: clean
clean:
	[-d "build" ] && cd build && make clean --no-print-directory && cd .. && rm -rf build || echo "build directory does not exist. Nothing to clean."

.PHONY: cleanAll
cleanAll:
	rm -rf build
	rm -f ./lib/libastro*