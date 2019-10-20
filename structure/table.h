#ifndef TABLE_H_
#define TABLE_H_

#include <stdarg.h> // va_list, va_start, va_arg, va_end

#include "common/mytypes.h"
#include "structure/hash.h"
#include "structure/ternary.h"
#include "clay/inc/clay.h"

//columns max count : 9
struct MyTable
{

    Clay clay_;
    List colnames_;
    my_octet format_[256];
    my_octet2 colcnt_;
    my_octet2 rowsize_;

    TSTree tree[9];

    struct Indexing
    {
        static const my_octet sperator = 0xBF;
        List colnums;
        Hash hash;

        Indexing() : hash() {}
    };

    struct ColDesc
    {

        const char *colname_;
        int colpos_;
        int colidx_;

        ColDesc(const char *colname, int colpos, int colidx)
            : colname_(colname), colpos_(colpos), colidx_(colidx) {}
    };

    Hash root_;

    void AddIndex(my_octet4 count, ...)
    {
        va_list ap;
        va_start(ap, count);

        my_octet4 idx;
        my_octet4 *buf = new my_octet4;
        *buf = 0;

        for (int i = 0; i < count; i++)
        {
            idx = va_arg(ap, my_octet4);
            *buf = *buf * 10 + idx;
        }

        List *list = new List();
        list->_head._data = buf;

        root_.add(buf, list);
    }

    void Commit()
    {
        //do not Add Col
    }

    //no copy colname, you must be heap or constant region
    void AddCol(const char *colname, my_octet4 csize)
    {
        switch (csize)
        {
        case 1:
            strncpy(format_ + colcnt_, "1", 1);
            break;
        case 2:
            strncpy(format_ + colcnt_, "2", 1);
            break;
        case 4:
            strncpy(format_ + colcnt_, "4", 1);
            break;
        case 8:
            strncpy(format_ + colcnt_, "8", 1);
            break;
        default:
            strncpy(format_ + colcnt_, "n", 1);
            break;
        }

        ColDesc *coldesc = new ColDesc(colname, rowsize_, colcnt_);
        colnames_.Add(coldesc);

        colcnt_++;
        rowsize_ += csize;
    }
};

#define AddRowTable(table, ...) addRowTable(table, __VA_ARGS__)

void addRowTable(MyTable *table, ...)
{
    va_list ap;
    va_start(ap, table);

    my_octet *row = (my_octet *)table->clay_.NewClay(table->rowsize_);
    my_octet *pos = row;
    for (int i = 0; table->format_[i] != '\0'; i++)
    {

        switch (table->format_[i])
        {
            //default word
        case '1':
            my_octet o1;
            o1 = (my_octet)va_arg(ap, my_octet4);
            *pos = o1;
            table->tree[i].insertn(pos, 1, row);
            pos += 1;
            break;
        case '2':
            my_octet2 o2;
            o2 = (my_octet2)va_arg(ap, my_octet4);
            *pos = o2;
            table->tree[i].insertn(pos, 2, row);
            pos += 2;
            break;
        case '4':
            my_octet4 o4;
            o4 = va_arg(ap, my_octet4);
            *pos = o4;
            table->tree[i].insertn(pos, 4, row);
            pos += 4;
            break;
        case '8':
            my_octet8 o8;
            o8 = va_arg(ap, double);
            *pos = o8;
            table->tree[i].insertn(pos, 8, row);
            pos += 8;
            break;
        case 'n':
        default:
            my_octet *n;
            n = va_arg(ap, my_octet *);
            int nlen = kstrncpy(pos, n, 4096);
            table->tree[i].insertn(pos, nlen, row);
            pos += nlen;
            break;
        }

    } //colcnt_
    va_end(ap);

    //TODO: hashing ? or ternary?
    for (int i = 0; i < table->colcnt_; i++)
    {
        //get colpos
        //get row data from colpos
        //
    }
}

//TODO : have to implemented
void SearchTable(MyTable *table, ...)
{

    va_list ap;
    va_start(ap, table);

    my_octet *row = (my_octet *)table->clay_.NewClay(table->rowsize_);
    my_octet *pos = row;
    for (int i = 0; table->format_[i] != '\0'; i++)
    {


    } //colcnt_
    va_end(ap);
}

//TODO : have to implemented
void BetweenTable(MyTable *table, ...)
{

    va_list ap;
    va_start(ap, table);

    my_octet *row = (my_octet *)table->clay_.NewClay(table->rowsize_);
    my_octet *pos = row;
    for (int i = 0; table->format_[i] != '\0'; i++)
    {
        

    } //colcnt_
    va_end(ap);
}

void IndexingTable(MyTable *table, ...){
    
}


#endif