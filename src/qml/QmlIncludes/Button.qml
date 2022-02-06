import QtQuick 2.0
import QtQuick.Controls 2.2

Rectangle {
    id:root
    property alias text: buttonLabel.text
    property alias textColor: buttonLabel.color
    property alias textWeight: buttonLabel.font.weight
    property alias textSize: buttonLabel.font.pixelSize

    property string onPressedColor: "Black"
    property string onHoveredColor: "Gray"
    property string onPressedBorderColor: "Black"
    property string onHoveredBorderColor: "Black"
    property real onPressedOpacity: 1
    property real onHoveredOpacity: 1
    property alias mouseArea: mouseAreaItem
    width: 100
    height: 40
    border.color: "Black"
    border.width: 1
    radius: 5
    color: "#dadada"
    Text {
        id: buttonLabel
        anchors.centerIn: parent
        text: "Sample text"
        color: "Black"
        font.weight: Font.Normal
        font.pixelSize: 12
    }
    MouseArea {
        id: mouseAreaItem
        anchors.fill: parent
        hoverEnabled: true
    }

    states: [
        State {
            name: "onPressedButtonRectangle"
            when: mouseAreaItem.pressed == true
            PropertyChanges {
                target: root
                color: onPressedColor
                border.color: onPressedBorderColor
                opacity: onPressedOpacity
            }
        },
        State {
            name: "onHoveredButtonRectangle"
            when: mouseAreaItem.containsMouse == true
            PropertyChanges {
                target: root
                color: onHoveredColor
                border.color: onHoveredBorderColor
                opacity: onHoveredOpacity
            }
        }
    ]
}
