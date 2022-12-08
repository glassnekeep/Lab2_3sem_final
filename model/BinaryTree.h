#pragma once

#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <class T>
class BinaryTree {
private:
    class TreeElement {
    public:
        T data;
        TreeElement* left;
        TreeElement* right;
        TreeElement(T val) {
            left = nullptr;
            right = nullptr;
            data = val;
        }
    };

    TreeElement* root;
    int size;

    void to_str_tree_KLP(TreeElement* curr, string* res) {
        if (curr) {
            *res += to_string(curr->data) + " ";
            to_str_tree_KLP(curr->left, res);
            to_str_tree_KLP(curr->right, res);
        }
    }

    void delete_tree(TreeElement* curr) {
        if (curr && curr->left && curr->right) {
            delete_tree(curr->left);
            delete_tree(curr->right);
            delete curr;
        }
    }

    TreeElement* findValue(int target) {
        if (root->data == target)
            return root;
        return findValueHelper(root, target);
    }

    TreeElement* findValueHelper(TreeElement* ptr, T val) const {
        if (ptr == nullptr)
            return nullptr;
        if (val < ptr->data)
            return findValueHelper(ptr->left, val);
        else if (val > ptr->data)
            return findValueHelper(ptr->right, val);
        else
            return ptr;

    }

    void map(TreeElement* curr, int (*pt2Func1)(int)) {
        if (curr) {
            curr->data = (*pt2Func1)(curr->data);
            map(curr->left, pt2Func1);
            map(curr->right, pt2Func1);
        }
    }

    void where1(BinaryTree<T> tree, TreeElement* curr, bool (*pt2Func2)(int)) {
        if (curr) {
            if ((*pt2Func2)(curr->data))
                tree.insert(curr->data);
            where1(tree, curr->left, pt2Func2);
            where1(tree, curr->right, pt2Func2);
        }
    }
public:
    BinaryTree(T key) {
        root = new TreeElement(key);
        size = 1;
    }

    BinaryTree(string s) {
        s += '.';
        string tmp;
        vector <string> vs;
        for (int i = 0; i < s.length(); i++)
            if (s[i] == ' ' || s[i] == '.') {
                vs.push_back(tmp);
                tmp.clear();
            }
            else
                tmp += s[i];
        root = new TreeElement(stoi(vs[0]));
        size = 1;
        for (int i = 1; i < vs.size(); i++)
            insert(stoi(vs[i]));
    }

    BinaryTree(T* arr, int count) {
        root = new TreeElement(arr[0]);
        size = 1;
        for (int i = 1; i < count; i++)
            insert(arr[i]);
    }

    ~BinaryTree() {
        delete_tree(root);
    }

    TreeElement* getRoot() {
        return root;
    }

    BinaryTree<T> getSubTree(T target) {
        TreeElement* node = findValue(target);

        BinaryTree<T> newTree(1);
        newTree.root = node;

        return newTree;
    }

    void map(int (*pt2Func1)(int)) {
        map(root, pt2Func1);
    }

    BinaryTree<T> where(BinaryTree<T> tree, bool (*pt2Func)(int)) {
        where1(tree, root, pt2Func);
        return tree;
    }

    void insert(T key) {
        TreeElement* curr = root;
        while (curr && curr->data != key) {
            if (curr->data > key && curr->left == nullptr) {
                curr->left = new TreeElement(key);
                ++size;
                return;
            }
            if (curr->data < key && curr->right == nullptr) {
                curr->right = new TreeElement(key);
                ++size;
                return;
            }
            if (curr->data > key)
                curr = curr->left;
            else
                curr = curr->right;
        }
    }

    void erase(T key) {
        TreeElement* curr = root;
        TreeElement* parent = nullptr;
        while (curr && curr->data != key) {
            parent = curr;
            if (curr->data > key)
                curr = curr->left;
            else
                curr = curr->right;
        }
        if (!curr)
            return;
        if (curr->left == nullptr) {
            if (parent && parent->left == curr)
                parent->left = curr->right;
            if (parent && parent->right == curr)
                parent->right = curr->right;
            --size;
            delete curr;
            return;
        }
        if (curr->right == nullptr) {
            if (parent && parent->left == curr)
                parent->left = curr->left;
            if (parent && parent->right == curr)
                parent->right = curr->left;
            --size;
            delete curr;
            return;
        }
        TreeElement* replace = curr->right;
        while (replace->left)
            replace = replace->left;
        T replace_value = replace->data;
        erase(replace_value);
        curr->data = replace_value;
    }

    int getSize() {
        return this->size;
    }

    string saveTreeToString() {
        string result = "";
        to_str_tree_KLP(root, &result);
        return result;
    }

    bool isTreeEntry(BinaryTree<T> tree) {
        return saveTreeToString(1).find(tree.saveTreeToString(1)) != std::string::npos;
    }

    bool find(T key) {
        TreeElement* curr = root;
        while (curr && curr->data != key) {
            if (curr->data > key)
                curr = curr->left;
            else
                curr = curr->right;
        }
        return curr != nullptr;
    }

    static bool equals(TreeElement* t1, TreeElement* t2) {
        if (t1 == t2)
            return true;
        if ((t1 == nullptr) || (t2 == nullptr))
            return false;
        return ((t1->data == t2->data) && equals(t1->left, t2->left) && equals(t1->right, t2->right));
    }

    void prettyPrint(TreeElement* node, string const& rpref = "", string const& cpref = "", string const& lpref = "") {
        if (!node)
            return;
        if (node->right)
            prettyPrint(node->right, rpref + "  ", rpref + "/-", rpref + "| ");
        cout << cpref << node->data << std::endl;
        if (node->left)
            prettyPrint(node->left, lpref + "| ", lpref + "\\-", lpref + "  ");
    }
};