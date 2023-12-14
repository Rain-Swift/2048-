#ifndef GAME2048_H
#define GAME2048_H

#include <cstdlib>
#include <ctime>

class Game2048 {
public:
    Game2048();

    void initialize();//初始化函数

    bool manipulate(int direction);//操作函数

    bool judge();//游戏结束判断函数

    int getTile(int x, int y) const;//表格输出函数

    int getPoint();//输出分数

    int getStep();//输出步数

    bool Revise();//撤销函数

    bool Win();//胜利判断函数

    void Recover();//复活函数

    int choice=3;//复活机会

    int addx,addy,addpx,addpy;//新加数的位置和上一次添加数的位置

private:

    int board[4][4];//数字表格

    int PreBoard[4][4];//上一次的数字表格

    int ranNum();//随机数函数1

    int ranNum1();//随机数函数2

    void addRandomTile();//在随机位置加数函数

    bool moveLeft();//左移

    bool moveRight();//右移

    bool moveUp();//上移

    bool moveDown();//下移

    bool CheckFull();//检查表格是否已满

    bool Revisible=0;//可撤销状态

    int prepoint=0;//上一次移动时的分数

    int point=0;//分数

    int step=0;//步数


};

#endif // GAME2048_H
