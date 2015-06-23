#ifndef LINK_H
#define LINK_H


#include "personnage.h"
#include "mechant.h"

class link : public personnage
{
public:
    link();
    ~link();
    QList<QPointF> empty(QList<mechant*> boss);
};


#endif // LINK_H

