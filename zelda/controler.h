#ifndef CONTROLER_H
#define CONTROLER_H

#include <QGraphicsItem>
#include <QWaitCondition>
#include <qmutex.h>
#include "link.h"
#include "mechant.h"
#include <qthread.h>
#include "mapitem.h"

#define MAX 500
#define MAPSIZE 20


class controler : public QThread
{
    Q_OBJECT
signals:
    void call_update_map(QPixmap* tiles, int* plan);
    void call_update_hero(link* hero);
    void call_update_mechants(QList<mechant*> boss);

protected:
    QPixmap* tiles;
    int* plan;
    QGraphicsItem* map[MAPSIZE][MAPSIZE];
    link* hero;
    mechant* monstre;
    QList<mechant*> boss;
    QList<mapitem*> wall;
    mapitem* porte;
    QMutex mutex;
    QWaitCondition condition;
    bool stop;
    void run();
    void change_map();
    void play();
    int niveau;

public:
    controler();
    ~controler();
    void init_map();
    void init_hero();
    void init_boss(int nb);
    void key_events(QKeyEvent *event);
    void key_r_events(QKeyEvent *event);
    bool colision();
};


#endif // CONTROLER_H
