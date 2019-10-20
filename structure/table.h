#ifndef TABLE_H_
#define TABLE_H_

#include <stdarg.h> // va_list, va_start, va_arg, va_end

#include "common/mytypes.h"
#include "structure/hash.h"
#include "structure/ternarylist.h"
#include "clay/inc/clay.h"

//columns max count : 9
struct MyTable
{

    Clay clay_;
    List colnames_;
    my_octet format_[256];
    my_octet2 colcnt_;
    my_octet2 rowsize_;
    my_octet4 rowcnt_;
    TSTreeList tree_[9];
    Hash root_;

    struct Indexing
    {
        static const my_octet sperator = 0xBF;
        List colnums;
        Hash hash;

        Indexing() : hash() {}
    };

    struct ColDesc
    {

        const my_octet *colname_;
        my_octet2 colpos_;
        my_octet2 colidx_;

        ColDesc(const my_octet *colname, my_octet2 colpos, my_octet2 colidx)
            : colname_(colname), colpos_(colpos), colidx_(colidx) {}
    };

    void Commit()
    {
        //do not Add Col
    }

    //no copy colname, you must be heap or constant region
    void AddCol(const my_octet *colname, my_octet4 csize)
    {
        switch (csize)
        {
        case 1:
            kstrncpy(format_ + colcnt_, "1", 1);
            break;
        case 2:
            kstrncpy(format_ + colcnt_, "2", 1);
            break;
        case 4:
            kstrncpy(format_ + colcnt_, "4", 1);
            break;
        case 8:
            kstrncpy(format_ + colcnt_, "8", 1);
            break;
        default:
            kstrncpy(format_ + colcnt_, "n", 1);
            break;
        }

        ColDesc *coldesc = new ColDesc(colname, rowsize_, colcnt_);
        colnames_.Add(coldesc);

        colcnt_++;
        rowsize_ += csize;
    }

    void AddRow(...)
    {
        va_list ap;
        va_start(ap, this);

        my_octet *row = (my_octet *)clay_.NewClay(rowsize_);
        my_octet *pos = row;
        for (int i = 0; format_[i] != '\0'; i++)
        {

            switch (format_[i])
            {
                //default word
            case '1':
                my_octet o1;
                o1 = (my_octet)va_arg(ap, my_octet4);
                *(my_octet *)pos = o1;
                tree_[i].insertn(pos, 1, row);
                pos += 1;
                break;
            case '2':
                my_octet2 o2;
                o2 = (my_octet2)va_arg(ap, my_octet4);
                *(my_octet2 *)pos = o2;
                tree_[i].insertn(pos, 2, row);
                pos += 2;
                break;
            case '4':
                my_octet4 o4;
                o4 = va_arg(ap, my_octet4);
                *(my_octet4 *)pos = o4;
                tree_[i].insertn(pos, 4, row);
                pos += 4;
                break;
            case '8':
                double d8;
                d8 = va_arg(ap, double);
                my_octet8 o8;
                o8 = *(my_octet8 *)&d8;
                *(my_octet8 *)pos = o8;
                tree_[i].insertn(pos, 8, row);
                pos += 8;
                break;
            case 'n':
            default:
                my_octet *n;
                n = va_arg(ap, my_octet *);
                int nlen = kstrncpy(pos, n, 4096);
                tree_[i].insertn(pos, nlen, row);
                pos += nlen;
                break;
            }

        } //colcnt_
        va_end(ap);

        rowcnt_++;
    }

    //TODO : have to implemented
    MyTable &SearchTable(const my_octet *colname, ...)
    {

        va_list ap;
        va_start(ap, this);

        my_octet *row = (my_octet *)clay_.NewClay(rowsize_);
        my_octet *pos = row;
        
        //PSEUDO CODE
        //find format using colname
        //find index using colname
        //value = va_arg(ap, format)
        //search using root_[index].search(value)
        //if list is nil, create and search save to list

        va_end(ap);

        return *this;
    }

    //must copy
    List* Fetch(){
        return new List();
    }

    //TODO : have to implemented
    MyTable &BetweenTable(...)
    {

        va_list ap;
        va_start(ap, this);

        my_octet *row = (my_octet *)clay_.NewClay(rowsize_);
        my_octet *pos = row;
        for (int i = 0; format_[i] != '\0'; i++)
        {

        } //colcnt_
        va_end(ap);

        return *this;
    }

    MyTable &IndexingTable(...)
    {

        return *this;
    }
};

#endif