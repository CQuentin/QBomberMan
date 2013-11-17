#include "toucheclavier.h"

ToucheClavier::ToucheClavier()
{

    for (int i = 0; i<5; i++){
        stateKeys[i] = false;
    }
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
        case Qt::Key_Space:
            stateKeys[4] = state;
            break;
        default : break;
        }
}

bool ToucheClavier::getStateKeys(int i){
    return stateKeys[i];
}
