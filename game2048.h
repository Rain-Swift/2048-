#ifndef GAME2048_H
#define GAME2048_H

#include <cstdlib>
#include <ctime>

class Game2048 {
public:
    Game2048();
    void initialize();
    bool manipulate(int direction);
    bool judge();
    int getTile(int x, int y) const;
    int ranNum();
    int ranNum1();
    int point=0;
    int step=0;
    bool Revise();
    bool Win();
    void Recover();
    int choice=1;

private:
    int board[4][4];
    int PreBoard[4][4];
    void addRandomTile();
    bool moveLeft();
    bool moveRight();
    bool moveUp();
    bool moveDown();
    bool CheckFull();
    bool Revisible=0;
    int prepoint=0;
};

#endif // GAME2048_H
