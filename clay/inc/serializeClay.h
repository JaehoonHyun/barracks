#ifndef SERIALIZE_CLAY_H_
#define SERIALIZE_CLAY_H_

#include "clay/inc/clay.h"

static void* writeClay(const char *path, void *data)
{

    //TODO : hdd tunning
    int fd = open(path, O_WRONLY | O_CREAT, 0644);
    assert(fd > 0);

    Clay *clay = (Clay *)data;

    //key, hashVal | data
    // write(fd, &hash->_hsize, sizeof(hash->_hsize));

    // List &list = hash->serial;
    // Node *iter = list.Iterator();
    // while (list.HasNext())
    // {
    //     write(fd, iter->_data, ((HashHeader *)iter->_data)->_size);
    //     iter = list.Next();
    // }

    List &list = clay->_list;

    for (Node *iter = list.Iterator(); list.HasNext(); iter = list.Next())
    {
        write(fd, iter->_data, sizeof(ClayChunk));
    }

    close(fd);

    return data;

}

static void *readClay(const char *path)
{

    //TODO : hdd tunning
    int fd = open(path, O_RDONLY);
    assert(fd > 0);

    //until eof
    struct stat st;
    stat(path, &st);
    unsigned int filesize = st.st_size;
    unsigned int filecursor = 0;

    Clay *clay = new Clay();

    while (filecursor < filesize)
    {

        my_octet2 msize;
        char *mem;
        
        msize = sizeof(ClayChunk);
        mem = new char[msize];

        read(fd, mem, msize);
        clay->AddClay((ClayChunk *)mem);

        filecursor += msize; //msize add
    }

    return clay;
}

#endif