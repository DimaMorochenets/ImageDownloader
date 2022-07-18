import QtQml 2.12
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.12

Item {
    id: _root

    property alias image: _wallpaper.source
    property alias backgroundOpacity: _shadow.opacity
    property real fadeInOpacity: 1
    property real fadeOutOpacity: 0

    Image {
        id: _wallpaper

        anchors.fill: parent

        source: "qrc:/Images/Wallpapers/home.jpg"

        onSourceChanged: {
            _shadow.opacity = _root.fadeInOpacity
            _opacityAnimation.running = false
            _opacityAnimation.running = true
        }
    }

    Rectangle {
        id: _shadow

        anchors.fill: parent

        color: "#22201F"
        opacity: fadeOutOpacity

        PropertyAnimation {
            id: _opacityAnimation

            target: _shadow
            property: "opacity"
            to: fadeOutOpacity
            duration: 750
            easing.type: Easing.InOutQuint
        }
    }
}
