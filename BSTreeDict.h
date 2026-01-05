
#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict : public Dict<V> {
private:
    BSTree<TableEntry<V>>* tree;
public:
    BSTreeDict() : tree(new BSTree<TableEntry<V>>()) {}
    ~BSTreeDict() override { delete tree; }
    void insert(std::string key, V value) override { tree->insert(TableEntry<V>(key, value)); }
    V search(std::string key) override { return tree->search(TableEntry<V>(key)).value; }
    V remove(std::string key) override { V v = search(key); tree->remove(TableEntry<V>(key)); return v; }
    int entries() override { return tree->size(); }
    V operator[](std::string key) { return search(key); }
    template <typename U>
    friend std::ostream& operator<<(std::ostream& out, const BSTreeDict<U>& bs) {
        out << *(bs.tree);
        return out;
    }
};

#endif

