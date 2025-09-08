#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>
void test1()
{

}
char *find_char(char const *source, char const *chars)
{
    //assert(source);
    //assert(chars);

    //int desc;
    // char *start = chars;
    while(*source != '\0')
    {
        while(*chars != '\0')
        {
            if(*source == *chars++)
                return chars;   
        }
        source++;
    }
    /*
    for(;*source != '\0';source++)
    {
        for(;*chars != '\0';chars++)
        {
            if(*source == *chars++)
                return chars;
        }
    }
    */
    return NULL;
    
}

int main(void)
{
    test1();    
    char *string1 = "newbalance";
    char *string2 = "bad guy";
    if(find_char(string1,string2) != NULL)
        printf("Match!");
    else
        printf("didn't match");

    return EXIT_SUCCESS;
}