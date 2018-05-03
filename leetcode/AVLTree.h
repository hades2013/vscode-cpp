//AVLTree.h

#ifndef __AVLTREE_H__
#define __AVLTREE_H__
#include "AVLNode.h"
//AVL树的模板实现
template <typename KeyType>
class AVLTree
{
    typedef AVLNode<KeyType> AVLNode;//类型定义
private:
    AVLNode * avlroot;//私有数据结构
    int __height(const AVLNode *root);//求树的高度
    int __diff(const AVLNode*root);//高度差（平衡因子）

    //AVL4种旋转：左左，左右，右右，右左
    //X定义为插入位置节点到根节点的路径上平衡条件被改变的节点中最深的那个节点
    //X通过递归返回的方式找到
    //左左：插入点位于X的左孩子节点的左子树
    //左右：插入点位于X的左孩子节点的右子树
    //右右：插入点位于X的右孩子节点的右子树
    //右左：插入点位于X的右孩子节点的左子树

    //单旋转
    AVLNode * __ll_Rotation(AVLNode *root);//left-left rotation
    AVLNode * __rr_Rotation(AVLNode *root);//right-right rotation
    //双旋转
    AVLNode * __lr_Rotation(AVLNode *root);//left-right rotation
AVLNode * __rl_Rotation(AVLNode *root);//right-left rotation



    AVLNode * __Balance(AVLNode *root);//平衡操作
    AVLNode * __Insert(AVLNode *root, const KeyType &k);//插入的内部实现


    //中序遍历的两种重载
    void __InorderTraversal(const AVLNode* root);//输出
    void __InorderTraversal(const AVLNode*root, std::vector<KeyType>&vec);//结果保存


    bool __isLeaf(AVLNode* const &);//判断是否是叶子节点
    bool __isNodeWithTwoChild(AVLNode * const &);//判断是否有两个孩子

    AVLNode* __search(AVLNode *const root, const KeyType &k);//查找的内部实现


    void __deleteTree(AVLNode * root);//删除树的所有节点


    AVLNode* __Delete(AVLNode * root, const KeyType& k);//删除节点

    AVLNode*__treeMin(AVLNode *root);//求当前根节点最小（一路向左）
    AVLNode*__treeMax(AVLNode*root);//求当前根节点的最大（一路向右）

public:
    AVLTree(){ avlroot = NULL; }//默认构造函数
    ~AVLTree();//析构函数删除树中所有节点
    AVLTree(const std::vector<KeyType>&);//构造函数，容器构造
    AVLTree(const KeyType * arr, size_t len);//构造函数，数组构造
    void InorderTraversal();//中序遍历外部接口
    void InorderTraversal(std::vector<KeyType>&);//中序遍历外部接口重载2
    bool Delete(const KeyType &k);//删除节点的外部接口
    bool Insert(const KeyType & k);//插入节点的外部接口
    bool IsEmpty(){ return avlroot == NULL; }//树空？
    bool search(const KeyType &k);//查询外部接口

};//class AVLTree
//...


#endif