import QtQuick 2.0
import QtQuick.Controls 2.15

Rectangle {
    property alias value: chBox.checked
    property alias text: chBox.text
    id: root
    height: 30
    width: 130
    clip: true
    CheckBox {
        id: chBox
        text: "text"
        indicator: Rectangle {
            height: parent.height
            width: parent.height
            border.color: "Black"
            color: chBox.checked ? "Gray" : "White"
        }
    }
}
