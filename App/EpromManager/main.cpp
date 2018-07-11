#include "eprommanager.h"
#include "gtutils.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator *trans = NULL;
    QString path = GTUtils::customPath() + "option/opt.ini";
    QString langPath = GTUtils::languagePath() + "ch/ch_eeprom.qm";
    QString lang = GTUtils::data(path, "face", "language", "").toString();
    if (lang.compare("chinese") == 0) {
        trans=new QTranslator;
        qDebug()<<langPath;
        trans->load(langPath);
        qApp->installTranslator(trans);
    }
    EpromManager w;
    w.show();

    return a.exec();
}
