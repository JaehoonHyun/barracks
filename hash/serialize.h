#ifndef SERIALIZE_H_
#define SERIALIZE_H_

static void writeHash(const char *path, Hash *hash)
{

    //TODO : hdd tunning
    int fd = open(path, O_WRONLY | O_CREAT, 0644);
    assert(fd > 0);

#if 0
    //serialized buffer
    struct {
        unsigned int key;
        MyData *data;
    } serialData[hash->_hsize];

    int serialDataCnt = 0; 

    for(int i = 0 ; i < hash->_hsize; i++){

        if(!hash->bucket[i].isEmpty()){
            serialData[serialDataCnt].key = i;
            serialData[serialDataCnt].data = new MyData[hash->bucket[i].count];
            serialDataCnt++;
        }
    }
#endif

    //key, hashVal | data

    write(fd, &hash->_hsize, sizeof(hash->_hsize));

    List &list = hash->serial;
    Node *iter = list.iterator();
    while (list.hasNext())
    {

        write(fd, iter->_data, ((HashHeader *)iter->_data)->size);

        iter = list.next();
    }

    close(fd);
}

static Hash *readHash(const char *path)
{

    //TODO : hdd tunning
    int fd = open(path, O_RDONLY);
    assert(fd > 0);

    unsigned int hsize;
    read(fd, &hsize, sizeof(hsize));
    Hash *hash = new Hash(hsize);

    //until eof
    struct stat st;
    stat(path, &st);
    unsigned int filesize = st.st_size;
    unsigned int filecursor = 0;

    while (filecursor < filesize)
    {

        unsigned int msize;
        read(fd, &msize, sizeof(msize));
        char *msg = new char[msize];

        HashHeader *header;
        header = (HashHeader *)msg;
        header->size = msize;
        unsigned int usersize;
        usersize = msize - sizeof(*header);

        read(fd, msg + sizeof(msize), sizeof(*header) - sizeof(msize)); //read HashHeader
        read(fd, msg + sizeof(*header), usersize);                      //read variable Data

        hash->add(header->_key, header, usersize); //reordering

        filecursor += msize; //msize add
    }

    return hash;
}


#endif