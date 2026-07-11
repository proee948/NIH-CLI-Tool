#ifndef NIH_H
#define NIH_H

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <cdk/cdk.h>

extern char BUFFER[1024];

void create_storage(void);
void save_command(int argc, char *argv[]);
void list_commands(void);
void search_command(int argc, char *argv[]);
void injection(char *passed_buffer);
void clear_buffer(char *passed_buffer);
int pass_to_xclip(char *passed_buffer);
int terminal_injection(const char *str);
int menu(void);

#endif
