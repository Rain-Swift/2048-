#include "MainWindow.h"
#include <QGridLayout>
#include <QKeyEvent>
#include <QString>
#include "game2048.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);  // 初始化界面
    this->setWindowTitle("2048");
    this->setFocusPolicy(Qt::StrongFocus);
    ui->left->setFocusPolicy(Qt::NoFocus);
    ui->up->setFocusPolicy(Qt::NoFocus);
    ui->down->setFocusPolicy(Qt::NoFocus);
    ui->right->setFocusPolicy(Qt::NoFocus);
    ui->revise->setFocusPolicy(Qt::NoFocus);
    tiles[0] = ui->l1;
    tiles[1] = ui->l2;
    tiles[2] = ui->l3;
    tiles[3] = ui->l4;
    tiles[4] = ui->l5;
    tiles[5] = ui->l6;
    tiles[6] = ui->l7;
    tiles[7] = ui->l8;
    tiles[8] = ui->l9;
    tiles[9] = ui->l10;
    tiles[10] = ui->l11;
    tiles[11] = ui->l12;
    tiles[12] = ui->l13;
    tiles[13] = ui->l14;
    tiles[14] = ui->l15;
    tiles[15] = ui->l16;

    a[0]=ui->score;//计分板
    a[1]=ui->step;//步数统计

    for (int i = 0; i < 16; ++i) {
        if (tiles[i]) {
            tiles[i]->setText(" ");  // 初始化文本
        }
    }
    game.initialize();
    updateUI();
}

MainWindow::~MainWindow() {
    delete ui;  // 清理 UI 资源
}

void MainWindow::updateUI() {
    for (int i = 0; i < 16; i++) {
        int row = i / 4;  // 计算行号
        int col = i % 4;  // 计算列号
        int value = game.getTile(row, col);  // 获取 Game2048 实例中的值
        switch(value){
        case 0:
            tiles[i]->setText(" ");
            break;
        case 2:
            tiles[i]->setText("<font color='black'>" + QString::number(value) + "</font>");
            break;
        case 4:
            tiles[i]->setText("<font color='darkred'>" + QString::number(value) + "</font>");
            break;
        case 8:
            tiles[i]->setText("<font color='red'>" + QString::number(value) + "</font>");
            break;
        case 16:
            tiles[i]->setText("<font color='orange'>" + QString::number(value) + "</font>");
            break;
        case 32:
            tiles[i]->setText("<font color='yellow'>" + QString::number(value) + "</font>");
            break;
        case 64:
            tiles[i]->setText("<font color='green'>" + QString::number(value) + "</font>");
            break;
        case 128:
            tiles[i]->setText("<font color='blue' size='1'>" + QString::number(value) + "</font>");
            break;
        case 256:
            tiles[i]->setText("<font color='indigo' size='1'>" + QString::number(value) + "</font>");
            break;
        case 512:
            tiles[i]->setText("<font color='darkviolet' size='1'>" + QString::number(value) + "</font>");
            break;
        case 1024:
            tiles[i]->setText("<font color='purple' size='0.5'>" + QString::number(value) + "</font>");
            break;
        case 2048:
            tiles[i]->setText("<font color='plum' size='0.5'>" + QString::number(value) + "</font>");
            break;
        }

    }
    a[0]->setText("得分："+QString::number(game.point));
    a[1]->setText("步数："+QString::number(game.step));

}

void MainWindow::keyPressEvent(QKeyEvent *event){
    switch (event->key()) {
    case Qt::Key_Up:
        on_up_clicked();
        break;
    case Qt::Key_Down:
        on_down_clicked() ;
        break;
        // 其他按键和函数...
    case Qt::Key_Left:
        on_left_clicked();
        break;
    case Qt::Key_Right:
        on_right_clicked();
        break;
    default:
        QMainWindow::keyPressEvent(event);  // 确保其他按键正常处理
    }

}

void MainWindow::on_up_clicked()
{
    if(!game.manipulate(3)) {
        updateUI();
        QMessageBox::information(this, "警告", "当前情况下，你不能上移，请尝试其他方向");
    }
    if(!game.judge()) {
        updateUI();
        End();
}

    updateUI();
}


void MainWindow::on_down_clicked()
{
    if(!game.manipulate(4)) {
        updateUI();
        QMessageBox::information(this, "警告", "当前情况下，你不能下移，请尝试其他方向");
    }
    if(!game.judge()) {
        updateUI();
        End();
}

    updateUI();

}


void MainWindow::on_left_clicked()
{
    if(!game.manipulate(1)) {
        updateUI();
        QMessageBox::information(this, "警告", "当前情况下，你不能左移，请尝试其他方向");
    }
    if(!game.judge()) {
        updateUI();
        End();
}

    updateUI();
}


void MainWindow::on_right_clicked()
{
    if(!game.manipulate(2)) {
        updateUI();
        QMessageBox::information(this, "警告", "当前情况下，你不能右移，请尝试其他方向");
    }
    if(!game.judge()) {
        updateUI();
        End();
}

    updateUI();
}


void MainWindow::on_revise_clicked()
{
    if(!game.Revise()) QMessageBox::information(this, "警告", "只能撤销一步，你已经撤销过了");
    updateUI();
}

void MainWindow::End(){
    QMessageBox::information(this, "游戏结束", "失败啦!\n您的得分是:"+QString::number(game.point)+"\n您的步数是:"+QString::number(game.step));
}


