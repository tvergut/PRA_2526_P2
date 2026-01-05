
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <stdexcept>
#include <ostream>
#include "Dict.h"
#include "TableEntry.h"
#include "ListLinked.h"

template <typename V>
class HashTable;

template <typename V>
std::ostream& operator<<(std::ostream& out, const HashTable<V>& th);

template <typename V>
class HashTable : public Dict<V> {
private:
    int n;
    int max;
    ListLinked<TableEntry<V>>* table;

    int h(std::string key) {
        unsigned long s = 0;
        for (std::size_t i = 0; i < key.size(); ++i) s += static_cast<unsigned char>(key.at(i));
        return static_cast<int>(s % max);
    }

public:
    HashTable(int size) : n(0), max(size), table(new ListLinked<TableEntry<V>>[size]) {}
    ~HashTable() override { delete[] table; }

    void insert(std::string key, V value) override {
        int i = h(key);
        TableEntry<V> probe(key);
        if (table[i].search(probe) != -1) throw std::runtime_error("duplicate key");
        table[i].prepend(TableEntry<V>(key, value));
        ++n;
    }

    V search(std::string key) override {
        int i = h(key);
        TableEntry<V> probe(key);
        int pos = table[i].search(probe);
        if (pos == -1) throw std::runtime_error("key not found");
        return table[i].get(pos).value;
    }

    V remove(std::string key) override {
        int i = h(key);
        TableEntry<V> probe(key);
        int pos = table[i].search(probe);
        if (pos == -1) throw std::runtime_error("key not found");
        TableEntry<V> te = table[i].remove(pos);
        --n;
        return te.value;
    }

    int entries() override { return n; }
    int capacity() { return max; }

    V operator[](std::string key) { return search(key); }

    friend std::ostream& operator<< <V>(std::ostream& out, const HashTable<V>& th);
};

template <typename V>
std::ostream& operator<<(std::ostream& out, const HashTable<V>& th) {
      for(int i = 0; i < th.max; ++i) {
        out << "[" << i << "]: ";
        for (int j = 0; j < th.table[i].size(); ++j) {
            if (j) out << ' ';
            TableEntry<V> te = th.table[i].get(j);
            out << "(" << te.key << "->" << te.value << ")";
        }
        out << "\n";
    }
    return out;
}

#endif
