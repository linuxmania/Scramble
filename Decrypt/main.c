#include <stdio.h>
#include <stdlib.h>
#include "util.h"

int main()
{
    printf("Hello from Decrypt!\n");

    FILE *fp1, *fp2;
    fp1  = fopen ("/tmp/out.bin", "rb");
    fp2  = fopen ("/tmp/out.txt", "w");

    char line[256];
    char stashed_line[4][256];
    char c;
    int count = 0;
    int line_count = 0;

    while (fgets(line, sizeof(line), fp1)) {
        printf("%s", line);

        // write the first four decrypted lines to memory, then rearrange and write to file
        if(line_count < 4){
            for(int i =0; i< sizeof(line); i++){
                if(line[i] == '\n'){
                    stashed_line[line_count][i] = line[i];
                    stashed_line[line_count][i+1] = '\0';
                    break;
                }
                count++;
                c = flopBit(line[i],count);
                c = switchIt(c);
                stashed_line[line_count][i] = c;
            }
        } else {
            if(line_count == 4){
                fputs(stashed_line[2], fp2);
                fputs(stashed_line[0], fp2);
                fputs(stashed_line[3], fp2);
                fputs(stashed_line[1], fp2);

            }
            for(int i =0; i< sizeof(line); i++){
                if(line[i] == '\n'){
                    putc(line[i], fp2);
                    break;
                }
                count++;
                c = flopBit(line[i],count);
                c = switchIt(c);
                putc(c, fp2);
            }
        }
        line_count++;
    }

    fclose(fp1);
    fclose(fp2);

    printf("Goodbye from Decrypt!\n");
    return 0;
}
