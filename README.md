# Sourcetrail

Sourcetrail is a free and open-source source explorer that helps you get productive on unfamiliar source code.

This is an **independent fork** of the original [Sourcetrail](https://github.com/CoatiSoftware/Sourcetrail), which its authors archived at the end of 2021. It is not affiliated with, endorsed by, or maintained by the original authors, and changes are not intended to be contributed upstream.

!["Sourcetrail User Interface"](docs/readme/user_interface.png "Sourcetrail User Interface")

## What is different in this fork

* Ported from Qt 5 to **Qt 6** (6.2 or newer) and from C++17 to **C++20**.
* **Linux** is the primary target. macOS should work but is untested.
* Windows and Java support are being removed. Some of their code and scripts are still in the tree but are no longer maintained.
* The upstream CI (Travis, AppVeyor), Patreon funding and in-app links to the original project are being phased out.

## Status

| Area | State |
|---|---|
| Linux, GCC 13, Qt 6.4, Boost 1.83 | Builds, 318 of 320 unit tests pass |
| macOS | Untested, bundle script still references Qt 5 |
| C/C++ indexing | Builds only with Clang/LLVM, not verified on the Qt 6 port |
| Python indexing | Needs the prebuilt upstream indexer, see below |
| Java indexing | Being removed |

Known test failures: two symlink tests in `FileSystemTestSuite.cpp`.

## Building

### Build in Docker (Linux)

The easiest way. It needs only Docker with BuildKit:

```
$ script/docker/build_linux.sh
```

The result is written to `release/Sourcetrail/`. See [Docker build options](#docker-build-options).

### Build natively

Required tools and libraries (package names are for Ubuntu 24.04):

| Requirement | Version | Ubuntu packages |
|---|---|---|
| C++ compiler | C++20 capable, GCC 13 tested | `build-essential` |
| CMake | 3.8 or newer | `cmake` |
| Boost | 1.67 or newer, 1.83 tested | `libboost-filesystem-dev libboost-program-options-dev libboost-system-dev libboost-date-time-dev` |
| Qt | 6.2 or newer, 6.4 tested | `qt6-base-dev qt6-svg-dev qt6-5compat-dev libgl-dev` |
| Git | any | `git` (the version number is generated from tags and commits) |
| Ninja, ccache | optional | `ninja-build ccache` |

```
$ git clone <repository-url> Sourcetrail
$ cd Sourcetrail
$ cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
$ cmake --build build
```

In-source builds are not allowed, always use a separate build directory.

### Running

Run `build/app/Sourcetrail` directly from the build directory. At runtime it needs the resources in `bin/app/data` and `bin/app/user`, and CMake creates symlinks to them inside the build directory.

On a machine without a display you can use Qt's offscreen platform, for example `QT_QPA_PLATFORM=offscreen`.

### Tests

The tests use [Catch2](https://github.com/catchorg/Catch2), which is bundled. Run them from the test directory of the build:

```
$ cd build/test
$ QT_QPA_PLATFORM=offscreen ./Sourcetrail_test
```

## Language support

The base application opens and browses existing Sourcetrail databases. Indexing source code needs a language package, which is off by default.

### C and C++

Needs Clang/LLVM development files, for example `clang-18 libclang-18-dev llvm-18-dev` on Ubuntu 24.04. The original project used LLVM 11, so expect to fix build errors with newer versions.

```
$ cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_CXX_LANGUAGE_PACKAGE=ON \
    -DClang_DIR=/usr/lib/llvm-18/lib/cmake/clang
```

### Python

Python indexing uses the prebuilt `SourcetrailPythonIndexer` published by the original authors, which `script/download_python_indexer.sh` fetches during the build. It is a separate, unmaintained binary that is not built from this repository.

```
$ cmake -S . -B build -DBUILD_PYTHON_LANGUAGE_PACKAGE=ON
```

## Docker build options

`script/docker/build_linux.sh [output_dir] [docker build args]` uses `deployment/dockerfiles/linux/qt6/Dockerfile`.

| Build arg | Default | Meaning |
|---|---|---|
| `BUILD_TYPE` | `Release` | CMake build type |
| `BUILD_CXX_INDEXER` | `OFF` | Install LLVM and build the C/C++ indexer |
| `LLVM_VERSION` | `18` | LLVM version used when the C/C++ indexer is on |
| `RUN_TESTS` | `OFF` | Run the unit tests during the build |
| `UBUNTU_VERSION` | `24.04` | Base image |

Example: `script/docker/build_linux.sh out --build-arg BUILD_CXX_INDEXER=ON`

## Packaging

* **Linux:** `./setup/Linux/createPackages.sh` creates a `.tar.gz` and an `.AppImage`, and depends on [linuxdeployqt](https://github.com/probonopd/linuxdeployqt). It has not been updated for Qt 6.
* **macOS:** `bundle_install.sh` in the build directory creates a `Sourcetrail.app` bundle and a `.dmg`. Not updated for Qt 6.

## Documentation

* [User documentation](DOCUMENTATION.md)
* [Changelog](CHANGELOG.md)

## Contributing

Issues and pull requests are welcome in this repository. See [CONTRIBUTING.md](CONTRIBUTING.md).

## License and credits

Sourcetrail is licensed under the [GNU General Public License Version 3](LICENSE.txt). The original authors are listed in [AUTHORS.txt](AUTHORS.txt).

## Trademark

The "Sourcetrail" name is a trademark owned by Coati Software and is not included within the assets licensed under the GNU GPLv3.
