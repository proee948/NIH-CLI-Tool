#include "nih.h"

int terminal_injection(const char *str)
{
    size_t len = strlen(str);
    for (size_t i = 0; i < len; i++) 
    {
        if(ioctl(0, TIOCSTI, &str[i]) == -1)
        {
            return 0;
        }
    } 
    return 1;
}

int pass_to_xclip(char *passed_buffer)
{
    FILE *ft = popen("xclip -selection clipboard", "w");
    if (ft == NULL) 
    {
        return 0;
    }
    fprintf(ft, "%s", passed_buffer);
    return (pclose(ft) == 0);
}

void injection(char *passed_buffer)
{
    if (terminal_injection(passed_buffer) == 0)
    {
        pass_to_xclip(passed_buffer);
    }
}  

void clear_buffer(char *passed_buffer) 
{
    if (passed_buffer != NULL) 
    {
        passed_buffer[0] = '\0';
    }
}
