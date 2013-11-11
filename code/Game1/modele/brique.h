#ifndef BRIQUE_H
#define BRIQUE_H

class Brique
{
public:
    Brique(bool cassable,int x ,int y);
    void detruireBrique();

private :
    bool estCassable;
    int posX;
    int posY;
    void setX(int x);
    void setY(int y);
    void setCassable(bool cassable);
};
#endif // BRIQUE_H
