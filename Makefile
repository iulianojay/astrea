DFLAG = Release
C_COMP = gcc
CXX_COMP = g++
VERBOSE = OFF
BUILD_SWIG = OFF
CROSS_COMIPLE = OFF
# JAVA_INSTALL_DIR = /home/jayiuliano/repos/newtool/lib/
JAVA_INSTALL_DIR = /mnt/c/Users/iulia/IdeaProjects/newtool/lib/

.PHONY: all
all: build

.PHONY: debug
debug:
	${eval DFLAG = Debug}

.PHONY: release
release:
	${eval DFLAG = Release}

.PHONY: relwdebug
relwdebug:
	${eval DFLAG = RelWithDebInfo}

.PHONY: verbose
verbose:
	${eval VERBOSE = ON}

.PHONY: swig
swig:
	${eval BUILD_SWIG = ON}

.PHONY: xcomp
swig:
	${eval CROSS_COMIPLE = ON}

.PHONY: build
build: CMakeLists.txt
	mkdir -p build
	CC=${C_COMP} CXX=${CXX_COMP} cmake -S . -B build \
		-DCMAKE_BUILD_TYPE=${DFLAG} \
		-DCMAKE_VERBOSE_MAKEFILE::BOOL=${VERBOSE} \
		-DBUILD_SWIG::BOOL=${BUILD_SWIG} \
		-DCROSS_COMIPLE::BOOL=${CROSS_COMIPLE}
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