import QtQuick 2.0

Rectangle {
    id:statusRoot;
    width: 800;
    height: 600;
    color:"lightgreen";
    Text {
        anchors.centerIn: parent;
        text: qsTr("Status")
    }
}

