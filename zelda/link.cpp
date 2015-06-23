#include "link.h"

#include <iostream>
/* Constructeur */
link::link() {
    image.load("../images/Link/deplacement/3/1.png",0,Qt::AutoColor);
    speed = 2;
    set_deplacement_x(0);
    set_deplacement_y(0);
    QString fichier = "../images/Link/";

    init_images(fichier);
    init_images_attaque(fichier);
    init_images_mort(fichier);
    isfighting = false;
    alive = true;
    direction = 2;
    pv = 100;
}

/* Destructeur */
link::~link() {
}


/* Detection emplacements libres et definition des zones d'impacts */
QList<QPointF> link::empty(QList<mechant*> boss) {
    QList<QPointF> dispo;
    QPointF zone_haut, zone_bas, zone_droite, zone_gauche;

    /* Coefficients zones d'impacts */
    qreal top_bottom_x = 8;
    qreal top_bottom_y = 6;
    qreal right_left_x = 6;
    qreal right_left_y = 10;

    if (boss.count() > 0) {
        /* Calcul distances d'impacts */
        qreal touche_x = this->boundingRect().right() - boss[0]->boundingRect().left() - 1;
        qreal touche_y = this->boundingRect().top() - boss[0]->boundingRect().bottom() + 1;

        /* Liste coordonnees des emplacements */
        zone_haut.setX(this->pos().x());
        zone_haut.setY(this->pos().y() + touche_y);
        dispo.append(zone_haut);

        zone_bas.setX(this->pos().x());
        zone_bas.setY(this->pos().y() - touche_y);
        dispo.append(zone_bas);

        zone_gauche.setX(this->pos().x() - touche_x);
        zone_gauche.setY(this->pos().y());
        dispo.append(zone_gauche);

        zone_droite.setX(this->pos().x() + touche_x);
        zone_droite.setY(this->pos().y());
        dispo.append(zone_droite);

        /* Test zones d'impacts avec ennemi */
        for (int i = 0; i < boss.count(); i++) {

            boss[i]->set_fighting(false);


            if ((boss[i]->pos().x() >= zone_haut.x() - top_bottom_x && boss[i]->pos().x() <= zone_haut.x() + top_bottom_x)
                    && (boss[i]->pos().y() <= zone_haut.y() + this->speed && boss[i]->pos().y() >= zone_haut.y() - top_bottom_y)) {

                /* Zone haute */
                dispo.removeOne(zone_haut);
                boss[i]->set_fighting(true);
                if(isfighting&& direction == 0){
                    boss[i]->set_alive(false);
                }

            } else if ((boss[i]->pos().x() >= zone_bas.x() - top_bottom_x && boss[i]->pos().x() <= zone_bas.x() + top_bottom_x)
                       && (boss[i]->pos().y() >= zone_bas.y() - this->speed && boss[i]->pos().y() <= zone_bas.y() + top_bottom_y)) {

                /* Zone basse */
                dispo.removeOne(zone_bas);
                boss[i]->set_fighting(true);
                if(isfighting&& direction == 2){
                    boss[i]->set_alive(false);
                }

            } else if ((boss[i]->pos().x() <= zone_gauche.x() + this->speed && boss[i]->pos().x() >= zone_gauche.x() - right_left_x)
                       && (boss[i]->pos().y() >= zone_gauche.y() - right_left_y && boss[i]->pos().y() <= zone_gauche.y() + right_left_y)) {

                /* Zone gauche */
                dispo.removeOne(zone_gauche);
                boss[i]->set_fighting(true);
                if(isfighting&& direction == 3){
                    boss[i]->set_alive(false);
                }

            } else if((boss[i]->pos().x() >= zone_droite.x() - this->speed && boss[i]->pos().x() <= zone_droite.x() + right_left_x)
                      && (boss[i]->pos().y() >= zone_droite.y() - right_left_y && boss[i]->pos().y() <= zone_droite.y() + right_left_y)) {

                /* Zone droite */
                dispo.removeOne(zone_droite);
                boss[i]->set_fighting(true);
                if(isfighting&& direction == 1){
                    boss[i]->set_alive(false);
                }

            }
        }
    }

    return dispo;
}

