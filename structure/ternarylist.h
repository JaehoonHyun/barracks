#ifndef TERNARY_H_
#define TERNARY_H_

#include "common/mytypes.h"
#include "structure/list.h"

struct TSNodeList
{

    List list;
    struct TSNodeList *less, *equal, *greater;
    unsigned char key;
    char isFull;

    TSNodeList() : less(0), equal(0), greater(0), key(0), isFull(0) {}
};

struct TSTreeList
{
    TSNodeList root;

    void insertn(const my_octet *str, int size, void *data)
    {
        const unsigned char *ptr;
        ptr = (const unsigned char *)str;
        TSNodeList *iter;

        iter = &root;
        int i = 0;
        while (true)
        {

            if (iter->isFull == 0)
            {
                iter->key = *ptr;
                iter->isFull = 1;

                ptr++;
                i++;

                if (i == size)
                {
                    iter->list.Add(data);
                    return;
                }
                iter->equal = new TSNodeList;
                iter = iter->equal;
            }
            else if (iter->key == *ptr)
            {
                ptr++;
                i++;
                if (i == size)
                {
                    iter->list.Add(data);
                    return;
                }
                iter = iter->equal;
            }
            else if (iter->key > *ptr)
            {
                iter->less = new TSNodeList;
                iter = iter->less;
            }
            else if (iter->key < *ptr)
            {
                iter->greater = new TSNodeList;
                iter = iter->greater;
            }
        }
    }

    void insert(const my_octet *str, void *data)
    {

        const unsigned char *ptr;
        ptr = (const unsigned char *)str;
        TSNodeList *iter;

        iter = &root;
        while (true)
        {

            if (iter->isFull == 0)
            {
                iter->key = *ptr;
                iter->isFull = 1;

                ptr++;

                if (*ptr == '\0')
                {
                    iter->list.Add(data);
                    return;
                }
                iter->equal = new TSNodeList;
                iter = iter->equal;
            }
            else if (iter->key == *ptr)
            {
                ptr++;
                if (*ptr == '\0')
                {
                    iter->list.Add(data);
                    return;
                }
                iter = iter->equal;
            }
            else if (iter->key > *ptr)
            {
                iter->less = new TSNodeList;
                iter = iter->less;
            }
            else if (iter->key < *ptr)
            {
                iter->greater = new TSNodeList;
                iter = iter->greater;
            }
        }
    }

    TSNodeList *_search(const my_octet *str)
    {

        TSNodeList *iter;
        const unsigned char *ptr;
        ptr = (const unsigned char *)str;

        iter = &root;
        while (true)
        {

            if (iter == 0)
            {
                return 0;
            }

            if (iter->key == *ptr)
            {
                ptr++;

                if (*ptr == '\0')
                {
                    if (!iter->list.IsEmpty())
                        return iter;
                    else
                        return 0;
                }
                iter = iter->equal;
            }
            else if (iter->key > *ptr)
            {
                iter = iter->less;
            }
            else if (iter->key < *ptr)
            {
                iter = iter->greater;
            }
        }
    }

    void *search(const my_octet *str)
    {

        TSNodeList *node;
        if ((node = _search(str)) != 0)
        {
            return &node->list;
        }

        return 0;
    }
};

#endif