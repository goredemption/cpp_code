#pragma once
#include<iostream>
#include<assert.h>
#include<vector>
using namespace std;

template<class K, class V>
struct AVLTreeNode {
	AVLTreeNode(const pair<K,V>& data=pair<K,V>())
		:_left(nullptr), _right(nullptr), _parent(nullptr),
		_bf(0), _data(data)
	{}
	AVLTreeNode* _left;
	AVLTreeNode* _right;
	AVLTreeNode* _parent;
	int _bf;
	pair<K,V> _data;
};

template<class K, class V>
class AVLTree {
public:
	typedef AVLTreeNode<K, V> Node;
	void InOrder() {
		_InOrder(_root);
	}
	Node* Find(const K& val) {
		Node* cur = _root;
		while (cur) {
			if (cur->_data.first < val) {
				cur = cur->_right;
			}
			else if (cur->_data.first > val) {
				cur = cur->_left;
			}
			else {
				return cur;
			}
		}
		return nullptr;
	}
	void RotateL(Node* cur) {
		Node* child = cur->_left;
		Node* grandfather = cur->_parent;

		cur->_left = child->_right;
		if (child->_right == nullptr) {
			;
		}
		else {
			child->_right->_parent = cur;
		}

		child->_parent = grandfather;
		if (grandfather == nullptr) {
			;
		}
		else if (grandfather->_left == cur) {
			grandfather->_left = child;
		}
		else {
			grandfather->_right = child;
		}

		child->_right = cur;
		cur->_parent = child;
		if (child->_parent == nullptr) {
			_root = child;
		}
		cur->_bf = 0;
		child->_bf = 0;
	}
	void RotateR(Node* cur) {
		Node* child = cur->_right;
		Node* grandfather = cur->_parent;
		cur->_right = child->_left;
		if (child->_left == nullptr) {
			;
		}
		else {
			child->_left->_parent = cur;
		}

		child->_left = cur;
		cur->_parent = child;

		child->_parent = grandfather;
		if (grandfather == nullptr) {
			;
		}
		else if (grandfather->_left == cur) {
			grandfather->_left = child;
		}
		else {
			grandfather->_right = child;
		}
		if (child->_parent == nullptr) {
			_root = child;
		}
		cur->_bf = 0;
		child->_bf = 0;
	}
	void RotateRL(Node* cur) {
		Node* parent = cur->_parent;
		Node* child = cur->_right;
		int child_bf = child->_bf;
		RotateR(cur);
		RotateL(parent);
		if (child_bf == -1) {
			child->_left->_bf = 0;
			child->_bf = 0;
			child->_right->_bf = 1;
		}
		else if (child_bf == 1) {
			child->_left->_bf = -1;
			child->_bf = 0;
			child->_right->_bf = 0;
		}
		else {
			child->_left->_bf = 0;
			child->_bf = 0;
			child->_right->_bf = 0;
		}
	}
	void RotateLR(Node* cur) {
		Node* parent = cur->_parent;
		Node* child = cur->_left;
		int child_bf = child->_bf;
		
		RotateL(cur);
		RotateR(parent);
		if (child_bf == -1) {
			child->_left->_bf = 0;
			child->_bf = 0;
			child->_right->_bf = 1;
		}
		else if (child_bf == 1) {
			child->_left->_bf = -1;
			child->_bf = 0;
			child->_right->_bf = 0;
		}
		else {
			child->_left->_bf = 0;
			child->_bf = 0;
			child->_right->_bf = 0;
		}
	}
	bool Insert(const pair<K, V>& val) {
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur) {
			if (cur->_data.first < val.first) {
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_data.first > val.first) {
				parent = cur;
				cur = cur->_left;
			}
			else {
				return false;
			}
		}
		Node* newnode = new Node(val);
		if (parent == nullptr) {
			_root = newnode;
		}
		else if (parent->_data.first < val.first) {
			parent->_right = newnode;
			newnode->_parent = parent;
		}
		else if (parent->_data.first > val.first) {
			parent->_left = newnode;
			newnode->_parent = parent;
		}
		else {
			assert(false);
		}
		cur = newnode;
		while (cur && parent) {
			if (parent->_left == cur) {
				parent->_bf -= 1;
				if (parent->_bf == 0) {
					break;
				}
				if (parent->_bf == -2) {
					if (cur->_bf == -1) {
						RotateL(parent);
						break;
					}
					else if (cur->_bf == 1) {
						RotateRL(cur);
						break;
					}
				}
				cur = parent;
				parent = parent->_parent;
			}
			else {
				parent->_bf += 1;
				if (parent->_bf == 0) {
					break;
				}
				if (parent->_bf == 2) {
					if (cur->_bf == 1) {
						RotateR(parent);
						break;
					}
					else if (cur->_bf == -1) {
						RotateLR(cur);
						break;
					}
				}
				cur = parent;
				parent = parent->_parent;
			}
		}
	}
	bool IsBalance() {
		return _IsBalance(_root);
	}
	int Height() {
		return _Height(_root);
	}
	int Size() {
		return _Size(_root);
	}
private:
	int _Size(Node* root) {
		if (root == nullptr) {
			return 0;
		}
		return _Size(root->_left) + _Size(root->_right) + 1;
	}
	int _Height(Node* root) {
		if (root == nullptr) {
			return 0;
		}
		int left = _Height(root->_left);
		int right = _Height(root->_right);
		return left > right ? left + 1 : right + 1;
	}
	bool _IsBalance(Node* root) {
		if (root == nullptr) {
			return true;
		}
		bool b1;
		int bf = _Height(root->_right) - _Height(root->_left);
		if (bf == root->_bf && bf<2 && bf>-2) {
			b1 = true;
		}
		else {
			b1 = false;
		}
		return b1 && _IsBalance(root->_left) && _IsBalance(root->_right);
	}
	//bool _IsBalance(Node* root)
	//{
	//	if (root == nullptr)
	//		return true;

	//	int leftHeight = _Height(root->_left);
	//	int rightHeight = _Height(root->_right);
	//	// 不平衡
	//	if (abs(leftHeight - rightHeight) >= 2)
	//	{
	//		cout << root->_data.first << endl;
	//		return false;
	//	}

	//	// 顺便检查一下平衡因子是否正确
	//	if (rightHeight - leftHeight != root->_bf)
	//	{
	//		cout << root->_data.first << endl;
	//		return false;
	//	}

	//	return _IsBalance(root->_left)
	//		&& _IsBalance(root->_right);
	//}

	void _InOrder(Node* root) {
		if (root == nullptr) {
			return;
		}
		_InOrder(root->_left);
		cout << root->_data.first << ':' << root->_data.second << endl;
		_InOrder(root->_right);
	}
private:
	Node* _root = nullptr;
};

void TestAVLTree1()
{
	int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13 };
	//int a[] = { 4,6,5 };
	AVLTree<int, int> t1;
	for (auto e : a)
	{
		if (e == 5)
		{
			int i = 0;
		}

		// 1、先看是插入谁导致出现的问题
		// 2、打条件断点，画出插入前的树
		// 3、单步跟踪，对比图一一分析细节原因
		t1.Insert({ e,e });

		cout << "Insert:" << e << "->" << t1.IsBalance() << endl;
	}

	t1.InOrder();

	cout << t1.IsBalance() << endl;
}

void TestAVLTree2()
{
	const int N = 100000000;
	vector<int> v;
	v.reserve(N);
	srand(time(0));

	for (size_t i = 0; i < N; i++)
	{
		v.push_back(rand() + i);
		//cout << v.back() << endl;
	}

	size_t begin2 = clock();
	AVLTree<int, int> t;
	for (auto e : v)
	{
		t.Insert(make_pair(e, e));
		//cout << "Insert:" << e << "->" << t.IsBalance() << endl;
	}
	size_t end2 = clock();

	cout << "Insert:" << end2 - begin2 << endl;
	//cout << t.IsBalance() << endl;

	cout << "Height:" << t.Height() << endl;
	cout << "Size:" << t.Size() << endl;

	size_t begin1 = clock();
	// 确定在的值
	for (auto e : v)
	{
		t.Find(e);
	}

	// 随机值
	/*for (size_t i = 0; i < N; i++)
	{
		t.Find((rand() + i));
	}*/
	//cout << t.IsBalance() << endl;
	size_t end1 = clock();

	cout << "Find:" << end1 - begin1 << endl;
}
