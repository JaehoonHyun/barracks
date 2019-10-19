#ifndef STACK_H_
#define STACK

#include "structure/list.h"

struct Stack : public List
{

    virtual Node *setPrev(Node *head)
    {
        return head;
    }

    virtual Node *setNext(Node *head)
    {
        return head->_next;
    }
};

#endif