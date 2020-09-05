#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {

	int data;

	vector<TreeNode*> nodes;

	TreeNode(int _data, vector<TreeNode*> _nodes = { nullptr }) {
		data = _data;

		for (int i = 1; i < (int)_nodes.size(); i++)
		{
			nodes[i - 1] = _nodes[i];
		}
	}
};

class Tree
{
private:
	TreeNode* root;

public:
	Tree();
	Tree(Tree const& other);
	Tree& operator=(Tree const& other);
	~Tree();

	TreeNode*& getRoot();

	void addElementAt(int _data, TreeNode*& _root, int _searchedRoot = NULL);

	bool member(TreeNode* root, int x);

	void filterOdd(TreeNode*& root);

	void printTree(TreeNode* root);

private:

	TreeNode* copy(TreeNode* other) {

		if (other == nullptr)
		{
			return other;
		}

		TreeNode* newRoot = new TreeNode(other->data);

		for (int i = 0; i < (int)other->nodes.size(); i++)
		{
			TreeNode* newChild = copy(other->nodes[i]);
			newRoot->nodes.push_back(newChild);
		}

		return newRoot;
	}

	void deleteTree(TreeNode* root) {
		if (root != nullptr)
		{
			for (int i = 0; i < (int)root->nodes.size(); i++)
			{
				deleteTree(root->nodes[i]);
			}


			delete root;
		}
	}

};


int main() {

	/*Tree tree;

	tree.addElementAt(8, tree.getRoot());
	tree.addElementAt(2, tree.getRoot(), 8);
	tree.addElementAt(3, tree.getRoot(), 8);

	tree.addElementAt(4, tree.getRoot(), 3);
	tree.addElementAt(5, tree.getRoot(), 3);
	tree.addElementAt(6, tree.getRoot(), 3);

	tree.printTree(tree.getRoot());

	tree.filterOdd(tree.getRoot());

	tree.printTree(tree.getRoot());*/

	/*cout << boolalpha << tree.member(tree.getRoot(), 8) << endl;

	cout << boolalpha << tree.member(tree.getRoot(), 2) << endl;
	cout << boolalpha << tree.member(tree.getRoot(), 3) << endl;
	cout << boolalpha << tree.member(tree.getRoot(), 4) << endl;
	cout << boolalpha << tree.member(tree.getRoot(), 5) << endl;
	cout << boolalpha << tree.member(tree.getRoot(), 6) << endl;*/


	system("pause");
	return 0;
}

Tree::Tree() :root(nullptr)
{ }

Tree::Tree(Tree const& other) : root(copy(other.root))
{ }

Tree& Tree::operator=(Tree const& other)
{
	if (this != &other)
	{
		deleteTree(root);
		root = copy(other.root);
	}

	return *this;
}

Tree::~Tree()
{
	deleteTree(root);
}

TreeNode*& Tree::getRoot()
{
	return root;
}

void Tree::addElementAt(int _data, TreeNode*& _root, int _searchedRoot)
{
	bool isAdded = false;

	if (_root == nullptr)
	{
		_root = new TreeNode(_data);
		cout << "Added main root: " << _data << endl;
		return;
	}

	if (_searchedRoot == NULL)
	{
		TreeNode* newNode = new TreeNode(_data);
		_root->nodes.push_back(newNode);
		isAdded = true;
		cout << "Added the new node: " << _data << "\tWith parent: " << _root->data << endl;
		return;
	}

	if (_root->data == _searchedRoot)
	{
		TreeNode* newNode = new TreeNode(_data);
		_root->nodes.push_back(newNode);
		isAdded = true;
		cout << "Added the new node: " << _data << "\tWith father: " << _root->data << endl;
		return;
	}

	for (int i = 0; i < (int)_root->nodes.size(); i++)
	{
		if (_root->nodes[i] == nullptr)
		{
			return;
		}

		if (isAdded)
		{
			return;
		}

		addElementAt(_data, _root->nodes[i], _searchedRoot);
	}
}

bool Tree::member(TreeNode* root, int x)
{
	bool flag = false;

	if (root == nullptr)
	{
		return flag;
	}

	if (root->data == x)
	{
		flag = true;
		return flag;
	}

	for (int i = 0; i < (int)root->nodes.size(); i++)
	{
		member(root->nodes[i], x);
	}


}

void Tree::filterOdd(TreeNode*& root)
{
	if (root->data % 2 != 0)
	{
		deleteTree(root);
	}
	else
	{
		for (int i = 0; i < root->nodes.size(); i++)
		{
			filterOdd(root->nodes[i]);
		}
	}
}

void Tree::printTree(TreeNode* root)
{
	cout << "Root: " << root->data << endl;

	for (int i = 0; i < root->nodes.size(); i++)
	{
		cout << "Child: " << root->nodes[i]->data << "\tOf root: " << root->data << endl;
	}
	for (int i = 0; i < root->nodes.size(); i++)
	{
		printTree(root->nodes[i]);
	}
}

