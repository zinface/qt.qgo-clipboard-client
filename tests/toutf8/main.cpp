#include <QCoreApplication>
#include <qtextcodec.h>
#include "qd.h"
#include "../src/utils/Base64Image.cpp"
int main(int argc, char *argv[]) {
    
    QCoreApplication a(argc, argv);
    
    QTextCodec *utf8 = QTextCodec::codecForName("UTF-8");
    QTextCodec *gbk = QTextCodec::codecForName("GBK");

    qd << "QString -> Base64";
    QString s = "获取剪贴板图片数据";
    qd << s 
        << Base64Text::fromText(s);

    qd << "QString -> GBK -> Base64";
    qd << s 
        << gbk->fromUnicode(s.toUtf8()) 
        << gbk->fromUnicode(s.toUtf8()).toBase64();
    // qd << s.toLocal8Bit().toBase64();
    // qd << codec->fromUnicode(s.toLocal8Bit()).toBase64();

    // 6I635Y+W5Ymq6LS05p2/5Zu+54mH5pWw5o2u
    qd << "Base64 -> QString";
    s = "6I635Y+W5Ymq6LS05p2/5Zu+54mH5pWw5o2u";
    qd << s 
        << Base64Text::fromBase64(s);

    // u/HIobz0zPmw5c28xqzK/b7d
    qd << "Base64 -> GBK -> QString";
    s = "u/HIobz0zPmw5c28xqzK/b7d";
    qd << s 
        << Base64Text::fromBase64(s) 
        // << gbk->toUnicode(Base64ByteArray::fromBase64(s))
        << gbk->toUnicode(QByteArray::fromBase64(s.toUtf8()));

}


// main(12): DEBUG  QString -> Base64
// main(14): DEBUG  获取剪贴板图片数据 6I635Y+W5Ymq6LS05p2/5Zu+54mH5pWw5o2u
// main(17): DEBUG  QString -> GBK -> Base64
// main(18): DEBUG  获取剪贴板图片数据 ��ȡ������ͼƬ���� u/HIobz0zPmw5c28xqzK/b7d
// main(25): DEBUG  Base64 -> QString
// main(27): DEBUG  6I635Y+W5Ymq6LS05p2/5Zu+54mH5pWw5o2u 获取剪贴板图片数据
// main(31): DEBUG  Base64 -> GBK -> QString
// main(33): DEBUG  u/HIobz0zPmw5c28xqzK/b7d ��ȡ������ͼƬ���� 获取剪贴板图片数据

