
#include "mainwindow.h"
#include <QClipboard>
#include <QApplication>
#include <QImage>
#include <QPainter>
#include <QTextStream>
#include <QLabel>
#include <QPicture>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMenu>
#include "utils/Base64Image.cpp"
#include "backend/clipboardApi.h"
#include <QTimer>
#include <QSystemTrayIcon>
#include <QCloseEvent>


MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
, previewLabel(new QLabel(this))
{
    clipboard = qApp->clipboard();
    clipboardApi = new ClipboardApi;
    systray = new QSystemTrayIcon(this);


    connect(clipboard, &QClipboard::dataChanged, this, &MainWindow::clipboardChanged);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(previewLabel);

    QAction *a_copy = new QAction("复制");
    QAction *a_copy_base64 = new QAction("复制为Base64");
    connect(a_copy, &QAction::triggered, this, &MainWindow::clipboardCopy);
    connect(a_copy_base64, &QAction::triggered, this, &MainWindow::clipboardCopyBase64);

    previewLabel->addAction(a_copy);
    previewLabel->addAction(a_copy_base64);
    previewLabel->setContextMenuPolicy(Qt::ContextMenuPolicy::ActionsContextMenu);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::onClipboardCheckLatest);
    // ms
    timer->setInterval(1000 * 3);
    timer->start();

    // Systray 
    QAction *showWindow = new QAction("显示窗口");
    connect(showWindow, SIGNAL(triggered()), this, SLOT(show()));
    QAction *quitAction = new QAction("退出");
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    QMenu *menu = new QMenu();
    menu->addAction(a_copy);
    menu->addAction(a_copy_base64);
    menu->addAction(showWindow);
    menu->addAction(quitAction);
    
    systray->setIcon(QIcon(":/systray.png"));
    systray->setContextMenu(menu);
    systray->show();
    
    connect(systray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(onSysTrayActivated(QSystemTrayIcon::ActivationReason)));
    
    // resize
    resize(400, 300);
}

MainWindow::~MainWindow()
{
    
}

/**
 * @brief  监听剪贴板变化
 * @note   
 * @retval None
 */
void MainWindow::clipboardChanged()
{
    // 获取剪贴板文本数据
    QString text = clipboard->text();
    if (!text.isEmpty()) {
        if (text.compare(checkData) == 0) {
            return;
        }
        checkData = text;
        clipboardApi->set("text", Base64Text::fromText(text));
        return;
    }

    // 获取剪贴板图片数据
    QImage img = clipboard->image();
    if (img.isNull()) {
            QTextStream(stdout) << __FUNCTION__ << 
                QString("") << "\n";
        return;
    }

    int imgW = img.width();
    int imgH = img.height();

    QTextStream(stdout) << __FUNCTION__ << 
        QString("Image: %1x%2\n").arg(imgW).arg(imgH);
    previewLabel->setFixedWidth(imgW);
    previewLabel->setFixedHeight(imgH);
    previewLabel->setPixmap(QPixmap::fromImage(img));

    clipboardApi->set("image", Base64Pixmap::fromImage(QPixmap::fromImage(img)));
    checkData = Base64Pixmap::fromImage(QPixmap::fromImage(img));
}

void MainWindow::clipboardCopy()
{
    QPixmap pixmap = previewLabel->pixmap(Qt::ReturnByValueConstant::ReturnByValue);
    clipboard->setPixmap(pixmap);
}

void MainWindow::clipboardCopyBase64()
{
    QPixmap pixmap = previewLabel->pixmap(Qt::ReturnByValueConstant::ReturnByValue);
    clipboard->setText(Base64Pixmap::fromImage(pixmap));
}

/**
 * @brief  获取云剪贴板状态信息
 * @note   
 * @retval None
 */
void MainWindow::onClipboardCheckLatest()
{
    auto object = clipboardApi->info();
    if (object.contains("create_at")) {
        if (object.value("create_at").toString().compare(checkTime) != 0) {
            onClipboardUpdate();
        }
    }
}

/**
 * @brief  同步云端状态到本地
 * @note   
 * @retval None
 */
void MainWindow::onClipboardUpdate()
{
    auto object = clipboardApi->get();

    // 存储云端时间状态
    if (object.contains("create_at")) {
        QString latestTime = object.value("create_at").toString();

        // 时间未变不更新
        if (checkTime.compare(latestTime) == 0) {
            return;
        }

        checkTime = latestTime;
    }

    // 存储云端最新数据
    if (object.contains("mime")) {
        // 获取数据类型
        QString mime = object.value("mime").toString();
        
        QTextStream(stdout) << __FUNCTION__ << 
            QString(": MineType = %1\n").arg(mime);

        if (object.value("mime").toString().compare("image") == 0) {
            auto data = object.value("data").toString().replace(" ", "+");
            
            if (checkData.compare(data) != 0) {
                clipboard->setImage(Base64Image::formBase64(data));
            }

            return;
        }

        if (object.value("mime").toString().compare("text") == 0) {
            auto data = object.value("data").toString().replace(" ", "+");
            QTextStream(stdout) << "Update:" << data << " -> " << Base64Text::fromBase64(data) << "\n";
            if (checkData.compare(Base64Text::fromBase64(data)) != 0) {
                clipboard->setText(Base64Text::fromBase64(data));
            }
            return;
        }
    }
}

void MainWindow::onSysTrayActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {

        case QSystemTrayIcon::ActivationReason::Unknown:
            break;
        case QSystemTrayIcon::ActivationReason::Context:
            break;
        case QSystemTrayIcon::ActivationReason::DoubleClick:
            this->showNormal();
            break;
        case QSystemTrayIcon::ActivationReason::Trigger:
            this->showNormal();
            break;
        case QSystemTrayIcon::ActivationReason::MiddleClick:
            break;
        default:
            break;
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (systray->isVisible()) {
        hide();
        event->ignore();
    }
}

void MainWindow::hideEvent(QHideEvent *event)
{
    if (systray->isVisible()) {
        hide();
        event->ignore();
    }
}



// void    clear(QClipboard::Mode mode = Clipboard)
// QImage    image(QClipboard::Mode mode = Clipboard) const
// const QMimeData *    mimeData(QClipboard::Mode mode = Clipboard) const
// bool    ownsClipboard() const
// bool    ownsFindBuffer() const
// bool    ownsSelection() const
// QPixmap    pixmap(QClipboard::Mode mode = Clipboard) const
// void    setImage(const QImage &image, QClipboard::Mode mode = Clipboard)
// void    setMimeData(QMimeData *src, QClipboard::Mode mode = Clipboard)
// void    setPixmap(const QPixmap &pixmap, QClipboard::Mode mode = Clipboard)
// void    setText(const QString &text, QClipboard::Mode mode = Clipboard)
// bool    supportsFindBuffer() const
// bool    supportsSelection() const
// QString    text(QClipboard::Mode mode = Clipboard) const
// QString    text(QString &subtype, QClipboard::Mode mode = Clipboard) const
