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
    python3-pip \
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

# Set env
ENV ASTREA_ROOT=$USER_HOME/astrea

# For some reason, this is the only way to install conan and gcovr
RUN pip install gcovr conan --break-system-packages

# Clone mp-units instead of copying local version
RUN mkdir $USER_HOME/open-source && \
    cd $USER_HOME/open-source && \
    git clone https://github.com/mpusz/mp-units.git && \
    cd mp-units && \
    git checkout v2.4.0
