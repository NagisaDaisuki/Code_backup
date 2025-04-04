#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_COLS 20 // 所能处理的最大列号
#define MAX_INPUT 1000 // 每个输入行的最大长度

/*
 * 
 *  程序1.1  
 *  首先读取一串列标号，这些标号成对出现，且以一个负值结尾作为结束标志
 *  剩余的输入行被程序读入并打印
 *  输入行中被选中范围的字符串被提取出来并打印
 *  标号以0开头
 */


int read_column_numbers(int columns[], int max);
void rearrange(char *output, char const *input, int n_columns, int const columns[]);

int main(void)
{
    int n_columns; // 进行处理的列标号
    int columns[MAX_COLS]; // 需要处理的列数
    char input[MAX_INPUT]; // 容纳输入行的数组
    char output[MAX_INPUT]; // 容纳输出行的数组
    
    // 读取该串列标号
    n_columns = read_column_numbers(columns,MAX_COLS);
    
    // 读取、处理和打印剩余行。
    while (gets(input) != NULL)
    {
        printf("Original input: %s\n",input);
        rearrange(output,input,n_columns,columns);
        printf("Rearrange line: %s\n",output);
    }
    return EXIT_SUCCESS;

}

/* 读取列标号，不可超出MAX_COLS指定的最大范围 */
int read_column_numbers(int columns[], int max)
{
    int num = 0;
    int ch;

    // 取得列标号，如果所读取的数字小于0则停止
    while(num < max && scanf("%d",&columns[num]) == 1 && columns[num] >= 0)
        num += 1;
    
    // 确认已经读取的标号为偶数个，因为它们是以对的形式出现的
    if(num % 2 != 0)
    {
        puts("Last column number is not paired.");
        exit(EXIT_FAILURE);
    }
    
    // 丢弃该行中包含最后一个数字的那部分内容 (清空输入缓冲区)
    while ((ch = getchar()) != EOF && ch != '\n');
    return num;
}
