#ifndef ADVUSERCOMPRESS_H
#define ADVUSERCOMPRESS_H

#include <QObject>
#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include "iadvuser.h"

namespace Ui {
class AdvUserCompress;
}

class AdvUserCompressPrivate;

class ADVUSERSHARED_EXPORT AdvUserCompress : public IAdvUser
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(AdvUserCompress)

public:
    explicit AdvUserCompress(const QString &advUserName, QWidget *parent = 0);
    ~AdvUserCompress();

    void uiInit() Q_DECL_OVERRIDE;
protected:
    bool advUserActive() Q_DECL_OVERRIDE;
    bool readAdv() Q_DECL_OVERRIDE;
    bool writeAdv() Q_DECL_OVERRIDE;
    void respondErrorExecute() Q_DECL_OVERRIDE;
private:
    Ui::AdvUserCompress *ui;
private slots:
    void onActnCompressToolBtnClicked();
};

#endif // ADVUSERCOMPRESS_H
