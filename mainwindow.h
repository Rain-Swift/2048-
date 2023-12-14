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
    void keyPressEvent(QKeyEvent *event) override;

    void on_up_clicked();

    void on_down_clicked();

    void on_left_clicked();

    void on_right_clicked();

    void on_revise_clicked();

    void updateLabelText();

    ;
private:
    Ui::MainWindow *ui;
    Game2048 game;  // 游戏逻辑实例
    QLabel* tiles[16];  // 存储指向 16 个标签的指针
    QLabel* a[2];
    void End(int n);
    void question(int n);
    void updateUI();  // 更新 UI 的方法

    QTimer *rotationTimer;
    QStringList stringsToRotate;
    int currentStringIndex;
    QString q,a1,a2,a3,a4;


};
#endif

