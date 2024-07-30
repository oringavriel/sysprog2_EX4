# System programming- assignment 4
this project focuses on templates, stl and iterators in c++.
It implements a k-ari tree (which its default is a binary tree – k=2)  and all kinds of iterators on it .
The project includes a TreeGUI.hpp template class for displaying the tree structures using the SDL2 and SDL2_ttf libraries- Each node of the tree is drawn as a circle with text and lines to connect the parent nodes to their children.
The project also contains a Makefile, Demo.hpp and testing unit for running and checking the code. 
## Classes:
### Complex.hpp
This class represents complex numbers and supports various operations
It has 2 private fields- double real, double imag to represent the real and imaginary part of the complex number.
it includes this public methods:
1.	Complex(double real = 0.0, double imag = 0.0) - real(real), imag(imag) {}- constructor
2.	double getReal() const – getter for the real part of the number
3.	double getImag() const- getter for the imaginary part of the number
4.	Complex operator+(const Complex &other) const- operator for adding 2 complex numbers
5.	bool operator==(const Complex &other) const- operator which compares 2 complex numbers and return true if they are equal
6.	bool operator!=(const Complex &other) const- operator which compares 2 complex numbers and return true if they are not equal
7.	bool operator>(const Complex &other) const- operator to check if this complex number is bigger than the other.
8.	friend ostream &operator<<(ostream &out, const Complex &c)- friend operator which allows us to print the complex number.
### Node.hpp
This template class represents a node of the tree ( can store any kind of data). 
It has 2 private fields:
1.	T value- the value of the node
2.	vector<Node<T> *> children- a list of the children of the node
This class includes this public methods:
1.	Node(T value) - value(value) {}- constructor of the node
2.	T getValue() const – getter for the value of the node
3.	const vector<Node<T> *> &getChildren() const – getter for the vector of the children of the node
4.	void addChild(Node<T> &child) – a method which adds a child node to the children vector
### Tree.hpp
This template class represents a tree with two template parameters: T to store any type of node and K for the maximum number of children of the node (its default state is K=2 for binary tree.
The class has private field Node<T> *root which points to the root node of the tree.
It has this methods:
1.	Tree() : root(nullptr) {}- constructor which Initializes an empty tree with root set to nullptr.
2.	void add_root(Node<T> &root)-  Sets the root node of the tree.
3.	Node<T> *getRoot() const- getter for the root node
4.	void add_sub_node(Node<T> &node, Node<T> &sub)- Adds a child node to the parent node.
it throws an exception if the parent node already has the maximum number of children .
5.	void displayTreeGUI()- Visualizes the tree using the TreeGUI class.

The Tree class provides several iterators for traversing the tree using internal classes to define the traverse order.
Each internal class has a constructor for the specific traversal and 3 operators needed for traversing the tree:
1.	operator* -  Returns the value of the current node
2.	Operator ++: Moves to the next node by the traversal order
3.	Operator !=: Checks if the iterator is not equal to another iterator 

The iterators of the tree class are:
1.	PreOrderIterator- Iterates over the nodes of the tree in preorder traversal order(Root, Left, Right). This iterator works only on binary trees. For a general tree it returns a DFS scan.
2.	PostOrderIterator- Iterates over the nodes of the tree in postorder traversal order(Left, Right, Root). This iterator works only on binary trees. For a general tree it returns a DFS scan.
3.	InOrderIterator- Iterates over the nodes of the tree in an inorder traversal order ( Left, Root, Right). This iterator works only on binary trees. For a general tree it returns a DFS scan.
4.	BFSIterator- Iterates over the nodes of the tree using breadth-first search.
5.	DFSIterator- Iterates over the nodes of the tree using depth-first search.
6.	HeapIterator- Iterates over the nodes of the tree as if the tree was a min-heap. 

For each iterator the tree class contains a begin and end methods to start and end the traversal.





