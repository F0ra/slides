#ifndef MWINDOW_H
#define MWINDOW_H
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QDebug>
#include <vector>
#include "playground.h"
#include "menugroup.h"

using std::vector;

class Mwindow : public QWidget
{
    Q_OBJECT
public:
    explicit Mwindow(QWidget *parent = nullptr);

signals:

public slots:
    void resetGrid(unsigned int rows, unsigned int cols) {
        mainLayout->removeWidget(playGround);
        delete playGround;
        playGround = new PlayGround(this, rows, cols);
        mainLayout->addWidget(playGround,1,0);
        playGround->shuffleGrid();
    }

    void shuffleGrid() {
        playGround->shuffleGrid();
    }

    void solve() {
        playGround->solve();
    }

private:
    PlayGround *playGround;
    MenuGroup *menu;
    QGridLayout *mainLayout;
};

#endif // MWINDOW_H
