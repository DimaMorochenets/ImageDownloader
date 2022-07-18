import QtQml 2.0
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.12

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

        onPageChanged: _opacityAnimation.running = true

        PropertyAnimation {
            id: _opacityAnimation

            target: _wallpaper
            property: "backgroundOpacity"
            to: _wallpaper.fadeInOpacity
            duration: 750
            easing.type: Easing.InOutQuint

            onFinished: _wallpaper.image = _mainMenu.currentWallpaper
        }
    }
}
