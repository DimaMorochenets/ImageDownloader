import QtQuick 2.10
import QtQml 2.0
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

ApplicationWindow {
    id: window

    minimumWidth: WIDTH
    minimumHeight: HEIGTH
    visibility: FULLSCREEN ? "FullScreen" : "Windowed"
    visible: true

    title: "Image Downloader"
}