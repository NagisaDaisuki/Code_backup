#pragma once
#include <iostream>
#include <new>      // 用于 std::nothrow
#include <utility>  // 用于 std::swap

// --- C++ 模板：安全且现代的双链表实现 ---

template <typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node* next = nullptr;
        Node* prev = nullptr;
    };

    Node* m_head = nullptr;
    Node* m_tail = nullptr;
    size_t m_size = 0;

public:
    // 默认构造函数
    DoublyLinkedList() = default;

    // --- RAII: 析构函数确保内存被释放 ---
    ~DoublyLinkedList() {
        while (m_head) {
            Node* temp = m_head;
            m_head = m_head->next;
            delete temp;
        }
    }

    // --- Rule of Five: 防止浅复制和悬坐指针 ---

    // 1. 复制构造函数 (深复制)
    DoublyLinkedList(const DoublyLinkedList& other) {
        if (!other.m_head) {
            return;
        }
        try {
            for (Node* current = other.m_head; current; current = current->next) {
                push_back(current->data); // 复用 push_back 来实现 
            }
        } catch (const std::bad_alloc&) {
            std::cerr << "Failed to allocate memory during copy." << std::endl;
            this->~DoublyLinkedList();
            throw;
        }
    }

    // 2. 复制赋值运算符 (Copy-and-Swap Idiom)
    DoublyLinkedList& operator=(const DoublyLinkedList& other) {
        if (this != &other) {
            DoublyLinkedList temp(other);
            swap(*this, temp);
        }
        return *this;
    }

    // 3. 移动构造函数
    DoublyLinkedList(DoublyLinkedList&& other) noexcept
        : m_head(other.m_head), m_tail(other.m_tail), m_size(other.m_size) {
        other.m_head = nullptr;
        other.m_tail = nullptr;
        other.m_size = 0;
    }

    // 4. 移动赋值运算符
    DoublyLinkedList& operator=(DoublyLinkedList&& other) noexcept {
        if (this != &other) {
            this->~DoublyLinkedList();
            m_head = other.m_head;
            m_tail = other.m_tail;
            m_size = other.m_size;
            other.m_head = nullptr;
            other.m_tail = nullptr;
            other.m_size = 0;
        }
        return *this;
    }

    // 友元函数用于 swap
    friend void swap(DoublyLinkedList& first, DoublyLinkedList& second) noexcept {
        using std::swap;
        swap(first.m_head, second.m_head);
        swap(first.m_tail, second.m_tail);
        swap(first.m_size, second.m_size);
    }

    // --- 公共接口 ---

    bool push_back(const T& data) {
        Node* new_node = new (std::nothrow) Node{data};
        if (!new_node) {
            std::cerr << "Failed to allocate memory for new node." << std::endl;
            return false;
        }
        if (!m_tail) { // 列表为空 
            m_head = m_tail = new_node;
        } else {
            m_tail->next = new_node;
            new_node->prev = m_tail;
            m_tail = new_node;
        }
        m_size++;
        return true;
    }

    bool pop_back() {
        if (!m_tail) {
            return false; // 列表为空
        }
        Node* old_tail = m_tail;
        m_tail = m_tail->prev;
        if (m_tail) {
            m_tail->next = nullptr;
        } else { // 列表中只有一个元素 
            m_head = nullptr;
        }
        delete old_tail;
        m_size--;
        return true;
    }

    size_t size() const { return m_size; }
    bool empty() const { return m_size == 0; }

    void print() const {
        std::cout << "List (size " << m_size << "): HEAD <-> ";
        for (Node* current = m_head; current; current = current->next) {
            std::cout << current->data << " <-> ";
        }
        std::cout << "TAIL" << std::endl;
    }
};

// --- 示例 main 函数 ---
// 要运行此示例，请创建造一个 .cpp 文件，包含此头文件并定义 main 函数
/*
#include "doubly_linked_list_cpp.hpp"
#include <string>

int main() {
    std::cout << "--- C++ Doubly Linked List Demo ---" << std::endl;
    DoublyLinkedList<int> list1;
    list1.push_back(10);
    list1.push_back(20);
    list1.push_back(30);
    std::cout << "list1: ";
    list1.print();

    std::cout << "\nPopping back of list1..." << std::endl;
    list1.pop_back();
    std::cout << "list1: ";
    list1.print();

    std::cout << "\nCreating list2 as a copy of list1..." << std::endl;
    DoublyLinkedList<int> list2 = list1; // 复制构造
    list2.push_back(99);
    std::cout << "list1: ";
    list1.print();
    std::cout << "list2: ";
    list2.print();

    std::cout << "\nCreating list3 and moving list2 into it..." << std::endl;
    DoublyLinkedList<int> list3 = std::move(list2);
    std::cout << "list2 (after move): ";
    list2.print();
    std::cout << "list3: ";
    list3.print();

    std::cout << "\nDemo finished." << std::endl;
    return 0;
}
*/
