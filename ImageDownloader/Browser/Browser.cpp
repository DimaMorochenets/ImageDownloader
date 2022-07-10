#include "Browser/Browser.h"
#include "Downloader/Downloader.h"

Browser::Browser(QWidget* parent):QMainWindow(parent)
{
    this->resize(1024, 720);

    searchLine = new QLineEdit(this);

    browser_button     = new QPushButton("Browser", this);
    settings_button    = new QPushButton("Settings", this);
    history_button     = new QPushButton("History", this);
    info_button        = new QPushButton("Info", this);
    search_button      = new QPushButton("Search", this);
    download_button    = new QPushButton("Download", this);
    cancel_button      = new QPushButton("Cancel", this);
    exit_button        = new QPushButton("Exit", this);

    vScroll = new QScrollArea(this);
    vScroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vScroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    vScroll->setVisible(false);
    resultArea = new QWidget(vScroll);
    table = new QGridLayout(resultArea);

    setElementsPosition();

    connect(search_button, &QPushButton::clicked, this, &Browser::searchClicked);
    connect(download_button, &QPushButton::clicked, this, &Browser::downloadClicked);
    connect(exit_button, &QPushButton::clicked, this, &Browser::exitClicked);
}

void Browser::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    setElementsPosition();
}

void Browser::setElementsPosition()
{
    browser_button->move(25, 25);
    browser_button->resize(200, 100);

    settings_button->move(25, 150);
    settings_button->resize(200, 100);

    history_button->move(25, 275);
    history_button->resize(200, 100);

    info_button->move(25, 400);
    info_button->resize(200, 100);

    searchLine->move(browser_button->width() + 50, 25);
    searchLine->resize(this->width() - browser_button->width() - 175, 50);

    search_button->move(this->width() - 125, 25);
    search_button->resize(100, 50);

    download_button->move(this->width() - 300, this->height() - 50);
    download_button->resize(100, 50);

    cancel_button->move(this->width() - 200, this->height() - 50);
    cancel_button->resize(100, 50);

    exit_button->move(this->width() - 100, this->height() - 50);
    exit_button->resize(100, 50);

    if(!imageList.empty())
        showImageList();
}

void Browser::searchClicked()
{
    clearResults();

    //request
    std::string keyWords = searchLine->text().toUtf8().constData();
    Request request;
    request.setKey(keyWords);
    if(!request.sendRequest()){
        QMessageBox::warning(this, "Request result", "Search query has no result!");
        return;
    }
    linkList = request.getLinksList();

    //display images
    QUrl curURL;
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &Browser::getImageFromURL);
    for(const auto& i:linkList){
        curURL = QString(i.c_str());
        manager->get(QNetworkRequest(curURL));
    }
}

void Browser::getImageFromURL(QNetworkReply* reply)
{
    if(reply->error() != QNetworkReply::NoError)
        return;

    QPixmap data;
    data.loadFromData(QByteArray(reply->readAll()));
    if(!data.isNull()){
        Image* image = new Image(resultArea);
        image->setURL(reply->url());
        image->setOriginSize(data.size());
        data = data.scaled(QSize(200, 200), Qt::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation);
        image->setPixmap(data);
        image->setAlignment(Qt::AlignCenter);
        imageList.push_back(image);
    }
    showImageList();
}

void Browser::showImageList()
{   
    int left = browser_button->width() + 50;
    int top = searchLine->height() + 50;
    int width = this->width() - browser_button->width() - 75;
    int height = this->height()  - 150;
    
    int i = 0, max_i = height / 200;
    int j = 0, max_j = width / 200;

    for(const auto& image:imageList){
        if(j == max_j) { i++; j = 0; }
        table->addWidget(image, i, j);
        j++;
    } 

    vScroll->setWidgetResizable(true);
    vScroll->resize(width, height);
    vScroll->move(left, top);
    vScroll->setWidget(resultArea);
    vScroll->setVisible(true);
    resultArea->setLayout(table);
}

void Browser::clearResults()
{
    QList<Image*> children = resultArea->findChildren<Image*>();
    while(children.count()){
        if(!children.count())
            break;
        delete children.at(0);
        children = resultArea->findChildren<Image*>();
    }
    resultArea->update();
    linkList.clear();
    imageList.clear();
}

void Browser::downloadClicked()
{
    std::vector<std::string> downloadImages;
    for(const auto& image:imageList){
        if(!image->isMarked())
            continue;
        
        downloadImages.push_back(image->getURL().toString().toUtf8().constData());
    }
    if(downloadImages.empty())
        return;
    
    Downloader downloader(downloadImages);
    downloader.DownloadAll();
}

void Browser::exitClicked()
{
    this->close();
}

Browser::~Browser(){}