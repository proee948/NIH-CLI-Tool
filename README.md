# NIH-CLI-Tool

C command-line utility for snippet management and terminal command ingestion.

## Features

- **Dual-Layer Execution Pipeline:** Attempts direct terminal keystroke injection via low-level system `ioctl` calls.
- **Silent Clipboard Fallback:** Automatically switches to an invisible `xclip` daemon pipeline if kernel protections block physical injection.
- **Dynamic File Parsing:** Zero-allocation line streaming allows you to jump directly to any selected line index instantly.
- **Persistent Storage:** Safely creates, appends, and queries shell commands directly within a flat asset payload (`snippets.txt`).

## Current Usage

### Create Storage
```bash
./nih -s
```

### Save a Command
```bash
./nih -w -- 'echo "Hello World" && sudo apt update'
```

### List Saved Commands
```bash
./nih -l
```

### Inject/Copy a Snippet
```bash
./nih -p 3
```

### Launch Interactive Selection Menu
```bash
./nih
```

## Useful Tips

### Handling Shell Operators (`|`, `<`, `>`, `*`, `&&`)
When saving a command string that includes system redirections, pipe mechanics, globbing wildcards, or logical chains, you must envelop the entire string payload within single quotes (`'`):

```bash
./nih -w -- 'du -sh * | sort -h'
```

#### Why you need this:
The active Bash shell evaluates operators like the pipeline (`|`) *before* passing tokens down to the destination binary. Without strict quote constraints, your shell will intercept the statement prematurely, attempting to pipe the internal execution states of `./nih` into subsequent operations. Single quotes completely dearm these control sequences, converting them into a harmless literal text stream.

If your snippet requires an inner single quote string literal, step out of the expression block, append an escaped quote sequence, and restart the literal tracking block immediately:

```bash
./nih -w -- 'echo '\''Hello World'\'''
```

### Using the `--` Double-Dash Separator
When writing a snippet that contains nested execution flags, place a detached double-dash prefix sequence (`--`) before writing your instruction data block:

```bash
./nih -w -- ls -la --color=always /var/log
```

#### Why you need this:
The underlying POSIX standard `getopt` parser automatically concludes flag lookups the exact moment it meets a standalone `--` operator. If this guard sequence is excluded, any subsequent token beginning with a dash parameter (such as `-la` or `--color`) will be mistakenly intercepted by `getopt` as configuration directives native to `./nih` itself, resulting in unexpected syntax errors.

## GOALS

- [x] Add an interactive `ncurses` selection menu UI to cycle through stored macros.

## Build

Compile the codebase using `gcc`, linking both the base `ncurses` runtime engine and the top-tier `cdk` abstraction toolkit libraries:

```bash
gcc main.c nih.c -o nih -lcdk -lncurses
```
