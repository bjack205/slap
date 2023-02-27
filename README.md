[![CMake](https://github.com/bjack205/slap/actions/workflows/CI.yml/badge.svg?branch=main)](https://github.com/bjack205/slap/actions/workflows/CI.yml)
[![Documentation](https://github.com/bjack205/slap/actions/workflows/Documentation.yml/badge.svg?branch=main)](https://github.com/bjack205/slap/actions/workflows/Documentation.yml)
[![codecov](https://codecov.io/gh/bjack205/slap/branch/main/graph/badge.svg?token=vEkwQfXy4q)](https://codecov.io/gh/bjack205/slap)
[![](https://img.shields.io/badge/docs-dev-blue.svg)](https://bjack205.github.io/slap/)

# slap
Simple Linear Algebra Protocols

The goal of this library is to provide a simple, lightweight, and easy-to-read linear algebra package in C. It prioritizes simplicity and readibility.

Some of the key features and design decisions are:
* All memory is owned by the user
* A matrix is just a pointer with some meta-data, and is typically passed by value
* Code is separated into header files that can be included or not, allowing an opt-in approach that decreases compilation time and code size

## Documentation
For details on installing, getting started, and using the library, please see the [Documentation](https://bjack205.github.io/slap/).

## Development Status
This project is still a WIP and under development, but should be usable in it's current form. I'm planning on releasing `v0.2` soon.
