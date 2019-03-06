#include "menugroup.h"


MenuGroup::MenuGroup(QWidget *parent) : QWidget(parent)
{
    MenuGroup_parent = parent;
    solve = new Solve;
    shuffle = new Shuffle;
    QGridLayout *menu = new QGridLayout(this);
    QPushButton *btn1 = new QPushButton("+ row",this);
    QPushButton *btn2 = new QPushButton("- row",this);
    QPushButton *btn3 = new QPushButton("+ col",this);
    QPushButton *btn4 = new QPushButton("- col",this);
    menu->addWidget(btn1,0,0);
    menu->addWidget(btn2,0,1);
    menu->addWidget(btn3,1,0);
    menu->addWidget(btn4,1,1);
    menu->addWidget(shuffle,2,0);
    menu->addWidget(solve,2,1);
//    setLayout(menu);
    setStyleSheet("background-color: white;"
                  "height: 40%;");
    connect(btn1,&QPushButton::clicked,this,&MenuGroup::plusRow);
    connect(btn2,&QPushButton::clicked,this,&MenuGroup::minusRow);
    connect(btn3,&QPushButton::clicked,this,&MenuGroup::plusCol);
    connect(btn4,&QPushButton::clicked,this,&MenuGroup::minusCol);
    connect(shuffle,&Shuffle::clicked,this,&MenuGroup::shuffleGrid);
    connect(solve,&Solve::clicked,this,&MenuGroup::solveSlot);
}

void MenuGroup::solveSlot() {
    emit solveSignal();
}

void MenuGroup::shuffleGrid() {
    emit shuffleGridSignal();
}

void MenuGroup::plusRow() {
    if (m_rows >= 5) return;
    ++m_rows;
    emit resetGrid(m_rows, m_cols);
}

void MenuGroup::minusRow() {
    if (m_rows <= 2) return;
    --m_rows;
    emit resetGrid(m_rows, m_cols);
}

void MenuGroup::plusCol() {
    if (m_cols >= 5) return;
    ++m_cols;
    emit resetGrid(m_rows, m_cols);
}

void MenuGroup::minusCol() {
    if (m_cols <= 2) return;
    --m_cols;
    emit resetGrid(m_rows, m_cols);
}
