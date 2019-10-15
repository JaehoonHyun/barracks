
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
#include <pwd.h>   //getpwuid(), getuid()

//middleware header
#include "gtest/gtest.h"

//custom header
#include "common/mydebug.h"
#include "common/mystring.h"
#include "hash/hash.h"
#include "hash/serialize.h"

static int my_add(int a, int b)
{
    return a + b;
}

TEST(tdd_gtest, basic_gtest)
{
    ASSERT_EQ(2, my_add(1, 1));
}

TEST(tdd_gtest, hash_test)
{

    struct MyData : public HashHeader
    {

        //data section
        int _age;

        MyData(int age) : _age(age)
        {
        }
    };

    const int HASH_SIZE = 10000;
    struct passwd *pw = getpwuid(getuid());
    const char *homedir = pw->pw_dir;

    Hash *hash = new Hash(HASH_SIZE);

    hash->add("timestamp", new MyData(10), sizeof(MyData));
    hash->add(genString(20), new MyData(11), sizeof(MyData));
    hash->add(genString(20), new MyData(12), sizeof(MyData));
    hash->add(genString(20), new MyData(13), sizeof(MyData));

    char *path = knewstrjoin(homedir, "/foo.data");
    writeHash(path, hash);
    Hash *rHash = readHash(path);

    MyData *data;
    data = (MyData *)rHash->search("timestamp");

    LOGI("age! : %d\n", data->_age);
}

int main(int argc, char **argv)
{

    srand((unsigned int)time(0));

    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();

    return 0;
}