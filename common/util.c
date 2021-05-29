void getCharBits( char c , char* ret)
{
    int i=0;
    int j = 0;
    for (i = (sizeof(char) * 8) - 1; i >= 0; i--)
    {
       ret[j++] = c & (1u << i) ? '1' : '0';
    }
    ret[j] = '\0';
}

char flopBit(char c, int k){
    int j = 0;
    switch(k%3){
        case 1:
            j = 3;
            break;
        case 2:
            j = 5;
    }
    if(j==0) return c;

    char l[9];
    getCharBits(c, l);
    l[j] = l[j] == '0' ? '1' : '0';

    return strtol(l, 0, 2);;
}

