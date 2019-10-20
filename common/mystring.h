#ifndef MY_STRING_H_
#define MY_STRING_H_

#include "common/mytypes.h"

static my_octet *genstring(unsigned int size)
{

    my_octet *ret = new my_octet[size + 1];

    for (unsigned int i = 0; i < size; i++)
    {
        ret[i] = 'a' + rand() % 26;
    }

    ret[size] = '\0';

    return ret;
}


unsigned int kstrncpy(my_octet *dst, const my_octet *src, unsigned int size)
{

    unsigned int i = 0;
    while (i < size && (dst[i] = src[i]))
    {
        i++;
    }
    
    dst[i] = '\0';

    return i-1;
}

int kstrncmp(my_octet *dst, const my_octet *src, unsigned int size)
{

    unsigned int i = 0;
    while (i < size && (dst[i] == src[i]))
    {
        if (dst[i] == '\0' || src[i] == '\0')
        {
            return dst[i] - src[i];
        }
        i++;
    }

    return 0;
}

char *knewstrjoin(const char *s1, const char *s2)
{
    unsigned int l1 = strnlen(s1, 1024);
    unsigned int l2 = strnlen(s2, 1024);

    char *ret = new char[l1 + l2];

    sprintf(ret, "%s%s", s1, s2);

    return ret;
}

#endif