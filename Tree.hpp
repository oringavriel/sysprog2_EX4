#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <queue>
#include <stack>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include "Node.hpp"
#include "TreeGUI.hpp"
using namespace std;

namespace ariel
{
    template <typename T, int K = 2>
    class Tree
    {
    private:
        Node<T> *root;

    public:
        Tree() : root(nullptr) {}

        void add_root(Node<T> &root)
        {
            this->root = &root;
        }

        Node<T> *getRoot() const
        {
            return this->root;
        }

        void add_sub_node(Node<T> &node, Node<T> &sub)
        {
            if (node.getChildren().size() >= K)
            {
                throw invalid_argument("node has max number of children");
            }
            else
            {
                node.addChild(sub);
            }
        }

        void displayTreeGUI()
        {
            TreeGUI<T> treeGUI(root);
            treeGUI.display();
        }

        class PreOrderIterator // root,left,right

        {
        private:
            stack<Node<T> *> stack;

        public:
            PreOrderIterator(Node<T> *root)
            {
                if (root != nullptr)
                {
                    stack.push(root);
                }
            }

            T operator*() const
            {
                return stack.top()->getValue();
            }

            PreOrderIterator &operator++()
            {
                if (K == 2)
                {
                    Node<T> *node = stack.top();
                    stack.pop();
                    auto children = node->getChildren();
                    for (auto it = children.rbegin(); it != children.rend(); ++it)
                    {
                        stack.push(*it);
                    }
                }
                else // if the tree is not binary return dfs iterator
                {
                    Node<T> *node = stack.top();
                    stack.pop();
                    for (auto it = node->getChildren().rbegin(); it != node->getChildren().rend(); ++it)
                    {
                        stack.push(*it);
                    }
                }
                return *this;
            }

            bool operator!=(const PreOrderIterator &other) const
            {
                return stack.size() != other.stack.size();
            }
        };

        class PostOrderIterator // left,right, root
        {
        private:
            stack<Node<T> *> stack1, stack2;

        public:
            PostOrderIterator(Node<T> *root)
            {
                if (root != nullptr)
                {
                    if (K != 2)
                    {
                        stack2.push(root);
                    }
                    else
                    {
                        stack1.push(root);
                        while (!stack1.empty())
                        {
                            Node<T> *node = stack1.top();
                            stack1.pop();
                            stack2.push(node);
                            // Push  right and left children to stack1
                            if (node->getChildren().size() > 0 && node->getChildren()[0])
                            {
                                stack1.push(node->getChildren()[0]);
                            }
                            if (node->getChildren().size() > 1 && node->getChildren()[1])
                            {
                                stack1.push(node->getChildren()[1]);
                            }
                        }
                    }
                }
            }

            T operator*() const
            {
                return stack2.top()->getValue(); 
            }

            PostOrderIterator &operator++()
            {
                if (K == 2)
                {
                    // For binary trees pop the top node from stack2
                    stack2.pop();
                    return *this;
                }

                //  For non-binary trees Get the top node from the stack and then remove it
                Node<T> *node = stack2.top();
                stack2.pop();
                // Push all children of the current node onto the stack in reverse order
                for (auto it = node->getChildren().rbegin(); it != node->getChildren().rend(); ++it)
                {
                    stack2.push(*it);
                }
                return *this;
            }

            bool operator!=(const PostOrderIterator &other) const
            {
                return stack2.size() != other.stack2.size(); // Iterators are different if either stack is non-empty
            }
        };

        class InOrderIterator // left,root,right
        {
        private:
            stack<Node<T> *> stack;

        public:
            void left(Node<T> *node) // method to push the left child
            {
                while (node != nullptr)
                {
                    stack.push(node); // Push current node
                    if (!node->getChildren().empty())
                    {
                        node = node->getChildren()[0]; // Move to the left child
                    }
                    else
                    {
                        node = nullptr; // No left child
                    }
                }
            }

            InOrderIterator(Node<T> *root)
            {
                if (K == 2)
                {
                    left(root);
                }

                else if (root != nullptr)
                {
                    stack.push(root);
                }
            }

            T operator*() const
            {
                return stack.top()->getValue();
            }

            InOrderIterator &operator++()
            {
                if (K == 2)
                {
                    Node<T> *node = stack.top();
                    stack.pop();
                    // If the node has a right child push all it's left children
                    if (node->getChildren().size() > 1)
                    {
                        left(node->getChildren()[1]);
                    }
                }
                else
                {
                    Node<T> *node = stack.top();
                    stack.pop();
                    for (auto it = node->getChildren().rbegin(); it != node->getChildren().rend(); ++it)
                    {
                        stack.push(*it);
                    }
                }
                return *this;
            }

            bool operator!=(const InOrderIterator &other) const
            {
                return stack.size() != other.stack.size();
            }
        };

        class BFSIterator
        {
        private:
            queue<Node<T> *> queue;

        public:
            BFSIterator(Node<T> *root)
            {
                if (root != nullptr)
                {
                    queue.push(root);
                }
            }

            T operator*() const
            {
                return queue.front()->getValue();
            }

            BFSIterator &operator++()
            {
                if (queue.empty())
                {
                    return *this;
                }
                Node<T> *node = queue.front();
                queue.pop();
                for (auto child : node->getChildren())
                {
                    queue.push(child);
                }
                return *this;
            }

            bool operator!=(const BFSIterator &other) const
            {
                return queue.size() != other.queue.size();
            }
        };

        class DFSIterator
        {
        private:
            stack<Node<T> *> stack;

        public:
            DFSIterator(Node<T> *root)
            {
                if (root != nullptr)
                {
                    stack.push(root);
                }
            }

            T operator*() const
            {
                return stack.top()->getValue();
            }

            DFSIterator &operator++()
            {
                if (stack.empty())
                {
                    return *this;
                }
                Node<T> *node = stack.top();
                stack.pop();
                for (auto it = node->getChildren().rbegin(); it != node->getChildren().rend(); ++it)
                {
                    stack.push(*it);
                }
                return *this;
            }

            bool operator!=(const DFSIterator &other) const
            {
                return stack.size() != other.stack.size();
            }
        };

        class HeapIterator
        {
        private:
            vector<Node<T> *> heap; 

        public:
            HeapIterator(Node<T> *root)
            {
                if (root)
                {
                    createHeap(root); 
                }
            }

            //  create a min-heap from binary tree
            void createHeap(Node<T> *root)
            {
                queue<Node<T> *> q; // Queue for level-order traversal
                q.push(root);
                while (!q.empty())
                {
                    Node<T> *node = q.front();
                    q.pop();
                    heap.push_back(node); // Add node to the heap vector
                    // Push left and right children to the queue
                    if (node->getChildren().size() > 0 && node->getChildren()[0])
                    {
                        q.push(node->getChildren()[0]);
                    }
                    if (node->getChildren().size() > 1 && node->getChildren()[1])
                    {
                        q.push(node->getChildren()[1]);
                    }
                }
                // Convert the vector into a min-heap
                make_heap(heap.begin(), heap.end(), [](Node<T> *a, Node<T> *b)
                          {
                              return a->getValue() > b->getValue(); // Comparison function for min-heap
                          });
            }

            T operator*() const
            {
                return heap.front()->getValue();
            }

            HeapIterator &operator++()
            {
                // Remove the root of the heap
                pop_heap(heap.begin(), heap.end(), [](Node<T> *a, Node<T> *b)
                         {
                             return a->getValue() > b->getValue(); // Comparison function for min-heap
                         });
                heap.pop_back(); // Remove the last element (new root after pop_heap)
                return *this;
            }

            bool operator!=(const HeapIterator &other) const
            {
                return !heap.empty() || !other.heap.empty();
            }
        };

        PreOrderIterator begin_pre_order()
        {
            return PreOrderIterator(root);
        }

        PreOrderIterator end_pre_order()
        {
            return PreOrderIterator(nullptr);
        }

        PostOrderIterator begin_post_order()
        {
            return PostOrderIterator(root);
        }

        PostOrderIterator end_post_order()
        {
            return PostOrderIterator(nullptr);
        }

        InOrderIterator begin_in_order()
        {
            return InOrderIterator(root);
        }

        InOrderIterator end_in_order()
        {
            return InOrderIterator(nullptr);
        }

        BFSIterator begin_bfs_scan()
        {
            return BFSIterator(root);
        }

        BFSIterator end_bfs_scan()
        {
            return BFSIterator(nullptr);
        }
        DFSIterator begin_dfs_scan()
        {
            return DFSIterator(root);
        }

        DFSIterator end_dfs_scan()
        {
            return DFSIterator(nullptr);
        }

        HeapIterator begin_heap()
        {
            return HeapIterator(root);
        }

        HeapIterator end_heap()
        {
            return HeapIterator(nullptr);
        }
    };

}

#endif