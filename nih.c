#include "nih.h"

char BUFFER[1024];

int main(int argc, char *argv[])
{
    if(argc == 1)
    {
        menu();
    }

    int opt;
    opterr = 0;

    while ((opt = getopt(argc, argv, "swlp:")) != -1) 
    {
        switch (opt)
        {
            case 's': 
                create_storage();
                printf("created save file");
                break;
            case 'w': 
                save_command(argc, argv);
                printf("written to save file");
                break;
            case 'l':
                list_commands();
                break;
            case 'p':
                search_command(argc, argv);
                break;  
        }
    }
    return 0;
}

void create_storage(void)
{
    FILE *f = fopen("snippets.txt", "w");
    if (f != NULL) {
        fclose(f);
    }
}

void save_command(int argc, char *argv[])
{
    FILE *f = fopen("snippets.txt", "a");
    if (f == NULL) { return; }

    for (int i = optind; i < argc; i++)  
    {
        if (strcmp(argv[i], "--") == 0) { continue; }
        fprintf(f, "%s ", argv[i]);
    }
    fprintf(f, "\n"); 
    fclose(f); 
}

void list_commands(void)
{
    FILE *f = fopen("snippets.txt", "r");
    if (f == NULL) { return; }
    
    int ch;
    while ((ch = fgetc(f)) != EOF)
    {
        putchar(ch);
    }
    fclose(f);
}

void search_command(int argc, char *argv[])
{
    FILE *f = fopen("snippets.txt", "r");
    if (f == NULL) { return; }

    int target_line = atoi(optarg);
    int current_line = 1;
    int ch;
    int i = 0;

    while (current_line < target_line && (ch = fgetc(f)) != EOF)
    {
        if (ch == '\n') {
            current_line++;
        }
    }

    while ((ch = fgetc(f)) != '\n' && ch != EOF)
    {
        if (i < 1023) {
            BUFFER[i++] = (char)ch;
        }
    }
    BUFFER[i] = '\0';
    fclose(f);

    if (i > 0) {
        injection(BUFFER);
    }
}
