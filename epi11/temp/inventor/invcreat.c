/*
 *  创建SUBASSEMBLY装配件存货记录的函数
 * */
#include "inventor.h"
#include <stdio.h>
#include <stdlib.h>

Inverc *create_subassy_record(int n_parts) {
  Inverc *new_rec;

  // 试图为 Inverc 部分分配内存
  new_rec = malloc(sizeof(Inverc));
  if (new_rec != NULL) {
    // 内存分配成功，现在存储SUBASSYINFO部分
    new_rec->info.subassy = malloc(sizeof(Subassyinfo));
    if (new_rec->info.subassy != NULL) {
      // 为零件获取一个足够大的数组
      new_rec->info.subassy->part = malloc(n_parts * sizeof(Subassyinfo));
      if (new_rec->info.subassy->part != NULL) {
        // 获取内存，填充我们已知道的字段，然后返回
        new_rec->type = SUBASSY;
        new_rec->info.subassy->n_parts = n_parts;
        return new_rec;
      }

      // 内存已用完，释放我们原先分配的内存。
      free(new_rec->info.subassy);
    }
    free(new_rec);
  }
  return NULL;
}

Inverc *create_part_record(int cost, int supplier) {
  Inverc *new_rec;
  new_rec = malloc(sizeof(Inverc));
  if (new_rec != NULL) {
    new_rec->info.part = malloc(sizeof(Partinfo));
    if (new_rec->info.part != NULL) {
      new_rec->info.part->cost = cost;
      new_rec->info.part->supplier = supplier;
      return new_rec;
    }
    free(new_rec->info.part);
  }
  free(new_rec);
}
