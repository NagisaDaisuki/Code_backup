#include "inventor.h"
#include <stdlib.h>

void discard_inventory_record(Inverc *record) {
  // 删除记录中的变体记录
  switch (record->type) {
  case SUBASSY:
    free(record->info.subassy->part);
    free(record->info.subassy);
    break;
  case PART:
    free(record->info.part);
    break;
  }

  // 删除记录的主体部分
  free(record);
}
/*
 *  if(record->type == SUBASSY)
 *    free(record->info.subassy->part);
 *  free(record->info.part);
 *  free(record);
 * */
