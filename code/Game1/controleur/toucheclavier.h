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
        DROIT = 3
    };
    bool stateKeys[4];

public:
    ToucheClavier();
    void setPressed(int key, bool state);
    bool getStateKeys(int i);
};

#endif // TOUCHECLAVIER_H
