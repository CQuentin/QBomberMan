#include "joueur.h"


Joueur::Joueur(int id, int x , int y){
    posX = x;
    posY = y;
    this->id = id;
    xSprite = 11;
    ySprite = 505;
    lSprite = 22;
    hSprite = 36;
    hauteur = 35;
    largeur = 19;
    maxHigh = 50;
    currentHigh = 0;
    step = 0;
    pauseSprite = 15;
    state = STANDING;
    orientG = false;
    nbMaxBombes = 1;
    nbBombes = 0;
    hp = 1;
    bombes.resize(0);
    immortality = false;
    immortalityCD = 1500;
    bonusPower = 1;
    bonusJump = 0;
    bonusTrigger = false;
    tired = 1;
    nbKills = 0;
    killBy = -1;

    if(id <4) // 1 : le nombre de couleurs différentes existantes
        sprite = QPixmap(QString("../Game1/ressource/sprites_bomberman_p%1.png").arg(id));
    else
        sprite = QPixmap("../Game1/ressource/sprites_bomberman.png");

    currentImage = sprite.copy(xSprite,ySprite,lSprite,hSprite);
    picture = new QGraphicsPixmapItem(currentImage);
    picture->setPos(x,y);
}


void Joueur::setX(int x)
{
    this->posX = x;
}

void Joueur::setY(int y)
{
    this->posY = y;
}

int Joueur::getX()
{
    return posX;
}

int Joueur::getY()
{
    return posY;
}


void Joueur::setPicture(QGraphicsPixmapItem *picture){
    this->picture = picture;
}

QGraphicsPixmapItem* Joueur::getPicture(){
    return picture;
}

bool Joueur::isColliding(int i, int j, QVector<QVector<Brique *> > grille){

    Brique *test = grille[i][j];

    if (test == NULL)
        return false;
    return true;
}


int Joueur::getMaxH(){
    return maxHigh;
}

int Joueur::getCurrentH(){
    return currentHigh;
}

void Joueur::setMaxH(int h){
    maxHigh = h;
}

void Joueur::setCurrentH(int h){
    currentHigh = h;
}

int Joueur::getHauteur(){
    return hauteur;
}

void Joueur::setHauteur(int h){
    hauteur = h;
}

int Joueur::getLargeur(){
    return largeur;
}

void Joueur::setLargeur(int l){
    largeur = l;
}

void Joueur::courireD(){

    if (state != FALLING && state != JUMPING){
        orientG = false;
        if (state != RUNNING_R)
            step = 0;

        state = RUNNING_R;
        if(pauseSprite >= 15){
            switch(step){
            case 0:
                setCoordSprite(13,28,32,34);
                step = 1;
                break;
            case 1:
                setCoordSprite(57,28,20,34);
                step = 2;
                break;
            case 2:
                setCoordSprite(83,29,27,33);
                step = 3;
                break;
            case 3:
                setCoordSprite(116,28,20,34);
                step = 4;
                break;
            case 4:
                setCoordSprite(141,27,20,35);
                step = 5;
                break;
            case 5:
                setCoordSprite(167,28,20,34);
                step = 6;
                break;
            case 6:
                setCoordSprite(193,29,27,33);
                step = 7;
                break;
            case 7:
                setCoordSprite(226,28,20,34);
                step = 8;
                break;
            case 8:
                setCoordSprite(252,27,20,35);
                step = 1;
                break;
            }
            pauseSprite = 0;
            currentImage = sprite.copy(xSprite,ySprite,lSprite,hSprite);

            if(immortality){ // ajout de transparance si le joueur est immortel
                QPainter p;
                p.begin(&currentImage);
                p.setCompositionMode(QPainter::CompositionMode_DestinationIn);
                p.fillRect(currentImage.rect(), QColor(0, 0, 0,100));
                p.end();
            }

            picture->setPixmap(currentImage);

        }
        else pauseSprite ++;
    }
    else if (orientG){  // si il est dans les airs et change de sens, rotation de l'image pour qu'il soit tourné vers la droite

        if(immortality){ // ajout de transparance si le joueur est immortel
            QPainter p;
            p.begin(&currentImage);
            p.setCompositionMode(QPainter::CompositionMode_DestinationIn);
            p.fillRect(currentImage.rect(), QColor(0, 0, 0,100));
            p.end();
        }

        picture->setPixmap(currentImage);
        orientG = false;
    }

}

void Joueur::courireG(){

    QTransform transform;
    if (state != FALLING && state != JUMPING){
        orientG = true;
        if (state != RUNNING_L)
            step = 0;

        state = RUNNING_L;
        if(pauseSprite >= 15){
            switch(step){
            case 0:
                setCoordSprite(13,28,32,34);
                step = 1;
                break;
            case 1:
                setCoordSprite(57,28,20,34);
                step = 2;
                break;
            case 2:
                setCoordSprite(83,29,27,33);
                step = 3;
                break;
            case 3:
                setCoordSprite(116,28,20,34);
                step = 4;
                break;
            case 4:
                setCoordSprite(141,27,20,35);
                step = 5;
                break;
            case 5:
                setCoordSprite(167,28,20,34);
                step = 6;
                break;
            case 6:
                setCoordSprite(193,29,27,33);
                step = 7;
                break;
            case 7:
                setCoordSprite(226,28,20,34);
                step = 8;
                break;
            case 8:
                setCoordSprite(252,27,20,35);
                step = 1;
                break;
            }
            currentImage = sprite.copy(xSprite,ySprite,lSprite,hSprite);
            // rotation de l'image pour qu'il soit tourné vers la gauche
            currentImage = currentImage.transformed(transform.rotate( -180,Qt::YAxis ), Qt::FastTransformation);
            pauseSprite = 0;

            if(immortality){ // ajout de transparance si le joueur est immortel
                QPainter p;
                p.begin(&currentImage);
                p.setCompositionMode(QPainter::CompositionMode_DestinationIn);
                p.fillRect(currentImage.rect(), QColor(0, 0, 0,100));
                p.end();
            }


            picture->setPixmap(currentImage);
        }
        else pauseSprite ++;
    }
    else if (!orientG){ // si il est dans les airs et change de sens, rotation de l'image pour qu'il soit tourné vers la gauche
        currentImage = currentImage.transformed(transform.rotate( -180,Qt::YAxis ), Qt::FastTransformation);

        if(immortality){
            QPainter p;
            p.begin(&currentImage);
            p.setCompositionMode(QPainter::CompositionMode_DestinationIn);
            p.fillRect(currentImage.rect(), QColor(0, 0, 0,100));
            p.end();
        }

        picture->setPixmap(currentImage);
        orientG = true;
    }
}

void Joueur::immobile(){
    QTransform transform;

    if(pauseSprite >= 45){
        switch(state){
        case STANDING :
            setCoordSprite(11,505,22,36);
            break;
        case RUNNING_R :
            setCoordSprite(294,28,25,34);
            state = STANDING;
            break;
        case RUNNING_L :
            setCoordSprite(294,28,25,34);
            state = STANDING;
            break;
        case FALLING :
            setCoordSprite(200,73,32,41);
            break;
            // LANDING et GETTING_UP : diminution de y, augmentation de H (pour baisser l'image, car personnage accroupi)
        case LANDING :
            setCoordSprite(238,81,27,35);
            state = GETTING_UP;
            break;
        case GETTING_UP :
            setCoordSprite(272,79,20,37);
            state = STANDING;
            break;
        case JUMPING :
            setCoordSprite(75,79,22,35);
            break;
        case DROPING :
            setCoordSprite(16,154,26,31);
            state = STANDING;
            break;
        }

        currentImage = sprite.copy(xSprite,ySprite,lSprite,hSprite);
        if (orientG)  // rotation de l'image pour qu'il soit tourné vers la gauche
            currentImage = currentImage.transformed(transform.rotate( -180,Qt::YAxis ), Qt::FastTransformation);
        pauseSprite = 0;

        if (immortality){ // ajout de transparance si le joueur est immortel
            QPainter p;
            p.begin(&currentImage);
            p.setCompositionMode(QPainter::CompositionMode_DestinationIn);
            p.fillRect(currentImage.rect(), QColor(0, 0, 0,100));
            p.end();
        }

        picture->setPixmap(currentImage);
    }
    else
        pauseSprite++;

}

void Joueur::setCurrentS(int s){
    state = s;
}

int Joueur::getCurrentS(){
    return state;
}

void Joueur::setMaxBombes(int n){
    nbMaxBombes = n;
}

int Joueur::getMaxBombes(){
    return nbMaxBombes;
}

void Joueur::incrNbBombe(){
    nbBombes++;
}

void Joueur::decrNbBombe(){
    nbBombes--;
}

bool Joueur::tryDropBombe(){
    if (nbBombes < nbMaxBombes){
        nbBombes++;
        if (state == STANDING) // on ne met pas la sprite où le personnage dépose une bombe si il est en cours de déplacement
            state = DROPING;
        return true;
    }
    else
        return false;
}

void Joueur::hit(){
    // enlève un point de vie au joueur si il n'est pas immortel
    // le tue si il a 0 point de vie, le rend immortel sinon

    if (!immortality){
        hp --;
        if(hp <= 0){
            step = 0;
            state = DYING;
            pauseSprite = 45;
        }
        else{
            immortality = true;
        }
    }

}

void Joueur::checkImmortality(){
    // diminue la durée d'immortalité, et retire l'immortalité quand elle atteint 0
    if (immortality){
        if (immortalityCD == 0){
            immortality = false;
            immortalityCD = 1500;
        }else
            immortalityCD -= 5;
    }
}

void Joueur::die(){
    if(pauseSprite >= 20){
        switch (step){
        case 0:
            setCoordSprite(261,435,31,33);
            step++;
            break;
        case 1:
            setCoordSprite(1,435,31,33);
            step++;
            break;
        case 2:
            setCoordSprite(39,435,31,33);
            step++;
            break;
        case 3:
            setCoordSprite(75,435,31,33);
            step++;
            break;
        case 4:
            setCoordSprite(110,435,31,33);
            step++;
            QSound::play("../Game1/ressource/sons/mort.wav");
            break;
        case 5:
            setCoordSprite(146,435,31,33);
            step++;
            break;
        case 6:
            setCoordSprite(182,435,31,33);
            step++;
            break;
        case 7:
            setCoordSprite(218,435,33,32);
            step++;
            break;
        case 8:
            state = DEAD;

            break;

        }
        currentImage = sprite.copy(xSprite,ySprite,lSprite,hSprite);
        pauseSprite = 0;
        picture->setPixmap(currentImage);
    }
    else pauseSprite++;
}

bool Joueur::isAlive(){

    return (hp > 0);
}


void Joueur::setId(int id){
    this->id = id;
}

int Joueur::getId(){
    return id;
}

void Joueur::setCoordSprite(int x, int y, int l, int h){
    xSprite = x;
    ySprite = y;
    lSprite = l;
    hSprite = h;
}

QVector<int> Joueur::getCoordSprite(){
    QVector<int> retour;
    retour.append(xSprite);
    retour.append(ySprite);
    retour.append(lSprite);
    retour.append(hSprite);

    return retour;
}

void Joueur::addBombe(Bombe *b){
    // ajoute une bombe, et lui donne des propriétés en fonction des bonus ramassé par le Joueur
    if(bonusTrigger)
        b->stopCountDown();
    b->setPower(bonusPower);
    bombes.append(b);
}

void Joueur::removeBombe(int i){
    bombes.remove(i);
}

QVector<Bombe*> Joueur::getVectorBombes(){
    return bombes;
}

Bombe* Joueur::getLastBombe(){
    int i = bombes.size();
    if(i > 0)
        return bombes.at(i-1);
    else return NULL;
}

bool Joueur::isOrientG(){
    return orientG;
}


void Joueur::setOrientG(bool o){
    orientG = o;
}

void Joueur::refreshPicture(){  // uniquement pour les autres Joueur
    QTransform transform;
    currentImage = sprite.copy(xSprite,ySprite,lSprite,hSprite);
    if (orientG)    // rotation de l'image si le joueur est orienté vers la gauche
        currentImage = currentImage.transformed(transform.rotate( -180,Qt::YAxis ), Qt::FastTransformation);

    if(immortality){ // ajout de transparance si le joueur est immortel
        QPainter p;
        p.begin(&currentImage);
        p.setCompositionMode(QPainter::CompositionMode_DestinationIn);
        p.fillRect(currentImage.rect(), QColor(0, 0, 0,100));
        p.end();
    }
    picture->setPixmap(currentImage);
}

void Joueur::receiveBonus(int t){
    QSound::play("../Game1/ressource/sons/bonus.wav");
    switch(t){
    case 0 :
        if(hp <3)
            hp ++;
        break;
    case 1 :
        if(bonusPower < 5)
            bonusPower ++;
        break;
    case 2 :
        if (nbMaxBombes < 5)
            nbMaxBombes ++;
        break;
    case 3 :
        if(bonusJump == 0){
            maxHigh = 100;
            bonusJump++;
        }
        else if (bonusJump == 1){
            maxHigh = 50;
            bonusJump++;
        }
        break;
    case 4 :
        if(tired>-1)
            tired = -1;
        break;
    case 5 :
        bonusTrigger = true;
        break;
    }

}


void Joueur::cheer(){
    state = WINNING;
    if(pauseSprite >= 15){
        switch (step){
        case 0:
            setCoordSprite(5,374,19,31);
            step++;
            break;
        case 1:
            setCoordSprite(33,374,31,34);
            step++;
            break;
        case 2:
            setCoordSprite(67,374,31,32);
            step++;
            break;
        case 3:
            setCoordSprite(101,374,31,34);
            step++;
            break;
        case 4:
            setCoordSprite(135,374,31,36);
            step++;
            break;
        case 5:
            setCoordSprite(173,374,23,36);
            step++;
            break;
        case 6:
            setCoordSprite(206,374,24,36);
            step++;
            break;
        case 7:
            setCoordSprite(241,373,23,37);
            step = 0;
            break;

        }
        currentImage = sprite.copy(xSprite,ySprite,lSprite,hSprite);
        pauseSprite = 0;
        picture->setPixmap(currentImage);
    }
    else pauseSprite++;
}

bool Joueur::hasBonusTrigger(){
    return bonusTrigger;
}

int Joueur::getBonusJump(){
    return bonusJump;
}

int Joueur::getTired(){
    return tired;
}

void Joueur::setTired(int t){
    tired = t;
}

bool Joueur::isImmortal(){
    return immortality;
}

void Joueur::setImmortality(bool i){
    immortality = i;
}

int Joueur::getPowerBomb(){
    return bonusPower;
}

void Joueur::setPowerBomb(int p){
    bonusPower = p;
}

void Joueur::setTriggerBomb(bool t){
    bonusTrigger = t;
}

void Joueur::setKillBy(int idJ){
    killBy = idJ;
}

int Joueur::getKillBy(){
    return killBy;
}

int Joueur::getNbKills(){
    return nbKills;
}

void Joueur::incrNbKills(){
    nbKills++;
}

Joueur::~Joueur(){
    delete this;
}
