# syntax=docker/dockerfile:1

FROM ubuntu:latest AS base

RUN apt-get update && \
    apt-get -y install \
    make \
    cmake 

ENV ASTREA_ROOT=/github/home/astrea
WORKDIR $ASTREA_ROOT

FROM base AS build

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && \
    apt-get -y install \
    gcc \
    gdb \ 
    mono-mcs \
    curl \
    libsqlite3-dev \
    libssl-dev \
    python3 \
    python3-pip \
    python3-venv \
    git \
    && \
    rm -rf /var/lib/apt/lists/*
RUN pip install conan --break-system-packages

COPY .conan2/ /github/home/.conan2
COPY astrea $ASTREA_ROOT/astrea 
COPY cmake $ASTREA_ROOT/cmake 
COPY extern $ASTREA_ROOT/extern 
COPY scripts $ASTREA_ROOT/scripts 
COPY CMakeLists.txt $ASTREA_ROOT/CMakeLists.txt 
COPY conanfile.txt $ASTREA_ROOT/conanfile.txt 
COPY Makefile $ASTREA_ROOT/Makefile 

# Clone mp-units instead of copying local version
RUN mkdir /github/home/open-source && \
    cd /github/home/open-source && \
    git clone https://github.com/mpusz/mp-units.git && \
    cd mp-units && \
    git checkout v2.4.0 && \
    cd $ASTREA_ROOT

RUN make release all

FROM base AS final

COPY --from=build $ASTREA_ROOT/build $ASTREA_ROOT/build
COPY --from=build $ASTREA_ROOT/install $ASTREA_ROOT/install
COPY --from=build $ASTREA_ROOT/Makefile $ASTREA_ROOT/Makefile 
COPY --from=build $ASTREA_ROOT/extern $ASTREA_ROOT/extern 
COPY data $ASTREA_ROOT/data 

