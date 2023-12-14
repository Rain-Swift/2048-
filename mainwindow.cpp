#include "MainWindow.h"
#include <QGridLayout>
#include <QKeyEvent>
#include <QString>
#include "game2048.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);  // 初始化界面
    statusBar()->hide();
    QPixmap background(":/new/prefix1/1.png");
    ui->backgroundLabel->setPixmap(background.scaled(ui->backgroundLabel->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
    ui->backgroundLabel->setScaledContents(true);
    QMessageBox::information(this, "提示","游戏规则：\n玩家要想办法在 4×4 棋盘的 16 格范围内凑出一个整数2048，具体包括：\n(1) 在一个 4×4 的棋盘上，随机初始化两个方格的值为 2，其中一个方格应在棋盘四个角的某一个位置，另一个方格位置随机，其它方格的值置为 0。\n(2) 玩家每次可以选择上下左右一个方向，每选一个方向，所有的数字往所选择的方向移动一次，相同的数字在相遇时会相加。\n(3) 一次移动结束后，系统同时会在 0 位置随机出现一个 2 或 4，2 出现的概率应比 4 高。\n(4) 凑出2048方格，或没有 0 位置且没有相邻数字相同时，游戏结束。\n(5) 游戏计分标准：初始得分为 0，每选择一次方向减 1 分，每次合并数字都会增加对应数字的分数，例如，两个 4 合并在一起则会增加 4 分。如果最终凑出“2048”方格则视为通关，没有凑出2048方格且游戏结束视为失败。\n(6)你可以点按界面的方向键来移动数字，也可以操控键盘中的方向键来移动数字。");
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
    case Qt::Key_Space:
        if(!game.Revise()) QMessageBox::information(this, "警告", "只能撤销一步，你已经撤销过了");
        updateUI();
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
        End(0);
}
    if(game.Win()){
        updateUI();
        End(1);
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
        End(0);
}
    if(game.Win()){
        updateUI();
        End(1);
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
        End(0);
}
    if(game.Win()){
        updateUI();
        End(1);
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
        End(0);
}
    if(game.Win()){
        updateUI();
        End(1);
}

    updateUI();
}


void MainWindow::on_revise_clicked()
{
    if(!game.Revise()) QMessageBox::information(this, "警告", "只能撤销一步，你已经撤销过了");
    updateUI();
}

void MainWindow::End(int n){
    if(n==0){
        if(game.choice>0){
        QMessageBox msgBox;
        msgBox.setWindowTitle("抉择");
        msgBox.setText("您看来陷入了困境，现在有"+QString::number(game.choice)+"次回答问题复活的机会，您是否接受？\n(选否则结束游戏）");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        if (msgBox.exec() == QMessageBox::Yes) {
            // 用户选择了“Yes”
    QMessageBox msgBox;
    msgBox.setWindowTitle("问题");
    msgBox.setText("世界上最高的建筑物（截至2023年）是什么？");
    msgBox.setIcon(QMessageBox::Question);

    // 添加自定义按钮
    QAbstractButton *button1 = msgBox.addButton("迪拜的哈利法塔", QMessageBox::ActionRole);
    QAbstractButton *button2 = msgBox.addButton("上海的上海中心大厦2", QMessageBox::ActionRole);
    QAbstractButton *button3 = msgBox.addButton("麦加的皇家时钟塔", QMessageBox::ActionRole);
    QAbstractButton *button4 = msgBox.addButton("纽约的一世界贸易中心", QMessageBox::ActionRole);

    // 显示对话框
    msgBox.exec();

    // 检查用户点击了哪个按钮
    if (msgBox.clickedButton() == button1) {
        game.Recover();
        QMessageBox::information(this, "恭喜", "回答正确，复活成功！你还有"+QString::number(game.choice)+"次复活机会");
    } else if (msgBox.clickedButton() == button2) {
        QMessageBox::information(this, "游戏结束", "回答错误，游戏结束!\n您的得分是:"+QString::number(game.point)+"\n您的步数是:"+QString::number(game.step));
    } else if (msgBox.clickedButton() == button3) {
        QMessageBox::information(this, "游戏结束", "回答错误，游戏结束!\n您的得分是:"+QString::number(game.point)+"\n您的步数是:"+QString::number(game.step));
    } else if (msgBox.clickedButton() == button4) {
        QMessageBox::information(this, "游戏结束", "回答错误，游戏结束!\n您的得分是:"+QString::number(game.point)+"\n您的步数是:"+QString::number(game.step));
    }
        }
        else {
    QMessageBox::information(this, "游戏结束", "失败啦!\n您的得分是:"+QString::number(game.point)+"\n您的步数是:"+QString::number(game.step));
        }
        }
        else {
            QMessageBox::information(this, "游戏结束", "失败啦!\n您的得分是:"+QString::number(game.point)+"\n您的步数是:"+QString::number(game.step));
        }
    }
    if(n==1)QMessageBox::information(this, "游戏结束", "恭喜您，成功啦!\n您的得分是:"+QString::number(game.point)+"\n您的步数是:"+QString::number(game.step));
}


