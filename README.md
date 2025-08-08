# 🐚 Minishell

**A tiny POSIX‑like shell in C** — with quoting & env expansion, builtins, redirections, pipes, here‑docs, and proper signal handling. Built as part of the **École 42** curriculum.

---

## 📑 Table of Contents

1. [Overview](#overview)
2. [Features](#features)
3. [Grammar & Parsing](#grammar--parsing)
4. [Builtins](#builtins)
5. [Directory Structure](#directory-structure)
6. [Build](#build)
7. [Usage](#usage)
8. [Redirections & Pipes](#redirections--pipes)
9. [Here‑docs](#here-docs)
10. [Signals](#signals)
11. [Exit Codes](#exit-codes)
12. [Make Targets](#make-targets)
13. [Testing & Debugging](#testing--debugging)
14. [Project Context](#project-context)

---

<a id="overview"></a>

## ✨ Overview

`minishell` aims to mimic the behavior of a real shell (like Bash) for a restricted but realistic subset:

* Parse user input with **quotes** (`'`, `"`) and **environment expansion** (`$VAR`).
* Execute programs using **PATH** lookup; handle **pipes** and **I/O redirections**.
* Implement **builtins** in‑process (no `fork/exec` when not needed).
* Manage **signals** (`SIGINT`, `SIGQUIT`) to feel like a shell.

---

<a id="features"></a>

## ⚙️ Features

* **Lexing/Parsing** with proper tokenization (quotes, escapes, `$VAR`, `$?`).
* **Executor** supports: `|`, `>`, `>>`, `<`, `<<` (here‑doc).
* **Builtins** (see below) with POSIX‑compatible behavior.
* **Environment** management (`env`, `export`, `unset`).
* **Signals**: interactive `Ctrl‑C` prints a new prompt; `Ctrl‑\` ignored in interactive mode.
* **Error handling**: descriptive errors to `stderr`, correct exit statuses.

---

<a id="grammar--parsing"></a>

## 🧠 Grammar & Parsing

**Tokens**: words, operators (`|`, `>`, `>>`, `<`, `<<`), literals inside single quotes (no expansion), double quotes (expansion allowed), and variables (`$VAR`, `$?`).

**Expansion** order (simplified):

1. Tokenize (respecting quotes).
2. Expand env variables in unquoted and double‑quoted segments.
3. Split fields after expansion (not inside quotes).
4. Apply redirections & build the pipeline.

---

<a id="builtins"></a>

## 🧩 Builtins

| Command               | Summary                                                            |
| --------------------- | ------------------------------------------------------------------ |
| `echo [-n] [args…]`   | Print arguments separated by spaces (no trailing newline if `-n`). |
| `cd [dir]`            | Change directory (defaults to `$HOME`). Updates `PWD`/`OLDPWD`.    |
| `pwd`                 | Print current directory.                                           |
| `export [KEY[=VAL]]…` | Add/update env variables; no arg → print in sorted form.           |
| `unset KEY…`          | Remove env variables.                                              |
| `env`                 | Print environment.                                                 |
| `exit [status]`       | Exit the shell with optional status.                               |

> Builtins run **in the parent** when possible (e.g., `cd`, `export`, `unset`, `exit`) so they affect the shell state.

---

<a id="directory-structure"></a>

## 🗂️ Directory Structure

```text
minishell/
├── include/           # headers (minishell.h, libft.h)
├── libft/             # embedded libft (static library)
├── src/
│   ├── builtins/      # echo, cd, pwd, export, unset, env, exit
│   ├── exec/          # executor, redirections, pipes, fork/execve
│   ├── pars/          # lexer, parser, expansion
│   ├── utils/         # helpers, error/message utils, factories
│   └── minishell.c    # entry point
├── Makefile
└── README.md          # you are here
```

> The sub‑folders reflect the tree you see in this repository (builtins/, exec/, pars/ …).

---

<a id="build"></a>

## 🚀 Build

This project links against **readline**.

### Linux (Debian/Ubuntu)

```bash
sudo apt-get update
sudo apt-get install -y readline-common libreadline-dev
make            # builds ./minishell (also builds libft)
```

### macOS (Homebrew)

```bash
brew install readline
make RL_PATH="$(brew --prefix readline)/lib" RL_INC="$(brew --prefix readline)/include"
```

*If your system needs `-lncurses`, run:*

```bash
make RL_LIBS="-lreadline -lncurses"
```

---

<a id="usage"></a>

## 📚 Usage

Run the shell:

```bash
./minishell
```

Examples inside the shell:

```sh
$ echo "Hello $USER"
$ export PATH=$PATH:/custom/bin
$ ls -l | grep ".c$" > c_files.txt
$ cat <<EOF | wc -l
line 1
line 2
EOF
$ cd /tmp && pwd
$ echo $?
$ exit 0
```

---

<a id="redirections--pipes"></a>

## 🔀 Redirections & Pipes

* `cmd > file` : truncate and write stdout
* `cmd >> file` : append
* `cmd < file` : read stdin from file
* `cmd1 | cmd2 | cmd3` : standard UNIX pipelines

Errors are printed to `stderr` with the appropriate exit status.

---

<a id="here-docs"></a>

## 📄 Here‑docs

`<< LIMITER` collects lines until `LIMITER` (not included). If the limiter is **quoted**, expansions are disabled.

```sh
cat <<EOF
$USER will be expanded here
EOF

cat <<'EOF'
$USER will NOT be expanded here
EOF
```

---

<a id="signals"></a>

## 🚦 Signals

* **Interactive:** `Ctrl‑C` prints a new prompt with status 130; `Ctrl‑\` is ignored.
* **In children:** default behavior is restored so programs receive signals normally.

---

<a id="exit-codes"></a>

## 🔢 Exit Codes

* Last command status available as `$?`.
* Builtins follow POSIX conventions (e.g., `exit` with non‑numeric arg → 2).
* Parsing/exec errors return non‑zero with descriptive messages.

---

<a id="make-targets"></a>

## 🧰 Make Targets

```text
make        # build minishell (+ libft)
make clean  # remove objects
make fclean # remove objects + binaries + libs
make re     # full rebuild
```

You can increase logs by running `make VERBOSE=1`.

---

<a id="testing--debugging"></a>

## 🧪 Testing & Debugging

* **Valgrind (Linux)** — check for leaks:

  ```bash
  valgrind --leak-check=full --show-leak-kinds=all ./minishell
  ```
* **Sanitizers (Clang/GCC):**

  ```bash
  make CFLAGS="-Wall -Wextra -Werror -g -fsanitize=address,undefined" re
  ./minishell
  ```
* **Scripted runs:**

  ```bash
  printf 'echo hello\nexit\n' | ./minishell
  ```

---

<a id="project-context"></a>

## 🏛️ Project Context

Part of the **42** Common Core: focus on **parsing**, **process control**, **file descriptors**, **signals**, and **robust C code** with resource management.
