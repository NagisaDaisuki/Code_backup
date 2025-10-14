
# 链表代码实现详解

本文档详细解释了 `singly_linked_list_c.c`, `doubly_linked_list_c.c`, `singly_linked_list_cpp.hpp`, 和 `doubly_linked_list_cpp.hpp` 四个文件中的代码实现。

---

## 1. C 语言安全单链表 (`singly_linked_list_c.c`) 详解

此文件使用 C 语言的结构体和指针手动管理内存，实现了基础但安全的单链表。

### 1.1. 头文件包含
```c
#include <stdio.h>   // 用于标准输入输出，如 printf, perror
#include <stdlib.h>  // 用于动态内存分配(malloc, free)和 size_t 类型
```
- `stdio.h`: 主要用于 `printf` 函数打印链表内容，以及 `perror` 函数在内存分配失败时打印系统错误信息。
- `stdlib.h`: 这是 C 语言内存管理的核心。`malloc` 用于为新节点和链表本身分配内存，`free` 用于释放它们。

### 1.2. 核心数据结构

```c
// 节点结构体
typedef struct SinglyNode {
    int data;
    struct SinglyNode* next;
} SinglyNode;

// 链表结构体，包含头指针和大小
typedef struct SinglyLinkedList {
    SinglyNode* head;
    size_t size;
} SinglyLinkedList;
```
- **`SinglyNode`**: 这是链表的基本组成单元。
    - `data`: 存储节点的数据，这里为 `int` 类型。
    - `next`: 一个指向下一个 `SinglyNode` 的指针。如果这是链表的最后一个节点，`next` 将为 `NULL`。
- **`SinglyLinkedList`**: 这是链表的“管理器”或“句柄”。
    - `head`: 一个指向链表第一个节点的指针。如果链表为空，`head` 为 `NULL`。
    - `size`: 一个 `size_t` 类型的无符号整数，用于实时追踪链表中的节点数量。这使得获取链表大小的操作时间复杂度为 O(1)，无需遍历整个链表。

### 1.3. 函数实现详解

#### `create_singly_list()`
```c
SinglyLinkedList* create_singly_list() {
    SinglyLinkedList* list = (SinglyLinkedList*)malloc(sizeof(SinglyLinkedList));
    if (!list) { // 安全性：检查内存分配是否成功
        perror("Failed to allocate memory for list");
        return NULL;
    }
    list->head = NULL;
    list->size = 0;
    return list;
}
```
- **作用**: 创建并初始化一个空的链表管理器。
- **详解**:
    1. 使用 `malloc` 为 `SinglyLinkedList` 结构体分配内存。
    2. **[安全关键点]** 检查 `malloc` 的返回值。如果系统内存不足，`malloc` 会返回 `NULL`。代码检查 `!list` (即 `list == NULL`)，如果为真，则使用 `perror` 打印详细的错误信息，并向调用者返回 `NULL`，明确表示创建失败。这可以防止调用者使用一个无效的指针，从而避免程序崩溃。
    3. 将 `head` 初始化为 `NULL`，表示链表当前没有任何节点。
    4. 将 `size` 初始化为 `0`。

#### `destroy_singly_list()`
```c
void destroy_singly_list(SinglyLinkedList** list_ptr) {
    if (!list_ptr || !*list_ptr) {
        return;
    }
    // ... 循环释放节点 ...
    free(list);
    *list_ptr = NULL; // 安全性：防止悬垂指针
}
```
- **作用**: 彻底销毁一个链表，释放其占用的所有内存，防止内存泄漏。
- **详解**:
    1. **[安全关键点]** 函数参数为 `SinglyLinkedList** list_ptr` (指向指针的指针)。这允许函数修改调用者作用域中的原始指针。
    2. `if (!list_ptr || !*list_ptr)` 检查传入的指针本身和它指向的指针是否有效，避免对 `NULL` 解引用。
    3. 循环遍历链表，`current` 指向当前要释放的节点。
    4. **[安全关键点]** 在循环中，`next_node = current->next;` 这一步至关重要。它在释放当前节点之前，先把下一个节点的地址保存起来。否则，一旦 `free(current)`，就再也找不到后续的链表部分了。
    5. `free(current);` 释放当前节点的内存。
    6. `current = next_node;` 移动到下一个节点继续循环。
    7. 循环结束后，所有节点都被释放。然后 `free(list);` 释放链表管理器结构体本身的内存。
    8. **[安全关键点]** `*list_ptr = NULL;` 将调用者原始的指针变量设置为 `NULL`。这可以防止调用者在销毁链表后，不小心再次使用这个（现在已经无效的）指针，即“悬垂指针”。

#### `singly_insert_front()`
- **作用**: 在链表头部添加一个新节点。
- **详解**:
    1. 检查 `list` 指针是否有效。
    2. 为新节点 `SinglyNode` 分配内存，并进行 `NULL` 检查。
    3. `new_node->data = data;` 设置新节点的数据。
    4. `new_node->next = list->head;` 将新节点的 `next` 指针指向当前链表的头节点。
    5. `list->head = new_node;` 更新链表的头指针，使其指向这个新创建的节点。
    6. `list->size++;` 链表大小加一。

#### `singly_delete_by_value()`
- **作用**: 查找并删除第一个值为 `data` 的节点。
- **详解**:
    1. 检查链表是否有效或为空。
    2. 使用 `current` 和 `prev` 两个指针遍历链表。`current` 指向当前检查的节点，`prev` 指向其前一个节点。
    3. **处理头节点**: 如果要删除的是头节点 (`prev == NULL`)，则直接将 `list->head` 更新为 `current->next`。
    4. **处理中间或尾部节点**: 如果 `prev` 不为 `NULL`，则将前一个节点的 `next` 指针“跳过”当前节点，直接指向当前节点的下一个节点 (`prev->next = current->next;`)。
    5. `free(current);` 释放找到的节点的内存。
    6. `list->size--;` 链表大小减一。

---

## 2. C 语言安全双链表 (`doubly_linked_list_c.c`) 详解

双链表在单链表的基础上为每个节点增加了一个指向上一个节点的 `prev` 指针，这使得双向遍历和尾部操作更高效。

### 2.1. 核心数据结构
```c
typedef struct DoublyNode {
    int data;
    struct DoublyNode* next;
    struct DoublyNode* prev; // 新增：指向上一个节点的指针
} DoublyNode;

typedef struct DoublyLinkedList {
    DoublyNode* head;
    DoublyNode* tail; // 新增：指向尾节点的指针
    size_t size;
} DoublyLinkedList;
```
- **`DoublyNode`**: `prev` 指针是与单链表节点唯一的不同。
- **`DoublyLinkedList`**: 增加了 `tail` 指针，它直接指向链表的最后一个节点。这使得在链表尾部插入节点的时间复杂度从 O(n) 降为 O(1)。

### 2.2. 函数实现详解

`create_doubly_list()` 和 `destroy_doubly_list()` 的逻辑与单链表版本基本相同。

#### `doubly_insert_back()`
- **作用**: 在链表尾部高效地插入一个新节点。
- **详解**:
    1. 分配新节点并检查内存。
    2. **处理空链表**: 如果 `list->tail` 为 `NULL`，说明链表是空的。此时，新节点既是头节点也是尾节点 (`list->head = new_node; list->tail = new_node;`)。
    3. **处理非空链表**:
        - `new_node->prev = list->tail;` 将新节点的 `prev` 指向当前的尾节点。
        - `list->tail->next = new_node;` 将当前尾节点的 `next` 指向新节点。
        - `list->tail = new_node;` 更新链表的 `tail` 指针，使其指向这个新节点。
    4. `list->size++;`

#### `doubly_delete_by_value()`
- **作用**: 查找并删除节点，需要同时处理 `next` 和 `prev` 指针。
- **详解**:
    1. 遍历找到要删除的 `current` 节点，逻辑同单链表。
    2. **[安全关键点]** 更新指针时需要考虑所有情况：
        - **更新前一个节点**: `if (current->prev != NULL)`，说明 `current` 不是头节点，那么它前一个节点的 `next` 指针需要更新为 `current->next`。否则，如果 `current` 是头节点，则需要更新 `list->head`。
        - **更新后一个节点**: `if (current->next != NULL)`，说明 `current` 不是尾节点，那么它后一个节点的 `prev` 指针需要更新为 `current->prev`。否则，如果 `current` 是尾节点，则需要更新 `list->tail`。
    3. `free(current);` 释放节点。
    4. `list->size--;`

---

## 3. C++ 模板安全单链表 (`singly_linked_list_cpp.hpp`) 详解

此文件使用 C++ 的类、模板和 RAII 特性，提供了更安全、更通用的单链表实现。

### 3.1. 核心设计
```c++
template <typename T>
class SinglyLinkedList {
private:
    struct Node { /* ... */ };
    Node* m_head = nullptr;
    size_t m_size = 0;
public:
    // ...
};
```
- **`template <typename T>`**: 使链表可以存储任何类型的数据（`int`, `double`, `std::string` 等），在编译时提供类型安全检查。
- **`class SinglyLinkedList`**: 将数据和操作封装在一起。
- **`private: struct Node`**: `Node` 结构体被定义在 `private` 区域，这是一个实现细节，外部用户不需要也无法直接访问 `Node`，增强了封装性。
- **`m_head`, `m_size`**: 成员变量（`m_` 前缀是常见的私有成员命名约定），`nullptr` 是 C++11 引入的类型安全的空指针。

### 3.2. RAII 和析构函数
```c++
~SinglyLinkedList() {
    while (m_head) {
        Node* temp = m_head;
        m_head = m_head->next;
        delete temp;
    }
}
```
- **RAII (Resource Acquisition Is Initialization)**: 资源获取即初始化。在这里，资源是动态分配的 `Node`。
- **`~SinglyLinkedList()` (析构函数)**:
    - **[C++ 安全核心]** 当一个 `SinglyLinkedList` 对象生命周期结束时（例如，离开其作用域），析构函数会被 **自动调用**。
    - 它的逻辑和 C 版本的 `destroy_list` 类似，遍历并 `delete` 每个节点。
    - **优势**: 用户不再需要手动调用 `destroy` 函数。只要正确创建了对象，C++ 保证在对象销毁时其资源会被释放。这从根本上杜绝了忘记释放内存而导致的内存泄漏。

### 3.3. The Rule of Five (五法则)

这是为了防止因编译器默认生成的函数（会进行浅拷贝）而导致严重错误的五位一体。浅拷贝一个链表意味着两个 `SinglyLinkedList` 对象内部的 `m_head` 指针指向了同一块内存。

1.  **拷贝构造函数 `SinglyLinkedList(const SinglyLinkedList& other)`**:
    - **作用**: 当用一个已存在的链表初始化一个新链表时调用（`SinglyLinkedList list2 = list1;`）。
    - **详解**: 它执行 **深拷贝**。遍历 `other` 链表的每一个节点，并为当前链表 (`this`) 创建一个全新的、数据相同的 `Node`。这样，两个链表就拥有了各自独立的内存空间。

2.  **拷贝赋值运算符 `operator=(const SinglyLinkedList& other)`**:
    - **作用**: 当将一个已存在的链表赋值给另一个已存在的链表时调用（`list2 = list1;`）。
    - **详解**: 使用了 **Copy-and-Swap** 写法。它通过调用拷贝构造函数创建一个 `other` 的临时副本 `temp`，然后用 `swap` 函数交换 `*this` 和 `temp` 的内部数据。当 `operator=` 函数结束时，`temp` 被销毁，其析构函数会释放 `*this` 的旧数据。这种方法简洁、异常安全，并能自动处理自我赋值 (`list1 = list1;`) 的情况。

3.  **移动构造函数 `SinglyLinkedList(SinglyLinkedList&& other) noexcept`**:
    - **作用**: 当用一个临时对象（右值）初始化新链表时调用。例如 `SinglyLinkedList list2 = create_temp_list();`。
    - **详解**: 它执行 **资源窃取**。它不复制任何节点，而是直接将 `other` 的 `m_head` 和 `m_size` "偷"过来，然后将 `other` 的成员设为 `nullptr` 和 `0`。这是一个 O(1) 的高效操作，避免了不必要的深拷贝。`noexcept` 关键字向编译器承诺此函数不会抛出异常。

4.  **移动赋值运算符 `operator=(SinglyLinkedList&& other) noexcept`**:
    - **作用**: 当将一个临时对象赋值给一个已存在的链表时调用。
    - **详解**: 类似于移动构造，但它首先要调用析构函数释放自己现有的资源，然后再从 `other` 手中窃取资源。

5.  **析构函数 `~SinglyLinkedList()`**: 如上所述，负责释放资源。

### 3.4. 公共接口
- **`push_front(const T& data)`**:
    - **[安全关键点]** `new (std::nothrow) Node{...}`: `std::nothrow` 告诉 `new` 在内存分配失败时不抛出 `std::bad_alloc` 异常，而是返回 `nullptr`。这使得错误处理方式更像 C 语言的 `malloc`，可以通过检查返回值来判断是否成功。
- **`pop_front()`**: 删除头节点，并 `delete` 释放其内存。
- **`size()`, `empty()`, `print()`**: 提供链表信息和打印功能的辅助函数。`const` 关键字表示这些函数不会修改链表的状态。

---

## 4. C++ 模板安全双链表 (`doubly_linked_list_cpp.hpp`) 详解

此文件在 C++ 单链表的基础上增加了 `m_tail` 指针和 `prev` 节点指针。

### 4.1. 核心设计
- 增加了 `m_tail` 成员变量，用于 O(1) 复杂度的尾部操作。
- `Node` 结构体中增加了 `prev` 指针。

### 4.2. RAII 和五法则
- **析构函数**: 逻辑与单链表版本完全相同，从头开始 `delete` 即可。
- **拷贝构造函数**: 为了方便，这里复用了 `push_back` 函数来逐个复制节点，实现深拷贝。
- **拷贝/移动赋值和移动构造**: 逻辑与单链表版本类似，只是需要额外处理 `m_tail` 指针的交换和窃取。

### 4.3. 公共接口
- **`push_back(const T& data)`**:
    - **详解**: 高效地在尾部添加节点。
    1.  分配新节点并检查。
    2.  如果链表为空 (`!m_tail`)，新节点既是头也是尾。
    3.  如果非空，则更新旧尾节点的 `next` 和新节点的 `prev`，然后更新 `m_tail` 指针。
- **`pop_back()`**:
    - **详解**: 高效地删除尾节点。
    1.  如果链表为空，直接返回。
    2.  `m_tail` 指针前移 (`m_tail = m_tail->prev;`)。
    3.  如果 `m_tail` 移动后不为 `nullptr`，则将其 `next` 设为 `nullptr`。
    4.  如果 `m_tail` 移动后为 `nullptr`，说明链表只有一个元素，现在变空了，所以也要把 `m_head` 设为 `nullptr`。
    5.  `delete` 旧的尾节点。

