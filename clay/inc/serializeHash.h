#ifndef SERIALIZE_HASH_H_
#define SERIALIZE_HASH_H_

// m : clay count
// n : data count in claychunk
// O(m*n)
void makeHash(Hash *hash, Clay *clay){
    List &list = clay->_list;
    for (Node *iter = list.Iterator(); list.HasNext(); iter = list.Next())
    {
        ClayChunk *chunk = (ClayChunk *)iter->_data;
        HashHeader *data;

        //for loop chunk when less than size
        my_octet2 pos = 0;
        while (pos < chunk->_pos)
        {
            data = (HashHeader *)&chunk->_mem[pos];
            hash->quickAdd(data);
            pos += data->_size;
        }

    }

}

#endif