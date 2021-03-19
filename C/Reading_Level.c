#include <string.h>
#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <math.h>

int count_letters(string x);
int word_count(string x);
int sentences(string x);
int lpw(int a, int b);
int wps(int a, int b);
float reading_level(float a, float b);

int main(void)
{
    string text = get_string("Text: ");
    int b = count_letters(text);
    int d = word_count(text);
    int f = sentences(text);
    float h = lpw(b, d);
    float k = wps(d, f);
    float l = reading_level(h, k);
    if (l < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (l >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %0.0f\n", l);
    }
}

int count_letters(string x)
{
    int a = 0;
    for (int i = 0; i < strlen(x); i++)
    {
        if (isalpha(x[i]))
        {
            a++;
        }
    }
    return a;
}

int word_count(string x)
{
    int c = 1;
    for (int i = 0; i < strlen(x); i++)
    {
        if (isspace(x[i]))
        {
            c++;
        }
    }
    return c;
}

int sentences(string x)
{
    int e = 0;
    for (int i = 0; i < strlen(x); i++)
    {
        if (ispunct(x[i]))
        {
            if ((x[i] == '.') || (x[i] == '?') || (x[i] == '!'))
            {
                e++;
            }
        }
    }
    if (e == 0)
    {
        e = 1;
    }
    return e;
}

int lpw(int a, int b)
{
    int g = round((100 * a) / b);
    return g;
}

int wps(int a, int b)
{
    int j = round((100 * b) / a);
    return j;
}

float reading_level(float a, float b)
{
    float r = round(0.0588 * a - 0.296 * b - 15.8);
    return r;
}