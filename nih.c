#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// prototypes
void nih_help(void);
void nih_create(void);
void nih_write(char *text);
void nih_inputsort(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    if (argc < 2) {
        nih_help();
        return 1;
    }

    for (int i = 1; i < argc; i++) {

        if (strcmp(argv[i], "-debug") == 0) {
            printf("DEBUG MODE\n");
            for (int j = 0; j < argc; j++) {
                printf("argv[%d]: %s\n", j, argv[j]);
            }
        }

        else if (strcmp(argv[i], "-h") == 0) {
            nih_help();
        }

        else if (strcmp(argv[i], "-create") == 0) {
            nih_create();
        }

        else if (strcmp(argv[i], "-write") == 0) {
            nih_inputsort(argc, argv);
        }
    }

    return 0;
}

void nih_help(void)
{
    printf("Usage: ./nih [options]\n");
    printf("-------FLAGS-------\n");
    printf("-h       (help)\n");
    printf("-debug   (dev info)\n");
    printf("-create\n-write\n");
}

void nih_create(void)
{
    FILE *f = fopen("snippets.txt", "a");
    if (f) fclose(f);
}

void nih_inputsort(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        if (strlen(argv[i]) > 10) {
            nih_write(argv[i]);
        }
    }
}

void nih_write(char *text)
{
    FILE *f = fopen("snippets.txt", "a");

    if (!f) {
        printf("Failed to open file\n");
        return;
    }

    fprintf(f, "%s\n", text);
    fclose(f);
}
