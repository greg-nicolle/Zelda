#ifndef MECHANT_H
#define MECHANT_H


#include "personnage.h"


class mechant : public personnage
{
public:
    mechant(QString fichier);
    ~mechant();

    void position_combat(QRectF target_bords, QPointF target_pos);
    void search(QPointF target, QList<QPointF> dispo);
    void traques_fuis(QPointF cible, QString action);
    bool check_pos(QPointF target, QPointF compare);
};


#endif // MECHANT_H
