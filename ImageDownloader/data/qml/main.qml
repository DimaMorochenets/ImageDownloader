import QtQml 2.0
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtMultimedia 5.12

import "Components"

ApplicationWindow {
    id: window

    minimumWidth: WIDTH
    minimumHeight: HEIGTH
    visibility: FULLSCREEN ? "FullScreen" : "Windowed"
    visible: true

    title: "Image Downloader"

    Wallpaper {
        id: wallpaper

        anchors.fill: parent
    }
}