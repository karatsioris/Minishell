*This project has been created as part of the 42 curriculum by **flhensel**, **kkaratsi***

# Minishell

## Description

Minishell is a simple shell — a small reimplementation of the basics of Bash.
The goal of the project is to gain a deep understanding of processes, file
descriptors, and how a shell parses and executes commands.

The program displays a prompt, reads a command line, parses it (handling quotes,
environment-variable expansion, redirections and pipes), then searches for and
executes the right program — either as a builtin, or as an external binary found
through the `PATH` variable or a relative/absolute path.

## Features

- Interactive prompt with command **history** (via `readline`).
- Execution of external commands through `PATH`, or a relative/absolute path.
- **Builtins:**
  - `echo` (with the `-n` option)
  - `cd` (relative or absolute path)
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`
- **Quoting:** single quotes (no interpretation) and double quotes (everything
  literal except `$`).
- **Environment variables:** `$VAR` expansion, and `$?` for the exit status of
  the last foreground command.
- **Redirections:** `<`, `>`, `>>`, and `<<` (heredoc).
- **Pipes:** `|`, chaining the output of one command into the next.
- **Signals:** `ctrl-C`, `ctrl-D` and `ctrl-\` behave like in Bash.
- Maintains `PWD`, `OLDPWD` and `SHLVL` like Bash.

## Instructions

### Requirements

- A C compiler (`cc`) and `make`.
- The **readline** library and its headers (e.g. `libreadline-dev` on
  Debian/Ubuntu).

### Compilation

```sh
make        # build the minishell executable
make clean  # remove object files
make fclean # remove object files and the executable
make re     # rebuild from scratch
```

### Running

```sh
./minishell
```

## Usage examples

```sh
minishell$ echo hello world
hello world
minishell$ ls -l | grep .c | wc -l
42
minishell$ export NAME=42
minishell$ echo "my school is $NAME"
minishell$ cat < infile > outfile
```

## Technical choices

- **Pipeline:** the input goes through a lexer (tokenizer) → parser (builds an
  AST of command and pipe nodes) → executer (walks the AST and runs it).
- **AST instead of a flat list:** a pipeline is represented as a binary tree of
  pipe nodes, each leaf being a command node that owns its argument array and its
  own list of redirections. This makes a chain like `a | b | c` fall out
  naturally as nested nodes, and keeps each command's redirections local to it.
- **Parent vs. child builtins:** builtins that change the shell's own state
  (`cd`, `export`, `unset`, `exit`) run in the **parent** process, because a
  change made inside a forked child would be lost on exit. The others
  (`echo`, `pwd`, `env`) can safely run in a child, which is what lets them work
  inside a pipeline.
- **Heredoc via a pipe, not a temp file:** `<<` reads the input and feeds it to
  the command through an anonymous `pipe()`, so no temporary file is created on
  disk and nothing needs to be cleaned up afterwards.
- **Signal handling per context:** the handlers are swapped depending on the
  shell's state (waiting at the prompt, running a command, or reading a heredoc),
  and a single global variable stores only the received signal number — the
  handler never touches the shell's data structures, as required by the subject.
- **Environment as a `char **`:** the environment is kept in the same `envp`
  format the system uses, so it can be passed straight to `execve` without
  conversion; `export`/`unset` rebuild this array.

## Resources

- [GNU Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html)
- `man bash`, `man readline`
- `man 2 execve`, `man 2 fork`, `man 2 pipe`, `man 2 dup2`, `man 2 wait`

### Use of AI

AI tools were used as a support aid, mainly for **testing, debugging and code
review**. All AI-assisted findings were verified by us, and the design and implementation of the project remain our own.
