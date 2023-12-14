#include "game2048.h"
#include <cstdlib>
#include <ctime>

Game2048::Game2048() {
    srand(static_cast<unsigned int>(std::time(nullptr)));
    initialize();
}//以系统时间作为随机数种子

void Game2048::initialize() {
    // 初始化游戏面板
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            board[i][j] = 0;
            PreBoard[i][j]=0;
        }
    }

    addx=0;//每次移动新加数的位置
    addy=0;
    addpx=0;//上次移动新加数的位置
    addpy=0;

    addRandomTile();
    addRandomTile();

    point=0;//初始化分数为0
    step=0;//初始化步数为0
    choice=3;//初始化复活机会为3
    Revisible=0;//不可撤销
    prepoint=0;//上一次分数为0

}

bool Game2048::CheckFull(){
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if(board[i][j] == 0) return false;
        }
    }
    return true;
}//检查是否已满

bool Game2048::manipulate(int direction) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            PreBoard[i][j]=board[i][j];
        }
    }
    prepoint=point;//保存上一次的数字表格

    Revisible=1;//状态变更为可撤销

    if(!judge()) return true;//已满则直接返回

    point--;
    step++;

    switch (direction) {
    case 1: // 向左
        if(!moveLeft()) return false;
        break;
    case 2: // 向右
        if(!moveRight()) return false;
        break;
    case 3: // 向上
        if(!moveUp()) return false;
        break;
    case 4: // 向下
        if(!moveDown()) return false;
        break;
    }
    addRandomTile(); // 每次操作后添加新方块
    return true;
}

bool Game2048::judge(){
    //右侧判断
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == board[i][j + 1]) return true;
        }
    }
    //下侧判断
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4 ; j++) {
            if (board[i][j] == board[i+1][j]) return true;
        }
    }
    //空位判断
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 0)
                return true;
        }
    }
    return false;
}

int Game2048::getTile(int x, int y) const {
    return board[x][y];
}

int Game2048::ranNum() {
    return (rand() % 2 + 1) * 2;
}

int Game2048::ranNum1() {
    return rand() % 4;
}

void Game2048::addRandomTile() {
    int x, y;
    do {
        x = ranNum1();
        y = ranNum1();
    } while (board[x][y] != 0);
    addpx=addx;
    addpy=addy;
    addx=x;
    addy=y;
    board[x][y] = ranNum();
}

bool Game2048::moveLeft() {
    int status=0;
    if(CheckFull()){
        for (int i = 0; i < 4; i++) {
            for (int j = 3; j > 0; j--) {
                if (board[i][j] == board[i][j - 1]) status=1;
            }
        }
        if(status==0) return false;
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 3; j >0; j--) {
            if (board[i][j] != 0 && board[i][j - 1] == 0) {
                board[i][j - 1] = board[i][j];
                board[i][j] = 0;
                j=4;
            }
        }
    }//填充空格
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j <3; j++) {
            if (board[i][j] == board[i][j + 1]&&board[i][j+1]!=0) {
                board[i][j] *= 2;
                point+=board[i][j];
                board[i][j+1] = 0;
                j++;
            }
        }
    }//合并数字
    for (int i = 0; i < 4; i++) {
        for (int j = 3; j >0; j--) {
            if (board[i][j] != 0 && board[i][j - 1] == 0) {
                board[i][j - 1] = board[i][j];
                board[i][j] = 0;
                j=4;
            }
        }
    }
    return true;
}

bool Game2048::moveRight() {
    int status=0;
    if(CheckFull()){
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == board[i][j + 1]) status=1;
            }
        }
        if(status==0) return false;
    }

    for (int i = 0;  i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 0 && board[i][j + 1] == 0) {
                board[i][j+1] = board[i][j];
                board[i][j]= 0;
                j=-1;
            }
        }
    }
        for (int i = 0;  i < 4; i++) {
        for (int j = 3; j > 0; j--) {
                    if (board[i][j] == board[i][j - 1]&&board[i][j-1]!=0) {
                        board[i][j ] *= 2;
                        point+=board[i][j];
                        board[i][j-1] = 0;
                        j--;
                    }

                }
        }
        for (int i = 0;  i < 4; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] != 0 && board[i][j + 1] == 0) {
                        board[i][j+1] = board[i][j];
                        board[i][j]= 0;
                        j=-1;
                    }
                }
        }
        return true;
}

bool Game2048::moveUp() {
    int status=0;
    if(CheckFull()){
                for (int i = 3; i >0; i--) {
                    for (int j = 0; j < 4; j++) {
                        if (board[i][j] == board[i-1][j]) status=1;
                    }
                }
                if(status==0) return false;
        }
    for (int j = 0; j<4; j++) {
        for (int i = 3; i >0; i--) {
            if (board[i-1][j] ==0 &&board[i][j]!=0) {
                board[i-1][j] = board[i][j];
                board[i][j]=0;
                i=4;
            }

        }
    }
    for (int j = 0; j<4; j++) {
        for (int i = 0; i < 3; i++) {
            if (board[i][j] == board[i+1][j]&&board[i][j]!=0) {
                board[i][j] *= 2;
                point+=board[i][j];
                board[i+1][j] = 0;
                i++;
            }

        }
    }
    for (int j = 0; j<4; j++) {
        for (int i = 3; i >0; i--) {
            if (board[i-1][j] ==0 &&board[i][j]!=0) {
                board[i-1][j] = board[i][j];
                board[i][j]=0;
                i=4;
            }

        }
    }
    return true;
}

bool Game2048::moveDown() {
    int status=0;
    if(CheckFull()){
        for (int i = 0; i <3; i++) {
            for (int j = 0; j < 4; j++) {
                if (board[i][j] == board[i+1][j]) status=1;
            }
        }
        if(status==0) return false;
    }
    for (int j = 0; j<4; j++) {
        for (int i = 0; i <3; i++) {
            if (board[i+1][j] ==0 &&board[i][j]!=0) {
                board[i+1][j] = board[i][j];
                board[i][j]=0;
                i=-1;
            }

        }
    }
    for (int j = 3;j >=0; j--) {
        for (int i = 3; i >0; i--) {
            if (board[i][j] == board[i-1][j]&&board[i-1][j]!=0) {
                board[i][j] *= 2;
                point+=board[i][j];
                board[i-1][j] = 0;
                i--;
            }

        }
    }
    for (int j = 0; j<4; j++) {
        for (int i = 0; i <3; i++) {
            if (board[i+1][j] ==0 &&board[i][j]!=0) {
                board[i+1][j] = board[i][j];
                board[i][j]=0;
                i=-1;
            }

        }
    }
    return true;
}

bool Game2048::Revise(){
    if(!Revisible) return false;
    if(Revisible){
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            board[i][j]=PreBoard[i][j];
        }
    }
    step--;
    point=prepoint-10;
    Revisible=0;
    }
    return true;
}

bool Game2048::Win(){
    for (int i = 0; i <4; i++) {
      for (int j = 0; j <4; j++) {
        if (board[i][j]==2048) {
            return true;
        }
      }
    }
    return false;
}

void Game2048::Recover(){
    for (int i = 0; i <4; i++) {
      for (int j = 0; j <4; j++) {
        if (board[i][j]==2) {
            board[i][j]=0;
        }
      }
    }
    choice--;
}

int Game2048::getPoint(){
    return point;
}

int Game2048::getStep(){
    return step;
}
