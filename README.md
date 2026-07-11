# NIH-CLI-Tool

A lightweight, production-ready C command-line utility for lightning-fast snippet management and terminal command ingestion.

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
./nih -w echo "Hello World" && sudo apt update
```

### List Saved Commands
```bash
./nih -l
```

### Inject/Copy a Snippet
```bash
./nih -p 3
```

## Useful Tips

### Using the `--` Double-Dash Separator
When using the write flag (`-w`) to save a snippet that contains its own command-line flags or hyphens, always place a `--` before your command payload:

### Using wildcards such as `<>` `|` `*` and such...
when you are saving commands such as these you must wrap the entire snippet in single quotes (').
```bash
./nih -w -- 'du -sh * | sort -h'
```
reason being these operators for example `|` is evaluated before anything else and thus creates parsing problems for `nih` , using single quotes (') blocks this behavior.



```bash
./nih -w -- ls -la --color=always /var/log
```

#### Why you need this:
The standard POSIX `getopt` parser automatically stops scanning for utility flags the exact moment it encounters a standalone `--`. Without it, if your snippet contains a dash (like `-la` or `--color`), `getopt` will mistake those strings for options belonging to the `./nih` binary itself, causing parsing errors or dropping characters before they can be committed to `snippets.txt`.

## GOALS

- [ ] Add an interactive `ncurses` selection menu UI to cycle through stored macros.

## Build

Compile using `gcc`:

```bash
gcc nih2.c nih.c -o nih
```

