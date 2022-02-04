import QtQuick 2.0

TextEdit {
    id: root
    text: "Sample"
    width: root.contentWidth

    readOnly: true
    selectByMouse: true

    color: "Black"
    horizontalAlignment: Text.AlignLeft
    verticalAlignment: Text.AlignVCenter
    font.pixelSize: 12
    font.family: "Segoe UI"
}
