
#ifndef LIST_LINKED_H
#define LIST_LINKED_H

#include "List.h"
#include "Node.h"
#include <stdexcept>
#include <ostream>

template <typename U>
class ListLinked;

template <typename U>
std::ostream& operator<<(std::ostream& out, const ListLinked<U>& list);

template <typename T>
class ListLinked : public List<T> {
private:
    Node<T>* first;
    int n;

    Node<T>* node_at(int pos) const {
        Node<T>* cur = first;
        for (int i = 0; i < pos; ++i) cur = cur->next;
        return cur;
    }

public:
    ListLinked() : first(nullptr), n(0) {}
    ~ListLinked() override {
        while (first) {
            Node<T>* aux = first->next;
            delete first;
            first = aux;
        }
    }

    T operator[](int pos) {
        if (pos < 0 || pos >= n) throw std::out_of_range("Posición inválida!");
        return node_at(pos)->data;
    }

    void insert(int pos, T e) override {
        if (pos < 0 || pos > n) throw std::out_of_range("Posición inválida!");
        if (pos == 0) {
            first = new Node<T>(e, first);
            ++n;
            return;
        }
        Node<T>* prev = node_at(pos - 1);
        prev->next = new Node<T>(e, prev->next);
        ++n;
    }

    void append(T e) override { insert(n, e); }
    void prepend(T e) override { insert(0, e); }

    T remove(int pos) override {
        if (pos < 0 || pos >= n) throw std::out_of_range("Posición inválida!");
        if (pos == 0) {
            Node<T>* del = first;
            T r = del->data;
            first = del->next;
            delete del;
            --n;
            return r;
        }
        Node<T>* prev = node_at(pos - 1);
        Node<T>* del = prev->next;
        T r = del->data;
        prev->next = del->next;
        delete del;
        --n;
        return r;
    }

    T get(int pos) override {
        if (pos < 0 || pos >= n) throw std::out_of_range("Posición inválida!");
        return node_at(pos)->data;
    }

    int search(T e) override {
        Node<T>* cur = first;
        int i = 0;
        while (cur) {
            if (cur->data == e) return i;
            cur = cur->next;
            ++i;
        }
        return -1;
    }

    bool empty() override { return n == 0; }
    int size() override { return n; }

    friend std::ostream& operator<< <T>(std::ostream& out, const ListLinked<T>& list);
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const ListLinked<T>& list) {
    out << "List => [\n";
    Node<T>* cur = list.first;
    while (cur) {
        out << "  " << cur->data << "\n";
        cur = cur->next;
    }
    out << "]\n";
    return out;
}

#endif
