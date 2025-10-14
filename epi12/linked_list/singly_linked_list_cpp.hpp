#pragma once
#include <iostream>
#include <new>      // 用于 std::nothrow
#include <utility>  // 用于 std::swap

// --- C++ 模板：安全且现代的单链表实现 ---

template <typename T>
class SinglyLinkedList {
private:
    struct Node {
        T data;
        Node* next;
    };

    Node* m_head = nullptr;
    size_t m_size = 0;

public:
    // 默认构造函数
    SinglyLinkedList() = default;

    // --- RAII: 析构函数确保内存被释放 ---
    ~SinglyLinkedList() {
        while (m_head) {
            Node* temp = m_head;
            m_head = m_head->next;
            delete temp;
        }
    }

    // --- Rule of Five: 防止浅拷贝和悬垂指针 ---

    // 1. 拷贝构造函数 (深拷贝)
    SinglyLinkedList(const SinglyLinkedList& other) {
        if (!other.m_head) {
            return;
        }
        Node* other_current = other.m_head;
        Node** this_current_ptr = &m_head;
        try {
            while(other_current) {
                Node* new_node = new Node{other_current->data, nullptr};
                *this_current_ptr = new_node;
                this_current_ptr = &(new_node->next);
                other_current = other_current->next;
                m_size++;
            }
        } catch (const std::bad_alloc&) {
            std::cerr << "Failed to allocate memory during copy." << std::endl;
            // 如果分配失败，清理已复制的节点
            this->~SinglyLinkedList(); 
            throw; // 重新抛出异常
        }
    }

    // 2. 拷贝赋值运算符 (Copy-and-Swap Idiom)
    SinglyLinkedList& operator=(const SinglyLinkedList& other) {
        if (this != &other) {
            SinglyLinkedList temp(other); // 使用拷贝构造函数
            swap(*this, temp);
        }
        return *this;
    }

    // 3. 移动构造函数
    SinglyLinkedList(SinglyLinkedList&& other) noexcept
        : m_head(other.m_head), m_size(other.m_size) {
        other.m_head = nullptr;
        other.m_size = 0;
    }

    // 4. 移动赋值运算符
    SinglyLinkedList& operator=(SinglyLinkedList&& other) noexcept {
        if (this != &other) {
            // 释放当前资源
            this->~SinglyLinkedList();
            // 窃取资源
            m_head = other.m_head;
            m_size = other.m_size;
            // 将源对象置于有效但为空的状态
            other.m_head = nullptr;
            other.m_size = 0;
        }
        return *this;
    }
    
    // 友元函数用于 swap
    friend void swap(SinglyLinkedList& first, SinglyLinkedList& second) noexcept {
        using std::swap;
        swap(first.m_head, second.m_head);
        swap(first.m_size, second.m_size);
    }

    // --- 公共接口 ---

    bool push_front(const T& data) {
        // 使用 std::nothrow 保证分配失败时不抛出异常，而是返回 nullptr
        Node* new_node = new (std::nothrow) Node{data, m_head};
        if (!new_node) {
            std::cerr << "Failed to allocate memory for new node." << std::endl;
            return false;
        }
        m_head = new_node;
        m_size++;
        return true;
    }

    bool pop_front() {
        if (!m_head) {
            return false; // 列表为空
        }
        Node* old_head = m_head;
        m_head = m_head->next;
        delete old_head;
        m_size--;
        return true;
    }

    size_t size() const { return m_size; }
    bool empty() const { return m_size == 0; }

    void print() const {
        std::cout << "List (size " << m_size << "): ";
        Node* current = m_head;
        while (current) {
            std::cout << current->data << " -> ";
            current = current->next;
        }
        std::cout << "nullptr" << std::endl;
    }
};

// --- 示例 main 函数 ---
// 要运行此示例，请创建一个 .cpp 文件，包含此头文件并定义 main 函数
/*
#include "singly_linked_list_cpp.hpp"
#include <string>

int main() {
    std::cout << "--- C++ Singly Linked List Demo ---" << std::endl;
    SinglyLinkedList<int> list1;
    list1.push_front(30);
    list1.push_front(20);
    list1.push_front(10);
    std::cout << "list1: ";
    list1.print();

    std::cout << "\nCreating list2 as a copy of list1..." << std::endl;
    SinglyLinkedList<int> list2 = list1; // 拷贝构造
    std::cout << "list2: ";
    list2.print();

    std::cout << "\nPopping front of list2..." << std::endl;
    list2.pop_front();
    std::cout << "list1: ";
    list1.print(); // list1 不受影响
    std::cout << "list2: ";
    list2.print();

    std::cout << "\nCreating list3 and moving list1 into it..." << std::endl;
    SinglyLinkedList<int> list3 = std::move(list1); // 移动构造
    std::cout << "list1 (after move): ";
    list1.print(); // list1 现在为空
    std::cout << "list3: ";
    list3.print();

    std::cout << "\nDemo with std::string:" << std::endl;
    SinglyLinkedList<std::string> str_list;
    str_list.push_front("world");
    str_list.push_front("hello");
    str_list.print();

    std::cout << "\nDemo finished." << std::endl;
    // 所有列表的内存在 main 函数结束时自动释放
    return 0;
}
*/
