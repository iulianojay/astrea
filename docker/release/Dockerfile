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
    bash-completion \
    mono-mcs \
    curl \
    clang-format \
    libsqlite3-dev \
    libssl-dev \
    libgl1-mesa-dev \
    xorg-dev \
    python3 \
    python3-pip \
    python3-venv \
    git \
    gnuplot \
    && \
    rm -rf /var/lib/apt/lists/*

# For some reason, this is the only way to install gcovr
RUN pip install gcovr --break-system-packages

COPY astrea $ASTREA_ROOT/astrea
COPY cmake $ASTREA_ROOT/cmake
COPY scripts $ASTREA_ROOT/scripts
COPY CMakeLists.txt $ASTREA_ROOT/CMakeLists.txt
COPY Makefile $ASTREA_ROOT/Makefile

RUN make python_env
RUN make release all

FROM base AS final

COPY --from=build $ASTREA_ROOT/.venv $ASTREA_ROOT/.venv
COPY --from=build $ASTREA_ROOT/build $ASTREA_ROOT/build
COPY --from=build $ASTREA_ROOT/install $ASTREA_ROOT/install
COPY --from=build $ASTREA_ROOT/Makefile $ASTREA_ROOT/Makefile
COPY astrea/astro/data $ASTREA_ROOT/astrea/astro/data

