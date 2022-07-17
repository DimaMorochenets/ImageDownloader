import QtQml 2.12
import QtQuick 2.12
import QtQuick.Controls 2.12

Item {
    id: _root

    property alias icon: _icon.source

    width: 100
    height: 100

    Button {
        anchors.fill: parent

        Image {
            id: _icon

            fillMode: Image.PreserveAspectCrop

            anchors.centerIn: parent

            width: 45
            height: 45

            source: "qrc:/Images/Icons/home.png"
        }

        background: Rectangle {
            color: parent.down ? "#423838" : "#676464"
        }
    }
}