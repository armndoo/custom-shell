# MandoSHell - C Command Line Interpreter

MandoSHell is a minimalist command-line interpreter developed in C. The project implements a robust REPL (Read-Eval-Print Loop) to handle user input, argument parsing, and process execution logic.



## Architecture

The system is organized into three distinct logical layers to ensure modularity and maintainability:

1. **Main Loop (REPL)**: Manages the primary execution flow, standard input/output, and the dynamic user prompt.
2. **Parser**: Handles string tokenization, transforming the raw input buffer into a null-terminated argument array (`argv`).
3. **Dispatcher**: Analyzes the initial token to route execution either to an internal builtin function or to an external system binary.



## Features

* **Dynamic Prompting**: Real-time working directory display with automatic HOME directory contraction using the tilde (`~`) character.
* **Exit Status Tracking**: Monitoring and storage of the return code from the most recent command (`last_status`), adhering to POSIX standards.
* **Core Builtins**: Native implementation of essential commands including `cd`, `exit`, `echo`, and `type`.
* **Path Resolution**: Integration with system environment variables to locate and launch external binaries.
* **Error Handling**: Systematic reporting of execution failures, including standard exit codes (e.g., 127 for command not found).

## Demonstration

https://github.com/user-attachments/assets/7ef004eb-a6ed-4a38-b5c2-d555623821a4




## Prerequisites

* GCC or Clang compiler
* CMake (version 3.10 or higher)

## Compilation

This project utilizes CMake for build management. To compile the shell, execute the following commands from the project root:

```bash
mkdir build
cd build
cmake ..
make
```
# Usage

Once compiled, the executable can be launched from the build directory:
Bash

```bash
./msh
```

# Technical Notes

    * Signal Handling: Manages EOF (End Of File) for graceful session termination.

    * Memory Management: Implements strict memory cleanup after each parsing cycle to prevent leaks during long-running sessions.

    * Process Control: Uses fork, exec, and waitpid logic to manage external process lifecycles and accurately capture exit statuses via system macros.

---
## Why I did this
I wanted to experience some real system programming, I saw this excercise online and I decided to make it from scratc in C. And also because I dont know what I am doing with my life. lol.
