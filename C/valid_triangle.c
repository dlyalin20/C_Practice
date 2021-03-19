#include <stdio.h>
#include <string.h>
#include <cs50.h>

bool check_side(int a, int b, int c);


int main(void)
{
	int a = get_int("Input a side length: ");
	int b = get_int("Input another side length: ");
	int c = get_int("Input one last side length: ");
	if (check_side(a, b, c))
	{
		if (check_side(a, c, b))
		{
			if (check_side(b, c, a))
			{
				printf("ABC is a triangle\n");
			}
			else
			{
				printf("ABC is not a triangle\n");
			}
		}
		else
		{
			printf("ABC is not a triangle\n");
		}
	}
	else
	{
		printf("ABC is not a triangle\n");
	}
}

bool check_side(int x, int y, int z)
{
	if ((x + y) > z)
	{
		return true;
	}
	else
	{
		return false;
	}