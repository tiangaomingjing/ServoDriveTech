import QtQuick 2.5
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
        id:testBtnRect;
        x:100;
        y:100;
        color:testBtn.containsPress?uiStyle.buttonPressedColor:testBtn.containsMouse?uiStyle.buttonHoverColor:uiStyle.buttonBackgroundColor;
        width: 50;
        height: 30;
        radius: uiStyle.buttonBorderRadius;
        MouseArea{
            id:testBtn;
            anchors.fill: parent;
            hoverEnabled: true;
            onClicked: {
                cDevice.qmlTest();
            }
        }
    }
    StyleLoader{
        id:m_styleLoader;
        target:"UiMotorStyle";
    }
}

