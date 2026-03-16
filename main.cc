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

template <typename T>
Tree<T> insert(Tree<T> tree, T value) {
	if (tree == nullptr)
		return make_shared<Node<T>>(value);

	if (value < tree->data) {
		tree->left = insert(tree->left, value);
		return tree;
	} else {
		tree->right = insert(tree->right, value);
		return tree;
	}
}

template <typename T>
bool search(Tree<T> tree, T value) {
	if (tree == nullptr)
		return false;
	if (tree->data == value)
		return true;

	if (value < tree->data)
		return search(tree->left, value);

	return search(tree->right, value);
}

template <typename T>
Tree<T> remove(Tree<T> tree, T value) {
	if (tree == nullptr)
		return nullptr;

	if (value < tree->data)
		tree->left = remove(tree->left, value);
	else if (value > tree->data)
		tree->right = remove(tree->right, value);
	else if (value == tree->data) {
		if (tree->right == nullptr)
			return tree->left;
		if (tree->left == nullptr)
			return tree->right;

		tree->data = inorder_successor(tree->right);
		tree->right = remove_inorder_successor(tree->right);
	}

	return tree;
}

template <typename T>
Tree<T> remove_inorder_successor(Tree<T> tree) {
	if (tree->left == nullptr)
		return tree->right;

	tree->left = remove_inorder_successor(tree->left);
	return tree;
}

template <typename T>
T inorder_successor(Tree<T> tree) {
	if (tree->left == nullptr)
		return tree->data;

	return inorder_successor(tree->left);
}

// Helper function for printing the entire list
template<typename T>
void inorder(Tree<T> t) {
	if (!t) return;
	inorder(t->left);
	cout << t->data << " ";
	inorder(t->right);
}

int main() {
	Tree<int> tree = nullptr;

	tree = insert(tree, 5);
	tree = insert(tree, 3);
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
}
