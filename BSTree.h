
#ifndef BSTREE_H
#define BSTREE_H

#include <stdexcept>
#include <ostream>
#include "BSNode.h"

template <typename T>
class BSTree;

template <typename T>
std::ostream& operator<<(std::ostream& out, const BSTree<T>& bst);

template <typename T>
class BSTree {
private:
    BSNode<T>* root;
    int nelem;

    BSNode<T>* search(BSNode<T>* n, T e) const {
        if (!n) throw std::runtime_error("not found");
        if (n->elem < e) return search(n->right, e);
        if (n->elem > e) return search(n->left, e);
        return n;
    }

    BSNode<T>* insert(BSNode<T>* n, T e) {
        if (!n) { ++nelem; return new BSNode<T>(e); }
        if (e < n->elem) n->left = insert(n->left, e);
        else if (e > n->elem) n->right = insert(n->right, e);
        else throw std::runtime_error("duplicate");
        return n;
    }

    void print_inorder(std::ostream& out, BSNode<T>* n) const {
        if (!n) return;
        print_inorder(out, n->left);
        out << n->elem << ' ';
        print_inorder(out, n->right);
    }

    BSNode<T>* remove(BSNode<T>* n, T e) {
        if (!n) throw std::runtime_error("not found");
        if (e < n->elem) { n->left = remove(n->left, e); return n; }
        if (e > n->elem) { n->right = remove(n->right, e); return n; }
        if (!n->left && !n->right) { --nelem; delete n; return nullptr; }
        if (!n->left) { BSNode<T>* r = n->right; --nelem; delete n; return r; }
        if (!n->right) { BSNode<T>* l = n->left; --nelem; delete n; return l; }
        T m = max(n->left);
        n->elem = m;
        n->left = remove_max(n->left);
        return n;
    }

    T max(BSNode<T>* n) const {
        BSNode<T>* cur = n;
        while (cur->right) cur = cur->right;
        return cur->elem;
    }

    BSNode<T>* remove_max(BSNode<T>* n) {
        if (!n->right) { BSNode<T>* l = n->left; --nelem; delete n; return l; }
               n->right = remove_max(n->right);
        return n;
    }

    void delete_cascade(BSNode<T>* n) {
        if (!n) return;
        delete_cascade(n->left);
        delete_cascade(n->right);
        delete n;
    }

public:
    BSTree() : root(nullptr), nelem(0) {}
    int size() const { return nelem; }
    T search(T e) const { return search(root, e)->elem; }
    T operator[] (T e) const { return search(e); }
    void insert(T e) { root = insert(root, e); }
    void remove(T e) { root = remove(root, e); }
    ~BSTree() { delete_cascade(root); }

    template <typename U>
    friend std::ostream& operator<<(std::ostream& out, const BSTree<U>& bst);
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const BSTree<T>& bst) {
    bst.print_inorder(out, bst.root);
    return out;
}

#endif
