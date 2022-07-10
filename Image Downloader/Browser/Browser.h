#ifndef BROWSER_H
#define BROWSER_H

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QAbstractSlider>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>

#include <utility>
#include <set>
#include <algorithm>

#include "Request/Request.h"
#include "Browser/Image.h"

class Browser:public QMainWindow{
    public:
        explicit Browser(QWidget *parent = nullptr);
        ~Browser();
        void resizeEvent(QResizeEvent* event);
        void showImageList();
        void clearResults();

    private Q_SLOTS:
        void searchClicked();
        void downloadClicked();
        void exitClicked();
        void getImageFromURL(QNetworkReply* reply);
    private:
        QLineEdit* searchLine;

        QWidget* resultArea;
        QGridLayout* table;
        QScrollArea* vScroll;

        QPushButton* browser_button;
        QPushButton* search_button;
        QPushButton* download_button;
        QPushButton* cancel_button;
        QPushButton* settings_button;
        QPushButton* history_button;
        QPushButton* info_button;
        QPushButton* exit_button;

        std::vector<std::string> linkList;
        std::vector<Image*> imageList;

        void setElementsPosition();
};

#endif