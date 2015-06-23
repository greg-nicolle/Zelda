#include "personnage.h"
#include "iostream"

/* Constructeur */
personnage::personnage() {
}

/* Destructeur */
personnage::~personnage() {
}

/* Getteur image */
QPixmap personnage::get_image() {
    return image;
}



/* Contours objet */
QRectF personnage::boundingRect() const {
    return QRectF(-15, -20, 30, 30);
}

/*Déplacement en temps normal*/
void personnage::move(){

    if(!alive){
            image = img_mort[0];


    }
   else if(!isfighting){
        moveBy(speed*deplacement_x,speed*deplacement_y);
        if(deplacement_x>0){
            direction = 1;
        }
        else if(deplacement_x<0){
            direction = 3;
        }
        else if(deplacement_y<0){
            direction = 0;
        }
        else if(deplacement_y>0){
            direction = 2;
        }
        if(deplacement_y||deplacement_x){
            changement_deplacement();
        }
    }
}
void personnage::changement_deplacement(){
    int mod = 4;

    curentimage++;
    if(img_deplacement[direction][curentimage/mod].isNull()){
        curentimage = 0;
    }

    image = img_deplacement[direction][curentimage/mod];
}

void personnage::changement_attaque(){
    int mod = 4;

    image = img_attaque[direction][curentattaque/mod];
    curentattaque++;

    if(img_attaque[direction][curentattaque/mod].isNull()){
        curentattaque = 0;
        isfighting = false;
    }
}

/* Gestion collision avec enemi */
void personnage::collision(QRectF vilain_bords, QPointF vilain_pos, qreal value) {
    qreal dist_x =  this->boundingRect().right() + vilain_bords.right() - value;
    qreal dist_y =  this->boundingRect().bottom() + vilain_bords.bottom() - value;

    QPointF diff = vilain_pos - this->pos();

    if (abs(diff.x()) <= dist_x && abs(diff.y()) <= dist_y) {
        this->move_back();
    }
}

/* Deplacement arriere */
void personnage::move_back() {
    if (!this->isfighting) {
        moveBy(-this->speed*this->deplacement_x,-this->speed*this->deplacement_y);
    }
}



/* Getteur combat actif */
bool personnage::get_fighting() {
    return this->isfighting;
}

/* Setteur combat actif */
void personnage::set_fighting(bool value) {
    this->isfighting = value;
}

void personnage::set_alive(bool ali){
    alive = ali;
}

/*Setteur de déplacement en x*/
void personnage::set_deplacement_x(int dep){
    deplacement_x = dep;
}

/*Setteur de déplacement en y*/
void personnage::set_deplacement_y(int dep){
    deplacement_y = dep;
}

void personnage::init_images(QString fichier){
    QPixmap tmp;
    QString tmp_string;

    for(int i=0;i<4;i++){

        for(int j=0;j<8;j++){

            tmp_string.clear();
            tmp_string+=fichier;
            tmp_string+="deplacement/";
            tmp_string+=tmp_string.number(i+1);
            tmp_string+="/";
            tmp_string+=tmp_string.number(j+1);
            tmp_string+=".png";
            tmp.load(tmp_string, 0, Qt::AutoColor);
            if(tmp.isNull()){
                break;
            }
            img_deplacement[i][j] = tmp;
        }
    }
    curentimage = 0;
}
bool personnage::get_alive(){
    return alive;
}

void personnage::init_images_attaque(QString fichier){
    QPixmap tmp;
    QString tmp_string;

    for(int i=0;i<4;i++){

        for(int j=0;j<8;j++){

            tmp_string.clear();
            tmp_string+=fichier;
            tmp_string+="attaque/";
            tmp_string+=tmp_string.number(i+1);
            tmp_string+="/";
            tmp_string+=tmp_string.number(j+1);
            tmp_string+=".png";
            tmp.load(tmp_string, 0, Qt::AutoColor);
            if(tmp.isNull()){
                break;
            }
            img_attaque[i][j] = tmp;
        }
    }
    curentattaque = 0;
}

void personnage::init_images_mort(QString fichier){
    QPixmap tmp;
    QString tmp_string;
        for(int j=0;j<6;j++){

        tmp_string.clear();
        tmp_string+=fichier;
        tmp_string+="mort/";
        tmp_string+=tmp_string.number(j+1);
        tmp_string+=".png";
        tmp.load(tmp_string, 0, Qt::AutoColor);
        if(tmp.isNull()){
            break;
        }
        img_mort[j] = tmp;
    }
    curentmort = 0;
}

void personnage::set_attaque(bool atta){
    isfighting = atta;
}

void personnage::attaque(){
    if(isfighting){
        changement_attaque();
    }
}
void personnage::degat(int d){
    pv -= d;
    if(pv<=0){
        alive = 0;
    }
}
void personnage::set_pv(int d){
    pv = d;
}

int personnage::get_pv(){
   return pv;
}
