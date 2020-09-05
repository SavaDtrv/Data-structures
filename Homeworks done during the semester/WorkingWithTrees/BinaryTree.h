#pragma once
#include <iostream>

using namespace std;

template <typename T>
struct treeNode {
	T data;
	treeNode* left;
	treeNode* right;

	treeNode(T _data, treeNode* _left = nullptr, treeNode* _right = nullptr)
		: data(_data), left(_left), right(_right) {}
};

template <typename T>
class BinaryTree {
private:
	treeNode<T>* root;

public:
	BinaryTree();
	BinaryTree(const treeNode<T>& _root);
	BinaryTree<T>& operator=(const BinaryTree<T>& other);
	~BinaryTree();

	bool find(T _data);
	bool insert(T _data);
	bool remove(T _data);
	int remove(int key);

	treeNode<T>* makePerfBalancedTree(T* arr, int beginIndex, int endIndex);

private:

	bool findElement(T _data, const treeNode<T>* _root) {
		if (!_root) {
			return false;
		}
		if (_root->data == _data) {
			return true;
		}
		if (_root->data < _data) {
			return findElement(_data, _root->right);
		}
		else {
			return findElement(_data, _root->left);
		}
	}

	bool insertElement(T _data, treeNode<T>*& _root) {
		if (_root == nullptr) {
			_root = new treeNode<T>(_data);
			return true;
		}

		if (_root->data < _data) {
			insertElement(_data, _root->right);
		}
		if (_root->data >= _data) {
			insertElement(_data, _root->left);
		}
	}

	bool removeElementByPair(T _data, treeNode<T>*& _root) {
		if (!_root) {
			return false; 
		}
		if (_root->data < _data) {
			return removeElementByPair(_data, _root->right);
		}
		if (_root->data > _data) {
			return removeElementByPair(_data, _root->left);
		}

		if (_root->data == _data) {
			treeNode<T>* toDelete = _root;
			if (!_root->left) {
				_root = _root->right;
			}
			else if (!_root->right) {
				_root = _root->left;
			}
			else {
				_root = removeMax(_root->left);
				_root->left = toDelete->left;
				_root->right = toDelete->right;
			}

			delete toDelete;
			return true;
		}

		return false;
	}
	
	//Doesn't work
	bool removeElementByKey(int key, treeNode<T>*& _root) {
		if (!_root) {
			return false;
		}
		if (_root->data < key) {
			return removeElementByKey(key, _root->right);
		}
		if (_root->data > key) {
			return removeElementByKey(key, _root->left);
		}

		treeNode<T>* toDelete = _root;
		if (!_root->left) {
			_root = _root->right;
		}
		else if (!_root->right) {
			_root = _root->left;
		}
		else {
			_root = removeMax(_root->left);
			_root->left = toDelete->left;
			_root->right = toDelete->right;
		}

		delete toDelete;
		return true;
	}

	treeNode<T>* removeMax(treeNode<T>*& _root) {
		if (_root->right) {
			return removeMax(_root->right);
		}
		else {
			treeNode<T>* res = _root;
			_root = _root->left;
			return res;
		}
	}

	treeNode<T>* makePerfBalancedTreeHelp(T* arr, int beginIndex, int endIndex, treeNode<T>*& _root) {
		if (beginIndex > endIndex) {
			return nullptr;
		}

		int midIndex = (beginIndex + endIndex) / 2;
		treeNode<T>* newNode = new treeNode<T>(arr[midIndex]);
		_root = newNode;

		makePerfBalancedTreeHelp(arr, beginIndex, midIndex - 1, _root->left);
		makePerfBalancedTreeHelp(arr, midIndex + 1, endIndex, _root->right);

		return _root;
	}


	void clearTree(treeNode<T>* _root) {
		if (_root) {
			clearTree(_root->left);
			clearTree(_root->right);
			delete _root;
		}
	}

	treeNode<T>* copyTree(const treeNode<T>* _root) {
		if (!_root) {
			return nullptr;
		}
		
		treeNode<T>* newNode = new treeNode<T>(_root->data);
		newNode->left = copyTree(_root->left);
		newNode->right = copyTree(_root->right);
		return newNode;
	}

};

template<typename T>
inline BinaryTree<T>::BinaryTree()
	:root(nullptr) {}

template<typename T>
inline BinaryTree<T>::BinaryTree(const treeNode<T>& _root)
	:root(copyTree(_root)) {}

template<typename T>
inline BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree<T>& other) {
	if (this != &other) {
		clearTree(root);
		root = copyTree(other.root);
	}

	return *this;
}

template<typename T>
inline BinaryTree<T>::~BinaryTree() {
	clearTree(root);
}

template<typename T>
inline bool BinaryTree<T>::find(T _data) {
	return findElement(_data, root);
}

template<typename T>
inline bool BinaryTree<T>::insert(T _data) {
	return insertElement(_data, root);
}

template<typename T>
inline bool BinaryTree<T>::remove(T _data) {
	return removeElementByPair(_data, root);
}

template<typename T>
inline int BinaryTree<T>::remove(int key) {
	int counter = 0;
	while (root) {
		if (removeElementByKey(key, root)) {
			counter++;
		}
		else {
			break;
		}
	}

	return counter;
}

template<typename T>
inline treeNode<T>* BinaryTree<T>::makePerfBalancedTree(T* arr, int beginIndex, int endIndex) {
	return makePerfBalancedTreeHelp(arr, beginIndex, endIndex, root);
}
