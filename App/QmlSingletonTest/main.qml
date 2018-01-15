import QtQuick 2.5

import Resource 1.0

//import QtQuick.Window 2.0
//Window {
//    width: 400;
//    height: 600;
//    visible: true

//    MouseArea {
//        anchors.fill: parent
//        onClicked: {
//            console.info("aaaaa ");
//        }
//    }

//    Text {
//        text: Res.StyleRes.language;
//        anchors.centerIn: parent
//    }
//}

Rectangle {
    width: 400;
    height: 600;
    visible: true

    MouseArea {
        anchors.fill: parent
        onClicked: {
            console.info("aaaaa ");
        }
    }

    Text {
//        text: StyleRes.language;
        text: StyleRes.language;
        anchors.centerIn: parent
    }
}

