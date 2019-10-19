#ifndef CLAY_H_
#define CLAY_H_

#include "common/mytypes.h"
#include "structure/stack.h"

#ifndef CLAY_CHUNK
#define CLAY_CHUNK 4096
#endif

struct ClayChunk
{
    my_octet2 _pos;
    char _mem[CLAY_CHUNK];

    ClayChunk() : _pos(0)
    {
    }
};

struct Clay
{
    struct Stack _list;
    void *NewClay(my_octet4 memsize);
    ClayChunk *AddClay(ClayChunk *chunk);
};


#endif