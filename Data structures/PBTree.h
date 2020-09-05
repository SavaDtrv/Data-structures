#include <iostream>

using namespace std;

template <typename T>
struct Node{
	T data;
	Node<T>* left, *right;

	Node(T _data, Node<T>* _left, Node<T>* _right)
		:data(_data), left(_left), right(_right) {}

};

template <typename T>
class PBBinTree {

private:
	Node<T>* root;

};


template <typename T>
class BinTreePosition {
public:
	BinTreePosition(Node<T>*& rp) : p(&rp); //rp = rootPointer

	operator bool() const {
		return *p != nullptr;
	}

	bool operator!() const{
		return *p == nullptr;
	}

	//returns the value of the root
	T& operator*() const {
		return (*p)->data;
	}


	//moves right, if possible
	BinTreePosition operator+() const {
		if (*p == nullptr){
			return *this;
		}

		return BinTreePosition((*p)->right);
	}
	//moves left, if possible
	BinTreePosition operator-() const {
		if (*p == nullptr){
			return *this;
		}

		return BinTreePosition((*p)->left);
	}


	friend class PBBinTree<T>;

private:

	Node<T>** p;
};