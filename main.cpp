
#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <QDesktopWidget>
#include <QMainWindow>

#include "config.h"

void moveCenter(MainWindow &wm) {
    QDesktopWidget *desktop = QApplication::desktop();
    wm.move((desktop->width() - wm.width()) /2,(desktop->height() - wm.height()) /2);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("云剪贴板(基于Qt) - v0.1");
   
    MainWindow wm;
    moveCenter(wm);

    qDebug() << "[ClipBoard Server]: " << REMOTE_HOST;
    return a.exec();
}
