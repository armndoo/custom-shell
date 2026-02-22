# MandoSHell - Simple Shell in C

A minimalist Command Line Interpreter (CLI) built in C. This project implements a basic REPL (Read-Eval-Print Loop) to handle user commands, parsing, and execution logic.

## Architecture
The shell is organized into three distinct logical layers to ensure modularity:

1. **REPL Loop (Main)**: Manages standard input and output, handles the user prompt, and maintains the execution cycle.
2. **Parser**: Responsible for string tokenization. It converts the raw input buffer into a null-terminated array of arguments (`argv`).

3. **Dispatcher**: Analyzes the first argument of the parsed input to route the execution to the appropriate builtin command or system binary.

## Features
* **Command Parsing**: Dynamic handling of command-line arguments.
* **Builtin Command Set**: Native implementation of essential commands such as `exit`, `echo`, and `type`.
* **Path Resolution**: Integration with system paths to identify and locate system executables through utility functions.

## Getting Started

### Prerequisites
* GCC or Clang compiler
* CMake (version 3.10 or higher)

### Compilation
This project uses CMake to manage the build process. To compile the shell, execute the following commands from the project root:

```bash
mkdir build
cd build
cmake ..
make
```

### Usage

Once compiled, the executable can be started from the build directory:
Bash

./msh

## Technical Notes

The shell handles the EOF (End Of File) signal to allow for clean exits and manages memory through a dedicated parsing stage before each execution cycle. The project is structured to separate builtin logic from the core shell engine.

## Why I did this
I wanted to experience some real system programming, I saw this excercise online and I decided to make it from scratc in C. And also because I dont know what I am doing with my life. lol.
