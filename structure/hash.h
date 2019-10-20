#ifndef HASH_H_
#define HASH_H_

#include "common/mytypes.h"
#include "common/mystring.h"

#include "structure/list.h"
static inline my_octet4 hashing(const my_octet *src, int hsize)
{

    unsigned long long key = 0;

    while (*src != '\0')
    {
        key = 65599 * key + *src;
        src++;
    }

    return key % hsize;
}

#define HASH_KEY_SIZE 24

#ifndef HASH_SIZE
#define MY_HASH_SIZE 65599
#endif

struct HashHeader
{
    my_octet4 _size;
    my_octet4 _hashVal;
    my_octet _key[HASH_KEY_SIZE];
};

struct Hash
{
    Hash() : _hsize(MY_HASH_SIZE), bucket(new List[MY_HASH_SIZE]) {}
    Hash(my_octet4 hsize) : _hsize(hsize), bucket(new List[hsize]) {}

    void add(HashHeader *data, my_octet4 size)
    {
        data->_hashVal = hashing(data->_key, _hsize);
        data->_size = size;
        bucket[data->_hashVal].Add(data);
    }

    void add(void *key, void *data){
        my_octet4 hashVal =  hashing((const char *)key, _hsize);
        bucket[hashVal].Add(data);
    }

    void quickAdd(HashHeader *data)
    {
        bucket[data->_hashVal].Add(data);
    }

    HashHeader *search(const my_octet *src)
    {

        my_octet4 hashVal;
        hashVal = hashing(src, _hsize);

        List &list = bucket[hashVal];
        Node *iter = list.Iterator();
        while (list.HasNext())
        {

            HashHeader *header = (HashHeader *)iter->_data;

            if (kstrncmp(header->_key, src, HASH_KEY_SIZE) == 0)
            {
                return header;
            }

            iter = list.Next();
        }

        return NULL;
    }

    my_octet4 _hsize;
    List *bucket;

private:
};

#endif