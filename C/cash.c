#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float price;
    int total;
    do
    {
        price = get_float("Change owed: ");
        total = round(price * 100);
    }
    while (price < 0);
    int quarter = 0;
    int dime = 0;
    int nickel = 0;
    int penny = 0;
    int coins = 0;
    do
    {
        if (total >= 25)
        {
            quarter++;
            total = (total - 25);
        }
        else if (total >= 10)
        {
            dime++;
            total = (total - 10);
        }
        else if (total >= 5)
        {
            nickel++;
            total = (total - 5);
        }
        else if (total >= 1)
        {
            penny++;
            total = (total - 1);
        }
    }
    while (total > 0);
    coins = (quarter + dime + nickel + penny);
    printf("%i\n", coins);
}
