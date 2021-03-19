#include <stdio.h>
#include <string.h>
#include <cs50.h>

bool check_side(int a, int b, int c);
int get_side(void);

int main(void)
{
	int a = 0;
	int b = 0;
	int c = 0;
	do
	{
		a = get_int("Input the first side length: ");
	}
	while (a <= 0);
	do
	{
		b = get_int("Input the second side length: ");
	}
	while (b <= 0);
	do
	{
		c = get_int("Input the third side length: ");
	}
	while (c <= 0);
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
}
