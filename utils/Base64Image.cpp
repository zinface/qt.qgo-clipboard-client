#ifndef __BASE64IMAGE__H__
#define __BASE64IMAGE__H__

#include <QImage>
#include <QPixmap>
#include <QBuffer>

class Base64Image {
public:
    static QImage formBase64(QString base64) {
        QPixmap image;
        image.loadFromData(QByteArray::fromBase64(base64.toLocal8Bit()));
        return image.toImage();
    }

    static QString fromImage(const QImage &image) {
        QByteArray imageData;
        QBuffer buffer(&imageData);

        image.save(&buffer, "png");
        return imageData.toBase64();
    }
};

class Base64Pixmap{
public:
    static QPixmap formBase64(QString base64) {
        QPixmap image;
        image.loadFromData(QByteArray::fromBase64(base64.toLocal8Bit()));
        return image;
    }

    static QString fromImage(const QPixmap &image) {
        return Base64Image::fromImage(image.toImage());
    }
};

class Base64Text {
    public:
    static QString fromBase64(QString base64) {
        return QByteArray::fromBase64(base64.toLocal8Bit());
    }

    static QString fromText(QString text) {
        return text.toLocal8Bit().toBase64();
    }
};

#endif  //!__BASE64IMAGE__H__