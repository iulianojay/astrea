# syntax=docker/dockerfile:1

FROM ubuntu:latest AS base

RUN apt-get update && \
    apt-get -y install \
    make \
    cmake 

ENV ASTREA_ROOT=/github/home/astrea
WORKDIR /github/home

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

# Clone mp-units instead of copying local version
RUN mkdir /github/home/open-source && \
    cd /github/home/open-source && \
    git clone https://github.com/mpusz/mp-units.git && \
    cd mp-units && \
    git checkout v2.4.0
