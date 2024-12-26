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