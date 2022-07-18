import QtQml 2.0
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtMultimedia 5.12

import "Components"

ApplicationWindow {
    id: _window

    minimumWidth: WIDTH
    minimumHeight: HEIGTH
    visibility: FULLSCREEN ? "FullScreen" : "Windowed"
    visible: true

    title: "Image Downloader"

    Wallpaper {
        id: _wallpaper

        anchors.fill: parent
    }

    MainMenu {
        id: _mainMenu

        anchors.top: parent.top
        anchors.topMargin: 25
        anchors.left: parent.left
        anchors.leftMargin: 25

        onPageChanged: _wallpaper.image = _mainMenu.currentWallpaper
    }
}