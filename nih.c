#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// prototypes
void nih_help(void);
void nih_create(void);
void nih_write(char *text);
void nih_inputsort(int argc, char *argv[]);
void nih_list(void);
void count_lines(void);
//prototypes

//globals//
int counter = 0;
//globals//

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

        else if (strcmp(argv[i], "-start") == 0) {
            nih_create();
        }

        else if (strcmp(argv[i], "-write") == 0) {
            nih_inputsort(argc, argv);
        }
        else if(strcmp(argv[i], "-list") == 0) {
            nih_list();
        }
    }
    return 0;
}

void nih_help(void)
{
    printf("\n");
    printf("Usage: ./nih [options]\n");
    printf("=====================================\n");
    printf("Available Flags:\n");
    printf("-------------------------------------\n");
    printf("  -h        Show help menu\n");
    printf("  -debug    Show debug information\n");
    printf("  -start    Create snippet file\n");
    printf("  -write    Save text (length > 10)\n");
    printf("  -list     List all saved snippets\n");
    printf("=====================================\n");
    printf("\n");
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
    count_lines();
    fprintf(f,"%d\t%s\n",counter,text);
    fclose(f);
}
void count_lines(void)
{
    char buffer[1024]; 

    FILE *f = fopen("snippets.txt", "r");

    if (f) {
        while (fgets(buffer, sizeof(buffer), f)) { // egde case: if line > 1024 chars, possible increment by 2.
            counter++;   // for each \n fgets encounters increment counter by 1
        }
        fclose(f);
    }
}
void nih_list(void)
{
    FILE *f = fopen("snippets.txt","r"); // open in read mode

    int a;
    while( (a = fgetc(f)) != EOF)         //print until EOF flag is seen
    {
        printf("%c",a);
    }
    fclose(f); 
}
