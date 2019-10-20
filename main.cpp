
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
#include "structure/table.h"

const char *ghomedir;

static int my_add(int a, int b)
{
    return a + b;
}

TEST(tdd_gtest, basic_gtest)
{
    ASSERT_EQ(2, my_add(1, 1));
}

TEST(tdd_gtest, table_index_test)
{

    printf("double : %d\n", sizeof(double));
    printf("my_octet8 : %d\n", sizeof(my_octet8));

    MyTable *table = new MyTable();
    table->AddCol("Age", sizeof(my_octet4));
    table->AddCol("Familiar", sizeof(my_octet8));
    table->AddCol("Count", sizeof(my_octet2));
    table->AddCol("PhoneNumber", sizeof(my_octet) * 16);
    table->Commit();

    // table->AddRow("%d%lf%d%s", 1000000,0.9,5231,"010-4847-8917");
    AddRowTable(table, 1000000, 412323.0f, 5231, "010-4847-8917");
    AddRowTable(table, 3221, 1.0f, 5231, "010-2234-1603");
    AddRowTable(table, 3500, 1.0f, 5231, "010-8801-1603");
    AddRowTable(table, 4500, 1.0f, 5231, "010-1222-9903");

    //TODO : have to implemented
    SearchTable(table, "Age", 3221);

    //TODO : have to implemented
    BetweenTable(table, "Age", 3221, 4000);

    //TODO : have to implemented
    IndexingTable(table, "Age", "Count");

    //TODO : test performance 100,1000,10000,100000,1000000,10000000

}

#if 0
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
#endif

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