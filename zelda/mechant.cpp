#include "mechant.h"


#include <iostream>


/* Constructeur */

mechant::mechant(QString fichier) {
    init_images(fichier);
    init_images_attaque(fichier);

    speed = 1;
    isfighting= false;
    nb_attaque = 200;
    tmp_attaque = nb_attaque;

    direction = 2;

    set_deplacement_x(0);
    set_deplacement_y(0);

    alive = true;
}
/* Destructeur */
mechant::~mechant() {
}



/* Deplacements sur positions de combat */
void mechant::position_combat(QRectF target_bords, QPointF target_pos) {

    qreal dist_y =  this->boundingRect().bottom() + target_bords.bottom() - 1;

    QPointF diff = target_pos - this->pos();

    this->deplacement_x = 0;
    this->deplacement_y = 0;

    if (!isfighting) {
        if (diff.x() < 0 && diff.y() < 0) {
            /* Coin haut gauche mechant */
            if(diff.x() > diff.y() && abs(diff.y()) >= dist_y) {
                /* Arrete Haute */
                this->deplacement_x = -1;
            } else {
                /* Arrete Gauche */
                this->deplacement_y = -1;
            }
        } else if (diff.x() < 0 && diff.y() > 0) {
            /* Coin bas gauche mechant */
            if(abs(diff.x()) < abs(diff.y()) && abs(diff.y()) >= dist_y) {
                /* Arrete Basse */
                this->deplacement_x = -1;
            } else {
                /* Arrete Gauche */
                this->deplacement_y = 1;
            }
        } else if (diff.x() > 0 && diff.y() < 0) {
            /* Coint haut droit mechant */
            if(abs(diff.x()) < abs(diff.y()) && abs(diff.y()) >= dist_y) {
                /* Arrete Haute */
                this->deplacement_x = 1;
            } else {
                /* Arrete Droite */
                this->deplacement_y = -1;
            }
        } else if (diff.x() > 0 && diff.y() > 0) {
            /* Coin bas droit mechant */
            if(diff.x() < diff.y() && abs(diff.y()) >= dist_y) {
                /* Arrete Basse */
                this->deplacement_x = 1;
            } else {
                /* Arrete Droite */
                this->deplacement_y = 1;
            }
        }

        this->move();
    }
}

/* Recherche cible */
void mechant::search(QPointF target, QList<QPointF> dispo) {
    QPointF cible;

    if (!this->isfighting) {
        if (dispo.count() != 0) {
            cible = dispo[0] - this->pos();

            for (int i = 0; i < dispo.count() ; i++) {

                QPointF tmp = dispo[i] - this->pos();

                if (abs(tmp.x()) <= abs(cible.x()) && abs(tmp.y()) <= abs(cible.y())) {
                    cible = tmp;
                }
            }

        } else {
            cible = target - this->pos();
        }

        traques_fuis(cible, "traques");
    }
}

void mechant::traques_fuis(QPointF cible, QString action) {
    qreal value;

    if (action == "traques") {
        value = 1;
    } else if (action == "fuis") {
        move_back();
        value = -1*std::rand()%3;
    }

    if(cible.x() < 0) {
        this->deplacement_x = -1 * value;
    } else if (cible.x() == 0) {
        this->deplacement_x = 0;
    } else {
        this->deplacement_x = 1 * value;
    }

    if(cible.y() < 0) {
        this->deplacement_y = -1 * value;
    } else if (cible.y() == 0) {
        this->deplacement_y = 0;
    } else {
        this->deplacement_y = 1 * value;
    }

    this->move();
}

/* Comparaison position */
bool mechant::check_pos(QPointF target, QPointF compare) {
    QPointF me = target - this->pos();
    QPointF other = target - compare;

    if (abs(other.x()) <= abs(me.x()) && abs(other.y()) <= abs(me.y())) {
        return true;
    } else {
        return false;
    }
}
