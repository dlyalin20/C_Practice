#include <cs50.h>
#include <stdio.h>

int collatz(int n);

int main(void)
{
    int n = get_int("n: ");
    printf("%i steps\n", collatz(n));
}

int collatz(int n)
{
    int x = 0;
    for ( ; n != 1; x++)
    {
        if (n%2==0)
        {
            n = n/2;
        }
        else
        {
            n = (3*n)+1;
        }
    }
    return x++;
}
