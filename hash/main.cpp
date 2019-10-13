#include <ctime>
#include <cstdlib>
#include <stdio.h>

#include <assert.h>
#include <fcntl.h>         // O_WRONLY
#include <unistd.h>        // write(), close()
#include <sys/stat.h>      // stat()

#include "hash.h"

#define HASH_SIZE 10000

char *genString(unsigned int size){

    char *ret = new char[size + 1];

    for(int i = 0; i < size; i++){
        ret[i] = 'a' + rand() % 26;
    }

    ret[size] = '\0';

    return ret;
    
}


struct MyData : public HashHeader{
    
    //data section
    int _age;

    MyData(int age):_age(age){
    }
}; 

void writeHash(const char *path, Hash *hash){
    
    //TODO : hdd tunning
    int fd = open(path, O_WRONLY | O_CREAT , 0644);
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
    
    List & list = hash->serial;
    Node *iter = list.iterator();
    while(list.hasNext()){

        write(fd, iter->_data, ((HashHeader *)iter->_data)->size);
        
        iter = list.next();
    }

    close(fd);


}

Hash* readHash(const char *path){

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

    while(filecursor < filesize){

        unsigned int msize;
        read(fd, &msize, sizeof(msize));
        char *msg = new char[msize];

        HashHeader *header;
        header = (HashHeader *)msg;
        header->size = msize;
        unsigned int usersize;
        usersize = msize - sizeof(*header);

        read(fd, msg + sizeof(msize), sizeof(*header) - sizeof(msize)); //read HashHeader
        read(fd, msg + sizeof(*header), usersize);  //read variable Data

        hash->add(header->_key, header, usersize); //reordering

        filecursor += msize; //msize add

    }

    

    return hash;

}

int main(){

    srand((unsigned int)time(0));

    Hash *hash = new Hash(HASH_SIZE);

    hash->add("timestamp"  , new MyData(10), sizeof(MyData));
    hash->add(genString(20), new MyData(11), sizeof(MyData));
    hash->add(genString(20), new MyData(12), sizeof(MyData));
    hash->add(genString(20), new MyData(13), sizeof(MyData));


    writeHash("/home/test/workspace/foo.data", hash);
    Hash *rHash = readHash("/home/test/workspace/foo.data");

    MyData * data;
    data = (MyData *)rHash->search("timestamp");
    
    printf("age : %d\n", data->_age);
    


    return 0;
}