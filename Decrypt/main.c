#include <stdio.h>
#include <stdlib.h>
 #include "util.h"

char switchIt(char c){
    char alpha[26] = "abcdefghijklmnopqrstuvwxyz";

    switch(c){
        case 'a':
            return alpha[6]; //g
        case 'b':
            return alpha[21]; //v
        case 'c':
            return alpha[22]; //w
        case 'd':
            return alpha[15]; //p
        case 'e':
            return alpha[0]; // a
        case 'f':
            return alpha[25]; //z
        case 'g':
            return alpha[9]; //j
        case 'h':
            return alpha[1]; //b
        case 'i':
            return alpha[12]; //m
        case 'j':
            return alpha[20]; //u
        case 'k':
            return alpha[11]; //l
        case 'l':
            return alpha[2]; //c
        case 'm':
            return alpha[24]; //y
        case 'n':
            return alpha[8]; //i
        case 'o':
            return alpha[16]; //q
        case 'p':
            return alpha[14]; //o
        case 'q':
            return alpha[23]; //x
        case 'r':
            return alpha[7];//h
        case 's':
            return alpha[5]; //f
        case 't':
            return alpha[17]; //r
        case 'u':
            return alpha[4]; //e
        case 'v':
            return alpha[19]; //t
        case 'w':
            return alpha[10]; //k
        case 'x':
            return alpha[18]; //s
        case 'y':
            return alpha[13]; //n
        case 'z':
            return alpha[3]; //d
    }

    return alpha[1];

}

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
