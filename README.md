# Hr
A horizontal rule for the terminal.

![hr](https://raw.githubusercontent.com/octobanana/hr/master/assets/hr.png)

## Contents
* [About](#about)
  * [Features](#features)
* [Pre-Build](#pre-build)
  * [Dependencies](#dependencies)
  * [Included Libraries](#included-libraries)
  * [Environment](#environment)
* [Build](#build)
* [Install](#install)
* [License](#license)

## About
__Hr__ prints a repeated string of characters the width of the terminal.
It is useful to visually divide output, such as in a shell script, or appending a dividing line with a fixed width to a file.
The output can be configured through the use of command line options and flags.

### Features
* display a horizontal line the exact width of the terminal
* display a specific number of columns and rows
* set the horizontal lines text and fill strings
* toggle bold and underline styles
* align text to the left, right, or center
* set the foreground and background colours using 4-bit, 8-bit, and 24-bit colours

## Pre-Build
This section describes what environments this program may run on,
any prior requirements or dependencies needed,
and any third party libraries used.

> #### Important
> Any shell commands using relative paths are expected to be executed in the
> root directory of this repository.

### Dependencies
* __C++17__ compiler/library
* __CMake__ >= 3.8

### Included Libraries
* [__parg__](https://github.com/octobanana/parg):
  for parsing CLI args, included as `./src/ob/parg.hh`

### Environment
* __Linux__ (supported)
* __BSD__ (supported)
* __macOS__ (supported)

## Build
The following shell command will build the project in release mode:
```sh
./build.sh
```
To build in debug mode, run the script with the `--debug` flag.

## Install
The following shell command will install the project in release mode:
```sh
./install.sh
```
To install in debug mode, run the script with the `--debug` flag.

## License
This project is licensed under the MIT License.

Copyright (c) 2018-2019 [Brett Robinson](https://octobanana.com/)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
