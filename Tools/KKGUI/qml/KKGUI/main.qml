import QtQuick 2.0

Rectangle {
    width: 1024
    height: 768
    color: "#ffffff"
    visible: true
    Text {
        text: qsTr("Hello World")
        anchors.centerIn: parent
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }

    TextEdit {
        id: text_edit1
        x: 69
        y: 63
        width: 80
        height: 20
        text: qsTr("aaaaaaaa")
        font.pixelSize: 12
    }
}
