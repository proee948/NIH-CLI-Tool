# NIH-CLI-Tool

A lightweight C-based command-line utility for simple command snippet storage.

Features
CLI flag parsing (argc/argv)
Debug mode to inspect arguments
Simple help system
File creation and persistence
Writes long input tokens into a text file
Basic snippet storage system (snippets.txt)

Build

Compile with gcc:

gcc main.c -o nih
Usage
./nih [options]

 Options
Help
./nih -h

Displays usage information.

Debug Mode
./nih -debug

Prints all passed arguments.

Create Storage File
./nih -create

Creates snippets.txt if it does not exist.

Write Mode
./nih -write arg1 arg2 arg3.....

Writes all arguments longer than 10 characters into snippets.txt.

File Structure
nih/
 ├── main.c
 ├── snippets.txt (auto-generated)
 └── README.md

~GOALS~
Add -read to display stored snippets
Add indexing system for snippets
Add delete/edit functionality
Support multi-word input parsing with quotes
Turn into full CLI note manager
