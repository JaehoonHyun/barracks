

#include "common/mytypes.h"
#include "clay/inc/clay.h"

my_octet checkEmpty(struct Clay *clay)
{
    return clay->_list.IsEmpty();
}

ClayChunk *checkSpaced(struct Clay *clay, my_octet4 memsize)
{

    if (checkEmpty(clay))
    {
        return 0;
    }

    ClayChunk *first;
    first = (ClayChunk *)clay->_list.First();
    if (first->_pos + memsize > CLAY_CHUNK)
    {
        return 0;
    }

    return first;
}

ClayChunk *allocateSpace(Clay *clay)
{
    return (ClayChunk *)clay->_list.Add(new ClayChunk);
}

void *Clay::NewClay(my_octet4 memsize)
{

    ClayChunk *chunk;
    if ((chunk = checkSpaced(this, memsize)) == 0)
    {
        chunk = allocateSpace(this);
    }

    my_octet2 old_pos = chunk->_pos;
    chunk->_pos += memsize;

    return (void *)&chunk->_mem[old_pos];
}

ClayChunk* Clay::AddClay(ClayChunk *chunk)
{
    return (ClayChunk*)_list.Add(chunk);
}
