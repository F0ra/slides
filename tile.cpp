#include "tile.h"

Tile::Tile(QWidget *parent, unsigned int cVal, unsigned int tVal) : QPushButton (parent)
{
    curentVal = cVal;
    targetVal = tVal;
    setStyle();
    connect(this,&Tile::clicked,this,&Tile::emitTilePtr);
}

void Tile::setStyle(){
    if(curentVal != 0) {
        setStyleSheet("background-color: yellow");
        setText(QString::number(curentVal));
    } else {
        setStyleSheet("background-color: black;"
                      "border-style: outset;");
        setText("");
    }
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

unsigned int Tile::getCurentValue() {return curentVal;}
unsigned int Tile::getTargetValue() {return targetVal;}
void Tile::setCurentVal(unsigned int val) {
//    this->style();
    curentVal = val;
    setStyle();
}
