#include <iostream>
using std::cout;
using std::endl;
using std::string;

template <typename T>
struct Node {
	T data;
	Node<T>* next;
};

template <typename T>
using List = Node<T>*;

/// Empty list is null
template <typename T>
List<T> init() {
	return nullptr;
}

template <typename T>
void deinit(List<T>& list) {
	if (list != nullptr) {
		deinit(list->next);
		delete list;
		list = nullptr;
	}
}

/// Requirements:
/// input: Φ [a, b, c, ...]
/// output: [Φ, a, b, c, ...]
template <typename T>
List<T> prepend(T elem, List<T> list) {
	Node<T>* n = new Node<T>();
	n->data = elem;
	n->next = list;
	return n;
}

/// Requirements:
/// input: [a, Φ, c, ...] Φ
/// output: true
///
/// input: [a, b, c, ...] Φ
/// output: false
template <typename T>
bool contains(List<T> list, T elem) {
	if (list == nullptr)
		return false;

	if (list->data == elem)
		return true;

	return contains(list->next, elem);
}

/// Requirements:
/// input: [a, b, c, ...] 2
/// output: c
///
/// input: [a, b, c, ...] 0
/// output: a
template <typename T>
T* index(List<T> list, unsigned int i) {
	if (list == nullptr)
		return nullptr;

	if (i == 0)
		return &list->data;

	return index(list->next, i - 1);
}

/// Requirements:
/// input: [a, b, c] 0
/// output: [b, c]
///
/// input: [a, b, c] 2
/// output: [a, b]
///
/// input: [a, b, c] 10000
/// output: [a, b, c]
template <typename T>
List<T> remove_at(List<T> list, unsigned int offset) {
	if (list == nullptr)
		return nullptr;

	if (offset == 0) {
		List<T> l = list->next;
		delete list;
		return l;
	}

	list->next = remove_at(list->next, offset - 1);
	return list;
}

// Helper function for printing the entire list
template <typename T>
void print(List<T> l) {
	cout << "[";
	for (string s = ""; l != nullptr; l = l->next) {
		cout << s << l->data;
		s = ", ";
	}
	cout << "]\n";
}

int main() {
	List<int> list = init<int>();

	// build list: [1 .. 13]
	for (int i = 1; i < 13; ++i) list = prepend(i, list);

	cout << "Initial list: ";
	print(list);

	// indexing
	int* m = index(list, 0);
	cout << "index 0: ";
	if (m != nullptr) cout << *m;
	else cout << "not found";
	cout << endl;

	m = index(list, 100);
	cout << "index 100: ";
	if (m != nullptr) cout << *m;
	else cout << "not found";
	cout << endl;

	m = index(list, 12);
	cout << "index 12: ";
	if (m != nullptr) cout << *m;
	else cout << "not found";
	cout << endl;

	// contains
	cout << "contains 2: " << (contains(list, 2) ? "true" : "false") << endl;
	cout << "contains 5: " << (contains(list, 5) ? "true" : "false") << endl;
	cout << "contains 13: " << (contains(list, 13) ? "true" : "false") << endl;

	// removal
	list = remove_at(list, 2);
	cout << "After removing at index 2: ";
	print(list);

	list = remove_at(list, 0);
	cout << "After removing at index 0: ";
	print(list);

	list = remove_at(list, 10);
	cout << "After removing at index 10: ";
	print(list);

	list = remove_at(list, 100);
	cout << "After removing at index 100: ";
	print(list);

	deinit(list);
}
