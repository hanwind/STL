#ifndef RBTREE_H
#define RBTREE_H
#include <iostream>
using namespace std;
namespace HanSTL{
	enum color
	{
		RED,
		BLACK,
	};
	template<class K,class V>
	struct RBTreeNode
	{
		int _color;
		K _Key;
		V _Value;
		RBTreeNode<K,V> * _left;
		RBTreeNode<K,V> * _right;
		RBTreeNode<K,V> * _parent;
		RBTreeNode(const K &key,const V &value)
			:_Key(key),_Value(value),_color(RED),_left(NULL),_right(NULL),_parent(NULL)
		{}
	};
	template<class K,class V>
	class RBTree
	{
		typedef RBTreeNode<K,V> node;
	public:
		RBTree():_root(NULL){}
	bool insert(const K &key,const V &value)//插入操作
	{
		if (_root == NULL)
		{
			_root = new node(key,value);
			_root->_color = BLACK;
			return  true;
		}
		node *parent = NULL;
		node *cur = _root;
		while (cur)
		{
			if (cur->_Key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_Key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return false;
			}

		}
		//找到插入位置将节点插入
		if (parent->_Key > key)
		{
			cur = new node(key,value);
			parent->_left = cur;
			cur->_parent = parent;
		}
		else if (parent->_Key < key)
		{
			cur = new node(key,value);
			parent->_right = cur;
			cur->_parent = parent;
		}
		//插入后调整
		while (cur  != _root && parent->_color == RED)
		{
			node *grandFather = parent->_parent;
			node *uncle = NULL;
			if (parent == grandFather->_left) //左边的情况
			{
				uncle = grandFather->_right;
				if (uncle && uncle->_color == RED)//情况一
				{
					grandFather->_color = RED;
					parent->_color = BLACK;
					uncle->_color = BLACK;

					cur = grandFather;
					parent = grandFather->_parent;
				}
				else //uncle ==NULL || uncle->_color ==没有叔叔节点或者叔叔节点为黑色
				{
					if (cur == parent->_right)
					{
						RotateL(parent);
					}
					parent->_color = BLACK;
					grandFather->_color = RED;
					RotateR(grandFather);
				}
			}
			else if (parent == grandFather->_right)//右边的情况
			{
				uncle = grandFather->_left;
				if (uncle && uncle->_color == RED)
				{
					grandFather->_color = RED;
					parent->_color = BLACK;
					uncle->_color = BLACK;

					cur = grandFather;
					parent  = grandFather->_parent;
				}
				else
				{
					if (cur == cur->_parent->_left)
					{
						RotateR(parent);
					}
					parent->_color = BLACK;
					grandFather->_color = RED;
					RotateL(grandFather);
				}

			}
		}//while 结束
		_root->_color = BLACK;//根节点永远为黑色

	}

	bool isRBTree()//判断是否是红黑树
	{
		int blackNodeNum = 0;
		int curBlackNodeNum = 0;
		node *cur = _root;
		while (cur)
		{
			if (cur->_color == BLACK)
				++blackNodeNum;
			cur = cur->_left;
		}
		return _isRBtree(_root->_left,blackNodeNum,curBlackNodeNum) &&
			_isRBtree(_root->_right,blackNodeNum,curBlackNodeNum);
	}

	void  InOrder()//中序遍历
	{
		_InOrder(_root);
	}

	protected:
		node *_root;
		bool _isRBtree(node *root,int blackNodeNum,int curBlackNodeNum)
		{
			if (root == NULL)
			{
				return true;
			}
			if (root->_color == BLACK)
			{
				++curBlackNodeNum;
			}
			if (blackNodeNum == curBlackNodeNum)
			{
				if (root->_parent ==NULL)//假如当前是根节点
				{
					return true;
				}
				else if (root->_color == RED && root->_color == root->_parent->_color)//子节点为红，则父节点必为黑
				{
					return false;
				}
				else
				{
					return true;
				}

			}

		}
		void _InOrder(node *root)
		{
			if (root == NULL)
			{
				return;
			}
			_InOrder(root->_left);
			cout<<root->_Key<<" ";
			_InOrder(root->_right);
		}
		void RotateL(node *&parent)//左单旋
		{
			node * subR = parent->_right;
			node * subRL = subR->_left;
			parent->_right = subRL;
			if (subRL)
			{
				subRL->_parent = parent;
			}
			subR->_left = parent;
			subR->_parent = parent->_parent;
			parent->_parent = subR;
			parent = subR;
			if (parent->_parent == NULL)//如果是根节点
			{
				_root = parent;
			}
			else if (parent->_parent->_Key > parent->_Key)//本来在左侧的子树，旋转后依旧在左侧
			{
				parent->_parent->_left = parent;
			}
			else if (parent->_parent->_Key < parent->_Key)//本来在右侧的子树，选择后依旧在右侧
			{
				parent->_parent->_right = parent;
			}
		}
		void RotateR(node *&parent)//右单旋
		{
			node * subL = parent->_left;
			node *subLR = subL->_right;
			parent->_left = subLR;
			if (subLR != NULL)
			{
				subLR->_parent = parent;
			}
			subL->_right = parent;
			subL->_parent = parent->_parent;
			parent->_parent = subL;

			parent= subL;
			if(parent->_parent == NULL)
			{
				_root = parent;
			}
			else if (parent->_parent->_Key > parent->_Key)
			{
				parent->_parent->_left = parent;
			}
			else if(parent->_parent->_Key < parent->_Key)
			{
				parent->_parent->_right = parent;
			}
		}
	private:
	};
}
#endif