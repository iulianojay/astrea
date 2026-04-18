# syntax=docker/dockerfile:1

FROM ubuntu:latest AS base

RUN apt-get update && \
    apt-get -y install \
    make \
    cmake

ENV ASTREA_ROOT=/github/home/astrea
WORKDIR $ASTREA_ROOT

FROM base AS build

# Accept version as build argument with fallback
ARG ASTREA_VERSION=1.1.1

ENV DEBIAN_FRONTEND=noninteractive
# Set version environment variable for CMake fallback
ENV ASTREA_VERSION=${ASTREA_VERSION}
RUN apt-get update && \
    apt-get -y install \
    gcc \
    g++ \
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
    python3-venv \
    git \
    gnuplot \
    && \
    rm -rf /var/lib/apt/lists/*

# Install uv
RUN curl -LsSf https://astral.sh/uv/install.sh | sh
ENV PATH="/root/.local/bin:$PATH"

# Install gcovr using uv
RUN uv tool install gcovr

COPY . $ASTREA_ROOT

RUN make python_env
RUN make release all install

FROM base AS final

COPY --from=build $ASTREA_ROOT/.venv $ASTREA_ROOT/.venv
COPY --from=build $ASTREA_ROOT/build $ASTREA_ROOT/build
COPY --from=build $ASTREA_ROOT/install $ASTREA_ROOT/install
COPY --from=build $ASTREA_ROOT/Makefile $ASTREA_ROOT/Makefile
COPY --from=build $ASTREA_ROOT/astrea/astro/data $ASTREA_ROOT/astrea/astro/data
