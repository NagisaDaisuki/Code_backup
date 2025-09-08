#include <stdio.h>

/**
 * @brief 计算一个字节数据中1的个数（用于奇偶校验）
 * @param data 需要计算1个数的字节数据
 * @return data中1的个数
 */

static int count_set_bits(unsigned char data) {
  int count = 0;
  while (data > 0) {
    data = data & (data - 1);
    count++;
  }
  return count;
}

/**
 * @brief 生成指定数据字节的偶校验位
 * 偶校验：数据中1的个数为偶数时，校验位为0；为奇数时，校验位为1。
 * @param data 需要生成校验位的数据字节 (0-255)
 * @return 生成的偶校验位 (0 或 1)
 */

int generate_parity(unsigned char data) {
  int set_bits_count = count_set_bits(data);

  // 如果1的个数是偶数，校验位为0
  if (set_bits_count % 2 == 0)
    return 0; // 偶数个1，生成偶校验位0
  else
    return 1; // 奇数个1，生成偶校验位1
}

/**
 * @brief 验证接收到的数据和偶校验位是否匹配
 * @param data 接收到的数据字节 (0-255)
 * @param received_parity 接收到的奇偶校验位 (0 或 1)
 * @return 0 表示数据校验通过 (没有检测到错误)，1 表示数据校验失败 (检测到错误)
 */

int verify_parity(unsigned char data, int received_parity) {
  int calculated_parity = generate_parity(data);

  // 如果计算出的校验位与接受到的校验位不同，则表示校验失败
  if (calculated_parity != received_parity)
    return 1; // 校验失败
  else
    return 0; // 校验通过
}

/*
 * @brief 将一个数组设置为0
 *
 * */

void clear_Array(int arrar[], int n_elements) {
  while (n_elements > 0) {
    arrar[--n_elements] = 0;
  }
}

// --- 示例用法 ---
int main(void) {
  unsigned char data1 = 0b00000001; // 一个1 (奇数个)
  unsigned char data2 = 0b00000011; // 俩个1 (偶数个)
  unsigned char data3 = 0b01010101; // 四个1 (偶数个)

  // 测试数据1
  int parity1 = generate_parity(data1);
  printf("Data: 0x%02X (%d), Set Bits: %d, Generated Parity: %d\n", data1,
         data1, count_set_bits(data1), parity1);
  // 模拟接收：假设校验位正确
  printf("Verify Data 1 (correct parity): %s\n",
         verify_parity(data1, parity1) == 0 ? "PASSED" : "FAILED");
  // 模拟接收：假设校验位错误
  printf("Verify Data 1 (incorrect parity): %s\n",
         verify_parity(data1, !parity1) == 0 ? "PASSED" : "FAILED");
  printf("---\n");

  // 测试数据2
  int parity2 = generate_parity(data2);
  printf("Data: 0x%02X (%d), Set Bits: %d, Generated Parity: %d\n", data2,
         data2, count_set_bits(data2), parity2);
  // 模拟接收：假设校验位正确
  printf("Verify Data 2 (correct parity): %s\n",
         verify_parity(data2, parity2) == 0 ? "PASSED" : "FAILED");
  // 模拟接收：假设校验位错误
  printf("Verify Data 2 (incorrect parity): %s\n",
         verify_parity(data2, !parity2) == 0 ? "PASSED" : "FAILED");
  printf("---\n");

  // 测试数据3
  int parity3 = generate_parity(data3);
  printf("Data: 0x%02X (%d), Set Bits: %d, Generated Parity: %d\n", data3,
         data3, count_set_bits(data3), parity3);
  // 模拟接收：假设校验位正确
  printf("Verify Data 3 (correct parity): %s\n",
         verify_parity(data3, parity3) == 0 ? "PASSED" : "FAILED");
  // 模拟接收：假设校验位错误
  printf("Verify Data 3 (incorrect parity): %s\n",
         verify_parity(data3, !parity3) == 0 ? "PASSED" : "FAILED");
  printf("---\n");

  return 0;
}
