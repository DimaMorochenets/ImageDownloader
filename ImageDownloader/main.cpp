#include "Browser/Browser.h"

int main(int argc, char** argv)
{
    QApplication ImageDownloader(argc, argv);
    ImageDownloader.setApplicationName("Images Downloader");

    Browser browser;
    browser.show();
    
    return ImageDownloader.exec();
}