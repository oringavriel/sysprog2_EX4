#ifndef NODE_HPP
#define NODE_HPP
#include <iostream>
#include <vector>
using namespace std;

namespace ariel
{
    template <typename T>
    class Node
    {

    private:
        T value;
        vector<Node<T> *> children;

    public:
        Node(T value) : value(value) {}
        T getValue() const { return value; }
        const vector<Node<T> *> &getChildren() const { return children; }
        void addChild(Node<T> &child) { children.push_back(&child); }
    };
}
#endif