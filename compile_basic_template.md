# Instruction to compile the basic template

This template is intended to compile basics C++ programs in Windows or Linux. We use CMake, which is multiplatform. Below we put some steps to compile this template. 

## Compile Project
Run this commands to compile the project with CMake

```
$ cd <project_dir>
$ mkdir build
$ cd build
$ cmake -G "MinGW Makefiles" ..
$ make
```

> Note: In Windows Platform we must put the option `-G "MinGW Makefiles"`. Don't forget the "`..`"

## Execute the program
After compile successfully, we can run the program. In Windows platform the `make` command generates an `*.exe` file, we run this file with the next command.

```
$ ./<project_name>.exe
```

In linux, is the same instruction, but without the `.exe`.