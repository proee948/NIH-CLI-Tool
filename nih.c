#include <string.h>
#include <stdio.h>
#include <unistd.h>

//prototypes//
void create_storage(void);
void save_command(int argc, char *argv[]);
void list_commands(void);
void search_command(int argc, char *argv[]);
//prototypes//


int main(int argc, char *argv[])
{
    int opt;
    opterr = 0; //forbids getopt from eating shit

    while( (opt = getopt(argc, argv, "swlp:")) != -1) // "swlp" >>> start/write/list/print
    {
        switch(opt)
        {
            case 's': 
                create_storage();
                printf("created storage file\n"); 
                break;

            case 'w': 
                save_command(argc, argv);
                printf("command saved\n"); 
                break;

            case '?': 
                break;

            case 'l':
                list_commands();
                break;

            case 'p':
                search_command(argc,argv);
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
    if (f == NULL) { return; }            // Safety check

    for(int i = optind; i < argc; i++)  
    {
        if(strcmp(argv[i],"--") == 0){continue;}
        fprintf(f, "%s ", argv[i]);
    }
    fprintf(f, "\n"); 
    fclose(f); 
}

void list_commands()
{
    FILE *f = fopen("snippets.txt","r");
    if (f == NULL){return;}
    fseek(f,0,SEEK_SET);
    
    int ch;
    while( (ch = fgetc(f)) != EOF)
    {
        putchar(ch);
    }
    fclose(f);
}

int line_lenght = 0; //this is a dynamically calculated lenght of FIRST line

void search_command(int argc, char *argv[])
{
    //called by -p then argument (position)

    FILE *f = fopen("snippets.txt","r");
    if (f == NULL){return;}
    fseek(f,0,SEEK_SET); 

    int ch;
    int line_number = *optarg - '0'; //user input after -p eg. '2',cancel ascii with -0
    int newline_count = 0; //used for case 3 and post

    switch(line_number)
    {
        case 1:
            while ( (ch = fgetc(f)) != '\n' ) {printf("%c",ch);} break;

        case 2:
            while ( (ch = fgetc(f)) != '\n' ) {line_lenght++;}
            fseek(f,line_lenght + 1,SEEK_SET);
            while ( (ch = fgetc(f)) != '\n' )  {printf("%c",ch);} 
            break;

        case 3:
            while(newline_count < 2 && (ch = fgetc(f)) != EOF)
            {
                if(ch == '\n'){newline_count++;}
            }
            while ((ch = fgetc(f)) != '\n') {printf("%c",ch);}
            break; 
        
        case 4:
            while(newline_count < 3 && (ch = fgetc(f)) != EOF)
            {
                if(ch == '\n'){newline_count++;}
            }
            while ((ch = fgetc(f)) != '\n')  {printf("%c",ch);}
            break;
        
        case 5:
            while(newline_count < 4 && (ch = fgetc(f)) != EOF)
            {
                if(ch == '\n'){newline_count++;}
            }
            while ((ch = fgetc(f)) != '\n')  {printf("%c",ch);}
            break;
            
        default: break;

    }
    fclose(f);
    
}
