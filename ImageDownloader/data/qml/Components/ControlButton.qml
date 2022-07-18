import QtQml 2.12
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12

Item {
    id: _root

    property color defaultColor: "#676464"
    property color howeredColor: "#7C7877"

    property int defaultWidth: 60
    property int howeredWidth: 180

    property alias icon: _icon.source
    property alias lable: _text.text

    width: howeredWidth
    height: 60

    Rectangle {
        id: _background

        anchors.left: parent.left
        anchors.top: parent.top

        width: defaultWidth
        height: parent.height
        radius: parent.height / 2

        color: defaultColor

        Image {
            id: _icon

            fillMode: Image.PreserveAspectCrop

            anchors.left: parent.left
            anchors.leftMargin: defaultWidth / 4
            anchors.top: parent.top
            anchors.topMargin: defaultWidth / 4

            width: 30
            height: 30

            source: "qrc:/Images/Icons/home.png"
        }

        Text {
            id: _text

            anchors.left: _icon.right
            anchors.leftMargin: _icon.width / 2
            anchors.verticalCenter: _icon.verticalCenter

            color: "white"
            font.pixelSize: 25
            text: "Home"
            wrapMode: Text.WordWrap

            visible: _mouseArea.containsMouse
        }

        PropertyAnimation {
            id: _widthAnimation

            target: _background
            property: "width"
            to: _mouseArea.containsMouse ? defaultWidth : howeredWidth
            duration: 500
            easing.type: Easing.InOutQuint
        }
    }

    MouseArea {
        id: _mouseArea

        anchors.fill: parent

        hoverEnabled: true
        preventStealing: false
        propagateComposedEvents: true

        onContainsMouseChanged: {
            _widthAnimation.running = false
            _widthAnimation.running = true
        }

        onEntered: _background.color = howeredColor
        onExited: _background.color = defaultColor
    }
}