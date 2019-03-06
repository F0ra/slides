#ifndef MENUGROUP_H
#define MENUGROUP_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>

class Shuffle : public QPushButton
{
    Q_OBJECT
public:
    explicit Shuffle(QWidget *parent = nullptr)  : QPushButton("Shuffle", parent) {

    }

signals:

public slots:
};

class Solve : public QPushButton
{
    Q_OBJECT
public:
    explicit Solve(QWidget *parent = nullptr)  : QPushButton("Solve", parent) {

    }
signals:

public slots:
};

class MenuGroup : public QWidget
{
    Q_OBJECT
public:
    explicit MenuGroup(QWidget *parent = nullptr);
    Shuffle *shuffle;
    Solve *solve;
signals:
    void resetGrid(unsigned int rows, unsigned int cols);
    void shuffleGridSignal();
    void solveSignal();
public slots:
    void shuffleGrid();
    void plusRow();
    void minusRow();
    void plusCol();
    void minusCol();
    void solveSlot();
private:
    unsigned int m_rows{4};
    unsigned int m_cols{4};
    QWidget *MenuGroup_parent;
};

#endif // MENUGROUP_H
