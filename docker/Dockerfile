# syntax=docker/dockerfile:1

# Comments are provided throughout this file to help you get started.
# If you need more help, visit the Dockerfile reference guide at
# https://docs.docker.com/go/dockerfile-reference/

# Want to help us make this template better? Share your feedback here: https://forms.gle/ybq9Krt8jtBL3iCk7

################################################################################
# Pick a base image to serve as the foundation for the other build stages in
# this file.
#
# For illustrative purposes, the following FROM command
# is using the alpine image (see https://hub.docker.com/_/alpine).
# By specifying the "latest" tag, it will also use whatever happens to be the
# most recent version of that image when you build your Dockerfile.
# If reproducibility is important, consider using a versioned tag
# (e.g., alpine:3.17.2) or SHA (e.g., alpine@sha256:c41ab5c992deb4fe7e5da09f67a8804a46bd0592bfdf0b1847dde0e0889d2bff).
FROM ubuntu:latest AS base

WORKDIR /home/appuser/waveguide

################################################################################
# Create a stage for building/compiling the application.
#
# The following commands will leverage the "base" stage above to generate
# a "hello world" script and make it executable, but for a real application, you
# would issue a RUN command for your application's build process to generate the
# executable. For language-specific examples, take a look at the Dockerfiles in
# the Awesome Compose repository: https://github.com/docker/awesome-compose
FROM base AS build

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && \
    apt-get -y install \
    gcc \
    gdb \ 
    mono-mcs \
    make \
    cmake \
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

COPY projects/waveguide/cmake /home/appuser/waveguide/cmake 
COPY projects/waveguide/data /home/appuser/waveguide/data 
COPY projects/waveguide/extern /home/appuser/waveguide/extern 
COPY projects/waveguide/scripts /home/appuser/waveguide/scripts 
COPY projects/waveguide/waveguide /home/appuser/waveguide/waveguide 
COPY projects/waveguide/CMakeLists.txt /home/appuser/waveguide/CMakeLists.txt 
COPY projects/waveguide/conanfile.txt /home/appuser/waveguide/conanfile.txt 
COPY projects/waveguide/Makefile /home/appuser/waveguide/Makefile 
COPY .conan2/ /home/appuser/.conan2
COPY open-source/ /home/appuser/open-source

RUN groupadd -r usergroup
RUN useradd -rm -d /home/appuser -s /bin/bash -g usergroup -u 10001 -p "$(openssl passwd -1 appuser)" appuser 
RUN chown -R appuser:usergroup /home/appuser
USER appuser

ENV WAVEGUIDE_ROOT=/home/appuser/waveguide
RUN ls -l && make conan-release

################################################################################
# Create a final stage for running your application.
#
# The following commands copy the output from the "build" stage above and tell
# the container runtime to execute it when the image is run. Ideally this stage
# contains the minimal runtime dependencies for the application as to produce
# the smallest image possible. This often means using a different and smaller
# image than the one used for building the application, but for illustrative
# purposes the "base" image is used here.
FROM base AS final

COPY --from=build /home/appuser/waveguide/build /home/appuser/waveguide/build
COPY --from=build /home/appuser/waveguide/install /home/appuser/waveguide/install

# Create a non-privileged user that the app will run under.
# See https://docs.docker.com/go/dockerfile-user-best-practices/
RUN groupadd -r usergroup
RUN useradd -rm -d /home/appuser -s /bin/bash -g usergroup -u 10001 -p "$(openssl passwd -1 appuser)" appuser 
RUN chown -R appuser:usergroup /home/appuser
USER appuser
ENV WAVEGUIDE_ROOT=/home/appuser/waveguide

