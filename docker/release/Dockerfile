# syntax=docker/dockerfile:1

FROM ubuntu:latest AS base

RUN apt-get update && \
    apt-get -y install \
    make \
    cmake

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

RUN make python_env
RUN make release all install

FROM base AS final

COPY --from=build ./.venv ./.venv
COPY --from=build ./build ./build
COPY --from=build ./install ./install
COPY --from=build ./Makefile ./Makefile
COPY astrea/astro/data ./astrea/astro/data

