#include "mwindow.h"
Mwindow::Mwindow(QWidget *parent) : QWidget(parent)
{
    playGround = new PlayGround(this);
    menu = new MenuGroup(this);
    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(menu,0,0);
    mainLayout->addWidget(playGround,1,0);
    setStyleSheet("background-color: black");
    connect(menu,&MenuGroup::resetGrid,this,&Mwindow::resetGrid);
    connect(menu,&MenuGroup::shuffleGridSignal,this,&Mwindow::shuffleGrid);
    connect(menu,&MenuGroup::solveSignal,this,&Mwindow::solve);
}
