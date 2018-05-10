#include <iostream> 

typedef struct Element  
{  
    void *data;  
    struct Element *next;  
} Element;  
  
bool push(Element **top, void *data)  
{  
    Element *elem = new Element;  
    if (!elem) return false;  
  
    elem->data = data;  
    elem->next = *top;  
    *top = elem;  
    return true;  
}  
  
bool createStack(Element **top)  
{  
    *top = NULL;  
    return true;  
}  
  
bool pop(Element **top, void **data)  
{  
    Element *elem;  
    if (!(elem = *top)) return false;  
  
    *data = elem->data;  
    *top = elem->next;  
    delete elem;  
    return true;  
}  
  
bool deleteStack(Element **top)  
{  
    Element *elem;  
    while (*top) {  
        elem = (*top)->next;  
        delete *top;  
        *top = elem;  
    }  
    return true;  
}  
  
bool sortNode(Element **head)  
{  
    for (Element *temp1 = *head; temp1 != NULL; temp1 = temp1->next) {  
        for (Element *temp2 = temp1->next; temp2 != NULL; temp2 = temp2->next) {  
            if (*(static_cast<int *>(temp1->data)) > *(static_cast<int *>(temp2->data))) {  
                int temp = *(static_cast<int *>(temp1->data));  
                *(static_cast<int *>(temp1->data)) = *(static_cast<int *>(temp2->data));  
                *(static_cast<int *>(temp2->data)) = temp;  
            }  
        }  
    }  
  
    return true;  
}  
  
void printStack(Element *top)  
{  
    if (top == NULL) {  
        std::cout << "Empty!" << std::endl;  
    }  
    Element *cur = top;  
    while (cur) {  
        std::cout << *(static_cast<int *>(cur->data)) << " ";  
        cur = cur->next;  
    }  
    std::cout << std::endl << std::endl;  
}  
  
int main()  
{  
    Element *head;  
    createStack(&head);  
    int n1 = 30, n2 = -20, n3 = 300, n4 = -40, n5 = 50;  
    push(&head, &n1);  
    push(&head, &n2);  
    push(&head, &n3);  
    push(&head, &n4);  
    push(&head, &n5);  
  
    printStack(head);  
  
    sortNode(&head);  
    printStack(head);  
  
    void * n;  
    pop(&head, &n);  
    std::cout << "popped " << *(static_cast<int*>(n)) << std::endl;  
    pop(&head, &n);  
    std::cout << "popped " << *(static_cast<int*>(n)) << std::endl;  
    std::cout << std::endl;  
  
    printStack(head);  
  
    std::cout << "deleting stack..." << std::endl;  
    deleteStack(&head);  
    printStack(head);  
  
    return 0;  
}  