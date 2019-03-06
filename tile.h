#ifndef TILE_H
#define TILE_H

#include <QPushButton>
#include <vector>
using std::vector;

class Tile : public QPushButton
{
    Q_OBJECT

public:
    explicit Tile(QWidget *parent, unsigned int cVal, unsigned int tVal);
    unsigned int getCurentValue();
    unsigned int getTargetValue();
    void setCurentVal(unsigned int val);
    vector<Tile*> neighbourTiles;

signals:
    void tilePtr(Tile*);

public slots:
    void emitTilePtr() {emit tilePtr(this);}

private:
    unsigned int curentVal;
    unsigned int targetVal;
    void setStyle();
};

#endif // TILE_H
