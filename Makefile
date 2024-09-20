DFLAG = Release
C_COMP = gcc
CXX_COMP = g++
VERBOSE = OFF
JAVA_INSTALL_DIR = /mnt/c/Users/iulia/IdeaProjects/newtool/lib/

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
	CC=${C_COMP} CXX=${CXX_COMP} cmake -S . -B build \
		-DCMAKE_BUILD_TYPE=${DFLAG} \
		-DCMAKE_VERBOSE_MAKEFILE::BOOL=${VERBOSE} \
		-DPython3_INCLUDE_DIR=/usr/include/python3.12 \
		-DPython3_LIBRARY=/usr/bin/python3.12
	cd build && make --no-print-directory -j 10

.PHONY: install-java
install-java:
	cp ./build/java/jvastro.jar ${JAVA_INSTALL_DIR} -rf
	cp ./build/java/libjvastro.so ${JAVA_INSTALL_DIR} -rf
	cp ./include ${JAVA_INSTALL_DIR} -rf

.PHONY: clean
clean:
	rm -rf ./bin/*
	rm -f ./lib/*

.PHONY: clean
new:
	rm -rf ./build/*