import QtQuick 2.0

Item{
    id:styleLoderRoot;
    objectName: "StyleLoader";
    property string target: " ";
    property IStyle iStyle:m_styleLoader.item;
    Loader{
        id:m_styleLoader;
//        source: Qt.resolvedUrl(qsTr("./%1/%2.qml").arg(qmlStyleHelper.css).arg(styleTarget));
        source: Qt.resolvedUrl("./"+qmlStyleHelper.css+"/"+target+".qml");
    }
//    onIStyleChanged: console.log("url= "+Qt.resolvedUrl(qsTr("./%1/%2.qml").arg(qmlStyleHelper.css).arg(styleTarget)));
//    onIStyleChanged: console.log("url= "+Qt.resolvedUrl("./"+qmlStyleHelper.css+"/"+styleTarget+".qml"));
}
