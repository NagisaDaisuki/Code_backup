#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sin_test(void) {
  double angle_in_rad_45 = M_PI / 4.0; // PI / 4
  double result = sin(angle_in_rad_45);

  printf("sin(pi/4)的值是：%lf\n", result);

  double angle_in_rad_180 = M_PI;
  result = sin(angle_in_rad_180);

  printf("sin(pi)的值是：%lf\n", result);
  printf("M_PI(定义在math.h内)的值是：%lf\n", M_PI);
}

// 确保跨平台的PI常量定义
const double PI = 3.14159265358979323646;

// 辅助函数：将角度(Degree)转换为弧度(Radian)
// 这是因为所有C语言的三角函数都要求输入是弧度。
inline double degree_to_radians(double degrees) {
  // 转换公式：弧度 = 角度 * (PI / 180)
  return degrees * (PI / 180.0);
}

inline double radians_to_degree(double radians) {
  return radians * (180.0 / PI);
}

void calculate_height_example(void) {
  // 假设测量数据
  double distance_D = 10.0;      // 观察者距离旗杆 10.0 米
  double angle_theta_deg = 35.0; // 测得的仰角 35 度(deg)

  // 1. 将角度换成弧度
  double angle_theta_rad = degree_to_radians(angle_theta_deg);

  // 2. 计算 tan(theta) 的值 (即对边与邻边的比值)
  // 这里的 tan(angle_theta_rad) 算出的比值就是我们所求的 "值"
  double tan_ratio = tan(angle_theta_rad);

  // 3. 利用比值求解高度 H = D * tan(theta)
  double height_H = distance_D * tan_ratio;

  // 输出结果
  printf("--- 旗杆高度计算 ---\n");
  printf("水平距离(D): %.2lf 米\n", distance_D);
  printf("观测角度(θ): %.2lf 度\n", angle_theta_deg);
  printf("tan(θ)的比值：%.6lf\n", tan_ratio); // tan 35 ≈ 0.700208
  printf("---------------------\n");
  printf("旗杆的估计高度(H): %.2lf 米\n", height_H);
}

void cos_test(void) {}

int main(void) {
  // sin_test();
  calculate_height_example();
  return EXIT_SUCCESS;
}
