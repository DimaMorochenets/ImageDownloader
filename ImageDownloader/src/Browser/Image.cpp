#include "src/Browser/Image.h"

Image::Image(QWidget* parent):QLabel(parent), mark(false){}
Image::Image(const QString& text, QWidget* parent):QLabel(parent), mark(false) {setText(text);}

void Image::setURL(const QUrl& URL) {url = URL;}
void Image::setOriginSize(const QSize& oSize) {originSize = oSize;}
QUrl Image::getURL() {return url;}
QSize Image::getOriginSize() {return originSize;}

void Image::mouseReleaseEvent(QMouseEvent* event)
{   
    if(event->type() != QMouseEvent::MouseButtonRelease)
        return;

    if(event->button() == Qt::LeftButton){
        if (this->styleSheet().isEmpty()){
            this->setStyleSheet("QLabel { background-color : green; }");
            this->mark = true;
        }
        else{
            this->setStyleSheet("");
            this->mark = false;
        }
    }
}

void Image::mouseDoubleClickEvent(QMouseEvent* event)
{
    if(event->type() != QMouseEvent::MouseButtonDblClick)
        return;

    if(event->button() == Qt::LeftButton)
        showOriginImage(); 
}

void Image::showOriginImage()
{
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &Image::getImageFromURL);
    manager->get(QNetworkRequest(this->url));
}

void Image::getImageFromURL(QNetworkReply* reply)
{
    if(reply->error() != QNetworkReply::NoError)
        return;

    QPixmap data;
    data.loadFromData(QByteArray(reply->readAll()));
    if(!data.isNull()){
        QLabel* image = new QLabel(url.userName(), nullptr);
        image->setPixmap(data);
        image->setAlignment(Qt::AlignCenter);
        image->resize(this->originSize);
        image->show();
    }
}