<h3><center>语句</center></h3>

----

#### 4.1 空语句
`;`空语句本身不执行任何任务

#### 4.2 表达式语句
只要在表达式后面加上一个分号，就可以把表达式转变为语句
~~~
x = y + 3;
ch = getchar();
~~~
是表达式语句

> 类似于printf函数这类没有返回值的函数在标准输出中输出内容的作用称为副作用(side effect)

#### 4.3 代码块
- 一对花括号之内的可选的声明和语句列表
~~~
{
    declarations
    statements
}
~~~

#### 4.4 if语句
- C 并不具备布尔类型而是用整型来替代
- else语句从属于最靠近它的不完整的if语句

#### 4.5 while语句
..............

#### 4.9 goto语句
`goto 语句标签;`
1. 资源清理和错误处理(C中没有异常机制)
~~~
#include <stdio.h>
#include <stdlib.h>

int func()
{
    int *p = malloc(100);
    if(!p) goto fail;
    
    FILE *fp = fopen("file.txt","r");
    if(!fp) goto cleanup;
    
    // 正常执行逻辑
    fclose(fp);
    free(p);
    return 0;
cleanup:
    free(p);
fail:
    return -1;
}
~~~
2.  从多层嵌套中快速跳出
~~~
for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
        if (i + j == 6) goto done;
    }
}
done:
printf("Exited nested loops\n");
~~~

goto 是 C 的原始控制流工具，能跳到代码中的任意标签；

不推荐滥用，但在特定情况下（如资源清理、退出多层嵌套）是非常有效的；

如果你在写**可读性强、模块化的现代代码**，能不用就尽量不用；

如果你在写**驱动、内核、嵌入式或老式 C 代码**，合理使用是完全 OK 的。

#### 4.10 总结
