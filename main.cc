#include <iostream>
#include <memory>
using namespace std;

template <typename T>
struct Node {
	T data;
	shared_ptr<Node<T>> left;
	shared_ptr<Node<T>> right;

	Node(T v) : data(v), left(nullptr), right(nullptr) {}
};

template <typename T>
using Tree = shared_ptr<Node<T>>;

// Helper function for printing the entire list
template<typename T>
void inorder(Tree<T> t) {
	if (!t) return;
	inorder(t->left);
	cout << t->data << " ";
	inorder(t->right);
}

int main() {
	/*
	Tree<int> tree = nullptr;

	tree = insert(tree, 5);
	tree = insert(tree, 3);
	tree = insert(tree, 1);
	tree = insert(tree, 7);
	tree = insert(tree, 2);
	tree = insert(tree, 4);
	tree = insert(tree, 6);
	tree = insert(tree, 8);
	cout << "tree: ";
	inorder(tree);
	cout << endl;

	cout << "Search 4: " << search(tree, 4) << endl;
	cout << "Search 10: " << search(tree, 10) << endl;

	tree = remove(tree, 7);

	cout << "Search 7 after removal: " << search(tree, 7) << endl;

	cout << "tree: ";
	inorder(tree);
	cout << endl;
	*/
}
