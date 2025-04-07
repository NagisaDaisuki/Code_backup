#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned short int test1(int year)
{
    unsigned short int leap_year = 0;
    if(year % 400 == 0)
        leap_year = 1;
    else if (year % 100 == 0)
        leap_year = 0;
    else if (year % 4 == 0)
        leap_year = 1;
    else 
        leap_year = 0;
}

int main()
{
    
    return EXIT_SUCCESS;
}