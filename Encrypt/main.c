#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

char switchIt(char c){
    char alpha[26] = "abcdefghijklmnopqrstuvwxyz";

    switch(c){
        case 'a':
            return alpha[4];
        case 'b':
            return alpha[7];
        case 'c':
            return alpha[11];
        case 'd':
            return alpha[25];
        case 'e':
            return alpha[20];
        case 'f':
            return alpha[18];
        case 'g':
            return alpha[0];
        case 'h':
            return alpha[17];
        case 'i':
            return alpha[13];
        case 'j':
            return alpha[6];
        case 'k':
            return alpha[22];
        case 'l':
            return alpha[10];
        case 'm':
            return alpha[8];
        case 'n':
            return alpha[24];
        case 'o':
            return alpha[15];
        case 'p':
            return alpha[3];
        case 'q':
            return alpha[14];
        case 'r':
            return alpha[19];
        case 's':
            return alpha[23];
        case 't':
            return alpha[21];
        case 'u':
            return alpha[9];
        case 'v':
            return alpha[1];
        case 'w':
            return alpha[2];
        case 'x':
            return alpha[16];
        case 'y':
            return alpha[12];
        case 'z':
            return alpha[5];
    }

    return alpha[1];

}

int processLine(char* line, FILE* fp, int count){
    for(int i =0; i< sizeof(line); i++){
        if(line[i] == '\n'){
            putc(line[i], fp);
            break;
        }
        count++;
        char c = switchIt(line[i]);
        c = flopBit(c,count);
        putc(c, fp);
    }
    return count;
}

int main()
{
    printf("Hello from Encrypt!\n");

    //read in /tmp/in.txt ; write out /tmp/out.txt

    FILE *fp1, *fp2;
    fp1  = fopen ("/tmp/in.txt", "r");
    fp2  = fopen ("/tmp/out.bin", "wb");

    char line[256];

    int count = 0;

    char stashed_line[4][256];
    int line_count = 0;

    while (fgets(line, sizeof(line), fp1)) {
        printf("%s", line);

    // read first four lines into memory, rearrange then process
        if(line_count < 4){

            switch(line_count){
                case 0 :
                    strncpy(stashed_line[2], line, sizeof(line));
                    break;
                case 1 :
                    strncpy(stashed_line[0], line, sizeof(line));
                    break;
                case 2 :
                    strncpy(stashed_line[3], line, sizeof(line));
                    break;
                case 3 :
                    strncpy(stashed_line[1], line, sizeof(line));
                    break;
            }
        } else {
            if(line_count == 4){
                for(int i =0; i < 4; i++){
                    count = processLine(stashed_line[i], fp2, count);
                }
                count = processLine(line, fp2, count);
            } else {
                count = processLine(line, fp2, count);
            }
        }
        line_count++;
    }

    fclose(fp1);
    fclose(fp2);

    printf("Goodbye from Encrypt!\n");
    return 0;
}
