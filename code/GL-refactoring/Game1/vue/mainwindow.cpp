#include "mainwindow.h"

/* Constructeur de la classe MainWindow */
MainWindow::MainWindow(QString hote, QWidget * parent) : QMainWindow(parent)
{

	initialiserSocket(hote);

    m_graviteBase = 1;
    m_largeurVueGraphique = 900;
    m_hauteurVueGraphique = 600;
    m_tailleCase = 20;
    m_largeurGrille = m_largeurVueGraphique / m_tailleCase;
    m_hauteurGrille = m_hauteurVueGraphique / m_tailleCase;
    m_gravite = 0;
    m_grilleJeu.resize(m_largeurGrille);
    m_grilleBonus.resize(m_largeurGrille);
    m_controleurClavier = new ToucheClavier();
    m_joueursVect.resize(2);     // nb joueur donné par serveur -> mettre les joueurs dans l'ordre de leur id
    m_finPartie = 0;
	grabKeyboard();

    for(int i = 0; i < m_largeurGrille; i++){
        m_grilleJeu[i].resize(m_hauteurGrille);
        m_grilleBonus[i].resize(m_hauteurGrille);
	}

    m_scene = new QGraphicsScene(0, 0, m_largeurVueGraphique, m_hauteurVueGraphique, this);
    m_vueGraphique = new QGraphicsView(m_scene, this);

    // m_fondEcran = new QPixmap("IMG_8708_blue_Sky2.jpg");
    // m_scene->setBackgroundBrush(*m_fondEcran);

    m_raffraichissement.start(5, this);
    m_vueGraphique->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_vueGraphique->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_vueGraphique->setFixedWidth(m_largeurVueGraphique);
    m_vueGraphique->setFixedHeight(m_hauteurVueGraphique);
    m_vueGraphique->show();

    this->setFixedSize(m_largeurVueGraphique, m_hauteurVueGraphique);
}


void MainWindow::readyRead(){
    while(m_socketClient->canReadLine())
	{

        QString line = QString::fromUtf8(m_socketClient->readLine()).trimmed();

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

            m_joueursVect.resize(mots[1].toInt()); // mots[1] étant le nbre max de joueurs
            m_idJoueur = mots[0].toInt();
			QPair<int,int> pair;

            if(m_entree.size() > m_idJoueur){
                pair = m_entree.at(m_idJoueur);
                ajouterJoueur(m_idJoueur,pair.second,pair.first);
			}
			else
                ajouterJoueur(m_idJoueur, 4, 2);
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


                foreach(Joueur *j ,m_joueursVect){
					if(j != NULL && j->getId() == J[0].toInt())
						present = true;
				}
				if(!present){
                    ajouterJoueur(J[0].toInt(), 5, 3);
				}

			}

		}
		//Bombe posé
		else if(bombeRegex.indexIn(line) != -1){
			QStringList bombe = bombeRegex.cap(1).split(" ");
			// bombe[0] id joueur
			// bombe[1] pos X
			// bombe[2] pos Y
			// bombe[3] si on apelle write ou non
            if (bombe[0].toInt()!= m_idJoueur)
				ajouterBombe(bombe[0].toInt(), bombe[1].toInt(), bombe[2].toInt(), false);


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
			// depl[7]  bool orientation gauche
			// depl[8] bool est en vie
			// depl[9] doit disparaitre
			// depl[10] power bombes
			// depl[11] trigger bombe
			// depl[12] immortel
            int idJoueurDepRegex      (depl[0].toInt()),
                posXJoueurDepRegex    (depl[1].toInt()),
                posYJoueurDepRegex    (depl[2].toInt()),
                posXSpriteDepRegex    (depl[3].toInt()),
                posYSpriteDepRegex    (depl[4].toInt()),
                largeurSpriteDepRegex (depl[5].toInt()),
                hauteurSpriteDepRegex (depl[6].toInt()),
                estOrienteGauche      (depl[7].toInt()),
                estEnVie              (depl[8].toInt()),
                doitDisparaitre       (depl[9].toInt()),
                puissanceBombe        (depl[10].toInt()),
                declencheurBombe      (depl[11].toInt()),
                estImmortel           (depl[12].toInt());



            if(idJoueurDepRegex != m_idJoueur){
                if(!estEnVie && doitDisparaitre)
                {
                    m_scene->removeItem(m_joueursVect[idJoueurDepRegex]->getPicture());
                    m_joueursVect[idJoueurDepRegex]->setCurrentS(9);

                    if(m_joueursVect[idJoueurDepRegex]->hasBonusTrigger()){
                        for(int i = 0; i < m_joueursVect[idJoueurDepRegex]->getVectorBombes().size(); i++)
                            m_joueursVect[idJoueurDepRegex]->getVectorBombes()[i]->startCountDown();
					}

                }else
                {

                    int oldPosX = m_joueursVect[idJoueurDepRegex]->getX();
                    int oldPosY =m_joueursVect[idJoueurDepRegex]->getY();
                    int dx = posXJoueurDepRegex - oldPosX;
                    int dy = posYJoueurDepRegex - oldPosY;


                    m_joueursVect[idJoueurDepRegex]->getPicture()->moveBy(dx,dy);
                    m_joueursVect[idJoueurDepRegex]->setImmortality(estImmortel);
                    m_joueursVect[idJoueurDepRegex]->setX(posXJoueurDepRegex);
                    m_joueursVect[idJoueurDepRegex]->setY(posYJoueurDepRegex);
                    m_joueursVect[idJoueurDepRegex]->setCoordSprite(posXSpriteDepRegex,
                                                                  posYSpriteDepRegex,
                                                                  largeurSpriteDepRegex,
                                                                  hauteurSpriteDepRegex);
                    m_joueursVect[idJoueurDepRegex]->setOrientG(estOrienteGauche);
                    m_joueursVect[idJoueurDepRegex]->refreshPicture();
                    m_joueursVect[idJoueurDepRegex]->setPowerBomb(puissanceBombe);
                    m_joueursVect[idJoueurDepRegex]->setTriggerBomb(declencheurBombe);
				}
			}
		}
        else if (declenchementRegex.indexIn(line) != -1)
        {
			QStringList tri = declenchementRegex.cap(1).split(" ");
            if(tri[0].toInt() != m_idJoueur)
            {
				triggerLastBombe(tri[0].toInt(),false);
			}

        }else if(addBonusRegex.indexIn(line) != -1)
        {
			QStringList abon = addBonusRegex.cap(1).split(" ");
            if(abon[0].toInt() != m_idJoueur)
            {
				ajouterBonus(abon[1].toInt(),abon[2].toInt(),false,abon[3].toInt());
			}
		}
        else if(removeBonusRegex.indexIn(line) != -1)
        {
			QStringList rbon = removeBonusRegex.cap(1).split(" ");
            if(rbon[0].toInt() != m_idJoueur)
            {
                m_scene->removeItem(m_grilleBonus[rbon[1].toInt()][rbon[2].toInt()]->getPicture());
                m_grilleBonus[rbon[1].toInt()][rbon[2].toInt()] = NULL;
			}
		}
        else if(killsRegex.indexIn(line) != -1)
        {
			QStringList kills = killsRegex.cap(1).split(" ");
            if(kills[0].toInt() != m_idJoueur)
            {
                m_joueursVect[kills[0].toInt()]->setKillBy(kills[1].toInt());
                m_joueursVect[kills[1].toInt()]->incrNbKills();
			}
		}
        else if (erreurRegex.indexIn(line) != -1)
        {
			QStringList erreurs = erreurRegex.cap(1).split(" ");
			qCritical() << erreurs[0];
			close();
		}
	}


}


void MainWindow::chargerNiveau(QString niveau){

	QString fileName = "../Game1/ressource/Niveaux/Niv" + niveau + ".level";
	QFile fichier(fileName);
	fichier.open(QIODevice::ReadOnly | 
				 QIODevice::Text);
	QTextStream flux(&fichier);
	QString ligne;
	int i = -1;
	while(!flux.atEnd())
	{
		ligne = flux.readLine();
		i++;
		QStringList colonne = ligne.split(" ");
		QPair<int,int> pair;
        for(int j(0); j < colonne.size(); j++)
		{
			switch(colonne[j].toInt())
			{

			case 1 :
				ajouterBrique(false,j,i);
				break;

			case 2:
				ajouterBrique(true,j,i);
				break;

			case 3:
				pair.first = i;
				pair.second = j;
                m_entree.push_back(pair);
				break;

			default:
				break;
			}
		}
	}
}

void MainWindow::connected(){
    m_socketClient->write(QString("/me:\n").toUtf8());
}

void MainWindow::disconnected(){
    qDebug() <<"DECO !";
}

void MainWindow::ajouterJoueur(int idJoueur, int i, int j){
	int posX = getPositionXFromGrille(i);
	int posY = getPositionYFromGrille(j);
    m_joueursVect[idJoueur] = new Joueur(idJoueur, posX, posY);
    m_scene->addItem(m_joueursVect[idJoueur]->getPicture());
}

void MainWindow::ajouterBrique(bool cassable, int i, int j)
{
    if(m_grilleJeu[i][j] == NULL){
		int posX = getPositionXFromGrille(i);
		int posY = getPositionYFromGrille(j);

        m_grilleJeu[i][j] = new Brique(cassable,posX,posY);

        m_scene->addItem(m_grilleJeu[i][j]->getPicture());
	}
}


void MainWindow::ajouterBombe(int bmId,int x, int y, bool w)
{

	Bombe *bombe = new Bombe(0,x,y,bmId);
	if(w)
	{
		bombe->setY(bombe->getY() - bombe->getHauteur()/2);
		bombe->setX(bombe->getX() - bombe->getLargeur()/2);
	}else
	{
		bombe->setX(x);
		bombe->setY(y);
	}
    m_joueursVect[bmId]->addBombe(bombe);
    m_scene->addItem(bombe->getPicture());

	if(w)
	{
        m_socketClient->write(QString("/bom:%1 %2 %3 $\n" ).arg(bombe->getBManId()).arg(bombe->getX()).arg(bombe->getY()).toUtf8());
	}

}

void MainWindow::ajouterExplosion(Bombe *bombe,int x, int y, int dx, int dy, bool end){
	QPixmap sprite = QPixmap("../Game1/ressource/sprites_bomberman.png");
	QTransform transform;

    if (end)
		sprite = sprite.copy(48, 591, 20, 20);
	else
		sprite = sprite.copy(18, 591, 20, 20);

	if (dx == -1)
		sprite = sprite.transformed(transform.rotate( -180,Qt::YAxis ), Qt::FastTransformation);
    else if (dy != 0)
    {
		sprite = sprite.transformed(transform.rotate( dy *90 ), Qt::FastTransformation);
	}


	QGraphicsPixmapItem *picture = new QGraphicsPixmapItem(sprite);
	bombe->addExplosions(picture);
	picture->setPos(x,y);
    m_scene->addItem(picture);

}

void MainWindow::ajouterBonus(int i, int j, bool w, int t){
	int x = getPositionXFromGrille(i);
	int y = getPositionYFromGrille(j);
    m_grilleBonus[i][j] = new Bonus(x,y,t);
    m_scene->addItem(m_grilleBonus[i][j]->getPicture());

	if(w)
        m_socketClient->write(QString("/abon:%1 %2 %3 %4 $\n" ).arg(m_idJoueur).arg(i).arg(j).arg(m_grilleBonus[i][j]->getBonusType()).toUtf8());


}

void MainWindow::keyReleaseEvent(QKeyEvent* event) {

	if(!event->isAutoRepeat()){
        m_controleurClavier->setPressed(event->key(),false);
	}
}

void MainWindow::keyPressEvent(QKeyEvent* event) {

	if(!event->isAutoRepeat())
        m_controleurClavier->setPressed(event->key(),true);
}

bool MainWindow::collisionTest(int x, int y){
    int hauteurP = m_joueursVect[m_idJoueur]->getHauteur(), largeurP = m_joueursVect[m_idJoueur]->getLargeur();
    int newX = m_joueursVect[m_idJoueur]->getX() + x;
    int newY = m_joueursVect[m_idJoueur]->getY() + y;
    bool colision = false;

    // nombre de points du m_joueursVect[m_idJoueur] espacés de m_tailleCase px
    int nbPointX = 1 + largeurP / m_tailleCase;
    if (largeurP % m_tailleCase != 0)
		nbPointX++;
    int nbPointY = 1 + hauteurP / m_tailleCase;
    if (hauteurP % m_tailleCase != 0)
		nbPointY++;

	int posGrilleI;
	int posGrilleJ;

    // on regarde dans quelle partie de la grille se trouve chaque points espacés de taille Cpx du m_joueursVect[m_idJoueur]
	for (int i = 0; i< nbPointX; i++){
        if(i * m_tailleCase > largeurP)
			posGrilleI = getGrilleIFromPosition(newX + largeurP);
		else
            posGrilleI = getGrilleIFromPosition(newX + i * m_tailleCase);

		for (int j = 0; j< nbPointY; j++){
            if(j * m_tailleCase > hauteurP)
				posGrilleJ = getGrilleJFromPosition(newY + hauteurP);
			else
                posGrilleJ = getGrilleJFromPosition(newY + j * m_tailleCase);

            if(m_joueursVect[m_idJoueur]->isColliding(posGrilleI,posGrilleJ,m_grilleJeu)){
				colision  = true;
			}
		}
	}

	return colision;
}


void MainWindow::tryMove(int x, int y){
    int newX = m_joueursVect[m_idJoueur]->getX() + x,
        newY = m_joueursVect[m_idJoueur]->getY() + y;

	if(!collisionTest(x,y)){
        m_joueursVect[m_idJoueur]->setX(newX);
        m_joueursVect[m_idJoueur]->setY(newY);
        m_joueursVect[m_idJoueur]->getPicture()->moveBy(x,y);
		// depl[0].toInt() id joueur
		// depl[1].toInt() pos X
		// depl[2].toInt() pos Y
		// depl[3].toInt() pos X dans sprite
		// depl[4].toInt() pos Y dans sprite
		// depl[5].toInt() pos largeur du sprite
		// depl[6].toInt() pos hauteur du sprite
		// depl[7]  bool orientation gauche
		// depl[8] bool est en vie


        QVector<int> qv = m_joueursVect[m_idJoueur]->getCoordSprite();
        m_socketClient->write(QString("/p:%1 %2 %3 %4 %5 %6 %7 %8 %9 %10 %11 %12 %13 $\n")
            .arg(m_idJoueur).arg(newX).arg(newY)
			.arg(qv.at(0)).arg(qv.at(1)).arg(qv[2]).arg(qv[3])
            .arg(m_joueursVect[m_idJoueur]->isOrientG())
            .arg(m_joueursVect[m_idJoueur]->isAlive())
			.arg(0)
            .arg(m_joueursVect[m_idJoueur]->getPowerBomb())
            .arg(m_joueursVect[m_idJoueur]->hasBonusTrigger())
            .arg(m_joueursVect[m_idJoueur]->isImmortal())
			.toUtf8());
	}


}

void MainWindow::tryJump(){
    if(m_joueursVect[m_idJoueur]->getBonusJump() == 2 || collisionTest(0,1)){
        m_gravite = -m_graviteBase;
	}
}

void MainWindow::timerEvent ( QTimerEvent * event ){
	int cptDead = 0;
	bool start = true;
    for(int i = 0; i < m_joueursVect.size(); i++){
        if(m_joueursVect[i] == NULL)
			start = false;
	}
    if (start)
    {
        if (m_finPartie == 0)
        {
            for (int i = 0; i < m_joueursVect.size(); i++){
                if (m_joueursVect[i]->getCurrentS() == 9)
					cptDead ++;
                if (cptDead >= m_joueursVect.size()-1){
                    m_finPartie = 1;
                }
			}
		}
        else if (m_finPartie > 0)
        {
            if (m_finPartie == 1)
				displayEndScreen();
            else if (m_finPartie == 2 && m_joueursVect[m_idJoueur]->isAlive()){
                m_joueursVect[m_idJoueur]->cheer();
                QVector<int> qv = m_joueursVect[m_idJoueur]->getCoordSprite();
                m_socketClient->write(QString("/p:%1 %2 %3 %4 %5 %6 %7 %8 %9 %10 %11 %12 %13 $\n")
                    .arg(m_idJoueur).arg(m_joueursVect[m_idJoueur]->getX()).arg(m_joueursVect[m_idJoueur]->getY())
					.arg(qv.at(0)).arg(qv.at(1)).arg(qv[2]).arg(qv[3])
                    .arg(m_joueursVect[m_idJoueur]->isOrientG())
                    .arg(m_joueursVect[m_idJoueur]->isAlive())
					.arg(0)
                    .arg(m_joueursVect[m_idJoueur]->getPowerBomb())
                    .arg(m_joueursVect[m_idJoueur]->hasBonusTrigger())
                    .arg(m_joueursVect[m_idJoueur]->isImmortal())
					.toUtf8());
			}
		}
        if(m_joueursVect[m_idJoueur]->getCurrentS() == 8)
        {
            m_joueursVect[m_idJoueur]->die();
            QVector<int> qv = m_joueursVect[m_idJoueur]->getCoordSprite();
            m_socketClient->write(QString("/p:%1 %2 %3 %4 %5 %6 %7 %8 %9 %10 %11 %12 %13 $\n").arg(m_idJoueur).arg(m_joueursVect[m_idJoueur]->getX()).arg(m_joueursVect[m_idJoueur]->getY())
				.arg(qv.at(0)).arg(qv.at(1)).arg(qv[2]).arg(qv[3])
                .arg(m_joueursVect[m_idJoueur]->isOrientG())
                .arg(m_joueursVect[m_idJoueur]->isAlive())
				.arg(0)
                .arg(m_joueursVect[m_idJoueur]->hasBonusTrigger())
                .arg(m_joueursVect[m_idJoueur]->isImmortal())
				.toUtf8());

            if(m_joueursVect[m_idJoueur]->getCurrentS() == 9)
            {

                if(m_joueursVect[m_idJoueur]->hasBonusTrigger())
                {
                    for(int i = 0; i < m_joueursVect[m_idJoueur]->getVectorBombes().size(); i++)
                        m_joueursVect[m_idJoueur]->getVectorBombes()[i]->startCountDown();
				}

                m_scene->removeItem(m_joueursVect[m_idJoueur]->getPicture());
                m_socketClient->write(QString("/p:%1 %2 %3 %4 %5 %6 %7 %8 %9 %10 %11 %12 %13 $\n").arg(m_idJoueur).arg(m_joueursVect[m_idJoueur]->getX()).arg(m_joueursVect[m_idJoueur]->getY())
					.arg(qv.at(0)).arg(qv.at(1)).arg(qv[2]).arg(qv[3])
                    .arg(m_joueursVect[m_idJoueur]->isOrientG())
                    .arg(m_joueursVect[m_idJoueur]->isAlive())
					.arg(1)
                    .arg(m_joueursVect[m_idJoueur]->hasBonusTrigger())
                    .arg(m_joueursVect[m_idJoueur]->isImmortal())
					.toUtf8());
			}
		}
        else if(m_joueursVect[m_idJoueur]->getCurrentS() != 9){
            m_joueursVect[m_idJoueur]->checkImmortality();

            // ----------- partie m_joueursVect[m_idJoueur]
            if (m_gravite < 0)
            {
                m_joueursVect[m_idJoueur]->setCurrentH(m_joueursVect[m_idJoueur]->getCurrentH()+1);
                if(m_joueursVect[m_idJoueur]->getCurrentH()>= m_joueursVect[m_idJoueur]->getMaxH() || collisionTest(0,-1))
                {
                    m_gravite = m_graviteBase;
                    m_joueursVect[m_idJoueur]->setCurrentH(0);
				}
                else
                {
                    m_joueursVect[m_idJoueur]->setCurrentS(6);
                    m_joueursVect[m_idJoueur]->immobile();
				}

			}
            else if(collisionTest(0,1))
            {
                if(m_gravite == 1)
                    m_joueursVect[m_idJoueur]->setCurrentS(4); //LANDING
                m_gravite = 0;
			}
			else {
                m_gravite = m_graviteBase;
                m_joueursVect[m_idJoueur]->setCurrentS(3); // FALLING
                m_joueursVect[m_idJoueur]->immobile();
			}

			int x = 0;
            if(
               (
                 m_gravite == 0 ||
                 m_joueursVect[m_idJoueur]->getBonusJump() == 2
                ) &&
                m_controleurClavier->getStateKeys(0)
               )
            {
                tryJump();
            }

            if(m_controleurClavier->getStateKeys(2))
            {
                if (m_joueursVect[m_idJoueur]->tryDropBombe())
                {
                    ajouterBombe(m_idJoueur,
                                 m_joueursVect[m_idJoueur]->getX() + m_joueursVect[m_idJoueur]->getLargeur() / 2,
                                 m_joueursVect[m_idJoueur]->getY() + m_joueursVect[m_idJoueur]->getHauteur() / 2,
                                 true);
                    m_controleurClavier->setPressed(Qt::Key_Down,false);
				}
			}

            if(m_controleurClavier->getStateKeys(1)){
				x +=- 1;
                m_joueursVect[m_idJoueur]->courireG();
			}
            else if(m_controleurClavier->getStateKeys(3)){
				x += 1;
                m_joueursVect[m_idJoueur]->courireD();
			}

            if(x == 0 && m_gravite == 0 )
                m_joueursVect[m_idJoueur]->immobile();

            if(m_controleurClavier->getStateKeys(4) && m_joueursVect[m_idJoueur]->hasBonusTrigger()){
                triggerLastBombe(m_idJoueur, true);
                m_controleurClavier->setPressed(Qt::Key_Space, false);
			}

            tryMove(0,m_gravite);

            int tired = m_joueursVect[m_idJoueur]->getTired();

			if (tired == -1)
                tryMove(x, 0);
			else if(tired == 0)
                m_joueursVect[m_idJoueur]->setTired(1); // baseTired ?
			else{
                tryMove(x, 0);
                m_joueursVect[m_idJoueur]->setTired(tired-1);
			}

			checkBonus();
		}


		// ----------- partie bombes
        for (int idJ(0); idJ < m_joueursVect.size(); idJ++)
        {
            for(int i(0); i < m_joueursVect[idJ]->getVectorBombes().size(); i++)
            {
                if(m_joueursVect[idJ]->getVectorBombes()[i]->isExploding())
                {
                    explosion(m_joueursVect[idJ]->getVectorBombes()[i], 0, 0);
                    explosion(m_joueursVect[idJ]->getVectorBombes()[i], 0, 1);
                    explosion(m_joueursVect[idJ]->getVectorBombes()[i], 0,-1);
                    explosion(m_joueursVect[idJ]->getVectorBombes()[i], 1, 0);
                    explosion(m_joueursVect[idJ]->getVectorBombes()[i],-1, 0);
				}
                if(m_joueursVect[idJ]->getVectorBombes()[i]->hasExploded())
                {
                    for(int j(0); j < m_joueursVect[idJ]->getVectorBombes()[i]->getExplosions().size(); j++)
                        m_scene->removeItem(m_joueursVect[idJ]->getVectorBombes()[i]->getExplosions().at(j));
                    m_scene->removeItem((m_joueursVect[idJ]->getVectorBombes()[i])->getPicture());
                    if (m_joueursVect[idJ]->getVectorBombes()[i]->getBManId() == m_joueursVect[idJ]->getId())
                    {
                        m_joueursVect[idJ]->decrNbBombe();
                        m_joueursVect[idJ]->removeBombe(i);
					}
				}
			}
		}
	}
}

QPoint MainWindow::getPositionFromGrille(int i, int j) const{
    // m_tailleCase car une case = tailleCp,

    return QPoint(i * m_tailleCase , j * m_tailleCase );
}

int MainWindow::getPositionXFromGrille(int i) const{
    // m_tailleCase car une case = tailleCp,
    return i * m_tailleCase;
}

int MainWindow::getPositionYFromGrille(int j)const{
    // m_tailleCase car une case = tailleCp,
    return j * m_tailleCase;
}

int MainWindow::getGrilleIFromPosition(int x) const{
    return x / m_tailleCase;
}

int MainWindow::getGrilleJFromPosition(int y) const{
    return  y / m_tailleCase;
}

void MainWindow::toggleGravity(){
    m_gravite = -m_gravite;
}

int MainWindow::getGravity() const{
    return m_gravite;
}


void MainWindow::triggerLastBombe(int bmId, bool w){
    if (m_joueursVect[bmId]->getLastBombe() != NULL){
        m_joueursVect[bmId]->getLastBombe()->trigger();
		if (w)
            m_socketClient->write(QString("/t:%1 $\n").arg(bmId).toUtf8());


	}
}

void MainWindow::explosion(Bombe *bombe, int dx, int dy){
	bool hit = false;

	int x (bombe->getX()),
		y (bombe->getY()),
	// point en haut à gauche
		posGrilleI (getGrilleIFromPosition(x)),
		posGrilleJ (getGrilleJFromPosition(y)),
	// point en bas à droite
        posGrilleI2 (getGrilleIFromPosition(x + bombe->getLargeur())),
        posGrilleJ2 (getGrilleJFromPosition(y + bombe->getHauteur())),
        porteeBombe (bombe->getPower()),
        i  (posGrilleI),
        j  (posGrilleJ),
        i2 (posGrilleI2),
        j2 (posGrilleJ2);

	if(
		dx == 0 &&
	    dy == 0
	  )
	{
		if(
            m_joueursVect[m_idJoueur]->isAlive() &&
		    hitTest(i, j, i2, j2)
		   )
		{
			hit = true;
		}
		ajouterExplosion(bombe,x,y,dx,dy,false);
	}
	else
	{
		bool end (false);

		i = i + dx;
		j = j + dy;
		i2 = i2 + dx;
		j2 = j2 + dy;
        x += dx * m_tailleCase; // 20 = taille explosion
        y += dy * m_tailleCase;
		while(
			  (
			    ( 
                  m_grilleJeu[i][j] == NULL			||
                  m_grilleJeu[i][j]->estCassable()
				)
				  &&
			    ( 
                  m_grilleJeu[i2][j2] == NULL		||
                  m_grilleJeu[i2][j2]->estCassable() ||
                  j2 == m_hauteurGrille-1				||
                  i2 == m_largeurGrille-1				||
			      j2 == 0						||
			      i2 == 0
				)
			  ) 
			  &&
			   porteeBombe > 0
			)
		{
			if (porteeBombe -1 <= 0)
				end = true;
			if(
               m_grilleJeu[i][j] != NULL &&
               m_grilleJeu[i][j]->estCassable()
			  )
			{
				detruireBrique(i, j, bombe->getBManId());
			}
			if(
               m_grilleJeu[i2][j2] != NULL &&
               m_grilleJeu[i2][j2]->estCassable()
			  )
			{
				detruireBrique(i2, j2, bombe->getBManId());
			}
			

			if(
               m_joueursVect[m_idJoueur]->isAlive() &&
			   hitTest(i,j,i2,j2)
			  )
			{
				hit = true;
			}
			

			ajouterExplosion(bombe,x,y,dx,dy,end);

			i = i +dx;
			j = j +dy;
			i2 = i2 +dx;
			j2 = j2 +dy;
            x += dx * m_tailleCase; // 20 = taille explosion
            y += dy * m_tailleCase;

			// garde fou, tout les test sont faux normalement
			if (j < 0)
				j = 0;

			if (i < 0)
				i = 0;

            if (j > m_hauteurGrille)
                j = m_hauteurGrille;

            if (i > m_largeurGrille)
                i = m_largeurGrille;

			if (j2 < 0)
				j2 = 0;

			if (i2 < 0)
				i2 = 0;

            if (j2 > m_hauteurGrille)
                j2 = m_hauteurGrille;

            if (i2 > m_largeurGrille)
                i2 = m_largeurGrille;

			porteeBombe --;
		}
	}
	if(hit)
	{
        m_joueursVect[m_idJoueur]->hit();
        if(! m_joueursVect[m_idJoueur]->isAlive()) // Si le personnage n'est pas en vie
		{
            m_joueursVect[m_idJoueur]->setKillBy(bombe->getBManId());
            m_joueursVect[bombe->getBManId()]->incrNbKills();
            m_socketClient->write(QString("/k:%1 %2 $\n").arg(m_idJoueur).arg(bombe->getBManId()).toUtf8());
		}
	}
}



bool MainWindow::hitTest(int bI, int bJ, int bI2, int bJ2){
    int hauteurP = m_joueursVect[m_idJoueur]->getHauteur(), largeurP = m_joueursVect[m_idJoueur]->getLargeur()/*-1*/;
	int posGrilleI;
	int posGrilleJ;
	bool estTouche (false);

    // nombre de points du m_joueursVect[m_idJoueur] espacés de m_tailleCase px
    int nbPointX = 1 + largeurP / m_tailleCase;
    if (largeurP % m_tailleCase != 0)
		nbPointX++;
    int nbPointY = 1 + hauteurP / m_tailleCase;
    if (hauteurP % m_tailleCase != 0)
		nbPointY++;



    // on regarde dans quelle partie de la grille se trouve chaque points espacés de taille Cpx du m_joueursVect[m_idJoueur]
	for (int i(0); i < nbPointX; i++){
        if(i * m_tailleCase > largeurP)
            posGrilleI = getGrilleIFromPosition(m_joueursVect[m_idJoueur]->getX() + largeurP);
		else
            posGrilleI = getGrilleIFromPosition(m_joueursVect[m_idJoueur]->getX() + i * m_tailleCase);

		for (int j = 0; j < nbPointY; j++){
            if(j * m_tailleCase > hauteurP)
                posGrilleJ = getGrilleJFromPosition(m_joueursVect[m_idJoueur]->getY() + hauteurP);
			else
                posGrilleJ = getGrilleJFromPosition(m_joueursVect[m_idJoueur]->getY() + j * m_tailleCase);

			if( 
				(posGrilleI == bI  && posGrilleJ == bJ) ||
				(posGrilleI == bI2 && posGrilleJ == bJ2) 
			  )
			{
				estTouche  = true;
			}
		}
	}

	return estTouche;
}

void MainWindow::detruireBrique(int i, int j, int idJ){
    m_scene->removeItem(m_grilleJeu[i][j]->getPicture());
    m_grilleJeu[i][j] = NULL;
    if(m_idJoueur == idJ){
		if((qrand() % 4) + 1 == 1) // une chance sur 4
			ajouterBonus(i, j, true, -1);
	}

}

void MainWindow::checkBonus(){
    int hauteurP (m_joueursVect[m_idJoueur]->getHauteur()),
        largeurP (m_joueursVect[m_idJoueur]->getLargeur()),
        x		 (m_joueursVect[m_idJoueur]->getX()),
        y		 (m_joueursVect[m_idJoueur]->getY());

    // nombre de points du m_joueursVect[m_idJoueur] espacés de m_tailleCase px
    int nbPointX = 1 + largeurP / m_tailleCase;
    if (largeurP % m_tailleCase != 0)
		nbPointX++;
    int nbPointY = 1 + hauteurP / m_tailleCase;
    if (hauteurP % m_tailleCase != 0)
		nbPointY++;

	int posGrilleI;
	int posGrilleJ;

    // on regarde dans quelle partie de la grille se trouve chaque points espacés de taille Cpx du m_joueursVect[m_idJoueur]
	for (int i (0); i < nbPointX; i++){
        if(i * m_tailleCase > largeurP)
			posGrilleI = getGrilleIFromPosition(x + largeurP);
		else
            posGrilleI = getGrilleIFromPosition(x + i * m_tailleCase);

		for (int j(0); j < nbPointY; j++){
            if(j * m_tailleCase > hauteurP)
				posGrilleJ = getGrilleJFromPosition(y + hauteurP);
			else
                posGrilleJ = getGrilleJFromPosition(y + j * m_tailleCase);

            if(m_grilleBonus[posGrilleI][posGrilleJ] != NULL)
			{
                m_joueursVect[m_idJoueur]->receiveBonus(m_grilleBonus[posGrilleI][posGrilleJ]->getBonusType());
                m_scene->removeItem(m_grilleBonus[posGrilleI][posGrilleJ]->getPicture());
                m_grilleBonus[posGrilleI][posGrilleJ] = NULL;

                m_socketClient->write(QString("/rbon:%1 %2 %3 $\n").arg(m_idJoueur).arg(posGrilleI).arg(posGrilleJ).toUtf8());
			}
		}
	}
}

QString MainWindow::getHote () const
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
    m_socketClient = new QTcpSocket(this);
    m_socketClient->connectToHost(m_hote, 4200);
    connect(m_socketClient, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(m_socketClient, SIGNAL(connected()), this, SLOT(connected()));
    if(m_socketClient->waitForConnected() > 5){
        m_socketClient->close();
        exit(1);
    }
}


void MainWindow::displayEndScreen(){
	int decH(0);
	QGraphicsTextItem * endText = new QGraphicsTextItem;
	QFont myFont = QFont("Time", 45);
	myFont.setBold(true);
	endText->setFont(myFont);
	endText->setTextWidth(900);

    if(m_joueursVect[m_idJoueur]->isAlive())
    {
		endText->setPlainText("Victoire");
		decH = 7*22;
		endText->setDefaultTextColor(Qt::green);
	}
    else
    {
		endText->setPlainText("Défaite");
		decH = 6*22;
		endText->setDefaultTextColor(Qt::red);
	}

    endText->setPos(m_largeurVueGraphique / 2 - decH, 0);
	endText->setZValue(99);
    m_scene->addItem(endText);
    m_finPartie = 2;


	setStyleSheet("QTableWidget {background-color: rgba(0, 0, 0,150); }"
		"QTableWidget {gridline-color: white; }"
		"QTableWidget {color: white; }"
		"QTableCornerButton::section {background-color: rgba(0, 0, 0,150); }"
		"QHeaderView::section {background-color:rgba(0, 0, 0,150); }"
		"QHeaderView::section {color:white; }"
		"QHeaderView::section {gridline-color:white ; }"
		"QHeaderView {background-color: rgba(0, 0, 0,150); }"
		"QHeaderView {color: white; }"
		);

    QTableWidget *score = new QTableWidget(m_joueursVect.size(), 2, this);
    score->hide();
    score->setGeometry(m_largeurVueGraphique / 2 - 65, m_hauteurVueGraphique / 2 - 90, 131, 180);
	score->setHorizontalHeaderItem(0, new QTableWidgetItem("Tués"));
	score->setHorizontalHeaderItem(1, new QTableWidgetItem("Tué par"));
	score->resizeColumnsToContents();
	score->resizeRowsToContents();

    for (int i(0); i < m_joueursVect.size(); i++)
	{
        score->setVerticalHeaderItem(i, new QTableWidgetItem(QString("J%1").arg(m_joueursVect[i]->getId() + 1)));

		QTableWidgetItem *item = new QTableWidgetItem();
		score->setItem(i, 0, item);
        item->setText(QString("%1").arg(m_joueursVect[i]->getNbKills()));

		QTableWidgetItem *item2 = new QTableWidgetItem();
		score->setItem(i, 1, item2);
        if (m_joueursVect[i]->getKillBy() != -1)
            item2->setText(QString("J%1").arg(m_joueursVect[i]->getKillBy() + 1));
	}
	score->show();
}

/* Destructeur de la classe MainWindow */
MainWindow::~MainWindow()
{
    for (int i(0); i < (int) m_grilleJeu.size(); i++)
        for(int j(0); j < (int) m_grilleJeu[i].size(); j++)
        {
            delete m_grilleJeu[i][j];
            m_grilleJeu[i][j] = 0;
        }
    for (int i(0); i < m_joueursVect.size(); i++)
    {
        delete m_joueursVect[i];
        m_joueursVect[i] = 0;
    }
    delete m_vueGraphique;
    delete m_scene;
    m_vueGraphique = 0;
    m_scene = 0;
}


