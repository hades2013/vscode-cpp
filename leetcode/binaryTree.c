#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct TreeNode {
    struct TreeNode *leftPtr;  /* pointer to left subtree */
    int data;                  /* node data */
    struct TreeNode *rightPtr; /* pointer to right subtree */
};

typedef struct TreeNode TreeNode;

void insertNode(TreeNode **treePtr, int value);
TreeNode * binaryTreeSereach(TreeNode * const treePtr, int value);
void deleteNode(TreeNode **treePtrP, int value);
void outputTree(TreeNode *treePtr, int spaces);
void deleteNode2(TreeNode **treePtrP, int value);

int main(void)
{
    int arr[] = { 45, 83, 28, 97, 71, 40, 18, 77, 99, 92, 72, 69, 44, 32, 19, 11 };
    int i;                      /* loop counter */
    int item;                   /* value to deal with */
    int totalSpaces = 0;        /* spaces preceding output */
    TreeNode *rootPtr = NULL; /* points to the tree root */

    srand(time(NULL)); /* randomize */
    printf("The numbers being placed in the tree are:\n\n");

    for (i = 0; i < sizeof(arr) / sizeof(int); i++) {
        item = arr[i];
        printf("%3d", item);
        insertNode(&rootPtr, item);
    }

    printf("\n\n\nnow the tree is:\n\n");

    if (rootPtr == NULL)
        printf("empty tree\n");
    else
        outputTree(rootPtr, totalSpaces);

    //random delete Nodes, then output the tree
    while (rootPtr != NULL)
    {
        item = rand() % 16;
        printf("\n\nafter delete %d:\n\n", arr[item]);
        deleteNode2(&rootPtr, arr[item]);

        if (rootPtr == NULL)
            printf("empty tree\n");
        else
            outputTree(rootPtr, totalSpaces);

    }

    return 0; 
}

void insertNode(TreeNode **treePtr, int value)
{

    /* if treePtr is NULL */
    if (*treePtr == NULL) {

        *treePtr = malloc(sizeof(TreeNode));

        if (*treePtr != NULL) {
            (*treePtr)->data = value;
            (*treePtr)->leftPtr = NULL;
            (*treePtr)->rightPtr = NULL;
        }
        else {
            printf("%d not inserted. No memory available.\n", value);
        }

    }
    else {

        /* insert node in left subtree */
        if (value < (*treePtr)->data) {
            insertNode(&((*treePtr)->leftPtr), value);
        }
        else {

            /* insert node in right subtree */
            if (value >(*treePtr)->data) {
                insertNode(&((*treePtr)->rightPtr), value);
            }
            else {
                printf("dup");
            }
        }

    }

}

TreeNode *binaryTreeSereach(TreeNode * const treePtr, int value)
{
    TreeNode *tempPtr = treePtr;

    while (tempPtr != NULL && tempPtr->data != value)
    {
        if (value > tempPtr->data)
            tempPtr = tempPtr->rightPtr;
        else
            tempPtr = tempPtr->leftPtr;
    }

    return tempPtr;
}

void deleteNode(TreeNode **treePtrP, int value)
{
    TreeNode *deleteNodePtr = *treePtrP;
    TreeNode *parentNodeOfDeletePtr = NULL;
    TreeNode *substituteNodePtr;
    TreeNode *parentNodeOfSubstitutePtr;

    //find deleNode and its parentNode
    while (deleteNodePtr != NULL && value != deleteNodePtr->data)
    {
        parentNodeOfDeletePtr = deleteNodePtr;

        if (deleteNodePtr->data > value)
        {
            deleteNodePtr = deleteNodePtr->leftPtr;
        }
        else
        {
            deleteNodePtr = deleteNodePtr->rightPtr;
        }
    }

    //case that can't find such Node
    if (deleteNodePtr == NULL)
    {
        printf("no such Node, delete fail\n\n");
        return;

    }

    //delete a leafNode
    if (deleteNodePtr->leftPtr == NULL && deleteNodePtr->rightPtr == NULL)
    {
        //delete Node is root
        if (parentNodeOfDeletePtr == NULL)
        {
            *treePtrP = NULL;
        }
        else if (parentNodeOfDeletePtr->leftPtr == deleteNodePtr)
        {
            parentNodeOfDeletePtr->leftPtr = NULL;
        }
        else
        {
            parentNodeOfDeletePtr->rightPtr = NULL;
        }

    }
    //delete a Node which has a left child Node
    else if (deleteNodePtr->leftPtr != NULL && deleteNodePtr->rightPtr == NULL)
    {
        //delete Node is root
        if (parentNodeOfDeletePtr == NULL)
        {
            *treePtrP = deleteNodePtr->leftPtr;
        }
        else if (parentNodeOfDeletePtr->rightPtr == deleteNodePtr)
            parentNodeOfDeletePtr->rightPtr = deleteNodePtr->leftPtr;
        else
            parentNodeOfDeletePtr->leftPtr = deleteNodePtr->leftPtr;

    }

    //delete a Node which has a right child Node
    else if (deleteNodePtr->leftPtr == NULL && deleteNodePtr->rightPtr != NULL)
    {
        //delete Node is root
        if (parentNodeOfDeletePtr == NULL)
        {
            *treePtrP = deleteNodePtr->rightPtr;
        }
        else if (parentNodeOfDeletePtr->rightPtr == deleteNodePtr)
            parentNodeOfDeletePtr->rightPtr = deleteNodePtr->rightPtr;
        else
            parentNodeOfDeletePtr->leftPtr = deleteNodePtr->rightPtr;

    }
    //delete a Node which has a left and a right child Node
    else
    {
        parentNodeOfSubstitutePtr = deleteNodePtr;
        substituteNodePtr = deleteNodePtr->leftPtr;

        //search down and right to find substituteNode and its parentNode
        while (substituteNodePtr->rightPtr != NULL)
        {
            parentNodeOfSubstitutePtr = substituteNodePtr;
            substituteNodePtr = substituteNodePtr->rightPtr;

        }

        //delete Node is root
        if (parentNodeOfDeletePtr == NULL)
        {
            *treePtrP = substituteNodePtr;
        }
        else if (parentNodeOfDeletePtr->leftPtr == deleteNodePtr)
        {
            parentNodeOfDeletePtr->leftPtr = substituteNodePtr;
        }
        else
        {
            parentNodeOfDeletePtr->rightPtr = substituteNodePtr;
        }

        substituteNodePtr->rightPtr = deleteNodePtr->rightPtr;

        if (parentNodeOfSubstitutePtr != deleteNodePtr)
        {
            substituteNodePtr->leftPtr = deleteNodePtr->leftPtr;

            if (parentNodeOfSubstitutePtr->leftPtr == substituteNodePtr)
            {
                parentNodeOfSubstitutePtr->leftPtr = substituteNodePtr->leftPtr;
            }
            else
            {
                parentNodeOfSubstitutePtr->rightPtr = substituteNodePtr->leftPtr;
            }
        }

    }

    free(deleteNodePtr);
}

void outputTree(TreeNode *treePtr, int spaces)
{
    int loop;

    while (treePtr != NULL) {

        outputTree(treePtr->rightPtr, spaces + 4);

        for (loop = 1; loop <= spaces; loop++) {
            printf(" ");
        }

        printf("%d\n", treePtr->data);

        outputTree(treePtr->leftPtr, spaces + 4);
        treePtr = NULL;
    }
}

void deleteNode2(TreeNode **treePtrP, int value)
{
    TreeNode *deleteNodePtr = *treePtrP;
    TreeNode *parentNodeOfDeletePtr = NULL;
    TreeNode *substituteNodePtr;
    TreeNode *parentNodeOfSubstitutePtr;

    //find deleNode and its parentNode
    while (deleteNodePtr != NULL && value != deleteNodePtr->data)
    {
        parentNodeOfDeletePtr = deleteNodePtr;

        if (deleteNodePtr->data > value)
        {
            deleteNodePtr = deleteNodePtr->leftPtr;
        }
        else
        {
            deleteNodePtr = deleteNodePtr->rightPtr;
        }
    }

    //case that can't find such Node
    if (deleteNodePtr == NULL)
    {
        printf("no such Node, delete fail\n\n");
        return;

    }

    // delete a leafNode
    if (deleteNodePtr->leftPtr == NULL && deleteNodePtr->rightPtr == NULL)
    {
        //delete Node is root
        if (parentNodeOfDeletePtr == NULL)
        {
            *treePtrP = NULL;
        }
        else if (parentNodeOfDeletePtr->leftPtr == deleteNodePtr)
        {
            parentNodeOfDeletePtr->leftPtr = NULL;
        }
        else
        {
            parentNodeOfDeletePtr->rightPtr = NULL;
        }

    }
    //delete a Node which has a left child Node
    else if (deleteNodePtr->leftPtr != NULL && deleteNodePtr->rightPtr == NULL)
    {
        //delete Node is root
        if (parentNodeOfDeletePtr == NULL)
        {
            *treePtrP = deleteNodePtr->leftPtr;
        }
        else if (parentNodeOfDeletePtr->rightPtr == deleteNodePtr)
            parentNodeOfDeletePtr->rightPtr = deleteNodePtr->leftPtr;
        else
            parentNodeOfDeletePtr->leftPtr = deleteNodePtr->leftPtr;
    }

    //delete a Node which has a right child Node
    else if (deleteNodePtr->leftPtr == NULL && deleteNodePtr->rightPtr != NULL)
    {
        //delete Node is root
        if (parentNodeOfDeletePtr == NULL)
        {
            *treePtrP = deleteNodePtr->rightPtr;
        }
        else if (parentNodeOfDeletePtr->rightPtr == deleteNodePtr)
            parentNodeOfDeletePtr->rightPtr = deleteNodePtr->rightPtr;
        else
            parentNodeOfDeletePtr->leftPtr = deleteNodePtr->rightPtr;
    }
    //delete a Node which has a left and a right child Node
    else
    {
        //find substituteNode and its parentNode
        parentNodeOfSubstitutePtr = deleteNodePtr;
        substituteNodePtr = deleteNodePtr->leftPtr;

        //search down and right
        while (substituteNodePtr->rightPtr != NULL)
        {
            parentNodeOfSubstitutePtr = substituteNodePtr;
            substituteNodePtr = substituteNodePtr->rightPtr;

        }

        if (parentNodeOfSubstitutePtr->leftPtr == substituteNodePtr)
        {
            parentNodeOfSubstitutePtr->leftPtr = substituteNodePtr->leftPtr;
        }
        else
        {
            parentNodeOfSubstitutePtr->rightPtr = substituteNodePtr->leftPtr;
        }

        deleteNodePtr->data = substituteNodePtr->data;
        deleteNodePtr = substituteNodePtr;
    }

    free(deleteNodePtr);
}