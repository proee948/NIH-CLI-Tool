
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>

void create_storage(void);
void save_command(int argc, char *argv[]);
void list_commands(void);
void search_command(int argc, char *argv[]);
int terminal_injection(const char *str);
void clear_buffer(char *);
void injection();

extern BUFFER[1024];