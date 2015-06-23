#ifndef MAPITEM_H
#define MAPITEM_H

#include "item.h"

class mapitem : public Item
{
public:
    mapitem();
    ~mapitem();

    bool is_traversant();

protected:
    bool traversant;
    int type;

//    set_pixmap();
};

#endif // MAPITEM_H
