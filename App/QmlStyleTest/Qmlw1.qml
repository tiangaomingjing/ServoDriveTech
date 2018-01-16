import QtQuick 2.0
import MyQmlStyle 1.0

Rectangle {
    id:qw1;
    property Qmlw1Style uiStyle: m_styleLoader.iStyle;
    property int step: 0;
    color:uiStyle.frameColor;
    width: 400;
    height: 600;

    Rectangle{
        id:btntest;
        x:10;
        y:100;
        width: 50;
        height: 30;
        radius: 5;
        color:uiStyle.buttonBackgroundColor;
        border.color: uiStyle.buttonBorderColor;
        border.width: uiStyle.buttonBorderWidth;
        Component.onCompleted: console.log(qsTr("%1:Rectangle init").arg(step++));
        Text{
            anchors.centerIn: parent;
            text:qsTr("mybutton");
            color:uiStyle.buttonTextColor;
        }
    }

    StyleLoader{
        id:m_styleLoader;
        styleTarget: "Qmlw1Style";
        Component.onCompleted: console.log(qsTr("%1:StyleLoader init").arg(step++));
    }
    Component.onCompleted: console.log(qsTr("%1:Root init").arg(step++));
}

