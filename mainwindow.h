
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QSystemTrayIcon>
#include <QTemporaryFile>
#include <QTemporaryDir>

QT_BEGIN_NAMESPACE
class QClipboard;
class QLabel;
class ClipboardApi;
class QSystemTrayIcon;
QT_END_NAMESPACE

namespace Ui {
    class MainWindow;
};
class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    enum ClipboardType {
        Image,
        Text,
        File,
    };

private:
    Ui::MainWindow *ui;
    ClipboardType currentType = Text;
    QTemporaryFile tempFile;
    QTemporaryDir tempDir;
    bool openTempDir = true;

public slots:
    void clipboardChanged();
    void clipboardCopy();
    void clipboardCopyBase64();
    void onClipboardCheckLatest();
    void onClipboardUpdate();
    void onSysTrayActivated(QSystemTrayIcon::ActivationReason reason);

private:
    QClipboard *clipboard;
    ClipboardApi *clipboardApi;
    QLabel *image;
    QString checkTime;
    QString checkData;
    QString checkMime;

    QSystemTrayIcon *systray;


    void updateShowText(QString text);
    void updatePreviewImage(int w, int h);

protected:
    void closeEvent(QCloseEvent *event);
    void hideEvent(QHideEvent *event);
    void resizeEvent(QResizeEvent *event);

};


#endif // MAINWINDOW_H

