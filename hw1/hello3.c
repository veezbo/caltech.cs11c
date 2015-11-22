#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Prompts user for name and then greets them with standard output
   somewhere between 1 and 10 times */
int main(void)
{
    int rand_number;
    int i;
    char s[100];

    srand(time(NULL));
    printf("Enter your name: ");
    scanf("%99s", s);
    /* Require one random call because the first rand call is big */
    rand();

    /* Calculate random number by finding which tenth rand() falls in
       in the range [0, RAND_MAX] */
    rand_number = rand() % 10 + 1;

    if (rand_number % 2 == 0)
    {
        for (i = 0; i < rand_number; i++)
        {
            printf("<%i>: hello, %s!\n", rand_number, s);
        }
    }
    else
    {
        for (i = 0; i < rand_number; i++)
        {
            printf("<%i>: hi there, %s!\n", rand_number, s);
        }
    }

    return 0;
}
