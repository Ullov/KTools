import QtQuick 2.0
import QtQuick.Controls 2.4

Rectangle {
    id: root
    color: "Black"
    height: decorativeRectangle.height
    width: 500

    ScrollView {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        TextArea {
            id: textField
            background: Rectangle {
                id: decorativeRectangle
                anchors.fill: parent
                height: 20 // To silence warning
                width: 20 // To silence warning
                border.color: "Black"
                border.width: 2
                radius: 4
            }
            font.pixelSize: 18
            font.family: fixedFont.name
            text: "Sample text"
            selectByMouse: true
        }
    }

    FontLoader {
        id: fixedFont
        source: "qrc:/resources/fonts/RobotoMono-Regular.ttf"
    }
}
