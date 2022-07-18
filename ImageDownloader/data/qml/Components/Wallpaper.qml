import QtQml 2.12
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtMultimedia 5.12

Item {
    id: _root

    property alias image: _wallpaper.source

    Image {
        id: _wallpaper

        anchors.fill: parent

        source: "qrc:/Images/Wallpapers/home.jpg"
    }
}