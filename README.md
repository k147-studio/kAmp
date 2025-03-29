# kAmp

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/d6a747c4f98841a9b2949d304b46f7df)](https://app.codacy.com/gh/k147-studio/kAmp?utm_source=github.com&utm_medium=referral&utm_content=k147-studio/kAmp&utm_campaign=Badge_Grade)

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
