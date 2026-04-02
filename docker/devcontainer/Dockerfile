# syntax=docker/dockerfile:1

FROM ubuntu:latest AS base

RUN apt-get update && \
    apt-get -y install \
    make \
    cmake

FROM base AS final

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
    python3-venv \
    git \
    gnuplot \
    && \
    rm -rf /var/lib/apt/lists/*

# Create a non-root user
ARG USER=user
RUN useradd -ms /bin/bash $USER

# Change ownership of home directory to the non-root user
ENV USER_HOME=/home/$USER
RUN chown -R $USER:$USER $USER_HOME

# Switch to user
USER $USER
WORKDIR $USER_HOME

# Install uv
RUN curl -LsSf https://astral.sh/uv/install.sh | sh
ENV PATH="$USER_HOME/.cargo/bin:$PATH"

# Install gcovr using uv 
RUN source $HOME/.local/bin/env
RUN uv tool install gcovr
