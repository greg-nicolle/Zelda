#include "map.h"
#include <iostream>

/* Constructeur */
map::map(QObject *parent) : QGraphicsScene(parent) {

    /* Connect signals */
    qRegisterMetaType< QList<mechant*> >("QList<mechant*>");
    connect(&control, SIGNAL(call_update_map(QPixmap*,int*)), this, SLOT(update_map(QPixmap*,int*)));
    connect(&control, SIGNAL(call_update_mechants(QList<mechant*>)), this, SLOT(update_mechants(QList<mechant*>)));
    connect(&control, SIGNAL(call_update_hero(link*)), this, SLOT(update_hero(link*)));


    /* Start controler thread */
    control.start();
}

/* Destructeur */
map::~map() {
}

/* Detection evenments clavier */
void map::keyPressEvent(QKeyEvent *event) {
    control.key_events(event);
}
void map::keyReleaseEvent(QKeyEvent *event){
    control.key_r_events(event);
}

/* Display map */
void map::update_map(QPixmap* tiles, int* plan) {

    for(int i = 0; i < MAPSIZE; i++) {
        for(int j = 0; j < MAPSIZE; j++) {
            delete carte[i][j];
            carte[i][j] = addPixmap(tiles[plan[i*MAPSIZE+j]]);
            carte[i][j]->setPos(-MAX/2+(MAX/MAPSIZE)*i,-MAX/2+(MAX/MAPSIZE)*j);
            if (plan[i*MAPSIZE+j]) {
                carte[i][j]->setZValue(plan[i*MAPSIZE+j]);
            } else {
                carte[i][j] = NULL;
            }
        }
    }
}

/* Refresh hero */
void map::update_hero(link* unit) {
    delete hero;
    hero = addPixmap(unit->get_image());
    hero->setPos(unit->pos());
    hero->setZValue(5);
    emit update_pv(unit->get_pv());
}

/* Refresh mechants */
void map::update_mechants(QList<mechant*> boss) {

    if(vilains.length()<boss.length()){
        vilains.resize(boss.length());
    }
    for(int i = 0; i < vilains.count(); i++ ) {
        delete vilains[i];
        if(i<boss.count()){
            vilains[i] = addPixmap(boss.at(i)->get_image());
            vilains[i]->setPos(boss.at(i)->pos());
            vilains[i]->setZValue(5);
        }
    }
    vilains.resize(boss.length());
}
