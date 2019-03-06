#include "playground.h"
#include "solve.cpp"
#include <QGridLayout>
#include <random>

PlayGround::PlayGround(QWidget *parent, unsigned int rows, unsigned int cols)
    : QWidget(parent)
{
    createGrid(rows, cols);
    createNeighbourTiles();
    drawGrid();
    setStyleSheet("background-color: black");
//    test();
}

PlayGround::~PlayGround()
{
    for (auto row : m_grid) {
        for (auto col : row) {
            delete col;
        }
    }
}

void PlayGround::fromTile(Tile* tile) {
    swapTiles(tile);
}

void PlayGround::swap(Tile* tile) {
    swapTiles(tile);
}

void PlayGround::swapTiles(Tile *tileToSwap) {
        for (auto tile : tileToSwap->neighbourTiles) {
            //qDebug()<<tile->getCurentValue();
            if (tile->getCurentValue() == 0) {
                tile->setCurentVal(tileToSwap->getCurentValue());
                tileToSwap->setCurentVal(0);
                return;
            }
        }
}

void PlayGround::createGrid(unsigned int rows, unsigned int cols) {
    m_grid.clear();
    m_grid.resize(rows);
    for (uint i{}; i < rows; ++i) {
        for (uint j{}; j < cols; ++j) {
            if (i==(rows-1) && j==(cols-1)) {
                m_grid[i].push_back(new Tile(this,0,0));
            } else {
                m_grid[i].push_back(new Tile(this,i*rows+j+1,i*rows+j+1));
            }
            connect(m_grid[i][j],&Tile::tilePtr,this,&PlayGround::fromTile);
        }
    }
}

vector<vector<int>> PlayGround::createGridSnapShot() {
    vector<vector<int>> snapShot;
    snapShot.resize(m_grid.size());
    for (int i{}; i < m_grid.size(); ++i) {
        for (int j{}; j < m_grid[0].size(); ++j) {
            snapShot[i].push_back(m_grid[i][j]->getCurentValue());
        }
    }
    return snapShot;
}

Tile* PlayGround::findTileByValue(int val) {
            for (int i{}; i < m_grid.size(); ++i) {
                for (int j{}; j < m_grid[0].size(); ++j) {
                    if (m_grid[i][j]->getCurentValue() == val) return m_grid[i][j];
                }
            }
}

void PlayGround::shuffleGrid(){
    auto rows = m_grid.size();
    auto cols  = m_grid[0].size();
    vector<vector<int>> tempVec;


    vector<int> flatSlides;
     while(true) {
         flatSlides.clear();
         tempVec.clear();
         tempVec.resize(rows);
            for (uint i{}; i < rows * cols; ++i) {
                flatSlides.push_back(i);
            }
            std::random_device rd;
            std::mt19937 g(rd());
            std::shuffle(flatSlides.begin(), flatSlides.end(), g);

            for (uint i{}; i < rows; ++i) {
                for (uint j{}; j < cols; ++j) {
                    tempVec[i].push_back(flatSlides[i*cols + j]);
                }
            }
            if (solvable(tempVec)) break;
     }

            for (uint i{}; i < rows; ++i) {
                for (uint j{}; j < cols; ++j) {
                    m_grid[i][j]->setCurentVal(flatSlides[i*cols + j]);
                }
            }
}

void PlayGround::solve() {
    vector<vector<int>> snap = createGridSnapShot();
//    qDebug()<<m_grid.size();
    solveSeq = getSequence(snap);
    doSolveStep();
//    for (auto step : seq) {
//        swapTiles(findTileByValue(step));
//    }

    //qDebug()<<solveSeq;
}

void PlayGround::doSolveStep(){
    static int step{};
    if (step>=solveSeq.size()) {
        step = 0;
        return;
    }
    swapTiles(findTileByValue(solveSeq[step]));
    ++step;
    QTimer::singleShot(200, this, &PlayGround::doSolveStep);
}

bool PlayGround::solvable(const vector<vector<int>> &arr) {
        vector<int> snakeOrdered;
        vector<int> snake;

        int hight = arr.size();
        int width = arr[0].size();

        for (int i{}; i <  hight; ++i) {
            for (int j{}; j < width; ++j) {
                if (i % 2 == 0) {
                        snakeOrdered.push_back(width*i + j + 1);
                    } else {
                        snakeOrdered.push_back(width*i * 2 - j);
                    }
                if (snakeOrdered.back() == (width * hight)) {
                    snakeOrdered.back() = 0;
                }
            }
        }

        for (int i{}; i <  hight; ++i) {
            for (int j{}; j < width; ++j) {
                if (i%2 == 0) {
                            snake.push_back(arr[i][j]);
                        } else {
                            snake.push_back(arr[i][width - 1 - j]);
                        }
                    }
                }

        int snakeOrderedIncorrectPairs{};
        for (int i{}; i < snakeOrdered.size() - 1; ++i) {
            for (int j = i; j < snakeOrdered.size(); ++j) {
                if (snakeOrdered[i] == 0) continue;
                if (snakeOrdered[i] < snakeOrdered[j]) {
                    ++snakeOrderedIncorrectPairs;
                }
            }
        }

        int snakeIncorrectPairs{};
        for (int i{}; i < snake.size() - 1; ++i) {
            for (int j = i; j < snake.size(); ++j) {
                if (snake[i] == 0) continue;
                if (snake[i] < snake[j]) {
                    ++snakeIncorrectPairs;
                }
            }
        }
        return (snakeOrderedIncorrectPairs%2) == (snakeIncorrectPairs%2);
    }

void PlayGround::drawGrid() {
    QGridLayout *grid = new QGridLayout(this);
    unsigned int rows = static_cast<unsigned int>(m_grid.size());
    unsigned int cols = static_cast<unsigned int>(m_grid[0].size());
    for (unsigned int i{}; i < rows; ++i) {
        for (unsigned int j{}; j < cols; ++j) {
            grid->addWidget(m_grid[i][j],static_cast<int>(i),static_cast<int>(j));
        }
    }
    setLayout(grid);
}

void PlayGround::createNeighbourTiles() {
        for (int i{}; i < static_cast<int>(m_grid.size()); ++i) {
            for (int j{}; j < static_cast<int>(m_grid[0].size()); ++j) {
                if (i - 1 >= 0) {
                    m_grid[i][j]->neighbourTiles.push_back(m_grid[i-1][j]);}
                if (i + 1 < m_grid.size()) {
                    m_grid[i][j]->neighbourTiles.push_back(m_grid[i+1][j]);}
                if (j - 1 >= 0) {
                    m_grid[i][j]->neighbourTiles.push_back(m_grid[i][j-1]);}
                if (j + 1 < m_grid[0].size()) {
                    m_grid[i][j]->neighbourTiles.push_back(m_grid[i][j+1]);}
            }
        }
}
