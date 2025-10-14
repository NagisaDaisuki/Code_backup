#include <stdio.h>
#include <stdlib.h>

// --- C语言: 安全的双链表实现 ---

// 节点结构体
typedef struct DoublyNode {
  int data;
  struct DoublyNode *next;
  struct DoublyNode *prev;
} DoublyNode;

// 链表结构体，包含头、尾指针和大小
typedef struct DoublyLinkedList {
  DoublyNode *head;
  DoublyNode *tail;
  size_t size;
} DoublyLinkedList;

/*
 *  @brief 创建并初始化一个新的空链表
 *  @return 指向新链表的指针；如果内存分配失败则返回 NULL
 * */
DoublyLinkedList *create_doubly_list() {
  DoublyLinkedList *list = (DoublyLinkedList *)malloc(sizeof(DoublyLinkedList));
  if (!list) {
    perror("Failed to allocate memory for list.");
    return NULL;
  }
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
  return list;
}

/*
 *  @brief 安全地销毁整个链表，释放所有节点和链表本身的内存
 *  @param list_ptr 指向要销毁的链表的指针的指针，操作后会将其设置为NULL
 * */
void destroy_doubly_list(DoublyLinkedList **list_ptr) {
  if (!list_ptr || !*list_ptr)
    return; // 安全检查
  DoublyLinkedList *list = *list_ptr;
  DoublyNode *current = list->head;
  DoublyNode *next_node;
  while (current != NULL) {
    next_node = current->next;
    free(current);
    current = current->next;
  }
  free(list);
  *list_ptr = NULL; // In order to avoid dangling pointer
}

/*
 *  @brief 在链表尾部插入一个新节点
 *  @param list 指向链表的指针
 *  @param data 要插入的数据
 *  @return 成功返回 1，失败返回 0
 * */
int doubly_insert_back(DoublyLinkedList *list, int data) {
  if (!list)
    return 0; // 安全检查
  DoublyNode *new_node = (DoublyNode *)malloc(sizeof(DoublyNode));
  if (!new_node) {
    perror("Failed to allocate memory for new node");
  }
}
