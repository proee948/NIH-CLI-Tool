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

int menu(void)
{
    FILE *f = fopen("snippets.txt", "r");
    if (f == NULL) { return 0; }

    char *items[128];
    int line_count = 0;
    char line_buffer[1024];

    while (fgets(line_buffer, sizeof(line_buffer), f) != NULL && line_count < 128)
    {
        size_t len = strlen(line_buffer);
        if (len > 0 && line_buffer[len - 1] == '\n') {
            line_buffer[len - 1] = '\0';
        }
        items[line_count++] = strdup(line_buffer);
    }
    fclose(f);
    if (line_count == 0) { return 0; }

    WINDOW *win = initscr();
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    CDKSCREEN *cdk = initCDKScreen(win);
    initCDKColor();

    CDKSCROLL *m = newCDKScroll(
        cdk,
        CENTER, CENTER,
        RIGHT,
        12, 66,
        "MENU",
        items,
        line_count,
        TRUE,
        A_REVERSE | COLOR_PAIR(1),
        TRUE,
        FALSE
    );

    int selection = activateCDKScroll(m, NULL);
    if (selection >= 0 && selection < line_count) 
    {
        strncpy(BUFFER, items[selection], sizeof(BUFFER) - 1);
        BUFFER[sizeof(BUFFER) - 1] = '\0';
    }

    destroyCDKScroll(m);
    destroyCDKScreen(cdk);
    endwin();

    for (int i = 0; i < line_count; i++) {
        free(items[i]);
    }
    if (strlen(BUFFER) > 0) {
        injection(BUFFER);
    }
}

