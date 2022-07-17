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

    ColumnLayout {
        id: _buttons

        anchors.top: parent.top + 200
        anchors.left: parent.left + 200

        spacing: 25

        ControlButton {
            id: _homeButton

            icon: "qrc:/Images/Icons/home.png"
        }

        ControlButton {
            id: _historyButton

            icon: "qrc:/Images/Icons/history.png"
        }

        ControlButton {
            id: _settingsButton

            icon: "qrc:/Images/Icons/settings.png"
        }

        ControlButton {
            id: _infoButton

            icon: "qrc:/Images/Icons/info.png"
        }

        ControlButton {
            id: _exitButton

            icon: "qrc:/Images/Icons/exit.png"
        }
    }
}