import QtQml 2.0
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "."

Item {
    id: _root

    property string currentWallpaper: "qrc:/Images/Icons/home.png"

    signal pageChanged

    width: 120
    height: 450

    ColumnLayout {
        id: _buttons

        spacing: 25

        ControlButton {
            id: _homeButton

            icon: "qrc:/Images/Icons/home.png"
            lable: "Home"
            wallpaperSource: "qrc:/Images/Wallpapers/home.jpg"

            onButtonClicked: {
                currentWallpaper = wallpaperSource
                _root.pageChanged()
            }
        }

        ControlButton {
            id: _historyButton

            icon: "qrc:/Images/Icons/history.png"
            lable: "History"
            wallpaperSource: "qrc:/Images/Wallpapers/history.jpg"

            onButtonClicked: {
                currentWallpaper = wallpaperSource
                _root.pageChanged()
            }
        }

        ControlButton {
            id: _settingsButton

            icon: "qrc:/Images/Icons/settings.png"
            lable: "Settings"
            wallpaperSource: "qrc:/Images/Wallpapers/settings.jpg"

            onButtonClicked: {
                currentWallpaper = wallpaperSource
                _root.pageChanged()
            }
        }

        ControlButton {
            id: _infoButton

            icon: "qrc:/Images/Icons/info.png"
            lable: "Info"
            wallpaperSource: "qrc:/Images/Wallpapers/info.jpg"

            onButtonClicked: {
                currentWallpaper = wallpaperSource
                _root.pageChanged()
            }
        }

        ControlButton {
            id: _exitButton

            icon: "qrc:/Images/Icons/exit.png"
            lable: "Exit"

            onButtonClicked: {
                console.log("Exiting from application!")
                Qt.quit()
            }
        }
    }
}