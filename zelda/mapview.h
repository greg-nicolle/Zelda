#ifndef MAPVIEW_H
#define MAPVIEW_H


#include <qgraphicsview.h>
#include "map.h"


class mapview : public QGraphicsView
{
    Q_OBJECT

protected:
    map scene;

public:
    explicit mapview(QObject *parent = 0);
};


#endif // MAPVIEW_H
