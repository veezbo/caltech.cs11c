#include <stdio.h>

/* Prompts user for name and then greets them with standard output */
int main(void)
{
    char s[100];
    printf("Enter your name: ");
    scanf("%99s", s);
    printf("hello, %s!\n", s);
    return 0;
}
