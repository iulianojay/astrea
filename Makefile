# Setup
DFLAG = Release
C_COMP = gcc
CXX_COMP = g++
VERBOSE = OFF
BUILD_SWIG = OFF

OS = linux
BUILD_DIR = build/${OS}
TOOLCHAIN_FILE =

# JAVA_INSTALL_DIR = /home/jayiuliano/repos/newtool/lib/
JAVA_INSTALL_DIR = C:/Users/iulia/IdeaProjects/newtool/lib/

# Umbrella recipies
.PHONY: default
default: linux

# Compile instructions
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

# OS instructions
.PHONY: windows_setup
windows_setup:
	${eval OS = windows}
	${eval TOOLCHAIN_FILE = config/windows_toolchain.cmake}

.PHONY: windows
windows: windows_setup CMakeLists.txt
	mkdir -p build
	CC=${C_COMP} CXX=${CXX_COMP} cmake -G Ninja -S . -B ${BUILD_DIR} \
		-DCMAKE_BUILD_TYPE=${DFLAG} \
		-DCMAKE_VERBOSE_MAKEFILE::BOOL=${VERBOSE} \
		-DOS=${OS} \
		-DBUILD_SWIG::BOOL=${BUILD_SWIG}
	cd ${BUILD_DIR} && cmake --build .

.PHONY: linux_setup
linux_setup:
	${eval OS = linux}
	${eval TOOLCHAIN_FILE = }

.PHONY: linux
linux: linux_setup CMakeLists.txt
	mkdir -p build
	CC=${C_COMP} CXX=${CXX_COMP} cmake -S . -B ${BUILD_DIR} \
		-DCMAKE_BUILD_TYPE=${DFLAG} \
		-DCMAKE_VERBOSE_MAKEFILE::BOOL=${VERBOSE} \
		-DOS=${OS} \
		-DBUILD_SWIG::BOOL=${BUILD_SWIG}
	cd ${BUILD_DIR} && rm -f build_output.txt && make --no-print-directory -j 1

# Build
.PHONY: build
build: CMakeLists.txt
	mkdir -p build
	CC=${C_COMP} CXX=${CXX_COMP} cmake -S . -B ${BUILD_DIR} \
		-DCMAKE_BUILD_TYPE=${DFLAG} \
		-DCMAKE_VERBOSE_MAKEFILE::BOOL=${VERBOSE} \
		-DOS=${OS} \
		-DBUILD_SWIG::BOOL=${BUILD_SWIG}
	cd ${BUILD_DIR} && rm -f build_output.txt && make --no-print-directory -j 1

# Install
.PHONY: install-java
install-java:
	cp ./build/java/jvastro.jar ${JAVA_INSTALL_DIR} -rf
	cp ./build/java/libjvastro.so ${JAVA_INSTALL_DIR} -rf
	cp ./include ${JAVA_INSTALL_DIR} -rf

# Clean
.PHONY: clean
clean:
	rm -rf ./bin/*
	rm -rf ./lib/*

.PHONY: new
new: clean
	rm -rf ./build/*