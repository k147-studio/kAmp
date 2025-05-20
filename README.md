# kAmp

[![Codacy Badge](https://app.codacy.com/project/badge/Grade/a990f176aa0246e4ad5cffbea1b5e019)](https://app.codacy.com/gh/k147-studio/kAmp/dashboard?utm_source=gh&utm_medium=referral&utm_content=&utm_campaign=Badge_grade)

## How to build

### Prerequisites

- `CMake` version 3.21 or higher
- `C++` compiler with at least support for C++17 (C++20 is recommended)

### Generators

Depending on your platform, you can use different generators. Here are some examples:
- `Xcode` on macOS
- `Unix Makefiles` on Linux
- `Visual Studio 17 2022` on Windows

### Steps

Here is an example of how to build the project using `Xcode` on macOS:

``bash
mkdir build
cd build
cmake .. -G "Xcode"
cmake --build .
``
