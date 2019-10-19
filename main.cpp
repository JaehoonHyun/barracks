
//c++ header
#include <ctime>
#include <cstdlib>
#include <stdio.h>

//c header
#include <assert.h>
#include <fcntl.h>    // O_WRONLY
#include <unistd.h>   // write(), close()
#include <sys/stat.h> // stat()
#include <sys/types.h>
#include <pwd.h> //getpwuid(), getuid()

//middleware header
#include "gtest/gtest.h"

//custom header
#include "common/mydebug.h"
#include "common/mystring.h"
#include "structure/hash.h"
#include "clay/inc/clay.h"
#include "clay/inc/serializeClay.h"
#include "clay/inc/serializeHash.h"

const char *ghomedir;

static int my_add(int a, int b)
{
    return a + b;
}

TEST(tdd_gtest, basic_gtest)
{
    ASSERT_EQ(2, my_add(1, 1));
}


TEST(tdd_gtest, memorypool_test)
{
    struct MyData : public HashHeader
    {

        //data section
        char _talk[512];

        MyData(const char key[], const char talk[])
        {
            kstrncpy(_key, key, sizeof(_key));
            kstrncpy(_talk, talk, sizeof(_talk));
        }
    };

    const int HASH_SIZE = 10000;

    Hash *hash = new Hash(HASH_SIZE);

    // hash->add(new MyData("ktjooho1", "hello"), sizeof(MyData));
    // hash->add(new MyData("ktjooho2", "how are you today?"), sizeof(MyData));
    // hash->add(new MyData("jaehoon1", "wow"), sizeof(MyData));
    // hash->add(new MyData("jaehoon2", "awesome"), sizeof(MyData));

    //TODO : used displacement
    // kstrncpy(data->_key, data->key, sizeof(_key));
    // kstrncpy(data->_talk, data->talk, sizeof(_talk));

    Clay clay;

    MyData *mem;
    mem = (MyData *)clay.NewClay(sizeof(MyData));
    new (mem) MyData("ktjooho1", "hello");
    hash->add(mem, sizeof(MyData));

    mem = (MyData *)clay.NewClay(sizeof(MyData));
    new (mem) MyData("ktjooho1", "hellohi");
    hash->add(mem, sizeof(MyData));

    for (int i = 0; i < 100; i++)
    {
        mem = (MyData *)clay.NewClay(sizeof(MyData));
        new (mem) MyData(genstring(20), genstring(500));
        hash->add(mem, sizeof(MyData));
    }

    assert(clay._list._count == 15);

    char *path = knewstrjoin(ghomedir, "/foo.data");
    writeClay(path, &clay);

    Hash *rdhash = new Hash(HASH_SIZE);
    Clay *rdclay = (Clay *)readClay(path);

    makeHash(rdhash, rdclay);

    MyData *rddata = (MyData *)rdhash->search("ktjooho1");
    printf("rddata : [%s][%s]\n", rddata->_key, rddata->_talk);
}

TEST(tdd_gtest, hash_test)
{

    struct MyData : public HashHeader
    {

        //data section
        int _age;

        MyData(int age) : _age(age)
        {
            kstrncpy(_key, genstring(20), 20);
        }
    };

    const int HASH_SIZE = 10000;

    Hash *hash = new Hash(HASH_SIZE);

    hash->add(new MyData(10), sizeof(MyData));
    hash->add(new MyData(11), sizeof(MyData));
    hash->add(new MyData(12), sizeof(MyData));
    hash->add(new MyData(13), sizeof(MyData));

}

int main(int argc, char **argv)
{

    srand((unsigned int)time(0));
    ghomedir = getpwuid(getuid())->pw_dir;

    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();

    return 0;
}