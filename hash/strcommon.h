#ifndef STR_COMMON_H_
#define STR_COMMON_H_

char* kstrncpy(char *dst, const char *src, int size){

    int i = 0;
    while(i < size && (dst[i] = src[i])){i++;}

    return dst;
}

int kstrncmp(char *dst, const char *src, int size){

    int i = 0;
    while(i < size && (dst[i] == src[i])){
        if(dst[i] == '\0' || src[i] == '\0'){
            return dst[i] - src[i];
        }
        i++;
    }

    return 0;
}



#endif