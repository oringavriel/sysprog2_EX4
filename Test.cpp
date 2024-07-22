
#include "doctest.h"
#include <string>
#include "Tree.hpp"
#include "Complex.hpp"
#include <iostream>
#include <stdexcept>

using namespace std;
using namespace ariel;
using namespace doctest;

TEST_CASE("test get and add- string")
{
    string str = "str";
    Node<string> root(str);
    CHECK((root.getValue() == "str") == true);
    string str1 = "str1";
    Node<string> sub(str1);
    root.addChild(sub);
    CHECK((root.getChildren()[0]->getValue() == "str1") == true);
}

TEST_CASE("test add and get root -double tree")
{
    Tree<double, 3> tree;
    double num = 1.1;
    Node<double> node1(num);
    tree.add_root(node1);
    CHECK((tree.getRoot()->getValue() == num) == true);
}

TEST_CASE("test add root, addsub and getters- int tree")
{
    Tree<int, 2> tree;
    int c1 = 1;
    int c2 = 2;
    Node<int> node1(c1);
    Node<int> node2(c2);
    tree.add_root(node1);
    tree.add_sub_node(node1, node2);
    CHECK((tree.getRoot()->getChildren()[0]->getValue() == c2) == true);

    SUBCASE("Add sub when the root has max children")
    {
        int c3 = 3;
        int c4 = 4;
        Node<int> node3(c3);
        Node<int> node4(c4);
        tree.add_sub_node(node1, node3);
        CHECK_THROWS(tree.add_sub_node(node1, node4));
    }
}

TEST_CASE("test complex tree")
{
    SUBCASE("test complex numbers class getters")
    {
        Complex c1(1, 2);
        Node<Complex> root(c1);
        CHECK((root.getValue().getReal() == 1) == true);
        CHECK((root.getValue().getImag() == 2) == true);
    }

    SUBCASE("Complex operators tests")
    {
        Complex c1(1, 2);
        Complex c11(1, 2);
        Complex c2(2, 2);
        Complex c3(2, 3);
        Complex c4 = c1 + c2;
        Complex c5(3, 4);
        CHECK((c11 == c1) == true);
        CHECK((c1 != c2) == true);
        CHECK((c4 == c5) == true);
        CHECK((c11 > c1) == false);
    }
    SUBCASE("test add and get root and getchildren")
    {
        Tree<Complex, 3> tree;
        Complex c1(1, 2);
        Node<Complex> node1 = (c1);
        tree.add_root(node1);
        CHECK((tree.getRoot()->getValue() == c1) == true);
    }
    SUBCASE("test valid addsub")
    {
        Tree<Complex, 2> tree;
        Complex c1(1, 2);
        Complex c2(3, 4);
        Node<Complex> node1(c1);
        Node<Complex> node2(c2);
        tree.add_root(node1);
        tree.add_sub_node(node1, node2);
        CHECK((tree.getRoot()->getChildren()[0]->getValue() == c2) == true);
    }
    SUBCASE("Add sub root when root has max children")
    {
        Tree<Complex, 3> tree;
        Complex c1(1, 2);
        Complex c2(3, 4);
        Node<Complex> node1(c1);
        Node<Complex> node2(c2);
        tree.add_root(node1);
        tree.add_sub_node(node1, node2);
        CHECK((tree.getRoot()->getChildren()[0]->getValue() == c2) == true);
        CHECK(tree.getRoot()->getValue() == c1);
        Complex c3(5, 6);
        Complex c4(7, 8);
        Complex c5(9, 10);
        Node<Complex> node3(c3);
        Node<Complex> node4(c4);
        Node<Complex> node5(c5);
        tree.add_sub_node(node1, node3);
        tree.add_sub_node(node1, node4);
        CHECK_THROWS(tree.add_sub_node(node1, node5));
    }
}

TEST_CASE("iterators test - int tree")
{

    Tree<int, 3> tree;
    Node<int> root(1);
    Node<int> child1(2);
    Node<int> child2(3);
    Node<int> child3(4);
    Node<int> child4(5);
    Node<int> child5(6);
    Node<int> child6(7);
    Node<int> child7(8);
    Node<int> child8(9);
    tree.add_root(root);
    tree.add_sub_node(root, child1);
    tree.add_sub_node(root, child2);
    tree.add_sub_node(root, child3);
    tree.add_sub_node(child1, child4);
    tree.add_sub_node(child1, child5);
    tree.add_sub_node(child2, child6);
    tree.add_sub_node(child3, child7);
    tree.add_sub_node(child3, child8);
    /*

                        1
                    /   |   \
                   2    3    4
                 /  \   |   / \
                5    6  7  8   9

    */

    SUBCASE("bfs iterator test")
    {
        int expected[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        size_t i = 0;
        for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
        {
            CHECK((*node == expected[i]) == true);
            i++;
        }
    }
    SUBCASE("pre order iterator test-should return dfs")
    {
        int expected[] = {1, 2, 5, 6, 3, 7, 4, 8, 9};
        size_t i = 0;
        for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
        {
            CHECK((*node == expected[i]) == true);
            i++;
        }
    }

    SUBCASE("dfs iterator test")
    {

        int expected[] = {1, 2, 5, 6, 3, 7, 4, 8, 9};
        size_t i = 0;
        for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node)
        {
            CHECK((*node == expected[i]) == true);
            i++;
        }
    }

    SUBCASE("in order iterator test")
    {
        int expected[] = {1, 2, 5, 6, 3, 7, 4, 8, 9};
        size_t i = 0;
        for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
        {
            CHECK((*node == expected[i]) == true);
            i++;
        }
    }

    SUBCASE("pre order iterator test")
    {

        int expected[] = {1, 2, 5, 6, 3, 7, 4, 8, 9};
        size_t i = 0;
        for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
        {
            CHECK((*node == expected[i]) == true);
            i++;
        }
    }

    SUBCASE("post order iterator test")
    {

        int expected[] = {1, 2, 5, 6, 3, 7, 4, 8, 9};
        size_t i = 0;
        for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
        {
            CHECK((*node == expected[i]) == true);
            i++;
        }
    }
}

TEST_CASE("Tree iterators test-double")
{
    Tree<double, 4> tree;
    Node<double> root(1.1);
    Node<double> child1(2.2);
    Node<double> child2(3.3);
    Node<double> child3(4.4);
    Node<double> child4(5.5);
    Node<double> child5(6.6);
    Node<double> child6(7.7);
    Node<double> child7(8.8);
    Node<double> child8(9.9);
    tree.add_root(root);
    tree.add_sub_node(root, child1);
    tree.add_sub_node(root, child2);
    tree.add_sub_node(root, child3);
    tree.add_sub_node(child1, child4);
    tree.add_sub_node(child2, child5);
    tree.add_sub_node(child2, child6);
    tree.add_sub_node(child3, child7);
    tree.add_sub_node(child7, child8);

    /*
                       1.1
                    /   |   \
                 2.2   3.3   4.4
                 |     / \    \
                5.5  6.6  7.7  8.8
                                \
                                 9.9


    */

    tree.displayTreeGUI();
    SUBCASE("bfs iterator test")
    {
        double expected[] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
        size_t i = 0;
        for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
        {
            CHECK((*node == expected[i]) == true);
            i++;
        }
    }
    SUBCASE("dfs iterator test")
    {

        double expected[] = {1.1, 2.2, 5.5, 3.3, 6.6, 7.7, 4.4, 8.8, 9.9};
        size_t i = 0;
        for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node)
        {
            CHECK((*node == expected[i]) == true);
            i++;
        }
    }
}

TEST_CASE("Binary int tree iterators test")
{
    Tree<int, 2> tree;
    int c1 = 1;
    int c2 = 2;
    int c3 = 3;
    Node<int> node1(c1);
    Node<int> node2(c2);
    Node<int> node3(c3);
    tree.add_root(node1);
    tree.add_sub_node(node1, node2);
    tree.add_sub_node(node1, node3);

    /*
                1
               /  \
              2    3
    */
    SUBCASE("pre order iterator test")
    {
        int expected[] = {1, 2, 3};
        size_t i = 0;
        for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
        {
            CHECK((*node == expected[i]) == true);
            i++;
        }
    }
    SUBCASE("In order test")
    {
        int expected[] = {2, 1, 3};
        size_t i = 0;
        for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
        {
            CHECK((*node == expected[i]) == true);
            i++;
        }
    }

    SUBCASE("Post order test")
    {
        int expected[] = {2, 3, 1};
        size_t i = 0;
        for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
        {
            CHECK((*node == expected[i]) == true);
            i++;
        }
    }
}

TEST_CASE("Binary double tree iterators tests")
{
    Tree<double, 2> tree;
    double c1 = 1.1;
    double c2 = 2.2;
    double c3 = 3.3;
    double c4 = 4.4;
    double c5 = 5.5;

    Node<double> node1(c1);
    Node<double> node2(c2);
    Node<double> node3(c3);
    Node<double> node4(c4);
    Node<double> node5(c5);
    tree.add_root(node1);

    tree.add_sub_node(node1, node2);
    tree.add_sub_node(node1, node3);
    tree.add_sub_node(node2, node4);
    tree.add_sub_node(node2, node5);

    /*
                1.1
               /  \
            2.2    3.3
            / \
          4.4  5.5
    */
    SUBCASE("pre-order test")
    {
        double expected[] = {1.1, 2.2, 4.4, 5.5, 3.3};
        size_t i = 0;
        for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
        {
            CHECK((*node == expected[i]) == true);
            i++;
        }
    }
    SUBCASE("In order test")
    {
        double expected[] = {4.4, 2.2, 5.5, 1.1, 3.3};
        size_t i = 0;
        for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
        {
            CHECK((*node == expected[i]) == true);
            i++;
        }
    }

    SUBCASE("Post order test")
    {
        double expected[] = {4.4, 5.5, 2.2, 3.3, 1.1};
        size_t i = 0;
        for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
        {
            CHECK((*node == expected[i]) == true);
            i++;
        }
    }
}

TEST_CASE("Binary complex tree iterators tests")
{
    Tree<Complex, 2> tree;
    Complex c1(1, 1);
    Complex c2(2, 2);
    Complex c3(3, 3);
    Complex c4(4, 4);
    Complex c5(5, 5);
    Node<Complex> node1(c1);
    Node<Complex> node2(c2);
    Node<Complex> node3(c3);
    Node<Complex> node4(c4);
    Node<Complex> node5(c5);
    tree.add_root(node1);
    tree.add_sub_node(node1, node2);
    tree.add_sub_node(node1, node3);
    tree.add_sub_node(node3, node4);
    tree.add_sub_node(node3, node5);

    /*
                1+1i
               /  \
              2+2i  3+3i
                     / \
                   4+4i  5+5i
    */

    SUBCASE("pre-order test")
    {
        Complex expected[] = {c1, c2, c3, c4, c5};
        size_t i = 0;
        for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
        {
            CHECK((*node == expected[i]) == true);
            i++;
        }
    }
    SUBCASE("In order test")
    {
        Complex expected[] = {c2, c1, c4, c3, c5};
        size_t i = 0;
        for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
        {
            CHECK((*node == expected[i]) == true);
            i++;
        }
    }

    SUBCASE("Post order test")
    {
        Complex expected[] = {c2, c4, c5, c3, c1};
        size_t i = 0;
        for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
        {
            CHECK((*node == expected[i]) == true);
            i++;
        }
    }
}

TEST_CASE("Binary tree heap iterator tests")
{
    Tree<int, 2> intTree;
    int root = 55;
    int leftChild = 0;
    int rightChild = -7;
    Node<int> rootNode(root);
    Node<int> leftNode(leftChild);
    Node<int> rightNode(rightChild);
    intTree.add_root(rootNode);
    intTree.add_sub_node(rootNode, leftNode);
    intTree.add_sub_node(rootNode, rightNode);

    /*
              55
             /  \
            0    -7

  */
    int expected[] = {-7, 0, 55};
    size_t i = 0;
    for (auto node = intTree.begin_heap(); node != intTree.end_heap(); ++node)
    {
        CHECK((*node == expected[i]) == true);
        i++;
    }

    SUBCASE("Binary tree heap iterator tests")
    {
        Tree<int, 2> intTree;
        int root = 100;
        int leftChild = 2;
        int rightChild = -9;
        int leftChild1 = 17;
        int rightChild1 = 87;
        int leftChild2 = 0;
        int rightChild2 = -3;
        Node<int> rootNode(root);
        Node<int> leftNode(leftChild);
        Node<int> rightNode(rightChild);
        Node<int> leftNode1(leftChild1);
        Node<int> rightNode1(rightChild1);
        Node<int> leftNode2(leftChild2);
        Node<int> rightNode2(rightChild2);
        intTree.add_root(rootNode);
        intTree.add_sub_node(rootNode, leftNode);
        intTree.add_sub_node(rootNode, rightNode);
        intTree.add_sub_node(leftNode, leftNode1);
        intTree.add_sub_node(leftNode, rightNode1);
        intTree.add_sub_node(rightNode, leftNode2);
        intTree.add_sub_node(rightNode, rightNode2);

        /*
                  100
                 /   \
                2     -9
               / \    / \
              17  87 0   -3
  */
        int expected[] = {-9, -3, 0, 2, 17, 87, 100};
        size_t i = 0;
        for (auto node = intTree.begin_heap(); node != intTree.end_heap(); ++node)
        {
            CHECK((*node == expected[i]) == true);
            i++;
        }
    }
}
