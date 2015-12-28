#include "mainwindow.hpp"
#include <QApplication>
#include <iostream>
#include <dirent.h>
#include <vector>
#include <QLabel>

/**
 * @brief main
 * @param argc
 * @param argv
 * @return
 *
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
