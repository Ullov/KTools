import QtQuick 2.0
import QtQuick.Controls 2.15

Rectangle {
    property alias value: chBox.checked
    property alias text: chBox.text
    id: root
    height: 25
    width: 130
    clip: true
    CheckBox {
        id: chBox
        text: "text"
        indicator: Rectangle {
            id: checkRect
            height: 20
            width: 20
            border.color: "Black"
            color: chBox.checked ? "Gray" : "White"
        }
        contentItem: Text {
            anchors.left: checkRect.right
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.margins: 5
            text: chBox.text
            font.pixelSize: 12
            opacity: enabled ? 1.0 : 0.3
            verticalAlignment: Text.AlignVCenter
        }
    }
}
