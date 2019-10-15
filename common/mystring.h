#ifndef MY_STRING_H_
#define MY_STRING_H_


static char *genString(unsigned int size)
{

    char *ret = new char[size + 1];

    for (int i = 0; i < size; i++)
    {
        ret[i] = 'a' + rand() % 26;
    }

    ret[size] = '\0';

    return ret;
}

#endif