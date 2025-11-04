#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1. 定义一个存储数据的结构体
typedef struct {
  int id;
  char name[20];
  float salary;
} Employee;

// 辅助函数：打印结构体内容
void print_employee(const Employee *e) // const *类型 指向常量的指针
{
  fprintf(stdout, "ID: %d, Name: %-20s, Salary: %.2f\n", e->id, e->name,
          e->salary);
}

// 定义文件名
#define DATA_FILE "employees.bin"

int main(void) {
  // 2. 准备数据：一个结构体数组
  Employee staff_data[] = {{101, "Alice Johnson", 60000.00f},
                           {102, "Bob Smith", 75000.50f},
                           {103, "Charlie Brown", 50000.25f}};
  const size_t num_employees = sizeof(staff_data) / sizeof(Employee);

  // ------------------------------------------------------------------------
  // 第一步：使用 fwrite 将结构体数组写入文件（输出流）
  // ------------------------------------------------------------------------

  FILE *output_file = fopen(DATA_FILE, "wb"); // write binary
  if (output_file == NULL) {
    perror("Error opening output file");
    return EXIT_FAILURE;
  }

  // fwrite(ptr, size, count, stream)
  // ptr: 要写入的数据块的起始地址
  // size: 每个数据块的大小（这里是 Employee 结构体的大小）
  // count: 要写入的数据块的数量（这里是数组元素的数量）
  // stream: 文件流指针

  size_t written_count =
      fwrite(staff_data, sizeof(Employee), num_employees, output_file);

  if (written_count == num_employees) {
    fprintf(stdout, "成功将 %zu 个 Employee 记录写入文件：%s\n", written_count,
            DATA_FILE);
  } else {
    fprintf(stderr, "警告：写入失败或部分失败。\n");
  }

  fclose(output_file);

  // ------------------------------------------------------------------------
  // 第二步：使用 fread 从文件中读取结构体数组（输入流）
  // ------------------------------------------------------------------------

  FILE *input_file = fopen(DATA_FILE, "rb"); // read binary
  if (input_file == NULL) {
    perror("Error opening input file for reading");
    return EXIT_FAILURE;
  }

  // 3. 准备接收数据的缓冲区（创建一个新的数组来存储读取的数据）
  Employee read_data[num_employees];

  fprintf(stdout, "\n从文件读取数据并输出到标准输出(stdout)：\n");
  printf("--------------------------------------------------------\n");

  // fread(ptr, size, count, stream)
  // ptr: 存储读取数据的内存地址
  // size: 每个数据块的大小（这里是 Employee 结构体的大小）
  // count: 尝试读取的数据块的数量
  // stream: 文件流指针
  size_t read_count =
      fread(read_data, sizeof(Employee), num_employees, input_file);

  if (read_count == num_employees) {
    printf("成功读取 %zu 个 Employee 记录。\n", read_count);

    // 4. 将读取到的结构体数组元素输出到标准输出
    for (size_t i = 0; i < read_count; i++) {
      printf("Record %zu: ", i + 1);
      print_employee(&read_data[i]);
    }
  } else {
    fprintf(stderr, "警告：尝试读取 %zu 个记录，但只读取了 %zu 个。\n",
            num_employees, read_count);
  }

  fclose(input_file);

  // 清理创建的文件（可选）
  // remove(DATA_FILE);

  return EXIT_SUCCESS;
}
