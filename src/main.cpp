
#include "global/global.h"
#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <QDesktopWidget>
#include <QMainWindow>

#include "config.h"
#include <screenutil.h>
#include <version.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("qgo-clipboard-client");
    a.setApplicationDisplayName("云剪贴板(基于Qt) - v" PROJECT_VERSION);
    a.setApplicationVersion(PROJECT_VERSION);

    MainWindow wm;
    wm.show();

    ScreenUtil::moveCenterForCursor(wm);

    qDebug() << "[ClipBoard Server]: " << REMOTE_HOST << ", But Config:" << GL.getAddress();
    return a.exec();
}
