import QtQuick 2.0

Rectangle {
    id:encoderRoot;
    width: 800;
    height: 600;
    color:"red";
    Text {
        anchors.centerIn: parent;
        text: qsTr("Encoder")
    }
}

