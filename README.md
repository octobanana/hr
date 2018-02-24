# hr
A horizontal rule for the terminal.  
Outputs a repeated string of characters the width of the terminal. The color, boldness, string, and number of rows can be configured through arguments.  
It is beneficial for visually dividing other programs output, such as in a shell script.  

## Build
Environment:  
* tested on linux
* c++ 14 compiler
* cmake

Libraries:  
* my [parg](https://github.com/octobanana/parg) library, for parsing cli args, included as `./src/parg.hh`

The following shell commands will build the project:  
```bash
git clone <repo_name>
cd <repo_name>
./build.sh -r
```
To build the debug version, run the build script without the -r flag.  

## Install
The following shell commands will install the project:  
```bash
./install.sh -r
```
