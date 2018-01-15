pragma Singleton
import QtQuick 2.0

Item {
    id:resource;
    objectName: "QMLResources";
    property string language: "chinese";
    property string css:"blue";
    property int fontSize: 12;
    property url encGaugeBackgrond: Qt.resolvedUrl("../../build/debug/custom/option/style/blue/qml/enc_gaugebackground.png");
    property url encGaugeCenter: Qt.resolvedUrl("../../build/debug/custom/option/style/blue/qml/enc_gaugecenter.png");
    property url encGaugeNeedle: Qt.resolvedUrl("../../build/debug/custom/option/style/blue/qml/enc_gaugeneedle.png");

}

