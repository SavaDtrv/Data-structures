#pragma once
#include <iostream>

using namespace std;

//smaller and equal go to left, bigger to right

//Perfect Blanaced Tree
/*
//public:
treeNode<T>* perfBalancedTree(T* arr, int begIndex, int endIndex);
//private:
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

*/

template <typename T>
struct treeNode {
	T data;
	treeNode* left;
	treeNode* right;

	treeNode(T _data, treeNode* _left = nullptr, treeNode* _right = nullptr)
		:data(_data), left(_left), right(_right) {}
};

template <typename T>
class BinTree {
private:
	treeNode<T>* root;
public:
	BinTree();
	BinTree(const BinTree<T>& other);
	BinTree<T>& operator=(const BinTree<T>& other);
	~BinTree();

	bool find(T _data);
	bool insert(T _data);
	bool remove(T _data);

private:
	bool findElement(T _data, const treeNode<T>* _root) {
		if (_root == nullptr) {
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

	bool removeElement(T _data, treeNode<T>*& _root) {
		if (_root == nullptr) {
			return false;
		}
		if (_root->data < _data) {
			return removeElement(_data, _root->right);
		}
		if (_root->data >= _data) {
			return removeElement(_data, _root->left);
		}
		if (_root->data == _data) {
			treeNode<T>* toDelete = _root;
			if (_root->left == nullptr) {
				_root = _root->right;
			}
			else if (_root->right == nullptr) {
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

	treeNode<T>* removeMax(treeNode<T>*& _root) {
		if (_root->right != nullptr) {
			return removeMax(_root->right);
		}
		else {
			treeNode<T>* res = _root;
			_root = _root->left;
			return res;
		}
	}

	void removeTree(treeNode<T>* _root) {
		if (_root != nullptr) {
			removeTree(_root->left);
			removeTree(_root->right);
			delete _root;
		}
	}

	treeNode<T>* copyTree(const treeNode<T>* _root) {
		if (_root == nullptr) {
			return nullptr;
		}

		treeNode<T>* newNode = new treeNode<T>(_root->data);
		newNode->left = copyTree(_root->left);
		newNode->right = copyTree(_root->right);
		return newNode;
	}
};

template<typename T>
inline BinTree<T>::BinTree()
	:root(nullptr) {}

template<typename T>
inline BinTree<T>::BinTree(const BinTree<T>& other) {
	root = copyTree(other.root);
}

template<typename T>
inline BinTree<T>& BinTree<T>::operator=(const BinTree<T>& other) {
	if (this != &other) {
		removeTree(root);
		root = copyTree(other.root);
	}
	
	return *this;
}

template<typename T>
inline BinTree<T>::~BinTree() {
	removeTree(root);
}

template<typename T>
inline bool BinTree<T>::find(T _data) {
	return findElement(_data, root);
}

template<typename T>
inline bool BinTree<T>::insert(T _data) {
	return insertElement(_data, root);
}

template<typename T>
inline bool BinTree<T>::remove(T _data) {
	return removeElement(_data, root);
}
