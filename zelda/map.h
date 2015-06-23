#ifndef MAP_H
#define MAP_H


#include <QGraphicsScene>
#include "controler.h"

#define MAX 500
#define MAPSIZE 20


class map : public QGraphicsScene
{
    Q_OBJECT

signals:
    void update_pv(int pv);
public slots:
    void update_map(QPixmap* tiles, int* plan);
    void update_hero(link* unit/*,int pv*/);
    void update_mechants(QList<mechant*> boss);


protected:
    controler control;
    QGraphicsItem* carte[MAPSIZE][MAPSIZE];
    QGraphicsItem* hero;
    QVector<QGraphicsItem*> vilains;

public:
    explicit map(QObject *parent = 0);
    ~map();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
//    bool colision();
};


#endif // MAP_H
