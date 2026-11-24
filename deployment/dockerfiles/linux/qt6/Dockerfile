# syntax=docker/dockerfile:1
#
# Linux-only builder for Sourcetrail (Qt 6, C++20).
# Build context must be the repository root, see script/docker/build_linux.sh.
#
#   docker build -f deployment/dockerfiles/linux/qt6/Dockerfile \
#       --target artifact --output type=local,dest=release .

ARG UBUNTU_VERSION=24.04
FROM ubuntu:${UBUNTU_VERSION} AS builder

ARG DEBIAN_FRONTEND=noninteractive
# Optional language support, off by default. The C++ indexer is not verified yet.
ARG BUILD_CXX_INDEXER=OFF
ARG LLVM_VERSION=18
ARG BUILD_TYPE=Release
ARG RUN_TESTS=OFF

RUN apt-get update && apt-get install -y --no-install-recommends \
        build-essential \
        ca-certificates \
        ccache \
        cmake \
        ninja-build \
        pkg-config \
        libboost-date-time-dev \
        libboost-filesystem-dev \
        libboost-program-options-dev \
        libboost-system-dev \
        qt6-base-dev \
        qt6-svg-dev \
        qt6-5compat-dev \
        libgl-dev \
    && if [ "$BUILD_CXX_INDEXER" = "ON" ]; then \
        apt-get install -y --no-install-recommends \
            clang-${LLVM_VERSION} libclang-${LLVM_VERSION}-dev llvm-${LLVM_VERSION}-dev; \
    fi \
    && rm -rf /var/lib/apt/lists/*

COPY . /src
WORKDIR /build

RUN --mount=type=cache,target=/root/.cache/ccache \
    CXX_ARGS=""; \
    if [ "$BUILD_CXX_INDEXER" = "ON" ]; then \
        CXX_ARGS="-DBUILD_CXX_LANGUAGE_PACKAGE=ON -DClang_DIR=/usr/lib/llvm-${LLVM_VERSION}/lib/cmake/clang"; \
    fi; \
    cmake -S /src -B /build -G Ninja \
        -DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
        -DBUILD_JAVA_LANGUAGE_PACKAGE=OFF \
        -DBUILD_PYTHON_LANGUAGE_PACKAGE=OFF \
        ${CXX_ARGS} \
    && cmake --build /build

# Offscreen Qt platform so the GUI tests can run without a display.
RUN if [ "$RUN_TESTS" = "ON" ]; then \
        cd /build/test && QT_QPA_PLATFORM=offscreen ./Sourcetrail_test; \
    fi

# Collect the runtime layout: binaries next to the data and user directories.
RUN mkdir -p /out/Sourcetrail \
    && cp /build/app/Sourcetrail /build/app/sourcetrail_indexer /out/Sourcetrail/ \
    && cp -rL /src/bin/app/data /src/bin/app/user /out/Sourcetrail/

# Export only the result: `--target artifact --output type=local,dest=<dir>`
FROM scratch AS artifact
COPY --from=builder /out /
