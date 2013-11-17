#ifndef TOUCHECLAVIER_H
#define TOUCHECLAVIER_H
#include <QKeyEvent>
#include <QDebug>
class ToucheClavier
{

private :
    enum touches
    {
        HAUT =0,
        GAUCHE = 1,
        BAS = 2,
        DROIT = 3,
        ESPACE = 4
    };
    bool stateKeys[5];

public:
    /*!
     * \brief Constructeur
     * \author Quentin CHEYNET
     */
    ToucheClavier();
    /*!
     * \brief Met l'état d'une touche à vrai ou faux
     * \param key La touche concernée
     * \param state Si la touche est enfoncée (vrai) ou non (faux)
     * \author Quentin CHEYNET
     */
    void setPressed(int key, bool state);
    /*!
     * \brief Renvoie l'état d'une touche (pressée ou non)
     * \param i La touche dans le tableau des touches
     * \return Vrai si la touche est pressée, faux sinon
     * \author Quentin CHEYNET
     */
    bool getStateKeys(int i);
};

#endif // TOUCHECLAVIER_H
