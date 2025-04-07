#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test1()
{
    enum Liquid {OUNCE = 1, CUP = 8, PINT = 16, QUART = 32, GALLON = 128};
    enum Liquid jar;
    jar = QUART;
    printf("%s\n","new man");
    jar = jar + PINT;
    printf("%s\n",jar);

}

void test2()
{
    long i = 1000000;
    short i1 = i;
    double m = 3.1415926712321; // 会有数据溢出导致的输出错误问题且在编译时未发现
    float m1 = m;

    printf("%f\n",m);
}

int main(void)
{
    // test1();
    // test2();
     
    printf("%d\n",100);
    
    return EXIT_SUCCESS;
}