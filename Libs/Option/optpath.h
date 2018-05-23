#ifndef OPTPATH_H
#define OPTPATH_H

#include <QObject>
#include "iopt.h"

namespace Ui {
class OptPath;
}
class OptPathPrivate;

class OPTIONSHARED_EXPORT OptPath : public IOpt
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(OptPath)
public:
    explicit OptPath(const QString &optName, QWidget *parent = 0);
    ~OptPath();
    void uiInit()Q_DECL_OVERRIDE;

    QString servo2FilePath();
    QString file2ServoPath();
    QString flashFilePath();
    QString oldFilePath();
    QString newFilePath();
signals:
    void pathesChanged(QStringList);
private:
    Ui::OptPath *ui;
protected:
    bool optActive() Q_DECL_OVERRIDE;
    bool readOpt() Q_DECL_OVERRIDE;
    bool writeOpt() Q_DECL_OVERRIDE;
    void respondErrorExecute() Q_DECL_OVERRIDE;
private slots:
    void onActionToolButtonClicked(int index);
};

#endif // OPTPATH_H
