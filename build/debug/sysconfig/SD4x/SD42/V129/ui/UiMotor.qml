import QtQuick 2.0
import QtCppClass 1.0

Rectangle {
    id:motorRoot;
    width: 800;
    height: 600;
    color:"blue";
    Text {
        anchors.centerIn: parent;
        text: qsTr("Motor")
    }
    Rectangle{
        x:100;
        y:100;
        color:"red";
        width: 50;
        height: 30;
        MouseArea{
            anchors.fill: parent;
            property bool flag: false;
            onClicked: {
                flag=!flag;
                if(flag)
                    parent.color="yellow";
                else
                    parent.color="red";
                cDevice.qmlTest();
            }
        }
    }
}

