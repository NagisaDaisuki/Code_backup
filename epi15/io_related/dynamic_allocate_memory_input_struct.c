#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1. 定义结构体
typedef struct {
  int id;
  char name[20];
  float salary;
} Employee;

// 定义初始容量和增长因子
#define INITIAL_CAPACITY 5
#define GROW_FACTOR 2

/*
 *  @brief 动态地从标准输入读取 Employee 结构体数组
 *  @param count 指向整型的指针， 用于存储最终读取的元素的数量
 *  @return Employee* 指向动态分配的结构体数组。
 * */
Employee *read_employees_from_stdin(size_t *count);

// 辅助函数：打印结构体数组
void print_employee(const Employee arr[], size_t size);

int main(void) {
  size_t num_read = 0;

  // 调用函数读取数据
  Employee *staff = read_employees_from_stdin(&num_read);

  // 打印结果
  print_employee(staff, num_read);

  // 释放动态分配的内存
  free(staff);

  return EXIT_SUCCESS;
}

Employee *read_employees_from_stdin(size_t *count) {
  Employee *employees = NULL;
  size_t capacity = 0;
  size_t current_count = 0;
  char buffer[256]; // 用于读取可能的多余行内容

  printf("请输入员工数据，每行格式为：ID 姓名 薪水 (如：101 John 60000.0)\n");
  printf("输入 'quit' 或遇到 EOF 结束输入。\n");
  printf("-------------------------------------\n");

  // 动态分配初始内存
  capacity = INITIAL_CAPACITY;
  employees = (Employee *)malloc(capacity * sizeof(Employee));

  if (employees == NULL) {
    perror("Initial memory allocation failed");
    exit(EXIT_FAILURE);
  }

  // 循环从 stdin 读取数据
  while (1) {
    Employee temp_employee;
    int result;

    printf("员工 %zu > ", current_count + 1);

    // 使用 scanf 读取三个成员数据
    result = scanf("%d %19s %f", &temp_employee.id, temp_employee.name,
                   &temp_employee.salary);

    // 检查输入是否为 'quit'
    if (result == 0) {
      // 如果 scanf 无法匹配 %d, 可能是输入了 非数字 字符
      if (scanf("%s", buffer) == 1 && strcmp(buffer, "quit") == 0) {
        break; // 遇到quit 退出循环
      }
      // 否则，清空输入缓冲区并提示
      fprintf(stderr, "错误输入格式，请重新输入。\n");
      // 清空当前输入行剩余内容
      while (getchar() != '\n' && !feof(stdin))
        ;
      continue;
    }

    // 检查是否到达文件末尾或遇到输入错误
    if (result == EOF)
      break;

    // 检查是否需要 重新分配内存（扩容）
    if (current_count >= capacity) {
      capacity *= GROW_FACTOR; // 自乘扩容因子
      Employee *new_ptr =
          (Employee *)realloc(employees, capacity * sizeof(Employee));
      if (new_ptr == NULL) {
        perror("Memory reallocation failed.");
        // 虽然失败，但我们返回已经成功读取的部分数据
        *count = current_count;
        return employees;
      }
      employees = new_ptr;
    }

    // 赋值给结构体数组
    employees[current_count] = temp_employee;
    current_count++;
  }

  // 设置最终读取的元素数量
  *count = current_count;

  // 缩小内存到实际所需大小(可选但推荐)
  Employee *final_ptr =
      (Employee *)realloc(employees, current_count * sizeof(Employee));
  if (final_ptr != NULL)
    return final_ptr;

  return employees;
}

void print_employee(const Employee arr[], size_t size) {
  if (size == 0) {
    printf("数组为空");
    return;
  }
  printf("\n--- 读取到的员工数据 ---\n");
  for (size_t i = 0; i < size; i++) {
    printf("Index %zu: ID: %d, Name: %-19s, Salary: %.2f\n", i, arr[i].id,
           arr[i].name, arr[i].salary);
  }
  printf("-------------------------------------\n");
}
