#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if 0
    // 编写一个 标准输出hello world!
    printf("hello world!\n");
#endif

int main(void)
{
    // 编写一个程序，从标准输入读取几行输入，每行输入都要打印在标准输出上，前面要加上行号
    // 试图让程序能够处理的输入行的长度没有限制(动态数组分配空间)
    int ch;
    int line;
    int at_beginning;
    
    line = 0;
    at_beginning = 1;
    
    // 读取字符并逐个处理
    while((ch = getchar()) != EOF)
    {
        
        // 如果位于一行的起始位置，打印行号
        if(at_beginning == 1)
        {
            at_beginning = 0;
            line += 1;
            printf("%d ",line);
        }
        // 打印字符，并对行尾进行检查
        putchar(ch);
        if(ch == '\n')
            at_beginning = 1;
    }
    return EXIT_SUCCESS;
}