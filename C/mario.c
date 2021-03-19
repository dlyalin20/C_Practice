#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int h;
    do 
    {
        h = get_int("Height: ");
    }
    while (h < 1 || h > 8);
    if (h == 1)
    {
        printf("#  #\n");
    }
    else if (h == 2)
    {
        printf(" #  #\n##  ##\n");
    }
    else if (h == 3)
    {
        printf("   #  #\n  ##  ##\n ###  ###\n");
    }
    else if (h == 4)
    {
        printf("   #  #\n  ##  ##\n ###  ###\n####  ####\n");
    }
    else if (h == 5)
    {
        printf("    #  #\n   ##  ##\n  ###  ###\n ####  ####\n#####  #####\n");
    }
    else if (h == 6)
    {
        printf("     #  #\n    ##  ##\n   ###  ###\n  ####  ####\n #####  #####\n######  ######\n");
    }
    else if (h == 7)
    {
        printf("      #  #\n     ##  ##\n    ###  ###\n   ####  ####\n  #####  #####\n ######  ######\n#######  #######\n");
    }
    else if (h == 8)
    {
        printf("       #  #\n      ##  ##\n     ###  ###\n    ####  ####\n   #####  #####\n  ######  ######\n #######  #######\n########  ########\n");
    }
}
