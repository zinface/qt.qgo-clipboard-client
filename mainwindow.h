
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QSystemTrayIcon>

QT_BEGIN_NAMESPACE
class QClipboard;
class QLabel;
class ClipboardApi;
class QSystemTrayIcon;
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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
    QLabel *previewLabel;
    QString checkTime;
    QString checkData;
    QString checkMime;

    QSystemTrayIcon *systray;


    void updatePreviewImage(int w, int h);

protected:
    void closeEvent(QCloseEvent *event);
    void hideEvent(QHideEvent *event);
    void resizeEvent(QResizeEvent *event);

};


#endif // MAINWINDOW_H

