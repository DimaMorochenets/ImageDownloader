#ifndef IMAGE_H
#define IMAGE_H

#include <QtWidgets/QLabel>
#include <QtCore/QString>
#include <QtCore/QSize>
#include <QtGui/QMouseEvent>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>


class Image : public QLabel{
    Q_OBJECT
    public:
        explicit Image(QWidget* parent = nullptr);
        explicit Image(const QString& text = "", QWidget* parent = nullptr);

        void setURL(const QUrl& URL);
        void setOriginSize(const QSize& oSize);
        QUrl getURL();
        QSize getOriginSize();
        bool isMarked() {return mark;}

        
        void mouseReleaseEvent(QMouseEvent* event);
        void mouseDoubleClickEvent(QMouseEvent* event);
        void showOriginImage();

    private Q_SLOTS:
        void getImageFromURL(QNetworkReply* reply);

    private:
        QUrl url;
        QSize originSize;
        bool mark;
};

#endif