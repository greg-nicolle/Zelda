#include <QKeyEvent>
#include "controler.h"
#include <iostream>
#include <fstream>

#define NB_MECHANTS 1


/* Constructeur */
controler::controler() {
    std::srand(time(NULL));
    niveau = 0;
    init_map();
    init_hero();
    init_boss(NB_MECHANTS);
}

/* Destructeur */
controler::~controler() {
    mutex.lock();
    condition.wakeOne();
    stop = true;
    mutex.unlock();
    wait();
}

/* Initialisation map */
void controler::init_map(){

    /* Load tiles */
    tiles = new QPixmap[4];
    tiles[0].load("../images/herbe.png",0,Qt::AutoColor);
    tiles[2].load("../images/herbe2.png",0,Qt::AutoColor);
    tiles[1].load("../images/brique.jpg",0,Qt::AutoColor);
    tiles[0] = tiles[0].scaled(MAX/MAPSIZE,MAX/MAPSIZE,Qt::KeepAspectRatio);
    tiles[1] = tiles[1].scaled(MAX/MAPSIZE,MAX/MAPSIZE,Qt::KeepAspectRatio);
    tiles[2] = tiles[2].scaled(MAX/MAPSIZE,MAX/MAPSIZE,Qt::KeepAspectRatio);

    tiles[3].load("../images/porte.jpg",0,Qt::AutoColor);
    tiles[3] = tiles[3].scaled(MAX/MAPSIZE,MAX/MAPSIZE,Qt::KeepAspectRatio);

    /* Tiles organization */
    plan = new int[MAPSIZE*MAPSIZE];
    std::ifstream entree0("../map/test0",std::ios::in);
    std::ifstream entree1("../map/test1",std::ios::in);

    wall.clear();

    for(int i = 0 ;i < MAPSIZE; i++) {
            for(int j = 0; j < MAPSIZE; j++) {
                if(niveau%2 == 0){
                    entree0 >> plan[i*MAPSIZE+j];
                }else{
                    entree1 >> plan[i*MAPSIZE+j];
                }
                if(plan[i*MAPSIZE+j]==1){
                    mapitem* tmp = new mapitem();
                    tmp->setPos(-MAX/2+(MAX/MAPSIZE)*i,-MAX/2+(MAX/MAPSIZE)*j);
                    tmp->set_image(tiles[plan[i*MAPSIZE+j]]);
                    wall.append(tmp);
                }else if(plan[i*MAPSIZE+j]==3){
                    mapitem* tmp = new mapitem();
                    tmp->setPos(-MAX/2+(MAX/MAPSIZE)*i,-MAX/2+(MAX/MAPSIZE)*j);
                    tmp->set_image(tiles[plan[i*MAPSIZE+j]]);
                    porte = tmp;
                }
            }
    }
    entree0.close();
    entree1.close();
}

/* Initialisation hero */
void controler::init_hero() {
    hero = new link();
    hero->setPos(0,0);
}

/* Initialisation mechants */
void controler::init_boss(int nb) {
    bool ok;
    for(int i = 0; i < nb; i++) {
        mechant* monstre = new mechant("../images/Wario/");

        do{
            ok = false;
            monstre->setPos(std::rand()%360-200,std::rand()%360-200);
             for(int j = 0; j < boss.count(); j++){
                 if(monstre->collidesWithItem(boss.at(j))){
                     ok = true;
                     break;
                 }
             }
        }while(ok);
        boss.append(monstre);
    }
}

/* Gestion evenments clavier */
void controler::key_events(QKeyEvent *event) {
    if(event->key() == Qt::Key_Right) {
       hero->set_deplacement_x(1);
    } else if(event->key() == Qt::Key_Left) {
        hero->set_deplacement_x(-1);
    } else if(event->key() == Qt::Key_Up) {
        hero->set_deplacement_y(-1);
    } else if(event->key() == Qt::Key_Down) {
        hero->set_deplacement_y(1);
    }
    else if(event->key() == Qt::Key_Space){
        hero->set_attaque(true);
    }else if(event->key() == Qt::Key_K){
        niveau++;
        change_map();
    }else if(event->key() == Qt::Key_R){
        niveau = 0;
        init_map();
        boss.clear();
        init_boss(NB_MECHANTS*(niveau+1));

        hero->set_pv(100);

        emit call_update_mechants(boss);

        emit call_update_map(tiles, plan);
    }
}

void controler::key_r_events(QKeyEvent *event){
    if(event->key() == Qt::Key_Right) {
       hero->set_deplacement_x(0);
    } else if(event->key() == Qt::Key_Left) {
        hero->set_deplacement_x(-0);
    } else if(event->key() == Qt::Key_Up) {
        hero->set_deplacement_y(-0);
    } else if(event->key() == Qt::Key_Down) {
        hero->set_deplacement_y(0);
    }
}

/* Gestion jeu */
void controler::play() {
    QList<QPointF> dispo;

    /* Gestion hero */
    hero->move();
    if(hero->collidesWithItem(porte)&&boss.count()==0){
        niveau++;
        change_map();
        hero->setPos(0,0);
    }
    for(int j = 0; j < wall.count(); j++){
        if(hero->collidesWithItem(wall[j])){
            hero->move_back();
        }
    }
    for(int i = 0; i < boss.count(); i++) {

        /* Gestion collision hero -> mechant */
        hero->collision(boss[i]->boundingRect(), boss[i]->pos(), 2);

        /* Check positions de combat disponibles */
        dispo = hero->empty(boss);
    }


    for(int i = 0; i < boss.count(); i++) {
        bool action = true;

        if(boss[i]->get_fighting()&&std::rand()%5==0){
            hero->degat(1);
        }

        boss[i]->search(hero->pos(), dispo);

        for(int j = 0; j < boss.count(); j++) {
            if(i != j && boss[i]->collidesWithItem(boss[j]) && !boss[i]->get_fighting()) {
                action = false;
                if(boss[i]->check_pos(hero->pos(), boss[j]->pos())) {
                    boss[i]->traques_fuis(boss[j]->pos(), "fuis");
                }
            }
        }

        for(int j = 0; j < wall.count(); j++){
            if(boss[i]->collidesWithItem(wall[j])){
                boss[i]->move_back();
            }
        }

        if (action) {
            if(boss[i]->collidesWithItem(hero)) {

                /* Deplacement mechant vers zone de combat la plus proche */
                boss[i]->position_combat(hero->boundingRect(), hero->pos());
            }
        }
        boss[i]->attaque();
    }
}

/* Demarrage thread */
void controler::run() {
    stop = false;

    emit call_update_map(tiles, plan);
    emit call_update_hero(hero);

    forever {
        if (stop) {
            break;
        }
        mutex.lock();

        play();
        hero->attaque();
        for(int i =0;i<boss.count();i++){
            if(!boss[i]->get_alive()){
                boss.removeAt(i);
                if(std::rand()%2==0){
                    hero->degat(-2);
                }
            }
        }
        /* Refresh item */
        emit call_update_hero(hero);
        emit call_update_mechants(boss);
        mutex.unlock();
        msleep(15);
    }
}


void controler::change_map(){
    init_map();
    boss.clear();
    init_boss(NB_MECHANTS*(niveau+1));

    emit call_update_mechants(boss);

    emit call_update_map(tiles, plan);
}
