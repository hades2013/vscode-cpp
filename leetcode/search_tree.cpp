#define _CRT_SECURE_NO_WARNINGS 1  
#include<iostream>  
#include<stdlib.h>  
  
using namespace std;  
template<class K,class V>  
struct AVLTreeNode  
{  
    K _key;  
    V _value;  
    AVLTreeNode<K, V> *_left;  
    AVLTreeNode<K, V> *_right;  
    AVLTreeNode<K, V> *_parent;  
    int _bf;//平衡因子，只能是-1，0，1  
  
    AVLTreeNode(const K&key, const V&value)  
        :_key(key)  
        , _value(value)  
        , _left(NULL)  
        , _right(NULL)  
        , _parent(NULL)  
        , _bf(0)  
    {}  
};  
template<class K, class V>  
class AVLTree  
{  
    typedef AVLTreeNode<K, V> Node;  
public:  
    AVLTree()  
        :_root(NULL)  
    {}  
    ~AVLTree()  
    {  
        _destroy(_root);  
    }  
public:  
    bool Insert(const K&key, const V&value)//插入  
    {  
        if (_root == NULL)  
        {  
            _root = new Node(key, value);  
        }  
        Node*parent = NULL;  
        Node*cur = _root;  
        while (cur)  
        {  
            if (cur->_key > key)  
            {  
                parent = cur;  
                cur = cur->_left;  
            }  
            else if (cur->_key < key)  
            {  
                parent = cur;  
                cur = cur->_right;  
            }  
            else  
                return false;  
        }  
        cur = new Node(key, value);  
        if (parent->_key>key)  
        {  
            parent->_left = cur;  
            cur->_parent = parent;  
        }  
        else  
        {  
            parent->_right = cur;  
            cur->_parent = parent;  
        }  
  
        bool IsRotate = false;  
  
        while (parent)  
        {  
            if (parent->_left == cur)  
            {  
                parent->_bf--;  
            }  
            else  
            {  
                parent->_bf++;  
            }  
  
            if (parent->_bf == 0)  
            {  
                break;  
            }  
            else if (parent->_bf == 1 || parent->_bf == -1)  
            {  
                cur = parent;  
                parent = cur->_parent;  
            }  
            else  
            {  
                IsRotate = true;  
                if (parent->_bf == 2)  
                {  
                    if (cur->_bf == 1)  
                    {  
                        //left    
                        _RotateL(parent);  
                    }  
                    else  
                    {  
                        //right left    
                        _RotateRL(parent);  
                    }  
                }  
                else if (parent->_bf == -2)  
                {  
                    if (cur->_bf == -1)  
                    {  
                        //right    
                        _RotateR(parent);  
                    }  
                    else  
                    {  
                        //left right    
                        _RotateLR(parent);  
                    }  
                }  
                break;  
            }  
        }  
        if (IsRotate)  
        {  
            Node *ppNode = parent->_parent;  
            if (ppNode == NULL)  
            {  
                _root = parent;  
            }  
            else  
            {  
                if (ppNode->_key < parent->_key)  
                {  
                    ppNode->_right = parent;  
                }  
                else  
                {  
                    ppNode->_left = parent;  
                }  
            }  
        }  
        return true;  
    }  
    bool IsBalanceTree()//判断是否是平衡二叉树  
    {  
        return _IsBalance(_root);  
    }  
    void InOrder()//前序遍历  
    {  
        _InOrder(_root);  
        cout << endl;  
    }  
protected:  
    bool _IsBalance(Node *root)  
    {  
        return true;  
    }  
    int _Height(Node *root)//求高  
    {  
        if (root == NULL)  
            return 0;  
        int leftlen = _Height(root->_left);  
        int rightlen = _Height(root->_right);  
        return leftlen > rightlen ? leftlen + 1 : rightlen + 1;  
    }  
    void _RotateL(Node*& parent)//左单旋  
    {  
        Node *subR = parent->_right;  
        Node *subRL = subR->_left;  
        parent->_right = subRL;  
        if (subRL != NULL)  
        {  
            subRL->_parent = parent;  
        }  
        subR->_left = parent;  
        subR->_parent = parent->_parent;  
        parent->_parent = subR;  
        parent->_bf = 0;  
        subR->_bf = 0;  
        parent = subR;  
    }  
    void _RotateR(Node*& parent)//右单旋  
    {  
        Node*subL = parent->_left;  
        Node*subLR = subL->_right;  
        parent->_left = subLR;  
        if (subLR != NULL)  
        {  
            subLR->_parent = parent;  
        }  
        subL->_right = parent;  
        subL->_parent = parent->_parent;  
        parent->_parent = subL;  
        subL->_bf = 0;  
        parent->_bf = 0;  
        parent = subL;  
    }  
    void _RotateLR_R(Node*& parent)//左右旋转(递归)  
    {  
        _RotateL(parent->_right);  
        _RotateR(parent);  
    }  
    void _RotateRL_R(Node*& parent)//右左旋转(递归)  
    {  
        _RotateR(parent->_left);  
        _RotateL(parent);  
    }  
    void _RotateLR(Node*& parent)   //左右旋转(非递归)  
    {  
        Node *subL = parent->_left;  
        Node *subLR = subL->_right;  
        subL->_right = subLR->_left;  
        if (subLR->_left != NULL)  
        {  
            subLR->_left->_parent = subL;  
        }  
        subLR->_left = subL;  
        subL->_parent = subLR;  
        //调整平衡因子，右树减去左树  
        if (subLR->_bf == 0 || subLR->_bf == 1)  
        {  
            subL->_bf = 0;  
        }  
        else  
        {  
            subL->_bf = 1;  
        }  
        parent->_left = subLR->_right;  
        if (subLR->_right != NULL)  
        {  
            subLR->_right->_parent = parent;  
        }  
        subLR->_right = parent;  
        subLR->_parent = parent->_parent;  
        parent->_parent = subLR;  
        //调整平衡因子，右树减去左树  
        if (subLR->_bf == 0 || subLR->_bf == 1)  
        {  
            parent->_bf = 0;  
        }  
        else  
        {  
            parent->_bf = 1;  
        }  
        parent = subLR;  
        subLR->_bf = 0;  
    }  
    void _RotateRL(Node*& parent)//右左旋转(非递归)  
    {  
        Node *subR = parent->_right;  
        Node *subRL = subR->_left;  
        subR->_left = subRL->_right;  
  
        if (subRL->_right != NULL)  
        {  
            subRL->_right->_parent = subR;  
        }  
        subRL->_right = subR;  
        subR->_parent = subRL;  
  
        if (subRL->_bf == 0 || subRL->_bf == 1)  
        {  
            subR->_bf = 0;  
        }  
        else  
        {  
            subR->_bf = 1;  
        }  
  
        parent->_right = subRL->_left;  
  
        if (subRL->_left != NULL)  
        {  
            subRL->_left->_parent = parent;  
        }  
        subRL->_left = parent;  
        subRL->_parent = parent->_parent;  
        parent->_parent = subRL;  
        if (subRL->_bf == 0 || subRL->_bf == -1)  
        {  
            parent->_bf = 0;  
        }  
        else  
        {  
            parent->_bf = -1;  
        }  
        parent = subRL;  
        subRL->_bf = 0;  
    }  
    void _InOrder(Node *root)  
    {  
        if (root == NULL)  
        {  
            return;  
        }  
        _InOrder(root->_left);  
        cout << root->_key << " ";  
        _InOrder(root->_right);  
    }  
    void _destroy(Node *root)  
    {  
        if (root)  
        {  
            _destroy(root->_left);  
            _destroy(root->_right);  
            delete root;  
            root = NULL;  
        }  
    }  
private:  
    Node *_root;  
};  
void test()  
{  
    AVLTree<int, int> AVLtree;  
    int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };  
    for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++)  
    {  
        AVLtree.Insert(a[i], a[i]);  
    }  
    AVLtree.InOrder();  
    AVLtree.IsBalanceTree();  
}  
int main()  
{  
    test();  
    system("pause");  
    return 0;  
}  