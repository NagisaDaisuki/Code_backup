/*
 *  终端命令分发器
 *
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// # -------------------------------------------------------------
// 1. 定义回调函数的签名（函数指针类型）
// 处理器函数接受一个 char* （参数字符串）>并返回 int （状态码）
// # -------------------------------------------------------------
typedef int (*CommandHandler)(const char *args);

// # -------------------------------------------------------------
// 2. 命令结构体
// # -------------------------------------------------------------
typedef struct {
  const char *command_name;
  CommandHandler handler;
  const char *description;
} CommandEntry;

// 回调函数A： 处理 "echo"命令
int handle_echo(const char *args) {
  if (args && *args)
    printf("Echoing: %s\n", args);
  else {
    fprintf(stdout, "Echo requires arguments.\n");
    return -1;
  }
  return 0;
}

// 回调函数B：处理"info"命令
int handle_info(const char *args) {
  (void)args; // 告诉编译器args 未使用
  fprintf(stdout, "--- Simple Terminal Dispatcher v1.0 ---\n");
  fprintf(stdout, "Type 'help' for command list.\n");
  return 0;
}

// 回调函数C：用于"exit"命令，它将返回一个特殊代码2333443
int handle_exit(const char *args) {
  (void)args;
  return 1; // 返回 1 表示退出主循环
}
// # -------------------------------------------------------------
// 3. 构建命令分发表（函数指针数组）
// # -------------------------------------------------------------
CommandEntry command_table[] = {
    {"echo", handle_echo, "Prints the provided arguments."},
    {"info", handle_info, "Displays application information."},
    {"exit", handle_exit, "Exits the application."},
    {"quit", handle_exit, "Same as exit."},
    // help 的处理放在主循环中
};

#define COMMAND_COUNT (sizeof(command_table) / sizeof(command_table[0]))

// # -------------------------------------------------------------
// 4. 宿主函数：解析和分发逻辑
// # -------------------------------------------------------------

// 查找并执行命令的函数
int dispatch_command(char *input_line) {
  char *command = NULL;
  char *args = NULL;
  const char *delim = " \t\n";
  // 1. 分离命令名和参数

  command = strtok(input_line, delim);
  if (command == NULL)
    return 0; // 忽略空行

  // args 存储命令后的所有内容
  args = strtok(NULL, "\n");

  // 2. 处理特殊命令 "help"
  if (strcmp(command, "help") == 0) {
    fprintf(stdout, "\nAvailable Commands:\n");
    for (size_t i = 0; i < COMMAND_COUNT; i++)
      printf("%-10s - %s\n", command_table[i].command_name,
             command_table[i].description);
    return 0;
  }

  // 3. 遍历命令分发表，查找匹配项
  for (size_t i = 0; i < COMMAND_COUNT; i++)
    if (strcmp(command_table[i].command_name, command) == 0)
      return command_table[i].handler(args);

  printf("Error: Unknown command '%s'. Type 'help' for more informations.\n",
         command);
  return -1;
}

// # -------------------------------------------------------------
// 5. 主函数
// # -------------------------------------------------------------
int main(void) {
  char input_buffer[256];
  int status = 0;

  fprintf(stdout, "Welcome to the C Callback Terminal. Type 'help'.\n");

  while (status == 0) {
    printf("> ");

    // 读取用户输入
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL)
      break; // EOF 或读取失败

    // 分发命令，status 接收回调函数的返回值
    status = dispatch_command(input_buffer);
  }

  printf("Exiting terminal...\n");
  return 0;
}
