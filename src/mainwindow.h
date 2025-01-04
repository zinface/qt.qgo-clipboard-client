
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
class QNotifyManager;
QT_END_NAMESPACE


namespace Ui {
    class MainWindow;
};
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initClipboardMonitor();
    void initSystemTrayIcon();

    enum ClipboardType {
        Image,
        Text,
        File,
    };

    void sendNotify(const QString &text, const float windowOpacity = 1.0);

private:
    Ui::MainWindow *ui;
    ClipboardType currentType = Text;
    QTemporaryFile tempFile;
    QTemporaryDir tempDir;
    bool openTempDir = true;

    QAction *a_copy;
    QAction *a_copy_base64;

    bool m_copyed;

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
    QLabel *preview_image;
    QString checkTime;
    QString checkData;
    QString checkMime;

    QSystemTrayIcon *systray;
    QNotifyManager *notify;


    void updateShowText(QString text, bool center = true);
    void updatePreviewImage(int w, int h);
    

protected:
    void closeEvent(QCloseEvent *event);
    void hideEvent(QHideEvent *event);
    void resizeEvent(QResizeEvent *event);

private slots:
    void on_action_setting_config_triggered();
};


#endif // MAINWINDOW_H

