#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
#include "ui_mainwindow.h"
#include "game2048.h"
#include <QMessageBox>
#include <QKeyEvent>
#include <QTimer>
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void keyPressEvent(QKeyEvent *event) override;//键盘点击事件

    void on_up_clicked();//对应方向的点击事件

    void on_down_clicked();//对应方向的点击事件

    void on_left_clicked();//对应方向的点击事件

    void on_right_clicked();//对应方向的点击事件

    void on_revise_clicked();//撤销函数

    void updateLabelText();//更新界面数字表格

    ;
private:
    Ui::MainWindow *ui;

    Game2048 game;  // 游戏逻辑实例

    QLabel* tiles[16];  // 存储指向 16 个标签的指针

    QLabel* a[2];

    void End(int n);//结束函数

    void question(int n);//题库

    void updateUI();  // 更新 UI 的方法

    QTimer *rotationTimer;//设置计时器

    QStringList stringsToRotate;//设置滚动的提示字符串

    int currentStringIndex;//当前提示内容的指针

    QString q,a1,a2,a3,a4;

    void Restart(int n);//重启函数

    int maxPoint=0,maxStep=0;//记录历史最高分和步数

};
#endif

