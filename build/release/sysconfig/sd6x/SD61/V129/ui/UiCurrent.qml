import QtQuick 2.0

Rectangle {
    id:currentRoot;
    width: 800;
    height: 600;
    color:Qt.lighter("red")
    border.color: "red";
    Text {
        anchors.centerIn: parent;
        text: qsTr("Current")
    }
}

