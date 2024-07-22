/**
 * Demo app for Ex4
 */
#include <iostream>
#include <string>
#include "Node.hpp"
#include "Tree.hpp"
#include "Complex.hpp"
using namespace std;
using namespace ariel;

int main()
{

    Node<double> root_node(1.1);
    Tree<double> tree; // Binary tree that contains doubles.
    tree.add_root(root_node);
    Node<double> n1(1.2);
    Node<double> n2(1.3);
    Node<double> n3(1.4);
    Node<double> n4(1.5);
    Node<double> n5(1.6);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);

    // The tree should look like:
    /**
     *       root = 1.1
     *     /       \
     *    1.2      1.3
     *   /  \      /
     *  1.4  1.5  1.6
     */

    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
    {
        cout << *node << ",";
    } // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6
    cout << endl;

    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
    {
        cout << *node << ",";
    } // prints: 1.4, 1.5, 1.2, 1.6, 1.3, 1.1
    cout << endl;

    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
    {
        cout << *node << ",";
    } // prints: 1.4, 1.2, 1.5, 1.1, 1.6, 1.3
    cout << endl;

    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
    {
        cout << *node << ",";
    } // prints: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6
    cout << endl;

    tree.displayTreeGUI();

    Tree<Complex, 2> complexTree;
    Complex root(3, 5);
    Complex sub1(1, 2);
    Complex sub2(3, 6);
    Complex sub3(4, 5);
    Complex sub4(3, 6);
    Complex sub5(2, 1);
    Complex sub6(1, 3);
    Node<Complex> rootNode(root);
    Node<Complex> node1(sub1);
    Node<Complex> node2(sub2);
    Node<Complex> node3(sub3);
    Node<Complex> node4(sub4);
    Node<Complex> node5(sub5);
    Node<Complex> node6(sub6);
    complexTree.add_root(rootNode);
    complexTree.add_sub_node(rootNode, node1);
    complexTree.add_sub_node(rootNode, node2);
    complexTree.add_sub_node(node1, node3);
    complexTree.add_sub_node(node1, node4);
    complexTree.add_sub_node(node2, node5);
    complexTree.add_sub_node(node2, node6);

    cout << "Pre-Order Traversal: ";
    for (auto it = complexTree.begin_pre_order(); it != complexTree.end_pre_order(); ++it)
    {
        cout << *it << ", ";
    }
    cout << endl;

    cout << "In-Order Traversal: ";
    for (auto it = complexTree.begin_in_order(); it != complexTree.end_in_order(); ++it)
    {
        cout << *it << ", ";
    }
    cout << endl;

    cout << "Post-Order Traversal: ";
    for (auto it = complexTree.begin_post_order(); it != complexTree.end_post_order(); ++it)
    {
        cout << *it << ", ";
    }
    cout << endl;

    cout << "Heap traversal: ";
    for (auto it = complexTree.begin_heap(); it != complexTree.end_heap(); ++it)
    {
        cout << *it << ", ";
    }
    cout << endl;

    complexTree.displayTreeGUI();

    Tree<int, 3> tree3k;
    Node<int> root1(1);
    Node<int> sub11(2);
    Node<int> sub22(3);
    Node<int> sub33(4);
    Node<int> sub44(5);
    Node<int> sub55(6);
    tree3k.add_root(root1);
    tree3k.add_sub_node(root1, sub11);
    tree3k.add_sub_node(root1, sub22);
    tree3k.add_sub_node(sub11, sub33);
    tree3k.add_sub_node(sub11, sub44);
    tree3k.add_sub_node(sub11, sub55);

    cout << "BFS traversal: ";
    for (auto it = tree.begin_bfs_scan(); it != tree.end_bfs_scan(); ++it)
    {
        cout << *it << ", ";
    }
    cout << endl;

    cout << "DFS traversal: ";
    for (auto it = tree.begin_dfs_scan(); it != tree.end_dfs_scan(); ++it)
    {
        cout << *it << ", ";
    }
    cout << endl;

    tree3k.displayTreeGUI();
}