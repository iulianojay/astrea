# syntax=docker/dockerfile:1

FROM ubuntu:latest AS base

RUN apt-get update && \
    apt-get -y install \
    make \
    cmake 

ENV ASTREA_ROOT=/home/appuser/astrea
WORKDIR $ASTREA_ROOT

FROM base AS final

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

COPY .conan2/ /home/appuser/.conan2

# Clone mp-units instead of copying local version
RUN mkdir /home/appuser/open-source && \
    cd /home/appuser/open-source && \
    git clone https://github.com/mpusz/mp-units.git && \
    cd mp-units && \
    git checkout v2.4.0 && \
    cd $ASTREA_ROOT

# Create a non-privileged user that the app will run under.
# See https://docs.docker.com/go/dockerfile-user-best-practices/
RUN groupadd -r usergroup
RUN useradd -rm -d /home/appuser -s /bin/bash -g usergroup -u 10001 -p "$(openssl passwd -1 appuser)" appuser 
RUN chown -R appuser:usergroup /home/appuser
USER appuser
