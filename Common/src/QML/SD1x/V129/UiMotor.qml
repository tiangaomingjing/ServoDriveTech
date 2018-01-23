import QtQuick 2.0
import QtCppClass 1.0
import MyQmlStyle 1.0

Rectangle {
    id:motorRoot;
    property UiMotorStyle uiStyle: m_styleLoader.iStyle;
    width: 800;
    height: 600;
    color:uiStyle.backgroundColor;
    Text {
        anchors.centerIn: parent;
        text: qsTr("Motor")
    }
    Rectangle{
        x:100;
        y:100;
        color:uiStyle.buttonBackgroundColor;
        width: 50;
        height: 30;
        radius: uiStyle.buttonBorderRadius;
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
    StyleLoader{
        id:m_styleLoader;
        target:"UiMotorStyle";
    }
}

