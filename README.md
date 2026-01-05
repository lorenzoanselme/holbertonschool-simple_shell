# holbertonschool-simple_shell

![C Language](https://img.shields.io/badge/Language-C-blue.svg)
![Status](https://img.shields.io/badge/Project-Completed-success.svg)
![Holberton](https://img.shields.io/badge/Holberton-School-red.svg)

## Description

**simple_shell** is a simplified implementation of a UNIX command line interpreter written in C, developed as part of the **Holberton School** curriculum.

The goal of this project is to understand how a shell works internally, including:

* reading user input
* parsing command lines
* process creation and execution
* environment handling
* implementation of built-in commands

The shell works in both **interactive** and **non-interactive** modes.

---

## Flowchart

A flowchart describing the global logic of the shell is available in the repository.

📄 [View the flowchart (PDF)](flowchart_simpleShell.pdf)

---

## Objectives

* Understand the internal behavior of a UNIX shell
* Work with system calls such as `fork`, `execve`, and `wait`
* Manage environment variables
* Implement basic built-in commands
* Write clean, well-structured, and memory-safe C code

---

## Requirements

### Compilation

* OS: **Ubuntu 20.04 LTS**
* Compiler: **GCC**
* Mandatory flags:

  ```bash
  -Wall -Werror -Wextra -pedantic -std=gnu89
  ```

### Coding Style

* All code follows the **Betty Coding Style**
* All functions are properly documented
* No more than **5 functions per file**
* All header files are include-guarded

### Constraints

* Only allowed system calls and functions may be used
* No use of `system()`
* No advanced features (pipes, redirections, etc.)
* No memory leaks

---

## Features Implemented

### Simple shell 0.1

* Display a prompt `$ ` in interactive mode
* Read and execute user commands
* Handle `Ctrl + D` (EOF)

### Simple shell 0.2

* Handle the `PATH` environment variable
* Search for executables in PATH directories
* Do **not** call `fork()` if the command does not exist
* Print formatted error messages:

  ```text
  ./hsh: 1: command: not found
  ```

### Simple shell 0.3

* Implement the `exit` built-in command
* Exit the shell without arguments
* Return the last command exit status

### Simple shell 0.4

* Implement the `env` built-in command
* Print the current environment
* Execute without forking

---

## Built-ins Supported

| Command | Description           |
| ------- | --------------------- |
| `exit`  | Exit the shell        |
| `env`   | Print the environment |

---

## Example Usage

### Interactive mode

```bash
$ ./hsh
$ ls -l
$ env
$ exit
```

### Non-interactive mode

```bash
echo "ls -la" | ./hsh
```

---

## Compilation

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

---

## Betty Style Check

To verify that the code follows the **Betty coding style**, run:

```bash
betty *.c *.h
```

---

## Memory Check

```bash
valgrind --leak-check=full ./hsh
```

No memory leaks detected.

---

## Project Structure

```
.
├── main.c
├── prompt.c
├── parser.c
├── path.c
├── execute.c
├── builtins.c
├── env_builtin.c
├── errors.c
├── utils.c
├── globals.c
├── shell.h
├── README.md
```

---

## Limitations

* No pipes (`|`)
* No redirections (`>`, `<`)
* No quote handling (`'`, `"`)
* No shell variables
* No auto-completion

---

## Authors

* **Lorenzo Anselme**

  * GitHub: [https://github.com/lorenzoanselme](https://github.com/lorenzoanselme)
* **Ethane Zimmermann**

  * GitHub: [https://github.com/ZimEthane](https://github.com/ZimEthane)

Project developed as part of the **Holberton School** curriculum.

---

## License

This project is free to use for educational purposes.
