# 🤧使用结构和指针

## 12.1 链表

- **链表(linked_list)** 就是一些包含数据的独立数据结构的集合。链表中的每个节点通过链或指针连接在一起。程序通过指针访问链表中的节点。通常节点是动态分配的，也有由节点数组构建的链表。

## 12.2 单链表

- 在单链表中，每个节点包含一个指向链表下一节点的指针。链表最后一个节点的指针字段的值为`NULL`，提示链表后面不在有其他节点。在找到链表的第一个节点后，指针就可以带你访问剩余的所有节点。为了记住链表的起始位置，可以使用一个**根指针(root pointer)**。根指针指向链表的第一个节点。注意根指针只是一个指针，它不包含任何数据。

~~~C
typedef struct NODE{
  struct NODE *link; // 指向下一个节点的指针
  int         value; // 存储数据的变量 
} Node;
~~~

> 单链表无法从结束位置往前遍历

### 12.2.1 在单链表中插入

~~~C
// 插入到一个有序的单链表。函数的参数是一个指向链表第一个节点的指针以及需要插入的值。

#include <stdlib.h>
#include <stdio.h>
#include "sll_node.h"

#define FALSE 0
#define TRUE  1

int sll_insert(Node *current, int new_value)
{
  Node *previous;
  Node *new;

  // 寻找正确的插入位置，方法是按顺序访问链表，直到到达其值大于或等于新插入值的节点。
  
  while(current->value < new_value)
  {
    previous = current;
    current = current->link;
  }
  // 为新节点分配内存，并把新值存储到新节点中，如果内存分配失败。
  // 函数返回false
  new = (Node*)malloc(sizeof(Node));
  if (new == NULL)
    return FALSE;
  new->value = new_value;

  // 把新节点插入到链表中，并返回true 
  new->link = current;
  previous->link = new; 
  return TRUE;
}
~~~

~~~C
result = sll_insert(root,12); // 假设有一个节点存储15，插入在这个节点前
~~~

- 这个插入函数是**不正确**的，它不能处理插入最后一个节点后的场景(最后一个节点的link为NULL)，也不能处理插入第一个节点前的场景(函数不能访问root，previous未定义)
- 可以将一个指向root的指针作为参数传递给函数。然后使用间接访问，函数不仅可以获得root(指向链表第一个节点的指针，也就是根指针)的值，也可以向它存储一个新的指针值(解决current和previous分开的问题，函数总是可以判断Node\*\*是否满足条件并间接访问root判断值大小是否满足。Node\*\*总是作为当前节点的前一个链接字段。)

~~~C
#include <stdlib.h>
#include <stdio.h>
#include "sll_node.h"

#define FALSE 0
#define TRUE  1

int sll_insert(Node **rootp, int new_value)
{
  Node *current;
  Node *previous;
  Node *new;
  
  // 得到指向第一个节点的指针
  current = *rootp;
  previous = NULL;
  
  // 寻找正确的插入位置，方法是按序访问链表，直到到达一个其值大于或等于新值的节点
  while(current != NULL && current->value < new_value)
  {
    previous = current;
    current = current->link;
  }

  // 为新节点分配内存，并把新值存储到新节点中，如果内存分配失败，
  // 函数返回false
  new = (Node*)malloc(sizeof(Node));
  if (new == NULL)
    return FALSE;
  new->link = current;
  if (previous == NULL)
    *rootp = new;
  else
    previous->link = new;
  return TRUE;
}

int sll_insert_ease(Node **head, int new_value)
{
  Node *new_node;
  
  // current_ptr 现在指向的是一个指针 (head 或 link 字段)
  // 初始时指向调用者的 head 指针变量
  Node **current_ptr = head;
  
  // 1. 寻找插入位置：循环直到指针指向NULL(末尾)或指向的值 >= new_value
  while (*current_ptr != NULL && (*current_ptr)->value < new_value)
    current_ptr = &(*current_ptr)->link;
  
  // 2. 分配新节点
  new_node = (Node*)malloc(sizeof(Node));
  if (new_node == NULL)
    return FALSE;
  new_node->value = new_value;
  
  // 3. 插入：新节点指向 current_ptr 当前指向的那个节点
  new_node->link = *current_ptr;
  
  // 4. 核心：更新current_ptr 指向的指针变量，让它指向新节点
  *current_ptr = new_node; // *current_ptr 其实就是上一个节点的link
  return TRUE;
}
// 书上的优化
int sll_insert(register Node **linkp, int new_value)
{
  register Node *current;
  register Node *new;
  
  while ((current = *linkp) != NULL && current->value < new_value)
    linkp = &current->link;

  new = (Node*)malloc(sizeof(Node));
  if (new == NULL)
    return FALSE;
  new->value = new_value;
  
  new->link = current;
  *linkp = new;
  return TRUE;
}
~~~

## 12.3 双链表

- 单链表的替代方案是双链表。在一个双链表中，每个节点都包含两个指针，指向前一个节点的指针和指向后一个节点的指针。这样就可以以任何方向遍历双链表，甚至可以忽前忽后地在双链表中访问。

~~~C
typedef struct NODE {
  struct NODE   *fwd;
  struct NODE   *bwd;
  int           value;
};
~~~

现在存在两个指针：一个指向链表的第一个节点(*fwd)，另一个指向最后一个节点(*bwd)。如果当前链表为空，这两字段都为`NULL`。

### 12.3.1 在双链表中插入

- `dll_insert`函数接受两个参数：一个指向根节点的指针和一个整型值。
- 先前所编写的单链表插入函数把重复的值也添加到链表中。在有些应用程序中，不插入重复的值可能更为合适。`dll_insert`函数只有当欲插入的值原先不存在于链表中时才将其插入。

考虑四种情况：

1. 新值可能必须插入到链表的中间位置。
2. 新值可能必须插入到链表的起始位置。
3. 新值可能必须插入到链表的结束位置。
4. 新值可能必须既插入到链表的初始位置，又插入到链表的结束位置(即原链表为空)。

~~~C
/*
  把一个值插入到一个双链表，rootp是一个指向根节点的指针，
  value是欲插入的新值
  返回值：如果欲插值原先已存在于链表中，函数返回0；
  如果内存不足导致无法插入，函数返回-1；如果插入成功，函数返回1。
*/
#include <stdlib.h>
#include <stdio.h>
#include "doubly_linked_list_node.h"

int dll_insert(Node *rootp, int value)
{
  Node *this;
  Node *next;
  Node *newnode;
  
  /*
    查看value是否已经存在于链表中，如果是就返回
    否则，为新值创建一个新节点("newnode"将指向它)
    "this"将指向应该在新节点之前的那个节点。
    "next"将指向应该在新节点之前的那个节点。
  */
  for (this = rootp; (next = this->fwd) != NULL; this = next){
    if (next->value == value)
      return 0;
    if (next->value > value)
      break;
  }

  newnode = (Node*)malloc(sizeof(Node));
  if (newnode == NULL)
    return -1;
  newnode->value = value;

  // 把新值添加到链表中
  if (next != NULL)
  {
    // 情况1或2:并非位于链表尾部
    if (this != rootp) // 情况1：并非位于链表起始位置
    {
      newnode->fwd = next;
      this->fwd = newnode;
      newnode->bwd = this;
      next->bwd = newnode;
    }
    else // 情况2：位于链表的起始位置
    {
      newnode->fwd = next;
      rootp->fwd = newnode;
      newnode->bwd = NULL;
      next->bwd = newnode;
    }   
  }
  else
  {
    // 情况3或4:位于链表的尾部
    if (this != rootp) // 情况3：并非位于链表的起始位置
    {
      newnode->fwd = NULL;
      this->fwd = newnode;
      newnode->bwd = this;
      rootp->bwd = newnode;
    }
    else // 情况4：位于链表的起始位置
    {
      newnode->fwd = NULL;
      rootp->fwd = newnode;
      newnode->bwd = NULL;
      rootp->bwd = newnode;
    }
  }
  return 1;
}
~~~

#### 语句提炼(statement factoring)
>
> 上面的双链表在最后判断节点插入位置时各个嵌套的if语句群存在大量的相似之处，可以使用**语句提炼**技巧消除这些重复代码

~~~C
if (x == 3)
{
  i = 1;
  some statement;
  j = 2;
}
else
{
  i = 1;
  some statement different;
  j = 2; 
}
~~~

> 这里不管`x == 3`的值是真是假，语句`i = 1` 和 `j = 2`都将执行。且这两天语句在if条件判断前都不会执行，所以：

~~~C
i = 1; 
if (x == 3)
  some statement;
else 
  some statement different;
j = 2;
~~~

> ***但是如果是对测试的结果有所影响的语句千万不能提炼出来！***

~~~C
/*
  双链表部分代码使用语句提炼
*/
// 把新节点添加到链表中
if(next != NULL)
{
  newnode->fwd = next;
  if (this != rootp)
  {
    this->fwd = newnode;
    newnode->bwd = this;
  }
  else
  {
    rootp->fwd = newnode;
    newnode->bwd = NULL;
  }
  next->bwd = newnode;
}
else
{
  newnode->fwd = NULL;
  if (this != rootp)
  {
    this->fwd = newnode;
    newnode->bwd = this;
  }
  else
  {
    rootp->fwd = newnode;
    newnode->bwd = NULL;
  }
  rootp->bwd = newnode;
}
~~~

第二个简化技巧

~~~C
if (pointer != NULL)
  field = pointer;
else
  field = NULL;
~~~

这段代码的意思是设置一个和pointer相等的变量，如果pointer未指向任何东西，这个变量就设置为NULL。但是：

~~~C
field = pointer;
~~~

这个代码的意思其实和上面的一模一样，也就是第三四种情况的else语句内的`newnode->fwd = NULL`可以写成`newnode->fwd = next`；同理`rootp->fwd = newnode`也可以写成`this->fwd = newnode`。

~~~C
/*
  最终提炼的双链表插入函数
*/
#include <stdio.h>
#include <stdlib.h>
#include "doubly_linked_list_node.h"

int dll_insert(register Node *rootp, int value)
{
  register Node *this;
  register Node *next;
  register Node *newnode;
  
  /*
    查看value是否已经存在于链表中，如果是就返回。
    否则，为新值创建一个新节点("newnode"将指向它)。
    "this"将指向应该在新节点之前的那个节点，
    "next"将指向应该在新节点之后的那个节点。
  */
  for (this = rootp; (next = this->fwd) != NULL; this = next)
  {
    if (next->value == value)
      return 0;
    if (next->value > value)
      break;
  }
  newnode = (Node*)malloc(sizeof(Node));
  if (newnode == NULL)
    return -1;
  newnode->value = value;

  // 把新节点添加到链表中
  newnode->fwd = next;
  this->fwd = newnode;

  //if (this != rootp)
  //  newnode->bwd = this;
  //else
  //  newnode->bwd = NULL;
  newnode->bwd = (this != rootp) ? this : NULL;
  
  //if (next != NULL)
  //  next->bwd = newnode;
  //else
  //  rootp->bwd = newnode;
  (next != NULL ? next : rootp)->bwd = newnode;
  return 1;
}
~~~
