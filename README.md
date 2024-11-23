# Pipex
## Creating a Project to Simulate the Behavior of Shell Using pipe (|)

This project involves creating a program that simulates the behavior of pipes in Unix-like systems.

## Specifically, the program should:
- Redirect the standard output (stdout) < of the first process to the write end of the pipe.
- Redirect the standard input (stdin) > of the second process to the read end of the pipe.
- Creating 2 child process to execute the commands
- Execute commands using execve().

## Pipex Program Usage
1. Clone repository
2. Move to directory
```bash
cd pipex
```
3.Run make file
```bash
make
```
4. Run th program : example
```bash
./pipex file1 cmd1 cmd2 file2
```
### The program should behave the same as the following shell command:
```bash
< file1 cmd1 | cmd2 > file2
```
