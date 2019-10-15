#ifndef STR_COMMON_H_
#define STR_COMMON_H_

char *kstrncpy(char *dst, const char *src, int size)
{

    int i = 0;
    while (i < size && (dst[i] = src[i]))
    {
        i++;
    }

    return dst;
}

int kstrncmp(char *dst, const char *src, int size)
{

    int i = 0;
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
    int l1 = strnlen(s1, 1024);
    int l2 = strnlen(s2, 1024);

    char *ret = new char[l1 + l2];

    sprintf(ret, "%s%s", s1, s2);

    return ret;
}

#endif