//AVLTree.cpp

#include "AVLTree.h"


//插入节点的私有成员实现
template <typename KeyType>
AVLNode<KeyType> * AVLTree<KeyType>::__Insert(AVLNode * root, const KeyType&k)
{
    if (NULL == root)
    {
        root = new AVLNode(k);
        return root;
    }//递归返回条件
    else if (k < root->key)
    {
        root->left = __Insert(root->left, k);//递归左子树
        //balance operation
        root = __Balance(root);//平衡操作包含了四种旋转
    }
    else if (k>root->key)
    {
        root->right = __Insert(root->right, k);//递归右子树
        //balance operation
        root = __Balance(root);//平衡操作包含了四种旋转
    }
    return root;
}

//树高
template <typename KeyType>
int AVLTree<KeyType>::__height(const AVLNode *root)//求树高
{
    if (root == NULL)
        return 0;
    return std::max(__height(root->left) , __height(root->right)) + 1;
}
//平衡因子
template <typename KeyType>
int AVLTree<KeyType>::__diff(const AVLNode *root)//求平衡因子，即当前节点左右子树的差
{
    return __height(root->left) - __height(root->right);
}

//平衡操作
template <typename KeyType>
AVLNode<KeyType> * AVLTree<KeyType>::__Balance(AVLNode *root)
{
    int balanceFactor = __diff(root);//__diff用来计算平衡因子（左右子树高度差）
    if (balanceFactor > 1)//左子树高于右子树
    {
        if (__diff(root->left) > 0)//左左外侧
            root=__ll_Rotation(root);
        else//左右内侧
            root=__lr_Rotation(root);
    }
    else if (balanceFactor < -1)//右子树高于左子树
    {
        if (__diff(root->right) > 0)//右左内侧
            root=__rl_Rotation(root);
        else//右右外侧
            root=__rr_Rotation(root);
    }
    return root;
}

//四种AVL旋转

template <typename KeyType>
AVLNode<KeyType> * AVLTree<KeyType>::__rr_Rotation(AVLNode *root)//right-right rotation
{
    AVLNode* tmp;
    tmp = root->right;
    root->right = tmp->left;
    tmp->left = root;
    return tmp;
}
template <typename KeyType>
AVLNode<KeyType> * AVLTree<KeyType>::__ll_Rotation(AVLNode *root)//left-left rotation
{
    AVLNode * tmp;
    tmp = root->left;
    root->left = tmp->right;
    tmp->right = root; 
    return tmp;
}
template <typename KeyType>
AVLNode<KeyType> * AVLTree<KeyType>::__lr_Rotation(AVLNode *root)//left-right rotation
{
    AVLNode * tmp;
    tmp = root->left;
    root->left = __rr_Rotation(tmp);
    return __ll_Rotation(root);
}

template <typename KeyType>
AVLNode<KeyType> * AVLTree<KeyType>::__rl_Rotation(AVLNode *root)//right-left rotation
{
    AVLNode * tmp;
    tmp = root->right;
    root->right = __ll_Rotation(tmp);
    return __rr_Rotation(root);
}

//删除节点的私有成员实现
template <typename KeyType>
AVLNode<KeyType>* AVLTree<KeyType>::__Delete(AVLNode *root, const KeyType& k)
{
    if (NULL == root)
        return root;
    if (!search(k))//查找删除元素是否存在
    {
        std::cerr << "Delete error , key not find" << std::endl;
        return root;
    }

    if (k == root->key)//根节点
    {
        if (__isNodeWithTwoChild(root))//左右子树都非空
        {
            if (__diff(root) > 0)//左子树更高，在左边删除
            {
                root->key = __treeMax(root->left)->key;//以左子树的最大值替换当前值
                root->left = __Delete(root->left, root->key);//删除左子树中已经替换上去的节点
            }
            else//右子树更高，在右边删除
            {
                root->key = __treeMin(root->right)->key;
                root->right = __Delete(root->right, root->key);
            }
        }
        else//有一个孩子、叶子节点的情况合并
        {
            //if (!__isLeaf(root))
                AVLNode * tmp = root;
                root = (root->left) ? (root->left) :( root->right);
                delete tmp;
                tmp = NULL;
        }
    }//end-if
    else if (k < root->key)//往左边删除
    {
        root->left = __Delete(root->left, k);//左子树中递归删除
        //判断平衡的条件与在插入时情况类似
        if (__diff(root) < -1)//不满足平衡条件，删除左边的后，右子树变高
        {
            if (__diff(root->right) > 0)
            {
                root = __rl_Rotation(root);
            }
            else
            {
                root = __rr_Rotation(root);
            }
        }
    }//end else if
    else
    {
        root->right = __Delete(root->right, k);
        if (__diff(root) > 1)//不满足平衡条件
        {
            if (__diff(root->left) < 0)
            {
                root = __lr_Rotation(root);
            }
            else
            {
                root = __ll_Rotation(root);
            }
        }
    }
    return root;
}


//删除节点的外部接口
template <typename KeyType>
bool AVLTree<KeyType>::Delete(const KeyType &k)
{
    return __Delete(avlroot, k)==NULL?false:true;
}

//构造函数1-容器构造
template < typename KeyType >
AVLTree<KeyType>::AVLTree(const std::vector<KeyType>&vec)
{
    avlroot = NULL;
    for (int i = 0; i < (int)vec.size(); i++)
    {
        Insert(vec[i]);
    }
}

//构造函数2-数组构造
template < typename KeyType >
AVLTree<KeyType>::AVLTree(const KeyType * arr,size_t len)
{
    avlroot = NULL;
    for (int i = 0; i < (int)len; i++)
    {
        Insert(*(arr + i));
    }
}

template <typename KeyType>
void AVLTree<KeyType>::__deleteTree(AVLNode *root)//删除所有节点
{
    if (NULL == root)
        return;
    __deleteTree(root->left);
    __deleteTree(root->right);
    delete root;
    root = NULL;
    return;
}

//析构函数
template <typename KeyType>
AVLTree<KeyType>::~AVLTree()
{
    __deleteTree(avlroot);
}

//查找内部实现
template <typename KeyType>
AVLNode<KeyType>* AVLTree<KeyType>::__search(AVLNode *const root, const KeyType &k)
{
    if (NULL == root)
        return NULL;
    if (k == root->key)
        return root;
    else if (k > root->key)
        return __search(root->right, k);
    else
        return __search(root->left, k);
}
//查找外部接口
template <typename KeyType>
bool AVLTree<KeyType>::search(const KeyType &k)
{
    return __search(avlroot, k) == NULL ? false : true;
}


//中序遍历内部调用（1直接打印）
template <typename KeyType>
void AVLTree<KeyType>::__InorderTraversal(const AVLNode*root)
{
    if (NULL == root)
        return;
    __InorderTraversal(root->left);
    std::cout << root->key << " ";
    __InorderTraversal(root->right);
}

//中序遍历内部调用（2存入容器）
template <typename KeyType>
void AVLTree<KeyType>::__InorderTraversal(const AVLNode*root,std::vector<KeyType>&vec)
{
    if (NULL == root)
        return;
    __InorderTraversal(root->left);
    vec.push_back(root->val);
    __InorderTraversal(root->right);
}

//中序遍历外部接口（重载版本1）
template <typename KeyType>
void AVLTree<KeyType>::InorderTraversal()
{
    __InorderTraversal(avlroot);
}

//中序遍历外部接口（重载版本2）
template <typename KeyType>
void AVLTree<KeyType>::InorderTraversal(std::vector<KeyType>&vec)
{
    __InorderTraversal(avlroot,vec);
}

int main()
{

#if 1
    std::vector<int>vec = { 7, 6, 5, 4, 3, 2, 1 };
    AVLTree<int> avl(vec);
    avl.Insert(8);
    int keyToFind = 9;
    if (avl.search(keyToFind))
    {
        std::cout << keyToFind << " is found" << std::endl;
    }
    else
    {
        std::cerr << keyToFind << " is not found" << std::endl;
    }

    keyToFind = 4;
    if (avl.search(keyToFind))
    {
        std::cout << keyToFind << " is found" << std::endl;
    }
    else
    {
        std::cerr << keyToFind << " is not found" << std::endl;
    }

    avl.Delete(4);
    //avl.InorderTraversal();
#endif
    std::cout << std::endl;
    system("pause");
    return 0;
}