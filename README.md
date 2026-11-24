# Sourcetrail

Sourcetrail is a free and open-source source explorer that helps you get productive on unfamiliar C and C++ source code.

This is an **independent fork** of the original [Sourcetrail](https://github.com/CoatiSoftware/Sourcetrail), which its authors archived at the end of 2021. It is not affiliated with, endorsed by, or maintained by the original authors, and changes are not intended to be contributed upstream.

!["Sourcetrail User Interface"](docs/readme/user_interface.png "Sourcetrail User Interface")

## What is different in this fork

* Ported from Qt 5 to **Qt 6** (6.2 or newer), from C++17 to **C++20**, and from LLVM 11 to **LLVM 18**.
* **C and C++ only.** Java and Python indexing have been removed.
* **Linux** is the primary target. macOS should work but is untested.
* Windows support, the Visual Studio source group and the Windows installer have been removed.
* The upstream CI, Patreon funding and sponsors have been removed.

## Status

| Area | State |
|---|---|
| Linux, GCC 13, Qt 6.4, Boost 1.83, LLVM 18 | Builds. 604 of 606 unit tests pass, including the C/C++ parser tests |
| C/C++ indexing | Works, a bundled sample project indexes with 0 errors |
| macOS | Untested, the bundle script still references Qt 5 |
| Docker builder | Written but never run |

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
| Clang/LLVM | 18 tested | `clang-18 libclang-18-dev llvm-18-dev` |
| Git | any | `git` (the version number is generated from tags and commits) |
| Ninja, ccache | optional | `ninja-build ccache` |

```
$ git clone <repository-url> Sourcetrail
$ cd Sourcetrail
$ cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release \
    -DClang_DIR=/usr/lib/llvm-18/lib/cmake/clang
$ cmake --build build
```

In-source builds are not allowed, always use a separate build directory.

The application links to the project repository (Help menu, About box, start window) only if you configure its URL, for example `-DPROJECT_URL=https://github.com/<owner>/<repo>`. Without it these links are hidden.

### Running

Run `build/app/Sourcetrail` directly from the build directory. At runtime it needs the resources in `bin/app/data` and `bin/app/user`, and CMake creates symlinks to them inside the build directory.

On a machine without a display you can use Qt's offscreen platform, for example `QT_QPA_PLATFORM=offscreen`.

### Tests

The tests use [Catch2](https://github.com/catchorg/Catch2), which is bundled. Run them from the test directory of the build:

```
$ cd build/test
$ QT_QPA_PLATFORM=offscreen ./Sourcetrail_test
```

## Indexing a project

Sourcetrail indexes C and C++ source code with Clang. The easiest way to set up a project is a compilation database (`compile_commands.json`), which CMake exports with `-DCMAKE_EXPORT_COMPILE_COMMANDS=ON`. See [DOCUMENTATION.md](DOCUMENTATION.md) for the other project types.

To try it, index the bundled sample project from the command line:

```
$ build/app/Sourcetrail index --full bin/app/user/projects/tictactoe_cpp/tictactoe_cpp.srctrlprj
```

Indexing can be turned off at configure time with `-DBUILD_CXX_LANGUAGE_PACKAGE=OFF`. The application then only opens existing databases.

## Docker build options

`script/docker/build_linux.sh [output_dir] [docker build args]` uses `deployment/dockerfiles/linux/qt6/Dockerfile`.

| Build arg | Default | Meaning |
|---|---|---|
| `BUILD_TYPE` | `Release` | CMake build type |
| `LLVM_VERSION` | `18` | Clang/LLVM version to build against |
| `RUN_TESTS` | `OFF` | Run the unit tests during the build, currently fails on the two known symlink tests |
| `UBUNTU_VERSION` | `24.04` | Base image |

Example: `script/docker/build_linux.sh out --build-arg LLVM_VERSION=18`

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
