
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QClipboard>
#include <QApplication>
#include <QImage>
#include <QPainter>
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
#include <QFileInfo>
#include <QMimeData>
#include <QDesktopServices>
#include <qd.h>

#include "view/configdialog.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , preview_image(new QLabel())
    , a_copy(new QAction("复制"))
    , a_copy_base64(new QAction("复制为Base64"))
    , m_copyed(false)
{
    ui->setupUi(this);

    clipboard = qApp->clipboard();
    clipboardApi = new ClipboardApi;
    systray = new QSystemTrayIcon(this);

    connect(clipboard, &QClipboard::dataChanged, this, &MainWindow::clipboardChanged);
    connect(a_copy, &QAction::triggered, this, &MainWindow::clipboardCopy);
    connect(a_copy_base64, &QAction::triggered, this, &MainWindow::clipboardCopyBase64);

    ui->label->addAction(a_copy);
    ui->label->addAction(a_copy_base64);
    ui->label->setContextMenuPolicy(Qt::ContextMenuPolicy::ActionsContextMenu);

    // Check Server
    initClipboardMonitor();

    // Systray 
    initSystemTrayIcon();

    // resize
    resize(400, 300);
}

MainWindow::~MainWindow()
{

}

void MainWindow::initClipboardMonitor()
{
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::onClipboardCheckLatest);
    // ms
    timer->setInterval(1000 * 3);
    timer->start();
}

void MainWindow::initSystemTrayIcon()
{
    QAction *showWindow = new QAction("显示窗口");
    connect(showWindow, SIGNAL(triggered()), this, SLOT(show()));
    QAction *quitAction = new QAction("退出");
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    QAction *autoOpenTempDirAction = new QAction("关闭自动打开目录");
    connect(autoOpenTempDirAction, &QAction::triggered, this, [=](){
        openTempDir = !openTempDir;
        autoOpenTempDirAction->setText(
            openTempDir?"关闭自动打开目录":"自动打开目录"
        );
    });

    QMenu *menu = new QMenu();
    menu->addAction(a_copy);
    menu->addAction(a_copy_base64);
    menu->addAction(autoOpenTempDirAction);
    menu->addAction(showWindow);
    menu->addAction(quitAction);

    systray->setIcon(QIcon(":/systray.png"));
    systray->setContextMenu(menu);
    systray->show();

    connect(systray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(onSysTrayActivated(QSystemTrayIcon::ActivationReason)));

}

/**
 * @brief  监听剪贴板变化
 * @note   
 * @retval None
 */
void MainWindow::clipboardChanged()
{
    if (m_copyed)
    {
        m_copyed = false;
        return;
    }

    // 获取剪贴板文本数据
    const QMimeData *data = clipboard->mimeData();
    auto atext = data->hasText();
    auto aimage =  data->hasImage();

    QString text = data->text();
    if (atext) {
        if (text.toUtf8().toBase64().compare(checkData.toUtf8()) == 0) {
            return;
        }

        {
            // 检查文件是否存在
            // file:// 开头的使用 QUrl 转本地文件路径
            // 本地文件路径是文件并且文件大小小于 5mb 将进入检查阶段
            QString filePath = text;
            if (filePath.startsWith("file://")) {
                filePath = QUrl(text).toLocalFile();
            }

            QFileInfo f(filePath);
            int max = 1     * 1024 * 1024 * 5;  // 5mb 大小
            //        ^byte   ^k     ^m

            if (f.exists(filePath) && f.isFile() && f.size() < max) {
                QString mime = QString("file/%1").arg(f.fileName());
                if (mime.compare(checkData) == 0) return;

                QFile file(f.absoluteFilePath());
                file.open(QIODevice::ReadOnly);
                auto byteArray = file.readAll();
                file.close();

                clipboardApi->set(mime, byteArray.toBase64());
                updateShowText(QString("(%1)(%2)\n(%3)").arg(f.fileName()).arg(f.size()).arg(mime));

                currentType = File;
                checkData = Base64Text::fromText(mime);
                return;
            }
        }

        qd << "Api: set text";
        checkData = text.toUtf8().toBase64();
        clipboardApi->set("text", checkData);
        updateShowText(text);

        return;
    }

    // 获取剪贴板图片数据
    QImage img = clipboard->image();
    if (aimage && img.isNull() == false) {
        int imgW = img.width();
        int imgH = img.height();

        qd << QString("Image: %1x%2").arg(imgW).arg(imgH);
        preview_image->setFixedWidth(imgW);
        preview_image->setFixedHeight(imgH);
        preview_image->setPixmap(QPixmap::fromImage(img));

        updatePreviewImage(width(), height());

        qd << "Api: set image";
        clipboardApi->set("image", Base64Pixmap::fromImage(QPixmap::fromImage(img)));
        checkData = Base64Pixmap::fromImage(QPixmap::fromImage(img));
    }
}

/**
 * @brief 菜单：复制
 */
void MainWindow::clipboardCopy()
{
#if (QT_VERSION < QT_VERSION_CHECK(5, 15, 0))
    QPixmap pixmap = *image->pixmap();
#else
    QPixmap pixmap = preview_image->pixmap(Qt::ReturnByValueConstant::ReturnByValue);
#endif
    m_copyed = true;
    clipboard->setPixmap(pixmap);
}

/**
 * @brief 菜单：复制 base64
 */
void MainWindow::clipboardCopyBase64()
{
#if (QT_VERSION < QT_VERSION_CHECK(5, 15, 0))
    QPixmap pixmap = *image->pixmap();
#else
    QPixmap pixmap = preview_image->pixmap(Qt::ReturnByValueConstant::ReturnByValue);
#endif
    m_copyed = true;
    clipboard->setText(Base64Pixmap::fromImage(pixmap));
}

/**
 * @brief  获取云剪贴板状态信息
 * @note   
 * @retval None
 */
void MainWindow::onClipboardCheckLatest()
{
    auto resp = clipboardApi->info();
    auto object = resp.toMap();

    qd << resp.toJson();
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
    auto resp = clipboardApi->get();
    auto object = resp.toMap();

    // 存储云端时间状态
    if (object.contains("create_at")) {
        QString latestTime = object.value("create_at").toString();

        // 时间未变不更新
        if (checkTime.compare(latestTime) == 0) {
            return;
        }

        checkTime = latestTime;
    }

    m_copyed = true;

    // 存储云端最新数据
    if (object.contains("mime")) {
        // 获取数据类型
        QString mime = object.value("mime").toString();
        
        qd << QString("MineType = %1").arg(mime);

        // is image
        if (object.value("mime").toString().compare("image") == 0) {
            auto data = object.value("data").toString().replace(" ", "+");
            
            if (checkData.compare(data) != 0) {
                QImage img = Base64Image::formBase64(data);
                preview_image->setPixmap(QPixmap::fromImage(img));
                checkData = Base64Pixmap::fromImage(QPixmap::fromImage(img));
                updatePreviewImage(img.width(),img.height());
                clipboard->setImage(img);
            }

            return;
        }

        // is text
        if (object.value("mime").toString().compare("text") == 0) {
            auto data = object.value("data").toString().replace(" ", "+");
            qd << "Update:" << data << " -> " << Base64Text::fromBase64(data);
            if (checkData.compare(data) != 0) {
                clipboard->setText(QString::fromUtf8(Base64Text::fromBase64(data).toUtf8()));
                updateShowText(Base64Text::fromBase64(data));
            }
            return;
        }

        // is mine
        if (object.value("mime").toString().startsWith("file/")) {
            auto data = object.value("data").toString().replace(" ", "+");
            qd << "Update:" << mime;

            QString fileName = mime.split("/").at(1);

            QString clipText = clipboard->text();
            if (clipText.contains(fileName)) {
                return;
            }

            if (checkData.compare(data) != 0) {
                QString filePath = tempDir.filePath(fileName);
                qd << "filePath:" << filePath;

                if (openTempDir) {
                    QDesktopServices::openUrl(QUrl(tempDir.path()));
                }

                QFile file(filePath);
                file.open(QIODevice::WriteOnly);
                file.write(Base64ByteArray::fromBase64(data));
                file.close();

                QFileInfo f(filePath);

                auto mimeData = new QMimeData();
                mimeData->setData("text/uri-list", filePath.toUtf8());
                clipboard->setMimeData(mimeData);

                updateShowText(QString("(%1)(%2)\n(%3)").arg(fileName).arg(f.size()).arg(filePath));
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

void MainWindow::updateShowText(QString text)
{
    ui->label->setText(text);
    currentType = Text;
}

void MainWindow::updatePreviewImage(int w, int h)
{
    ui->label->setMinimumSize(10, 10);
#if (QT_VERSION < QT_VERSION_CHECK(5, 15, 0))
    QPixmap imagePixmap = *image->pixmap();
#else
    QPixmap imagePixmap = preview_image->pixmap(Qt::ReturnByValueConstant::ReturnByValue);
#endif
    if (imagePixmap.isNull()) {
        return;
    }

    QPixmap temp;
    bool doScale = false;
    if (imagePixmap.width() > w || imagePixmap.height() > h) {
        temp = imagePixmap.scaled(w, h, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    } else {
        temp = imagePixmap;
    }
    ui->label->setPixmap(temp);
    ui->label->setAlignment(Qt::AlignmentFlag::AlignCenter);
    currentType = Image;
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

void MainWindow::resizeEvent(QResizeEvent *event)
{
    int w = event->size().width();
    int h = event->size().height();

    if (currentType == Image)
        updatePreviewImage(w, h);
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

void MainWindow::on_action_setting_config_triggered()
{
    ConfigDialog dialog;
    dialog.setWindowTitle("设置服务器地址");
    dialog.exec();
}

