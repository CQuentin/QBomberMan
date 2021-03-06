#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QWidget>
#include <QKeyEvent>
#include <QTimerEvent>
#include <QDebug>
#include <QVector>
#include <QBasicTimer>
#include <QTcpSocket>
#include <QTableWidget>
#include <QTableWidgetItem>
#include "../modele/brique.h"
#include "../modele/bonus.h"
#include "../modele/joueur.h"
#include "../controleur/toucheclavier.h"


class MainWindow : public QMainWindow
{
	Q_OBJECT

private:
	QString m_hote;
    QGraphicsScene * m_scene;
    QGraphicsView * m_vueGraphique;
    // QPixmap * m_fondEcran; // non utilisé
    QVector<Joueur*> m_joueursVect;
    QVector<QVector<Brique*> > m_grilleJeu;
    QVector<QVector<Bonus* > > m_grilleBonus;
    QVector<QPair<int,int  > > m_entree;
    int m_largeurVueGraphique;
    int m_hauteurVueGraphique;
    int m_largeurGrille;
    int m_hauteurGrille;
    int m_tailleCase;
    int m_gravite;
    int m_graviteBase;
    int m_idJoueur;
    int m_finPartie;
    QBasicTimer m_raffraichissement;
    QTcpSocket *m_socketClient;
    ToucheClavier *m_controleurClavier;

	private slots:
		void readyRead();
		void connected();
        void disconnected();

public:
	/*!
	* \brief Constructeur
	*
	* Constructeur de la classe MainWindow
	*
	* \param parent : QMainWindow parent
	* \author Quentin CHEYNET
	*/
	explicit MainWindow(QString hote, QWidget * parent = 0);

	/*!
	* \brief Fonction de Création du niveau
	* \param niveau : niveau à charger
	* \author Jérémy Vaz Borges
	*/
	void chargerNiveau(QString niveau);

	/*!
    * \brief détection des évènement clavier (touches enfoncées)
	* \param event
	* \author Quentin CHEYNET
	*/
	void keyPressEvent(QKeyEvent* event);

	/*!
	* \brief détéction des évènement clavier (touches relachées)
	* \param event
	* \author Quentin CHEYNET
	*/
	void keyReleaseEvent(QKeyEvent* event);

	/*!
	* \brief timerEvent
	* \param event
	* \author Quentin CHEYNET
	*/
	void timerEvent ( QTimerEvent * event );

	/*!
	* \brief ajoute une brique dans la vue
	*
	* Une instance de Brique est créée. Elle est ajoutée dans
    * l'attribut m_grilleJeu, puis elle est affichée dans la scène
	*
	* \param cassable Décide si la nouvelle brique est cassable ou non
    * \param i Colonne de la grille
	* \param j Ligne de la grille
	* \author Quentin CHEYNET
	*/
	void ajouterBrique(bool cassable, int i, int j);

	/*!
	* \brief ajoute un personnage dans la vue
	*
	* Une instance de Joueur est créée, puis elle est affichée dans la scène
    * \param idJoueur Identifiant du joueur
	* \param i Colonne de la grille
	* \param j Ligne de la grille
	* \author Quentin CHEYNET
	*/
    void ajouterJoueur(int idJoueur, int i, int j);

	/*!
	* \brief ajoute une bombe dans la vue
	*
	* Une instance de Bombe est créée, puis elle est affichée dans la scène
	* \param bmId Identifiant du joueur qui a posé la bombe
	* \param i Colonne de la grille
	* \param j Ligne de la grille
	* \param w Si la bombe doit être envoyé
	* \author Quentin CHEYNET
	*/
	void ajouterBombe(int bmId, int x, int y, bool w);


	/*!
	* \brief ajoute une explosion dans la vue
	* L'image d'une explosion est ajoutée
	* \param bombe La bombe à laquelle appatiennent les explosions
    * \param x Abscisse de l'image dans m_scene
    * \param Y Ordonnée de l'image dans m_scene
	* \param dx direction horizontal de l'explosion
	* \param dy direction vertical de l'explosion
	* \param end Si l'image doit être la fin de l'explosion
	* \author Quentin CHEYNET
	*/
	void ajouterExplosion(Bombe *bombe, int x, int y, int dx, int dy, bool end);

	/*!
	* \brief renvoie la position en pixel d'un objet dans la scene
	*
	* Un objet (Joueur, Brique, Bombe, Explosion) est représenté
    * dans m_grilleJeu (QVector deux dimmensions), mais son image (attribut picture )
	* doit s'afficher dans la scene, avec une position exprimé en pixel.
	* La fonction calcule x et y à partir des indices i et j, et renvoie
	* un QPoint (x,y).
	*
	* \param i Colonne de la grille
	* \param j Ligne de la grille
	* \return Un QPoint, correspondant à la position dans la scène
	* \author Quentin CHEYNET
	*/
    QPoint getPositionFromGrille(int i, int j) const;

	/*!
	* \brief renvoie l'abscisse en pixel d'un objet dans la scene
	*
	* Un objet (Joueur, Brique, Bombe, Explosion) est représenté
    * dans m_grilleJeu (QVector deux dimmensions), mais son image (attribut picture )
	* doit s'afficher dans la scene, avec une position exprimé en pixel.
	* La fonction calcule x à partir de l' indice i et renvoie x
	*
	* \param i Colonne de la grille
	* \return x, correspondant à l'abscisse dans la scène
	* \author Quentin CHEYNET
	*/
    int getPositionXFromGrille(int i) const;

	/*!
	* \brief renvoie l'ordonnée en pixel d'un objet dans la scene
	*
	* Un objet (Joueur, Brique, Bombe, Explosion) est représenté
    * dans m_grilleJeu (QVector deux dimmensions), mais son image (attribut picture )
	* doit s'afficher dans la scene, avec une position exprimé en pixel.
	* La fonction calcule y à partir de l' indice j et renvoie y
	*
	* \param j Ligne de la grille
	* \return y, correspondant à l'ordonnée dans la scène
	* \author Quentin CHEYNET
	*/
    int getPositionYFromGrille(int j) const;

	/*!
	* \brief renvoie la colonne i d'un objet dans la grille
	*
	* Un objet (Joueur, Brique, Bombe, Explosion) est représenté
    * dans m_grilleJeu (QVector deux dimmensions), mais son image (attribut picture )
	* s'affiche dans la scene, avec une position exprimé en pixel.
	* La fonction calcule l'indice i de la grille à partire de l'abscisse x
	*
    * \param x Abscisse de l'image dans m_scene
	* \return i,colonne de la grille
	* \author Quentin CHEYNET
	*/
    int getGrilleIFromPosition(int x) const;

	/*!
	* \brief renvoie la ligne j d'un objet dans la grille
	*
	* Un objet (Joueur, Brique, Bombe, Explosion) est représenté
    * dans m_grilleJeu (QVector deux dimmensions), mais son image (attribut picture )
	* s'affiche dans la scene, avec une position exprimé en pixel.
	* La fonction calcule l'indice j de la grille à partire de l'ordonnée y
	*
    * \param x Ordonnée de l'image dans m_scene
	* \return j,ligne de la grille
	* \author Quentin CHEYNET
	*/
    int getGrilleJFromPosition(int y) const;

	/*!
	* \brief fait bouger un personnage en prenant en compte les collisions
    * \param x Abscisse de l'image dans m_scene
    * \param Y Ordonnée de l'image dans m_scene
	* \author Quentin CHEYNET
	*/
	void tryMove(int x, int y);

	/*!
	* \brief Test si un Joueur déplacé de x,y va entrer en collison avec une brique
    * \param x Abscisse de l'image dans m_scene
    * \param Y Ordonnée de l'image dans m_scene
	* \return vrai si il y a une collision
	* \author Quentin CHEYNET
	*/
	bool collisionTest(int x, int y);
	/*!
	* \brief fait sauter un personnage en prenant en compte les collisions
	* \author Quentin CHEYNET
	*/
	void tryJump();

	/*!
	* \brief inverse le signe de la gravité
	* \author Quentin CHEYNET
	*/
	void toggleGravity();

	/*!
	* \brief renvoie la valeur de la gravité
    * \return m_gravite
	* \author Quentin CHEYNET
	*/
    int getGravity() const;

	/*!
	* \brief génère l'explosion d'une bombe
	* \param bombe La bombe qui explose
	* \param dx Le sens horizontal de l'explosion
	* \param dY Le sens horizontal de l'explosion
	* \author Quentin CHEYNET
	*/
	void explosion (Bombe *bombe, int dx, int dy);

	/*!
	* \brief fait exploser toutes les bombes
	* \param bmId L'identifiant du joueur qui a appuyé sur espace
	* \author Quentin CHEYNET
	*/
	void triggerLastBombe(int bmId, bool w);


	/*!
	* \brief regarde si une explosion touche un joueur
	* \param bI position I dans la grille de l'explosion, en partant du point haut gauche de la bombe
	* \param bJ position J dans la grille de l'explosion, en partant du point haut gauche de la bombe
	* \param bI2 position I dans la grille de l'explosion, en partant du point bas droite de la bombe
	* \param bJ2 position J dans la grille de l'explosion, en partant du point haut droite de la bombe
	* \author Quentin CHEYNET
	*/
	bool hitTest(int bI, int bJ, int bI2, int bJ2);

	/*!
	* \brief détruit une brique, et décide si un bonus doit apparaître
	* \param i Ligne de la grille
	* \param j Colonne de la grille
	* \param idJ Joueur qui a détruit la brique
	* \author Quentin CHEYNET
	*/
	void detruireBrique(int i, int j, int idJ);


	/*!
	* \brief ajoute un bonus dans la scene
    * \param i Ligne de la grille des Bonus
    * \param j Colonne de la grille des Bonus
	* \param w Si l'ajout du bonus doit être envoyé aux autres joueurs
	* \param t Le type de bonus ( -1 si à définir aléatoirement)
	* \author Quentin CHEYNET
	*/
	void ajouterBonus(int i, int j, bool w, int t);


	/*!
	* \brief vérifie si le joueur se trouve sur un bonus, et gère son obtntion si c'est le cas
	* \author Quentin CHEYNET
	*/
	void checkBonus();


	/*!
	* \brief Permet de récupérer l'hote ou l'on va se connecter.
	* \author Sébastien Trousse
	*/
    QString getHote () const;


	/*!
	* \brief vérifie si le joueur se trouve sur un bonus, et gère son obtntion si c'est le cas
    * \param hote Ligne de la grille des Bonus
	* \author Sébastien Trousse
	*/
	void setHote(QString hote);
	/*!
	* \brief vérifie si le joueur se trouve sur un bonus, et gère son obtntion si c'est le cas
	* \author Sébastien Trousse
	*/
	void initialiserSocket(QString hote);

	/*!
	* \brief affiche l'écran de fin (victoire/défaite et score)
	* \author Quentin Cheynet
	*/
    void displayEndScreen();

	~MainWindow();

};
#endif
