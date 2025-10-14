// 模拟一个几何图形记录
// 这种模式结合了联合体的内存效率（只分配最大成员所需的空间）
// 和结构体的类型安全（通过标签字段知道当前数据的实际类型），
// 完美地模拟了 Pascal 中的变体记录。

#include <stdio.h>
#include <stdlib.h>

// 1. 定义标签
typedef enum { SHAPE_CIRCLE, SHAPE_RECTANGLE } ShapeType;

// 2. 定义变体记录 (Struct + Union)
typedef struct {
  ShapeType type; // 标签字段：指示联合体的当前类型

  // 联合体：存储所有可能的数据，共享内存
  union {
    // 圆形数据
    struct {
      double radius;
    } circle;
    // 矩形数据
    struct {
      double width;
      double height;
    } rectangle;
  } data;
} ShapeRecord;

void print_shape(ShapeRecord *shape);

int main(int argc, char *argv[]) {
  ShapeRecord my_circle;
  ShapeRecord my_rectangle;

  // 1. 设置圆形记录
  my_circle.type = SHAPE_CIRCLE;
  my_circle.data.circle.radius = 10.0;

  // 2. 设置矩形记录
  my_rectangle.type = SHAPE_RECTANGLE;
  my_rectangle.data.rectangle.width = 5.0;
  my_rectangle.data.rectangle.height = 8.0;

  // 打印并安全地访问数据
  print_shape(&my_circle);
  print_shape(&my_rectangle);

  return EXIT_SUCCESS;
}

void print_shape(ShapeRecord *shape) {
  // 检查标签字段，确定数据的真实类型
  switch (shape->type) {
  case SHAPE_CIRCLE:
    printf("图形类型：圆形\n");
    printf("  半径：%.2f\n", shape->data.circle.radius);
    printf("  面积：%.2f\n",
           3.14159 * shape->data.circle.radius * shape->data.circle.radius);
    break;
  case SHAPE_RECTANGLE:
    printf("图形类型：矩形\n");
    printf("  宽度：%.2f\n", shape->data.rectangle.width);
    printf("  高度：%.2f\n", shape->data.rectangle.height);
    printf("  面积：%.2f\n",
           shape->data.rectangle.width * shape->data.rectangle.height);
    break;
  default:
    printf("未知图形类型。\n");
    break;
  }
}
