#ifndef HASH_H_
#define HASH_H_

#include "list.h"
#include "strcommon.h"

static inline unsigned int hashing(const char *src, int hsize){


    unsigned long long key = 0;
    
    while(*src != '\0'){
        key = 65599 * key + *src;
        src++;
    }

    return key % hsize;
}

#define HASH_KEY_SIZE 24

struct HashHeader {
    unsigned int size;
    unsigned int hashVal;
    char _key[HASH_KEY_SIZE];
};

struct Hash {

    
    Hash(unsigned int hsize):_hsize(hsize), bucket(new List[hsize]){}
    
    void add(const char *src, HashHeader *data, unsigned int size){ 
        data->hashVal = hashing(src, _hsize);
        data->size = size;
        kstrncpy(data->_key, src, HASH_KEY_SIZE);
        bucket[data->hashVal].add(data);
        serial.add(data);
    }

    HashHeader *search(const char *src){
        
        unsigned int hashVal;
        hashVal = hashing(src, _hsize);

        List &list = bucket[hashVal];
        Node *iter = list.iterator();
        while(list.hasNext()){

            HashHeader *header = (HashHeader *)iter->_data;

            if(kstrncmp(header->_key, src, HASH_KEY_SIZE) == 0){
                return header;
            }

            iter = list.next(); 
        }

    }
    
    List *bucket;
    unsigned int _hsize;

    //serial
    List serial;
    
private:
};

#endif