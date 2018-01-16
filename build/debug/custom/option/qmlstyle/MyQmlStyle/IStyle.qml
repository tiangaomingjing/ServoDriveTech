import QtQuick 2.0

Item {
    id:istyleRoot;
    objectName: "styleInterface";

    property color      backgroundColor: "#F0F0F0";

    property color      frameBoderColor: "gray";
    property int        frameBoderWidth:2;
    property color      frameColor: "#E0DDDD";
    property int        frameRadius: 5;
    property color      frameTitleColor:"black";
    property color      frameTextColor: "black";

    property color      lineEditBackgroundDefaultColor: "white";
    property color      lineEditBackgroundModifyColor: "yellow";
    property color      lineEditBackgroundErrorColor: "red";
    property color      lineEditTextDefaultColor: "black";
    property color      lineEditTextModifyColor: "red";
    property int        lineEditBoderWidth: 1;
    property int        lineEditBorderRadius: 5;
    property color      lineEditBorderColor: "gray";

    property int        buttonBorderRadius: 5;
    property color      buttonBorderColor: "gray";
    property int        buttonBorderWidth: 1;
    property color      buttonHoverColor: "lightblue";
    property color      buttonPressedColor: "blue";
    property color      buttonBackgroundColor: "#F0F0F0";
    property color      buttonTextColor: "black";
}

