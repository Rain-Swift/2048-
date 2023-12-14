#include "MainWindow.h"
#include "game2048.h"
#include <QGridLayout>
#include <QKeyEvent>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), currentStringIndex(0) {
  ui->setupUi(this); // 初始化界面

  // 初始化提示字符串列表
  stringsToRotate
      << "提示：每局游戏有三次回答趣味问题复活的机会，成功复活会消除面板中所有"
         "的‘2’"
      << "提示：你如果对移动不满意，可以选择撤销，但每次撤销扣10分，且不能连续"
         "撤销两步"
      << "提示：你也可以用键盘中的方向键来操控移动方向，空格键可以撤销操作"
      << "提示：每次移动会有一个空格被数字2或4填充，填充位置用黄色背景标出";

  // 设置定时器（用于滚动提示内容）
  rotationTimer = new QTimer(this);
  connect(rotationTimer, &QTimer::timeout, this, &MainWindow::updateLabelText);
  rotationTimer->start(4000); // 设置定时器每秒更新一次

  statusBar()->hide(); // 隐藏状态栏

  QPixmap background(":/new/prefix1/1.png");
  ui->backgroundLabel->setPixmap(background.scaled(
      ui->backgroundLabel->size(), Qt::KeepAspectRatioByExpanding,
      Qt::SmoothTransformation));
  ui->backgroundLabel->setScaledContents(true); // 设置背景

  QMessageBox::information(
      this, "提示",
      "游戏规则：\n玩家要想办法在 4×4 棋盘的 16 "
      "格范围内凑出一个整数2048，具体包括：\n(1) 在一个 4×4 "
      "的棋盘上，随机初始化两个方格的值为 "
      "2，其中一个方格应在棋盘四个角的某一个位置，另一个方格位置随机，其它方格"
      "的值置为 0。\n(2) "
      "玩家每次可以选择上下左右一个方向，每选一个方向，所有的数字往所选择的方向"
      "移动一次，相同的数字在相遇时会相加。\n(3) 一次移动结束后，系统同时会在 "
      "0 位置随机出现一个 2 或 4，2 出现的概率应比 4 高。\n(4) "
      "凑出2048方格，或没有 0 位置且没有相邻数字相同时，游戏结束。\n(5) "
      "游戏计分标准：初始得分为 0，每选择一次方向减 1 "
      "分，每次合并数字都会增加对应数字的分数，例如，两个 4 合并在一起则会增加 "
      "4 "
      "分。如果最终凑出“2048”方格则视为通关，没有凑出2048方格且游戏结束视为失败"
      "。\n(6)"
      "你可以点按界面的方向键来移动数字，也可以操控键盘中的方向键来移动数字。");
  this->setWindowTitle("2048");
  this->setFocusPolicy(Qt::StrongFocus);
  ui->left->setFocusPolicy(Qt::NoFocus);
  ui->up->setFocusPolicy(Qt::NoFocus);
  ui->down->setFocusPolicy(Qt::NoFocus);
  ui->right->setFocusPolicy(Qt::NoFocus);
  ui->revise->setFocusPolicy(Qt::NoFocus); // 设置焦点策略

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
  tiles[15] = ui->l16; // 建立映射关系

  a[0] = ui->score; // 计分板
  a[1] = ui->step;  // 步数统计

  for (int i = 0; i < 16; ++i) {
    if (tiles[i]) {
      tiles[i]->setText(" "); // 初始化文本
    }
  }
  game.initialize(); // 初始化游戏
  updateUI();        // 更新界面
}

MainWindow::~MainWindow() {
  delete ui; // 清理 UI 资源
}

void MainWindow::updateUI() {
  for (int i = 0; i < 16; i++) {
    int row = i / 4;                    // 计算行号
    int col = i % 4;                    // 计算列号
    int value = game.getTile(row, col); // 获取 Game2048 实例中的值
    switch (value) {
    case 0:
      tiles[i]->setText(" ");
      break;
    case 2:
      tiles[i]->setText("<font color='black'>" + QString::number(value) +
                        "</font>");
      break;
    case 4:
      tiles[i]->setText("<font color='darkred'>" + QString::number(value) +
                        "</font>");
      break;
    case 8:
      tiles[i]->setText("<font color='red'>" + QString::number(value) +
                        "</font>");
      break;
    case 16:
      tiles[i]->setText("<font color='orange'>" + QString::number(value) +
                        "</font>");
      break;
    case 32:
      tiles[i]->setText("<font color='yellow'>" + QString::number(value) +
                        "</font>");
      break;
    case 64:
      tiles[i]->setText("<font color='green'>" + QString::number(value) +
                        "</font>");
      break;
    case 128:
      tiles[i]->setText("<font color='blue' size='1'>" +
                        QString::number(value) + "</font>");
      break;
    case 256:
      tiles[i]->setText("<font color='indigo' size='1'>" +
                        QString::number(value) + "</font>");
      break;
    case 512:
      tiles[i]->setText("<font color='darkviolet' size='1'>" +
                        QString::number(value) + "</font>");
      break;
    case 1024:
      tiles[i]->setText("<font color='purple' size='0.2'>" +
                        QString::number(value) + "</font>");
      break;
    case 2048:
      tiles[i]->setText("<font color='plum' size='0.2'>" +
                        QString::number(value) + "</font>");
      break;
    } // 根据数字设置颜色和尺寸
  }

  a[0]->setText("得分：" + QString::number(game.getPoint()));
  a[1]->setText("步数：" + QString::number(game.getStep())); // 更新统计版

  tiles[game.addx * 4 + game.addy]->setStyleSheet(
      "QLabel {"
      "  background-color: yellow;" // 设置背景色为黄色
      "  border: 1px solid black;"  // 设置边框为1像素宽的黑色实线
      "}");
  if (game.addx != game.addpx || game.addy != game.addpy)
    tiles[game.addpx * 4 + game.addpy]->setStyleSheet(
        "QLabel {"
        "  background-color: rgba(255, 255, 255, 0);" // 背景色透明
        "  border: 1px solid black;" // 设置边框为1像素宽的黑色实线
        "}");
  // 将每次新出现的数背景标黄，并恢复上次标黄的位置
}

// 根据键盘按键移动数字
void MainWindow::keyPressEvent(QKeyEvent *event) {
  switch (event->key()) {
  case Qt::Key_Up:
    on_up_clicked();
    break;
  case Qt::Key_Down:
    on_down_clicked();
    break;
    // 其他按键和函数...
  case Qt::Key_Left:
    on_left_clicked();
    break;
  case Qt::Key_Right:
    on_right_clicked();
    break;
  case Qt::Key_Space:
    if (!game.Revise())
      QMessageBox::information(this, "警告", "只能撤销一步，你已经撤销过了");
    updateUI();
    break;
  default:
    QMainWindow::keyPressEvent(event); // 确保其他按键正常处理
  }
}

// 根据界面按钮移动数字
void MainWindow::on_up_clicked() {
  if (!game.manipulate(3)) {
    updateUI();
    QMessageBox::information(this, "警告",
                             "当前情况下，你不能上移，请尝试其他方向");
  }
  if (!game.judge()) {
    updateUI();
    End(0);
  }
  if (game.Win()) {
    updateUI();
    End(1);
  }
  updateUI();
}

void MainWindow::on_down_clicked() {
  if (!game.manipulate(4)) {
    updateUI();
    QMessageBox::information(this, "警告",
                             "当前情况下，你不能下移，请尝试其他方向");
  }
  if (!game.judge()) {
    updateUI();
    End(0);
  }
  if (game.Win()) {
    updateUI();
    End(1);
  }
  updateUI();
}

void MainWindow::on_left_clicked() {
  if (!game.manipulate(1)) {
    updateUI();
    QMessageBox::information(this, "警告",
                             "当前情况下，你不能左移，请尝试其他方向");
  }
  if (!game.judge()) {
    updateUI();
    End(0);
  }
  if (game.Win()) {
    updateUI();
    End(1);
  }

  updateUI();
}

void MainWindow::on_right_clicked() {
  if (!game.manipulate(2)) {
    updateUI();
    QMessageBox::information(this, "警告",
                             "当前情况下，你不能右移，请尝试其他方向");
  }
  if (!game.judge()) {
    updateUI();
    End(0);
  }
  if (game.Win()) {
    updateUI();
    End(1);
  }

  updateUI();
}

// 撤销按键
void MainWindow::on_revise_clicked() {
  if (!game.Revise())
    QMessageBox::information(this, "警告", "只能撤销一步，你已经撤销过了");
  updateUI();
}

// 游戏结束函数
void MainWindow::End(int n) {
  // 设置游戏结束提醒消息框
  QMessageBox LoseBox;
  LoseBox.setWindowTitle("游戏结束");
  LoseBox.setText("失败啦!\n您的得分是:" + QString::number(game.getPoint()) +
                  "\n您的步数是:" + QString::number(game.getStep()) +
                  "\n您的历史最高分" + QString::number(maxPoint) +
                  "\n对应步数：" + QString::number(maxStep));
  LoseBox.setIcon(QMessageBox::Question);
  QAbstractButton *button5 =
      LoseBox.addButton("结束游戏", QMessageBox::ActionRole);
  QAbstractButton *button6 =
      LoseBox.addButton("重新开始", QMessageBox::ActionRole);

  if (n == 0) {
    if (game.choice > 0) {
      // 设置复活选择消息框
      QMessageBox msgBox;
      msgBox.setWindowTitle("抉择");
      msgBox.setText("您看来陷入了困境，现在还有" +
                     QString::number(game.choice) +
                     "次回答问题复活的机会，您是否接受？\n(选否则结束游戏）");
      msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
      msgBox.setDefaultButton(QMessageBox::No);
      if (msgBox.exec() == QMessageBox::Yes) {
        // 用户选择了“Yes”

        // 从题库中选择问题
        question(game.choice);

        // 设置趣味问题消息框
        QMessageBox msgBox;
        msgBox.setWindowTitle("问题");
        msgBox.setText(q);
        msgBox.setIcon(QMessageBox::Question);
        QAbstractButton *button1 =
            msgBox.addButton(a1, QMessageBox::ActionRole);
        QAbstractButton *button2 =
            msgBox.addButton(a2, QMessageBox::ActionRole);
        QAbstractButton *button3 =
            msgBox.addButton(a3, QMessageBox::ActionRole);
        QAbstractButton *button4 =
            msgBox.addButton(a4, QMessageBox::ActionRole);

        // 显示对话框
        msgBox.exec();

        // 检查用户点击了哪个按钮
        if (msgBox.clickedButton() == button1) {
          game.Recover();
          QMessageBox::information(this, "恭喜",
                                   "回答正确，复活成功！你还有" +
                                       QString::number(game.choice) +
                                       "次复活机会");
        }
        else if (msgBox.clickedButton() == button2 && game.choice > 0) {
          game.choice--;
          QMessageBox::information(
              this, "提示",
              "回答错误，你还有" + QString::number(game.choice) + "次复活机会");
          End(0);
        }
        else if (msgBox.clickedButton() == button3 && game.choice > 0) {
          game.choice--;
          QMessageBox::information(
              this, "提示",
              "回答错误，你还有" + QString::number(game.choice) + "次复活机会");
          End(0);
        }
        else if (msgBox.clickedButton() == button4 && game.choice > 0) {
          game.choice--;
          QMessageBox::information(
              this, "提示",
              "回答错误，你还有" + QString::number(game.choice) + "次复活机会");
          End(0);
        }
        else {
          LoseBox.setText("回答错误，游戏结束!\n您的得分是:" +
                          QString::number(game.getPoint()) +
                          "\n您的步数是:" + QString::number(game.getStep()) +
                          "\n您的历史最高分" + QString::number(maxPoint) +
                          "\n对应步数：" + QString::number(maxStep));
          LoseBox.exec();
          if (LoseBox.clickedButton() == button5)
            Restart(1);
          if (LoseBox.clickedButton() == button6)
            Restart(0);
        }
      }
      else {
        LoseBox.exec();
        if (LoseBox.clickedButton() == button5)
          Restart(1);
        if (LoseBox.clickedButton() == button6)
          Restart(0);
      }
    }
    else {
      LoseBox.exec();
      if (LoseBox.clickedButton() == button5)
        Restart(1);
      if (LoseBox.clickedButton() == button6)
        Restart(0);
    }
  }
  if (n == 1)
    QMessageBox::information(
        this, "游戏结束",
        "恭喜您，成功啦!\n您的得分是:" + QString::number(game.getPoint()) +
            "\n您的步数是:" + QString::number(game.getStep()) +
            "\n您的历史最高分" + QString::number(maxPoint) + "\n对应步数：" +
            QString::number(maxStep));
}

void MainWindow::updateLabelText() {
  // 更新 QLabel 的文本
  ui->tips->setText(stringsToRotate.at(currentStringIndex));

  // 更新索引以获取下一个字符串
  currentStringIndex = (currentStringIndex + 1) % stringsToRotate.size();
}

//趣味问题的题库
void MainWindow::question(int n) {
  if (n == 3) {
    q = "世界上最高的建筑物（截至2023年）是什么？";
    a1 = "迪拜的哈利法塔";
    a2 = "上海的上海中心大厦";
    a3 = "麦加的皇家时钟塔";
    a4 = "纽约的一世界贸易中心";
  }
  if (n == 2) {
    q = "世界上最大的热带雨林是什么？";
    a1 = "亚马逊雨林";
    a2 = "刚果盆地雨林";
    a3 = "东南亚雨林";
    a4 = "马达加斯加雨林";
  }
  if (n == 1) {
    q = "世界上最古老的文明是什么？";
    a1 = "美索不达米亚文明";
    a2 = "埃及文明";
    a3 = "玛雅文明";
    a4 = "中华文明";
  }
  return;
}

//重新开始函数
void MainWindow::Restart(int n) {
  if (game.getPoint() > maxPoint) {
    maxPoint = game.getPoint();
    maxStep = game.getStep();
  }
  if (n == 0) {
    tiles[game.addx * 4 + game.addy]->setStyleSheet(
        "QLabel {"
        "  background-color: rgba(255, 255, 255, 0);"
        "  border: 1px solid black;" // 设置边框为1像素宽的黑色实线
        "}");
    game.initialize();
  }
  if (n == 1)
    QCoreApplication::quit();//退出游戏
}
