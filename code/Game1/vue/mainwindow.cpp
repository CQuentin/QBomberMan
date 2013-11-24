#include "mainwindow.h"

/* Constructeur de la classe MainWindow */
MainWindow::MainWindow(QWidget * parent) : QMainWindow(parent)
{

    socket = new QTcpSocket(parent);
    socket->connectToHost("localhost", 4200);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));



    baseGravity = 1;
    largeur = 900;
    hauteur = 600;
    tailleC = 20;
    largeurG = largeur/tailleC;
    hauteurG = hauteur/tailleC;
    gravity = 0;
    grille.resize(largeurG);
    grilleBonus.resize(largeurG);
    controleur = new ToucheClavier();
    personnages.resize(0);     // nb joueur donné par serveur -> mettre les joueurs dans l'ordre de leur id
  //id = 0;
    grabKeyboard();

    for(int i = 0; i<largeurG; i++){
        grille[i].resize(hauteurG);
        grilleBonus[i].resize(hauteurG);
    }

    scene = new QGraphicsScene(0, 0, largeur, hauteur, this);
    view = new QGraphicsView(scene, this);

    /*  -------------- début niveau -------------------- */

    //TODO : gérer avec des classes niveau
    // for nb joueur...
 //  ajouterPersonnage(id,5,3);
    ajouterBrique(false,5,5);


    // -------- 4 murs du contour
    for (int i =0; i< largeurG; i++)
        ajouterBrique(false,i,29);
    for (int i =0; i< largeurG; i++)
        ajouterBrique(false,i,0);
    for (int j =0; j< hauteurG; j++)
        ajouterBrique(false,0,j);
    for (int j =0; j< hauteurG; j++)
        ajouterBrique(false,44,j);
    // -------- fin 4 murs du contour


    for (int k = 1; k<30; k+=5)
        for(int i = 0; i < largeurG; i++)
           ajouterBrique(true,i,k);

    for (int k = 1; k<45; k+=5)
            for(int j = 0; j < hauteurG; j++)
             ajouterBrique(true,k,j);


    for (int j =29; j>= 15; j--)
        ajouterBrique(true,30,j);

    for (int i =30; i< 37; i++)
        ajouterBrique(true,i,14);

    for (int i =30; i< 37; i++)
        ajouterBrique(false,i,15);

    for (int i = 0; i< 2; i++)
        ajouterBrique(false,i,27);
    for (int i = 5; i< 10; i++)
        ajouterBrique(false,i,25);

    int dec = 0;
    for(int j = 23; j>=15; j-=2){
        for (int i =6; i< 16; i++)
            ajouterBrique(false,i+dec,j);
        dec+= 4;
        if(dec >=largeurG)
            dec = 44;



    }
    /*  -------------- fin niveau -------------------- */

    // background = new QPixmap("IMG_8708_blue_Sky2.jpg");
    // scene->setBackgroundBrush(*background);

    timer.start(5, this);

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedWidth(largeur);
    view->setFixedHeight(hauteur);
    view->show();


}


void MainWindow::readyRead(){
    while(socket->canReadLine())
    {

        QString line = QString::fromUtf8(socket->readLine()).trimmed();

        // TODO: REGEX a créer pour l
        //QRegExp messageRegex("^([^:]+):(.*)$");
        QRegExp usersRegex("^/users:(.*)$");
        QRegExp idRegex("^/i:(.*)$");
        QRegExp deplacementRegex("^/p:(.*)$");
        QRegExp bombeRegex("^/bom:(.*)$");
        QRegExp declenchementRegex("^/t:([0-9]+)$");

        if(idRegex.indexIn(line) != -1){
            QStringList mots = idRegex.cap(1).split(" ");
            id = mots[0].toInt();
            qDebug() << "id reçu :" << id;
            qDebug() << "ajout de : "<< id;
            ajouterPersonnage(id,2,3);

            // qDebug()<<" taille = "<<personnages.size();
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
                 *Exemple de code quand ça fonctionnera !
                 *J[0] id joueur
                 *J[1] pos x
                 *J[2] pos y
                 */
//                personnages.resize(users.length());
                foreach(Joueur *j ,personnages){
                    if(j->getId() == J[0].toInt())
                        present = true;
                }
                if(!present){
                    qDebug() << "OKIDOKI ajout de :" << J[0].toInt();
                    ajouterPersonnage(J[0].toInt(),5,3);
                }
            }

        }
        //Bombe posé
        else if(bombeRegex.indexIn(line) != -1){
            QStringList bombe = usersRegex.cap(1).split(" ");
            // bombe[0] id joueur
            // bombe[1] pos X
            // bombe[2] pos Y
            // bombe[3] power des qui aura les bonus
            if (bombe[0].toInt()!= id)
                ajouterBombe(bombe[0].toInt(),bombe[1].toInt(),bombe[2].toInt());


        }
        //Deplacement
        else if(deplacementRegex.indexIn(line) != -1){
            QStringList depl = deplacementRegex.cap(1).split(" ");
            // depl[0].toInt() id joueur
            // depl[1].toInt() pos X
            // depl[2].toInt() pos Y
            // depl[3].toInt() pos X dans sprite
            // depl[4].toInt() pos Y dans sprite
            // depl[5].toInt() pos largeur du sprite
            // depl[6].toInt() pos hauteur du sprite
            // depl[7]  bool orientation gauche
            // depl[8] bool est en vie

            int oldPosX = personnages[depl[0].toInt()]->getX();
            int oldPosY =personnages[depl[0].toInt()]->getY();
            int dx = depl[1].toInt() - oldPosX;
            int dy = depl[2].toInt() - oldPosY;

            //TODO vérifier si depl[7].toInt() peut passer pour un bool
            personnages[depl[0].toInt()]->getPicture()->moveBy(dx,dy);
                        personnages[depl[0].toInt()]->newPosition(depl[1].toInt(),depl[2].toInt());
                        personnages[depl[0].toInt()]->setCoordSprite(depl[3].toInt(),depl[4].toInt(),depl[5].toInt(),depl[6].toInt());
                        personnages[depl[0].toInt()]->setOrientG(depl[7].toInt());
                        personnages[depl[0].toInt()]->refreshPicture();
        }

        else if (declenchementRegex.indexIn(line) != -1){
            QString tri = declenchementRegex.cap(1) ;
            // tri[0] id joueur
            triggerLastBombe(tri.toInt());

        }
    }


}

void MainWindow::connected(){
    socket->write(QString("/me:\n").toUtf8());
}

void MainWindow::ajouterPersonnage(int id,int i, int j){
    int posX = getPositionXFromGrille(i);
    int posY = getPositionYFromGrille(j);
    //personnages.append(new Joueur(id,posX,posY));
    personnages.resize(personnages.size()+1);
    personnages[id]=new Joueur(id,posX,posY);
    scene->addItem(personnages[id]->getPicture());
}

void MainWindow::ajouterBrique(bool cassable, int i, int j)
{
    if(grille[i][j] == NULL){
        int posX = getPositionXFromGrille(i);
        int posY = getPositionYFromGrille(j);

        grille[i][j] = new Brique(cassable,posX,posY);

        scene->addItem(grille[i][j]->getPicture());
    }
}

//mettre id joueur
void MainWindow::ajouterBombe(int bmId,int x, int y)
{
    Bombe *bombe = new Bombe(0,x,y,bmId);
    bombe->setY(bombe->getY() - bombe->getHauteur()/2);
    bombe->setX(bombe->getX() - bombe->getLargeur()/2);
    //bombes.append(bombe);
    personnages[bmId]->addBombe(bombe);
    scene->addItem(bombe->getPicture());
    //TODO ajouter le power au mess
    socket->write(QString("/bom: %1 %2 %3 $\n" ).arg(bombe->getBManId()).arg(bombe->getX()).arg(bombe->getY()).toUtf8());
}

void MainWindow::ajouterExplosion(Bombe *bombe,int x, int y, int dx, int dy,bool end){
    QPixmap sprite = QPixmap("../Game1/ressource/sprites_bomberman.png");
    QTransform transform;

    if(end)
        sprite = sprite.copy(48,591,20,20);
    else
        sprite = sprite.copy(18,591,20,20);


    if (dx == -1)
        sprite = sprite.transformed(transform.rotate( -180,Qt::YAxis ), Qt::FastTransformation);
    else if (dy != 0){
        sprite = sprite.transformed(transform.rotate( dy *90 ), Qt::FastTransformation);
    }


    QGraphicsPixmapItem *picture = new QGraphicsPixmapItem(sprite);
    bombe->addExplosions(picture);
    picture->setPos(x,y);
    scene->addItem(picture);

}

void MainWindow::ajouterBonus(int i, int j){
    int x = getPositionXFromGrille(i);
    int y = getPositionYFromGrille(j);
    grilleBonus[i][j] = new Bonus(x,y);
    scene->addItem(grilleBonus[i][j]->getPicture());
    int t = grilleBonus[i][j]->getBonusType();
    //TODO write bonus (i,j,t)

}

void MainWindow::keyReleaseEvent(QKeyEvent* event) {

    if(!event->isAutoRepeat()){
        controleur->setPressed(event->key(),false);
    }
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

            if(personnages[id]->isColliding(posGrilleI,posGrilleJ,grille)){
                colision  = true;
            }
        }
    }

    return colision;
}

//TODO partie modèle à placer dans Joueur (garder partie graphique)
void MainWindow::tryMove(int x, int y){
    int newX = personnages[id]->getX()+x;
    int newY = personnages[id]->getY()+y;

    if(!collisionTest(x,y)){
        personnages[id]->setX(newX);
        personnages[id]->setY(newY);
        personnages[id]->getPicture()->moveBy(x,y);
        //TODO getOrientG
               // depl[0].toInt() id joueur
               // depl[1].toInt() pos X
               // depl[2].toInt() pos Y
               // depl[3].toInt() pos X dans sprite
               // depl[4].toInt() pos Y dans sprite
               // depl[5].toInt() pos largeur du sprite
               // depl[6].toInt() pos hauteur du sprite
               // depl[7]  bool orientation gauche
               // depl[8] bool est en vie
              // qDebug() << id;
               QVector<int> qv = personnages[id]->getCoordSprite();
              // socket->write(QString("/p: %1 %2 %3 %4 %5 %6 %7 %8 $\n").arg(id).arg(newX).arg(newY).arg(qv.at(0)).arg(qv.at(1)).arg(qv[2]).arg(qv[3]).arg(personnages[id]->isOrientG()).toUtf8());
    }


}
//TODO partie modèle à placer dans Joueur (garder partie graphique)
void MainWindow::tryJump(){
    if(personnages[id]->getBonusJump() == 2 || collisionTest(0,1)){
        gravity = -baseGravity;
        //        personnages[id]->setCurrentS(6);
    }
}

void MainWindow::timerEvent ( QTimerEvent * event ){
    if (personnages.size() >0){
        if(personnages[id]->getCurrentS() == 8){
            personnages[id]->die();
            if(personnages[id]->getCurrentS() == 9)
                scene->removeItem(personnages[id]->getPicture());
        }
        else if(personnages[id]->getCurrentS() != 9){
            personnages[id]->checkImmortality();

            // ----------- partie personnages[id]
            if (gravity<0){
                personnages[id]->setCurrentH(personnages[id]->getCurrentH()+1);
                if(personnages[id]->getCurrentH()>= personnages[id]->getMaxH() || collisionTest(0,-1)){
                    gravity = baseGravity;
                    personnages[id]->setCurrentH(0);
                }
                else{
                    personnages[id]->setCurrentS(6);
                    personnages[id]->immobile();
                }

            }
            else if(collisionTest(0,1)){
                if(gravity == 1)
                    personnages[id]->setCurrentS(4); //LANDING
                gravity = 0;
            }
            else {
                gravity = baseGravity;
                personnages[id]->setCurrentS(3); // FALLING
                personnages[id]->immobile();
            }

            int x = 0;
            if((gravity == 0 || personnages[id]->getBonusJump() == 2) && controleur->getStateKeys(0))
                tryJump();

            if(controleur->getStateKeys(2)){
                if (personnages[id]->tryDropBombe()){
                    ajouterBombe(id,personnages[id]->getX()+personnages[id]->getLargeur()/2,personnages[id]->getY()+ personnages[id]->getHauteur()/2);
                    controleur->setPressed(Qt::Key_Down,false);
                }
            }

            if(controleur->getStateKeys(1)){
                x +=- 1;
                personnages[id]->courireG();
            }
            else if(controleur->getStateKeys(3)){
                x += 1;
                personnages[id]->courireD();
            }

            if(x == 0 && gravity == 0 /*&& personnages[id]->getCurrentS() != 3*/)
                personnages[id]->immobile();

            if(controleur->getStateKeys(4) && personnages[id]->hasBonusTrigger()){
                triggerLastBombe(id);
            }

            tryMove(0,gravity);

            int tired = personnages[id]->getTired();

            if (tired == -1)
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
        // int tmpSizeB = bombes.size();
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
    // à modifier pour gérer les différentes tailles
    return QPoint(i * tailleC , j * tailleC );
}

int MainWindow::getPositionXFromGrille(int i){
    // tailleC car une case = tailleCp,
    // à modifier pour gérer les différentes tailles
    return i * tailleC;
}

int MainWindow::getPositionYFromGrille( int j){
    // tailleC car une case = tailleCp,
    // à modifier pour gérer les différentes tailles

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


void MainWindow::triggerLastBombe(int bmId){
//    int i = bombes.size()-1;
//    while(i >= 0 && bombes[i]->getBManId() != bmId )
//        i--;
//    if (i>=0)
//        bombes[i]->trigger();
   if (personnages[bmId]->getLastBombe() != NULL){
       personnages[bmId]->getLastBombe()->trigger();
       socket->write(QString("/t: %1 $\n").arg(bmId).toUtf8());
   }
}

void MainWindow::explosion(Bombe *bombe, int dx, int dy){
    bool hit = false;

    int x = bombe->getX();
    int y = bombe->getY();

    // point en haut à gauche
    int posGrilleI = getGrilleIFromPosition(x);
    int posGrilleJ = getGrilleJFromPosition(y);

    // point en bas à droite
    int posGrilleI2 = getGrilleIFromPosition(x+bombe->getLargeur());
    int posGrilleJ2 = getGrilleJFromPosition(y+bombe->getHauteur());

    int range = bombe->getPower();
    int i = posGrilleI, j= posGrilleJ;
    int i2 = posGrilleI2, j2 = posGrilleJ2;

    if(dx == 0 && dy == 0){
        if(personnages[id]->isAlive() && hitTest(i,j,i2,j2))
            hit = true;
        ajouterExplosion(bombe,x,y,dx,dy,false);
    }
    else{
        bool end = false;

        i = i +dx;
        j = j +dy;
        i2 = i2 +dx;
        j2 = j2 +dy;
        x += dx * tailleC; // 20 = taille explosion
        y += dy * tailleC;
        while(((grille[i][j] == NULL || grille[i][j]->estCassable()) && ((grille[i2][j2] == NULL || grille[i2][j2]->estCassable() || j2 == hauteurG-1 || i2 == largeurG-1 || j2 == 0 || i2 == 0) ))&& range >0){
            if (range -1 <= 0)
                end = true;
            if(grille[i][j] != NULL && grille[i][j]->estCassable()){
//                scene->removeItem(grille[i][j]->getPicture());
//                grille[i][j] = NULL;
                detruireBrique(i,j);
            }
            if(grille[i2][j2] != NULL && grille[i2][j2]->estCassable()){
//               scene->removeItem(grille[i2][j2]->getPicture());
//               grille[i2][j2] = NULL;
              detruireBrique(i2,j2);
            }
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

    if(hit)
        personnages[id]->hit();

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

            if((posGrilleI == bI && posGrilleJ == bJ) ||(posGrilleI == bI2 && posGrilleJ == bJ2)){
                hit  = true;
            }
        }
    }

    return hit;
}

void MainWindow::detruireBrique(int i, int j){
    scene->removeItem(grille[i][j]->getPicture());
    grille[i][j] = NULL;
    if(id == 0){
        if(qrand()%4 +1 == 1) // une chance sur 4
            ajouterBonus(i,j);
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
            }
        }
    }
}

/* Destructeur de la classe MainWindow */
MainWindow::~MainWindow()
{
    for(int i=0; i<(int) grille.size(); i++)
        for(int j=0; j<(int) grille[i].size(); j++)
            delete grille[i][j];
    for(int i = 0; i < personnages.size(); i++)
     delete personnages[i];
    delete view;
    delete scene;
    // delete background;
}
