// terminal injection logic is here along with wayland/X11 copy-to-clipboard fallback \
since ioctl is disabled by default on modern linux kernel

#include "nih.h"

int terminal_injection(const char *str)
{
    size_t len = strlen(str);
    for (size_t i = 0; i < len; i++) 
    {
        if(ioctl(0, TIOCSTI, &str[i]) == -1)
        {
            return 0; //term with 0
        }
    } 
    return 1; //return 1 if all chars are passed succesfulyy into terminal
    
}
void injection()
{
    if( terminal_injection(BUFFER) == 1)
    {
        ; //dead block, injection succeeded
    }
    else
        {
            FILE *fp = fopen("snippets.txt","r"); //open snippets.txt

            switch(line_number)
    {
        /*case 1:

            while ( (ch = fgetc(f)) != '\n' && ch != EOF)
            {
                BUFFER[i++] = (char) ch;
            }

            BUFFER[i] = '\0';
            injection(BUFFER); 
            clear_buffer(BUFFER);
            i = 0;

            break;

        case 2:
            while ( (ch = fgetc(f)) != '\n' ) {line_lenght++;}
            while ( (ch = fgetc(f)) != '\n' && ch != EOF)  
            {
               BUFFER[i++] = (char) ch;
            } 

            BUFFER[i] = '\0';
            injection(BUFFER); 
            clear_buffer(BUFFER);
            i = 0;
            break;

        case 3:
            while(newline_count < 2 && (ch = fgetc(f)) != EOF)
            {
                if(ch == '\n'){newline_count++;}
            }
            while ((ch = fgetc(f)) != '\n'  && ch != EOF) 
            {
                BUFFER[i++] = (char) ch;
            }
            BUFFER[i] = '\0';
            injection(BUFFER); 
            clear_buffer(BUFFER);
            i = 0;
            break; 
        
        case 4:
            while(newline_count < 3 && (ch = fgetc(f)) != EOF)
            {
                if(ch == '\n'){newline_count++;}
            }
            while ((ch = fgetc(f)) != '\n'  && ch != EOF)  
            {}
            break; 
        
        case 5:
            while(newline_count < 4 && (ch = fgetc(f)) != EOF)
            {
                if(ch == '\n'){newline_count++;}
            }
            while ((ch = fgetc(f)) != '\n'  && ch != EOF)  
            {}
            break; 
            
        default: break;
            

            //FILE *f;
            //popen("sed")
            //popen("xclip -selection clipboard")
            //snprintf()
        }

} */ ////this logic will be reused to extract specified line from snippets.txt and then pipe it to xclip!

void clear_buffer(char *passed_buffer) 
{
    if (passed_buffer != NULL) 
    {
        passed_buffer[0] = '\0';
    }
}
