//#include <QGuiApplication>
//#include <QQmlApplicationEngine>

//int main(int argc, char *argv[])
//{
//  QGuiApplication app(argc, argv);

//  QQmlApplicationEngine engine;
//  engine.addImportPath("D:/Smart/ServoMaster/git-project/ServoDriveTech/ServoDriveTech/App/QmlSingletonTest/");
//  QString localFile="D:\\Smart\\ServoMaster\\git-project\\ServoDriveTech\\ServoDriveTech\\App\\QmlSingletonTest\\main.qml";
//  engine.load(QUrl::fromLocalFile(localFile));
////  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

//  return app.exec();
//}


#include <QGuiApplication>
#include <QQuickView>
#include <QQmlEngine>
int main(int argc, char *argv[])
{
  QGuiApplication app(argc, argv);

  QQuickView v;
  v.engine()->addImportPath("D:/Smart/ServoMaster/git-project/ServoDriveTech/ServoDriveTech/App/QmlSingletonTest/");
  QString localFile="D:\\Smart\\ServoMaster\\git-project\\ServoDriveTech\\ServoDriveTech\\App\\QmlSingletonTest\\main.qml";
  v.setSource(QUrl::fromLocalFile(localFile));
  v.show();

  return app.exec();
}
