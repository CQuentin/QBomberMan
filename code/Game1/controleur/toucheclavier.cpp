#include "toucheclavier.h"

ToucheClavier::ToucheClavier()
{

    stateKeys[0] = false;

    stateKeys[1] = false;

    stateKeys[2] = false;
    stateKeys[3] = false;
}


void ToucheClavier::setPressed(int key, bool state){

        switch(key){
        case Qt::Key_Z:
            stateKeys[0] = state;
            break;
        case Qt::Key_Q:
            stateKeys[1] = state;
            break;
        case Qt::Key_S:
            stateKeys[2] = state;
            break;
        case Qt::Key_D:
            stateKeys[3] = state;
            break;
        default : break;
        }
}

bool ToucheClavier::getStateKeys(int i){
    return stateKeys[i];
}
