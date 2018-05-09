#include<stdio.h>
#define MAXLEN 20

int my_getline(char s[], int lim);
int htoi(char s[]);
int main()
{
    char num[MAXLEN];
    int new_num;
    int len;
    while ((len = my_getline(num, MAXLEN)) > 0) {
        new_num = htoi(num);
        if (new_num != -1 )
            printf("%d\n", new_num);
        else
            printf("not a hexidecimal\n");

    }
    return 0;
}

int htoi(char s[])
{
    int n = 0;
    int i = 0;
    while (s[i] != '\0' && s[i] != '\n') {
        if (s[i] == '0') {
            if (s[i+1] == 'x' || s[i+1] == 'X')
                            i+=2;
        }
        if (s[i] >= '0' && s[i] <= '9') {
            n = n * 16 + (s[i] - '0');
        } else if (s[i] >= 'a' && s[i] <= 'f') {
            n = n * 16 + (s[i] - 'a') + 10;
        } else if (s[i] >= 'A' && s[i] <= 'F') {
            n = n * 16 + (s[i] - 'A') + 10;
        } else
            return -1;
        ++i;

    }
    return n;
}

int my_getline(char s[], int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n';
         ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}