
#ifndef TABLEENTRY_H
#define TABLEENTRY_H

#include <string>
#include <ostream>

template <typename V>
class TableEntry {
public:
    std::string key;
    V value;

    TableEntry(std::string key, V value) : key(key), value(value) {}
    TableEntry(std::string key) : key(key), value() {}
    TableEntry() : key(""), value() {}

    template <typename U>
    friend bool operator==(const TableEntry<U>& a, const TableEntry<U>& b);
    template <typename U>
    friend bool operator!=(const TableEntry<U>& a, const TableEntry<U>& b);
    template <typename U>
    friend bool operator<(const TableEntry<U>& a, const TableEntry<U>& b);
    template <typename U>
    friend bool operator>(const TableEntry<U>& a, const TableEntry<U>& b);
    template <typename U>
    friend std::ostream& operator<<(std::ostream& out, const TableEntry<U>& te);
};

template <typename V>
bool operator==(const TableEntry<V>& a, const TableEntry<V>& b) { return a.key == b.key; }

template <typename V>
bool operator!=(const TableEntry<V>& a, const TableEntry<V>& b) { return !(a == b); }

template <typename V>
bool operator<(const TableEntry<V>& a, const TableEntry<V>& b) { return a.key < b.key; }

template <typename V>
bool operator>(const TableEntry<V>& a, const TableEntry<V>& b) { return a.key > b.key; }

template <typename V>
std::ostream& operator<<(std::ostream& out, const TableEntry<V>& te) {
    out << "(" << te.key << " -> " << te.value << ")";
    return out;
}

#endif

