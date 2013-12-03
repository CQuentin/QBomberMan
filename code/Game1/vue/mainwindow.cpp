#include "mainwindow.h"

/* Constructeur de la classe MainWindow */
MainWindow::MainWindow(QString hote, QWidget * parent) : QMainWindow(parent)
{
    initialiserSocket(hote);
    baseGravity = 1;
    largeur = 900;
    hauteur = 600;
    tailleC = 20;
    largeurG = largeur/tailleC;
    hauteurG = hauteur/tailleC;
    gravity = 0;
    grilleBrique.resize(largeurG);
    grilleBonus.resize(largeurG);
    controleur = new ToucheClavier();
    personnages.resize(2);
    end = 0;
    grabKeyboard();

    for(int i = 0; i<largeurG; i++){
        grilleBrique[i].resize(hauteurG);
        grilleBonus[i].resize(hauteurG);
    }

    scene = new QGraphicsScene(0, 0, largeur, hauteur, this);
    view = new QGraphicsView(scene, this);

    // background = new QPixmap("IMG_8708_blue_Sky2.jpg");
    // scene->setBackgroundBrush(*background);

    timer.start(5, this);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedWidth(largeur);
    view->setFixedHeight(hauteur);
    view->show();

    this->setFixedSize(largeur, hauteur);
}


void MainWindow::readyRead(){
    while(socket->canReadLine())
    {
        QString line = QString::fromUtf8(socket->readLine()).trimmed();

        //QRegExp messageRegex("^([^:]+):(.*)$");
        QRegExp usersRegex("^/users:(.*)$");
        QRegExp idRegex("^/i:(.*)$");
        QRegExp deplacementRegex("^/p:(.*)$");
        QRegExp bombeRegex("^/bom:(.*)$");
        QRegExp declenchementRegex("^/t:(.*)$");
        QRegExp addBonusRegex("^/abon:(.*)$");
        QRegExp removeBonusRegex("^/rbon:(.*)$");
        QRegExp killsRegex("^/k:(.*)$");
        QRegExp erreurRegex("^/erreur:(.*)$");

        if(idRegex.indexIn(line) != -1){
            QStringList mots = idRegex.cap(1).split(" ");

            chargerNiveau(mots[2]);

            personnages.resize(mots[1].toInt()); // mots[1] étant le nbre max de joueurs
            id = mots[0].toInt();
            QPair<int,int> pair;

            if(entrer.size() > id){
                pair = entrer.at(id);
                ajouterPersonnage(id,pair.second,pair.first);
            }
            else
                ajouterPersonnage(id,4,2);
        }

        // Nouveau Joueur
        else if(usersRegex.indexIn(line) != -1)
        {
            // If so, update our users list on the right:
            QStringList users = usersRegex.cap(1).split(",");

            foreach(QString user, users){
                QStringList J = user.split(" ");
                bool present = false;
                /*
                *J[0] id joueur
                */

                foreach(Joueur *j ,personnages){
                    if(j != NULL && j->getId() == J[0].toInt())
                        present = true;
                }
                if(!present)
                    ajouterPersonnage(J[0].toInt(),5,3);
            }

        }
        //Bombe posée
        else if(bombeRegex.indexIn(line) != -1){
            QStringList bombe = bombeRegex.cap(1).split(" ");
            // bombe[0] id joueur
            // bombe[1] pos X
            // bombe[2] pos Y
            if (bombe[0].toInt()!= id)
                ajouterBombe(bombe[0].toInt(),bombe[1].toInt(),bombe[2].toInt(), false);
        }
        //Deplacement
        else if(deplacementRegex.indexIn(line) != -1){
            QStringList depl = deplacementRegex.cap(1).split(" ");
            // depl[0].toInt() id joueur
            // depl[1].toInt() pos X
            // depl[2].toInt() pos Y
            // depl[3].toInt() pos X dans sprite
            // depl[4].toInt() pos Y dans sprite
            // depl[5].toInt() largeur du sprite
            // depl[6].toInt() hauteur du sprite
            // depl[7] bool orientation gauche
            // depl[8] bool est en vie
            // depl[9] doit disparaitre
            // depl[10] power bombes
            // depl[11] trigger bombe
            // depl[12] immortel

            if(depl[0].toInt() != id){
                if(!depl[8].toInt() && depl[9].toInt()){
                    scene->removeItem(personnages[depl[0].toInt()]->getPicture());
                    personnages[depl[0].toInt()]->setCurrentS(9);

                    //si le Joueur est mort et qu'il avait le bonus TRIGGER, on lance le timer de ses bombes
                    if(personnages[depl[11].toInt()]){
                        for(int i = 0; i < personnages[depl[0].toInt()]->getVectorBombes().size(); i++)
                            personnages[depl[0].toInt()]->getVectorBombes()[i]->startCountDown();
                    }

                }else{

                    int oldPosX = personnages[depl[0].toInt()]->getX();
                    int oldPosY =personnages[depl[0].toInt()]->getY();
                    int dx = depl[1].toInt() - oldPosX;
                    int dy = depl[2].toInt() - oldPosY;


                    personnages[depl[0].toInt()]->getPicture()->moveBy(dx,dy);
                    personnages[depl[0].toInt()]->setImmortality(depl[12].toInt());
                    personnages[depl[0].toInt()]->setX(depl[1].toInt());
                    personnages[depl[0].toInt()]->setY(depl[2].toInt());
                    personnages[depl[0].toInt()]->setCoordSprite(depl[3].toInt(),depl[4].toInt(),depl[5].toInt(),depl[6].toInt());
                    personnages[depl[0].toInt()]->setOrientG(depl[7].toInt());
                    personnages[depl[0].toInt()]->refreshPicture();
                    personnages[depl[0].toInt()]->setPowerBomb(depl[10].toInt());
                    personnages[depl[0].toInt()]->setTriggerBomb(depl[11].toInt());
                }
            }
        }
        // déclenchement d'une bombe avec espace
        else if (declenchementRegex.indexIn(line) != -1){
            QStringList tri = declenchementRegex.cap(1).split(" ");
            if(tri[0].toInt() != id)
                triggerLastBombe(tri[0].toInt(),false);
            // apparition d'un bonus
        }else if(addBonusRegex.indexIn(line) != -1){
            QStringList abon = addBonusRegex.cap(1).split(" ");
            if(abon[0].toInt() != id)
                ajouterBonus(abon[1].toInt(),abon[2].toInt(),false,abon[3].toInt());
        }
        // disparition d'un bonus
        else if(removeBonusRegex.indexIn(line) != -1){
            QStringList rbon = removeBonusRegex.cap(1).split(" ");
            if(rbon[0].toInt() != id){
                scene->removeItem(grilleBonus[rbon[1].toInt()][rbon[2].toInt()]->getPicture());
                grilleBonus[rbon[1].toInt()][rbon[2].toInt()] = NULL;
            }
        }
        // dit qui a tué qui
        else if(killsRegex.indexIn(line) != -1){
            QStringList kills = killsRegex.cap(1).split(" ");
            if(kills[0].toInt() != id){
                personnages[kills[0].toInt()]->setKillBy(kills[1].toInt());
                personnages[kills[1].toInt()]->incrNbKills();
            }
        }
        else if (erreurRegex.indexIn(line) != -1){
            QStringList erreurs = erreurRegex.cap(1).split(" ");
            qCritical() << erreurs[0];
            close();
        }
    }


}


void MainWindow::chargerNiveau(QString niveau){

    QString fileName = "../Game1/ressource/Niveaux/Niv"+niveau+".level";
    QFile fichier(fileName);
    fichier.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream flux(&fichier);
    QString ligne;
    int i = -1 ;
    while(!flux.atEnd()){
        ligne = flux.readLine();
        i++;
        QStringList colonne = ligne.split(" ");
        QPair<int,int> pair;
        for(int j = 0 ; j < colonne.size() ; j++){
            switch(colonne[j].toInt()){

            case 1 :
                ajouterBrique(false,j,i);
                break;

            case 2:
                ajouterBrique(true,j,i);
                break;

            case 3:
                pair.first = i;
                pair.second = j;
                entrer.push_back(pair);
                break;

            default:
                break;
            }
        }
    }
}

void MainWindow::connected(){
    socket->write(QString("/me:\n").toUtf8());
}

void MainWindow::ajouterPersonnage(int id,int i, int j){
    int posX = getPositionXFromGrille(i);
    int posY = getPositionYFromGrille(j);
    personnages[id]=new Joueur(id,posX,posY);
    scene->addItem(personnages[id]->getPicture());
}

void MainWindow::ajouterBrique(bool cassable, int i, int j){
    if(grilleBrique[i][j] == NULL){
        int posX = getPositionXFromGrille(i);
        int posY = getPositionYFromGrille(j);
        grilleBrique[i][j] = new Brique(cassable,posX,posY);
        scene->addItem(grilleBrique[i][j]->getPicture());
    }
}


void MainWindow::ajouterBombe(int bmId,int x, int y, bool w){
    Bombe *bombe = new Bombe(0,x,y,bmId);
    if(w){
        bombe->setY(bombe->getY() - bombe->getHauteur()/2);
        bombe->setX(bombe->getX() - bombe->getLargeur()/2);
    }
    else{
        bombe->setX(x);
        bombe->setY(y);
    }
    personnages[bmId]->addBombe(bombe);
    scene->addItem(bombe->getPicture());

    if(w)
        socket->write(QString("/bom:%1 %2 %3 $\n" ).arg(bombe->getBManId()).arg(bombe->getX()).arg(bombe->getY()).toUtf8());

}

void MainWindow::ajouterExplosion(Bombe *bombe,int x, int y, int dx, int dy,bool end){
    QPixmap sprite = QPixmap("../Game1/ressource/sprites_bomberman.png");
    QTransform transform;

    if(end) // si l'image est le carré noir ou le morceau arrondi
        sprite = sprite.copy(48,591,20,20);
    else
        sprite = sprite.copy(18,591,20,20);

    // rotation de l'image en fonction de du sens de propagation de l'explosion
    if (dx == -1)
        sprite = sprite.transformed(transform.rotate( -180,Qt::YAxis ), Qt::FastTransformation);
    else if (dy != 0)
        sprite = sprite.transformed(transform.rotate( dy *90 ), Qt::FastTransformation);

    QGraphicsPixmapItem *picture = new QGraphicsPixmapItem(sprite);
    bombe->addExplosions(picture);
    picture->setPos(x,y);
    scene->addItem(picture);

}

void MainWindow::ajouterBonus(int i, int j, bool w, int t){
    int x = getPositionXFromGrille(i);
    int y = getPositionYFromGrille(j);
    grilleBonus[i][j] = new Bonus(x,y,t);
    scene->addItem(grilleBonus[i][j]->getPicture());

    if(w)
        socket->write(QString("/abon:%1 %2 %3 %4 $\n" ).arg(id).arg(i).arg(j).arg(grilleBonus[i][j]->getBonusType()).toUtf8());
}

void MainWindow::keyReleaseEvent(QKeyEvent* event) {
    if(!event->isAutoRepeat())
        controleur->setPressed(event->key(),false);
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    if(!event->isAutoRepeat())
        controleur->setPressed(event->key(),true);
}

bool MainWindow::collisionTest(int x, int y){
    int hauteurP = personnages[id]->getHauteur(), largeurP = personnages[id]->getLargeur();
    bool colision = false;
    int newX = personnages[id]->getX()+x;
    int newY = personnages[id]->getY()+y;

    // nombre de points du personnages[id] espacés de tailleC px
    int nbPointX =1 + largeurP / tailleC;
    if (largeurP % tailleC !=0)
        nbPointX++;
    int nbPointY =1 + hauteurP / tailleC;
    if (hauteurP % tailleC !=0)
        nbPointY++;

    int posGrilleI;
    int posGrilleJ;

    // on regarde dans quelle partie de la grille se trouve chaque points espacés de taille Cpx du personnages[id]
    for (int i = 0; i< nbPointX; i++){
        if(i * tailleC > largeurP)
            posGrilleI = getGrilleIFromPosition(newX + largeurP);
        else
            posGrilleI = getGrilleIFromPosition(newX + i * tailleC);

        for (int j = 0; j< nbPointY; j++){
            if(j * tailleC > hauteurP)
                posGrilleJ = getGrilleJFromPosition(newY + hauteurP);
            else
                posGrilleJ = getGrilleJFromPosition(newY + j * tailleC);

            if(personnages[id]->isColliding(posGrilleI,posGrilleJ,grilleBrique)){
                colision  = true;
            }
        }
    }

    return colision;
}


void MainWindow::tryMove(int x, int y){
    int newX = personnages[id]->getX()+x;
    int newY = personnages[id]->getY()+y;

    if(!collisionTest(x,y)){
        personnages[id]->setX(newX);
        personnages[id]->setY(newY);
        personnages[id]->getPicture()->moveBy(x,y);

        QVector<int> qv = personnages[id]->getCoordSprite();
        socket->write(QString("/p:%1 %2 %3 %4 %5 %6 %7 %8 %9 %10 %11 %12 %13 $\n")
                      .arg(id).arg(newX).arg(newY)
                      .arg(qv.at(0)).arg(qv.at(1)).arg(qv[2]).arg(qv[3])
                .arg(personnages[id]->isOrientG())
                .arg(personnages[id]->isAlive())
                .arg(0)
                .arg(personnages[id]->getPowerBomb())
                .arg(personnages[id]->hasBonusTrigger())
                .arg(personnages[id]->isImmortal())
                .toUtf8());
    }
}

void MainWindow::tryJump(){
    // si le Joueur a le bonus pour voler ou si il a une brique sous ses pieds
    if(personnages[id]->getBonusJump() == 2 || collisionTest(0,1))
        gravity = -baseGravity;
}

void MainWindow::timerEvent ( QTimerEvent * event ){
    int cptDead = 0;
    bool start = true;
    // tant que tout les joueurs n'ont pas rejoint la partie, start = false et on ne fait rien
    for(int i = 0; i < personnages.size(); i++){
        if(personnages[i] == NULL)
            start = false;
    }
    if (start){
        // on regarde si il reste au plus un Joueur en vie. Si c'est le cas, on dit que c'est la fin
        if(end == 0){
            for (int i =0; i < personnages.size(); i++){
                if (personnages[i]->getCurrentS() == 9)
                    cptDead ++;
                if (cptDead >= personnages.size()-1)
                    end = 1;
            }
        }
        // si c'est la fin, le Joueur vivant est content, et on affiche les scores si ce n'est pas déjà fait (end == 1)
        if(end >0){
            if (end == 1)
                displayEndScreen();
            if (end == 2 && personnages[id]->isAlive()){
                personnages[id]->cheer();
                QVector<int> qv = personnages[id]->getCoordSprite();
                socket->write(QString("/p:%1 %2 %3 %4 %5 %6 %7 %8 %9 %10 %11 %12 %13 $\n")
                              .arg(id).arg(personnages[id]->getX()).arg(personnages[id]->getY())
                              .arg(qv.at(0)).arg(qv.at(1)).arg(qv[2]).arg(qv[3])
                        .arg(personnages[id]->isOrientG())
                        .arg(personnages[id]->isAlive())
                        .arg(0)
                        .arg(personnages[id]->getPowerBomb())
                        .arg(personnages[id]->hasBonusTrigger())
                        .arg(personnages[id]->isImmortal())
                        .toUtf8());
            }
        }
        // si ce n'est pas la fin, on regarde si son personnage est en train de mourrir
        else if(personnages[id]->getCurrentS() == 8){
            //si c'est le cas, on met les sprites de la mort et on les envoie aux autres joueurs
            personnages[id]->die();
            QVector<int> qv = personnages[id]->getCoordSprite();
            socket->write(QString("/p:%1 %2 %3 %4 %5 %6 %7 %8 %9 %10 %11 %12 %13 $\n").arg(id).arg(personnages[id]->getX()).arg(personnages[id]->getY())
                          .arg(qv.at(0)).arg(qv.at(1)).arg(qv[2]).arg(qv[3])
                    .arg(personnages[id]->isOrientG())
                    .arg(personnages[id]->isAlive())
                    .arg(0)
                    .arg(personnages[id]->hasBonusTrigger())
                    .arg(personnages[id]->isImmortal())
                    .toUtf8());

            if(personnages[id]->getCurrentS() == 9){

                // si le Joueur a le bonus TRIGGER, on lance le timer de ses bombes
                if(personnages[id]->hasBonusTrigger()){
                    for(int i = 0; i < personnages[id]->getVectorBombes().size(); i++)
                        personnages[id]->getVectorBombes()[i]->startCountDown();
                }

                scene->removeItem(personnages[id]->getPicture());
                socket->write(QString("/p:%1 %2 %3 %4 %5 %6 %7 %8 %9 %10 %11 %12 %13 $\n").arg(id).arg(personnages[id]->getX()).arg(personnages[id]->getY())
                              .arg(qv.at(0)).arg(qv.at(1)).arg(qv[2]).arg(qv[3])
                        .arg(personnages[id]->isOrientG())
                        .arg(personnages[id]->isAlive())
                        .arg(1)
                        .arg(personnages[id]->hasBonusTrigger())
                        .arg(personnages[id]->isImmortal())
                        .toUtf8());
            }
        }
        // si son personnage n'est pas en train de mourrir, on vérifie qu'il n'est pas déjà mort.
        else if(personnages[id]->getCurrentS() != 9){
            // si il est en vie, on calcule toutes les données cncernant notre personnage

            // ----------- partie personnages[id]
            int x = 0; // déplacement du personnage sur l'axe des abscisse

            // gestion du saut
            personnages[id]->checkImmortality();
            if (gravity<0){
                personnages[id]->setCurrentH(personnages[id]->getCurrentH()+1);
                if(personnages[id]->getCurrentH()>= personnages[id]->getMaxH() || collisionTest(0,-1)){ // fin du saut, on retombe
                    gravity = baseGravity;
                    personnages[id]->setCurrentH(0);
                }
                else{ // on continue à monter
                    personnages[id]->setCurrentS(6);
                    personnages[id]->immobile();
                }

            }
            // atterissage
            else if(collisionTest(0,1)){
                if(gravity == 1)
                    personnages[id]->setCurrentS(4); //LANDING
                gravity = 0;
            }
            // chute
            else {
                gravity = baseGravity;
                personnages[id]->setCurrentS(3); // FALLING
                personnages[id]->immobile();
            }

            // on essaie de sauter si on a appuyer sur la flèche du haut
            if((gravity == 0 || personnages[id]->getBonusJump() == 2) && controleur->getStateKeys(0))
                tryJump();

            // on essaie de poser une bombe si on a appuyer sur la flèche du bas
            if(controleur->getStateKeys(2)){
                if (personnages[id]->tryDropBombe()){
                    ajouterBombe(id,personnages[id]->getX()+personnages[id]->getLargeur()/2,personnages[id]->getY()+ personnages[id]->getHauteur()/2,true);
                    controleur->setPressed(Qt::Key_Down,false);
                }
            }

            // déplacement gauche / droite en fonction de la touche sur laquelle on appuit
            if(controleur->getStateKeys(1)){
                x +=- 1;
                personnages[id]->courireG();
            }
            else if(controleur->getStateKeys(3)){
                x += 1;
                personnages[id]->courireD();
            }

            // si on ne bouge pas, on regarde quel état et quelle image le Joueur doit avoir
            if(x == 0 && gravity == 0 )
                personnages[id]->immobile();

            // on fait exploser la dernière bombe posée du personnage si on appuit sur espace et q'u o a le bonus TRIGGER
            if(controleur->getStateKeys(4) && personnages[id]->hasBonusTrigger()){
                triggerLastBombe(id,true);
                controleur->setPressed(Qt::Key_Space, false);
            }

            // on bouge le personnage en fonction de gravity (qui dépend du saut et des collisions)
            tryMove(0,gravity);

            //tired permet de ne bouger qu'une fois sur deux (possible de modifier) pour ralentir le personnage
            int tired = personnages[id]->getTired();

            if (tired == -1) // -1 si le personnage a le bonus SPEED, il bouge chaque fois
                tryMove(x,0);
            else if(tired == 0)
                personnages[id]->setTired(1); // baseTired ?
            else{
                tryMove(x,0);
                personnages[id]->setTired(tired-1);
            }
            checkBonus();
        }

        // ----------- partie bombes
        // on fait exploser toutes les bombes présentes dans scene, si elles doivent exploser
        for (int idJ = 0; idJ < personnages.size(); idJ++ ){
            for(int i = 0; i<personnages[idJ]->getVectorBombes().size(); i++){
                if(personnages[idJ]->getVectorBombes()[i]->isExploding()){
                    explosion(personnages[idJ]->getVectorBombes()[i],0,0);
                    explosion(personnages[idJ]->getVectorBombes()[i],0,1);
                    explosion(personnages[idJ]->getVectorBombes()[i],0,-1);
                    explosion(personnages[idJ]->getVectorBombes()[i],1,0);
                    explosion(personnages[idJ]->getVectorBombes()[i],-1,0);
                }
                if(personnages[idJ]->getVectorBombes()[i]->hasExploded()){
                    for(int j = 0; j< personnages[idJ]->getVectorBombes()[i]->getExplosions().size(); j++)
                        scene->removeItem(personnages[idJ]->getVectorBombes()[i]->getExplosions().at(j));
                    scene->removeItem((personnages[idJ]->getVectorBombes()[i])->getPicture());
                    if(personnages[idJ]->getVectorBombes()[i]->getBManId() == personnages[idJ]->getId()){
                        personnages[idJ]->decrNbBombe();
                        personnages[idJ]->removeBombe(i);
                    }
                }
            }
        }
    }
}

QPoint MainWindow::getPositionFromGrille(int i, int j){
    // tailleC car une case = tailleCp,

    return QPoint(i * tailleC , j * tailleC );
}

int MainWindow::getPositionXFromGrille(int i){
    // tailleC car une case = tailleCp,
    return i * tailleC;
}

int MainWindow::getPositionYFromGrille( int j){
    // tailleC car une case = tailleCp,
    return j*tailleC;
}

int MainWindow::getGrilleIFromPosition(int x){
    return x/tailleC;
}

int MainWindow::getGrilleJFromPosition(int y){
    return  y/tailleC;
}

void MainWindow::toggleGravity(){
    gravity = - gravity;
}

int MainWindow::getGravity(){
    return gravity;
}


void MainWindow::triggerLastBombe(int bmId, bool w){
    if (personnages[bmId]->getLastBombe() != NULL){
        personnages[bmId]->getLastBombe()->trigger();
        if (w)
            socket->write(QString("/t:%1 $\n").arg(bmId).toUtf8());
    }
}

void MainWindow::explosion(Bombe *bombe, int dx, int dy){
    bool hit = false;

    int x = bombe->getX();
    int y = bombe->getY();

    // point en haut à gauche de la bombe
    int posGrilleI = getGrilleIFromPosition(x);
    int posGrilleJ = getGrilleJFromPosition(y);

    // point en bas à droite de la bombe
    int posGrilleI2 = getGrilleIFromPosition(x+bombe->getLargeur());
    int posGrilleJ2 = getGrilleJFromPosition(y+bombe->getHauteur());

    int range = bombe->getPower();
    int i = posGrilleI, j= posGrilleJ;
    int i2 = posGrilleI2, j2 = posGrilleJ2;

    if(dx == 0 && dy == 0){ // explosion sur la position de la bombe
        if(personnages[id]->isAlive() && hitTest(i,j,i2,j2))
            hit = true;
        ajouterExplosion(bombe,x,y,dx,dy,false);
    }
    else{
        // gestion de la propagation des explosions en fonction de leur sens (dx et dy)

        //end sert à savoir si l'image doit être le carré noir ou le morceau arrondi(dernière explosion)
        bool end = false;

        i = i +dx;
        j = j +dy;
        i2 = i2 +dx;
        j2 = j2 +dy;
        x += dx * tailleC; // 20 = taille explosion
        y += dy * tailleC;

        /*
        On ajoute une explosion tant que :
            - l'explosion n'est pas bloqué par une brique incassable
            - l'explosion partant de deux points (haut gauche, bas droite), il faut vérifier que le point le plus avancé ne soit pas derrière
              la limite du jeu
            - range > 0 (range dépend de power, la portée des bombes
        */
        while(((grilleBrique[i][j] == NULL || grilleBrique[i][j]->estCassable())
               && ((grilleBrique[i2][j2] == NULL || grilleBrique[i2][j2]->estCassable() || j2 == hauteurG-1 || i2 == largeurG-1 || j2 == 0 || i2 == 0) ))
              && range >0)
        {

            if (range -1 <= 0)
                end = true;
            if(grilleBrique[i][j] != NULL && grilleBrique[i][j]->estCassable())
                detruireBrique(i,j,bombe->getBManId());
            if(grilleBrique[i2][j2] != NULL && grilleBrique[i2][j2]->estCassable())
                detruireBrique(i2,j2, bombe->getBManId());

            // on regarde si son personnage est touché
            if(personnages[id]->isAlive() && hitTest(i,j,i2,j2))
                hit = true;

            ajouterExplosion(bombe,x,y,dx,dy,end);

            i = i +dx;
            j = j +dy;
            i2 = i2 +dx;
            j2 = j2 +dy;
            x += dx * tailleC; // 20 = taille explosion
            y += dy * tailleC;

            // garde fou, tout les test sont faux normalement
            if (j < 0)
                j = 0;
            if (i < 0)
                i = 0;
            if (j > hauteurG)
                j = hauteurG;
            if (i > largeurG)
                i = largeurG;
            if (j2 < 0)
                j2 = 0;
            if (i2 < 0)
                i2 = 0;
            if (j2 > hauteurG)
                j2 = hauteurG;
            if (i2 > largeurG)
                i2 = largeurG;
            range --;
        }
    }
    // si le personnage touché est morts, on envoie aux autres joueurs qui a tué qui
    if(hit){
        personnages[id]->hit();
        if(!personnages[id]->isAlive()){
            personnages[id]->setKillBy(bombe->getBManId());
            personnages[bombe->getBManId()]->incrNbKills();
            socket->write(QString("/k:%1 %2 $\n").arg(id).arg(bombe->getBManId()).toUtf8());
        }
    }
}



bool MainWindow::hitTest(int bI, int bJ, int bI2, int bJ2){
    int hauteurP = personnages[id]->getHauteur(), largeurP = personnages[id]->getLargeur()/*-1*/;
    bool hit = false;


    // nombre de points du personnages[id] espacés de tailleC px
    int nbPointX =1 + largeurP / tailleC;
    if (largeurP % tailleC !=0)
        nbPointX++;
    int nbPointY =1 + hauteurP / tailleC;
    if (hauteurP % tailleC !=0)
        nbPointY++;

    int posGrilleI;
    int posGrilleJ;

    // on regarde dans quelle partie de la grille se trouve chaque points espacés de taille Cpx du personnages[id]
    for (int i = 0; i< nbPointX; i++){
        if(i * tailleC > largeurP)
            posGrilleI = getGrilleIFromPosition(personnages[id]->getX() + largeurP);
        else
            posGrilleI = getGrilleIFromPosition(personnages[id]->getX() + i * tailleC);

        for (int j = 0; j< nbPointY; j++){
            if(j * tailleC > hauteurP)
                posGrilleJ = getGrilleJFromPosition(personnages[id]->getY() + hauteurP);
            else
                posGrilleJ = getGrilleJFromPosition(personnages[id]->getY() + j * tailleC);

            if((posGrilleI == bI && posGrilleJ == bJ) ||(posGrilleI == bI2 && posGrilleJ == bJ2))
                hit  = true;
        }
    }
    return hit;
}

void MainWindow::detruireBrique(int i, int j,int idJ){
    scene->removeItem(grilleBrique[i][j]->getPicture());
    grilleBrique[i][j] = NULL;
    // le client qui a détruit la brique se charge de générer aléatoirement le bonus et de l'envoyer aux aurtes clients
    if(id == idJ){
        if(qrand()%4 +1 == 1) // une chance sur 4
            ajouterBonus(i,j,true,-1);
    }

}

void MainWindow::checkBonus(){
    int hauteurP = personnages[id]->getHauteur(), largeurP = personnages[id]->getLargeur();

    int x = personnages[id]->getX();
    int y = personnages[id]->getY();

    // nombre de points du personnages[id] espacés de tailleC px
    int nbPointX =1 + largeurP / tailleC;
    if (largeurP % tailleC !=0)
        nbPointX++;
    int nbPointY =1 + hauteurP / tailleC;
    if (hauteurP % tailleC !=0)
        nbPointY++;

    int posGrilleI;
    int posGrilleJ;

    // on regarde dans quelle partie de la grille se trouve chaque points espacés de taille Cpx du personnages[id]
    for (int i = 0; i< nbPointX; i++){
        if(i * tailleC > largeurP)
            posGrilleI = getGrilleIFromPosition(x + largeurP);
        else
            posGrilleI = getGrilleIFromPosition(x + i * tailleC);

        for (int j = 0; j< nbPointY; j++){
            if(j * tailleC > hauteurP)
                posGrilleJ = getGrilleJFromPosition(y + hauteurP);
            else
                posGrilleJ = getGrilleJFromPosition(y + j * tailleC);

            if(grilleBonus[posGrilleI][posGrilleJ] != NULL){
                personnages[id]->receiveBonus(grilleBonus[posGrilleI][posGrilleJ]->getBonusType());
                scene->removeItem(grilleBonus[posGrilleI][posGrilleJ]->getPicture());
                grilleBonus[posGrilleI][posGrilleJ] = NULL;

                socket->write(QString("/rbon:%1 %2 %3 $\n").arg(id).arg(posGrilleI).arg(posGrilleJ).toUtf8());
            }
        }
    }
}

QString const MainWindow::getHote ()
{
    return m_hote;
}

void MainWindow::setHote(QString hote)
{
    m_hote = hote;
}

void MainWindow::initialiserSocket(QString  hote)
{
    m_hote = hote;
    socket = new QTcpSocket(this);
    socket->connectToHost(m_hote, 4200);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
}


void MainWindow::displayEndScreen(){
    int decH = 0; // décale la position du texte sur l'axe des abscisses pour à peu près le centrer
    QGraphicsTextItem * endText = new QGraphicsTextItem;
    QFont myFont = QFont("Time", 45);
    myFont.setBold(true);
    endText->setFont(myFont);
    endText->setTextWidth(900);

    if(personnages[id]->isAlive()){
        endText->setPlainText("Victoire");
        decH = 7*22;
        endText->setDefaultTextColor(Qt::green);
    }
    else{
        endText->setPlainText("Défaite");
        decH = 6*22;
        endText->setDefaultTextColor(Qt::red);
    }

    endText->setPos(largeur/2 - decH, 0);
    endText->setZValue(99);
    scene->addItem(endText);
    end = 2;


    setStyleSheet("QTableWidget {background-color: rgba(0, 0, 0,150);}"
                  "QTableWidget {gridline-color: white;}"
                  "QTableWidget {color: white; }"
                  "QTableCornerButton::section {background-color: rgba(0, 0, 0,150);}"
                  "QHeaderView::section {background-color:rgba(0, 0, 0,150);}"
                  "QHeaderView::section {color:white;}"
                  "QHeaderView::section {gridline-color:white ;}"
                  "QHeaderView {background-color: rgba(0, 0, 0,150);}"
                  "QHeaderView {color: white;}"
                  );

    QTableWidget *score = new QTableWidget(personnages.size(),2,this);
    score->setGeometry(largeur/2 -65,hauteur/2 -90,131,180);

    score->setHorizontalHeaderItem(0, new QTableWidgetItem("Tués"));
    score->setHorizontalHeaderItem(1, new QTableWidgetItem("Tué par"));
    score->resizeColumnsToContents();
    score->resizeRowsToContents();

    for(int i = 0; i<personnages.size(); i++){
        score->setVerticalHeaderItem(i, new QTableWidgetItem(QString("J%1").arg(personnages[i]->getId() +1)));
        QTableWidgetItem *item = new QTableWidgetItem();
        score->setItem(i,0,item);
        item->setText(QString("%1").arg(personnages[i]->getNbKills()));


        QTableWidgetItem *item2 = new QTableWidgetItem();
        score->setItem(i,1,item2);
        if(personnages[i]->getKillBy() != -1)
            item2->setText(QString("J%1").arg(personnages[i]->getKillBy() +1));
    }
    score->show();
}

/* Destructeur de la classe MainWindow */
MainWindow::~MainWindow()
{
    for(int i=0; i<(int) grilleBrique.size(); i++)
        for(int j=0; j<(int) grilleBrique[i].size(); j++)
            delete grilleBrique[i][j];

    for(int i=0; i<(int) grilleBonus.size(); i++)
        for(int j=0; j<(int) grilleBonus[i].size(); j++)
            delete grilleBonus[i][j];

    for(int i = 0; i < personnages.size(); i++)
        delete personnages[i];

    delete view;
    delete scene;
}
