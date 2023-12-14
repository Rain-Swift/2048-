#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.setWindowIcon(QIcon(":/new/prefix1/icon.png"));
    mainWindow.show();
    return app.exec();
}
