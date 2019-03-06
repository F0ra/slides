#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <QTimer>
#include <QWidget>
#include <QPushButton>
#include <QDebug>
#include "tile.h"
#include <vector>
using std::vector;

class PlayGround : public QWidget
{
    Q_OBJECT

public:
    PlayGround(QWidget *parent = nullptr, unsigned int rows = 4, unsigned int cols = 4);
    ~PlayGround();
    void solve();
public slots:
    void fromTile(Tile* tile);
    void shuffleGrid();
    void swap(Tile* tile);
    void test() {
        qDebug()<<"test";
        QTimer::singleShot(600, this, SLOT(test()));}
private:
    vector<vector <Tile*>> m_grid;
    vector<int> solveSeq;
    void createGrid(unsigned int rows = 4, unsigned int cols = 4);
    void createNeighbourTiles();
    void drawGrid();
    void swapTiles(Tile *tileToSwap);
    bool solvable(const vector<vector<int>> &arr);
    vector<vector<int>> createGridSnapShot();
    Tile* findTileByValue(int val);
    void doSolveStep();

};

#endif // PLAYGROUND_H
