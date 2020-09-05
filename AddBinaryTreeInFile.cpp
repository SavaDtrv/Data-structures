#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>

using namespace std;

struct Node {

	int data;
	Node* left;
	Node* right;

	Node(int _data, Node* _left, Node* _right) :data(_data), left(_left), right(_right)
	{}
};

void addTreeInFile(ofstream& fileName, Node* _root)
{
	if (!_root)
	{
		return;
	}

	if (fileName.is_open())
	{
		fileName << '(';
		fileName << _root->data;
		fileName << ' ';

		if (!_root->left)
		{
			fileName << "() ";
		}
		else {
			addTreeInFile(fileName, _root->left);
		}

		if (!_root->right)
		{
			fileName << "()) ";
		}
		else {
			addTreeInFile(fileName, _root->right);
			fileName << ")";
		}
	}
}

int main() {
	
	Node* root = new Node(5, nullptr, nullptr);
	Node* root_1 = new Node(3, nullptr, nullptr);
	Node* root_2 = new Node(1, nullptr, nullptr);

	root->left = root_1;
	root_1->left = root_2;

	Node* root_3 = new Node(7, nullptr, nullptr);

	root->right = root_3;

	Node* root_4 = new Node(6, nullptr, nullptr);
	Node* root_5 = new Node(9, nullptr, nullptr);
	Node* root_6 = new Node(10, nullptr, nullptr);

	root_3->left = root_4;
	root_3->right = root_5;
	root_5->right = root_6;

	ofstream file("MyFile.txt", ios::out || ios::trunc);

	addTreeInFile(file, root);

	system("pause");
	return 0;
}