#pragma once

#include <memory>
#include "iterator.hpp"

template<typename T>
class Stack {
public:
    struct Node {
        T data;
        Node *next;
        Node(T data_, Node *next_) {
            data = data_;
            next = next_;
        }
    };
public:
    Stack() {
        head = nullptr;
    }
    ~Stack() {
        while (head != nullptr) {
            pop();
        }
    }
    Iterator<Node> begin() {
        Iterator<Node> temp(head);
        return temp;
    }
    Iterator<Node> end() {
        Iterator<Node> temp(nullptr);
        return temp;
    }
    void insert(Iterator<Node> iter, T data) {
        if (head == nullptr) {
            head = new Node(data, nullptr);
        }
        else if (iter == begin()) {
            head = new Node(data, head);
        }
        else {
            auto tempiter = begin();
            for (; (*tempiter).next != iter.get_ptr(); ++tempiter) {
            }
            tempiter.get_ptr()->next = new Node(data, iter.get_ptr());
        }
    }
    void erase(Iterator<Node> iter) {
        if (iter == begin()) {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
        else {
            auto tempiter = begin();
            for (; (*tempiter).next != iter.get_ptr(); ++tempiter) {
            }
            tempiter.get_ptr()->next = iter.get_ptr()->next;
            delete iter.get_ptr();
        }
    }
    void pop() {
        auto iter = begin();
        erase(iter);
    }
    void push(T data) {
        auto iter = begin();
        insert(iter, data);
    }
    T top() {
        return *head;
    }
private:
    Node *head;
};
