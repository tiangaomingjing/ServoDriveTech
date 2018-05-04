#include "dialogadvusr.h"
#include "ui_dialogadvusr.h"
#include "iadvuser.h"
#include "advusercheck.h"
#include "advusermask.h"
#include "advusercontainer.h"


DialogAdvUsr::DialogAdvUsr(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAdvUsr)
{
    ui->setupUi(this);
    connect(ui->listWidget, SIGNAL(currentRowChanged(int)), this, SLOT(onListWidgetRowChanged(int)));

    QWidget *w;
    while (ui->stackedWidget->count()) {
        w = ui->stackedWidget->widget(0);
        delete w;
    }
    m_advContainer = AdvUserContainer::instance();
    QListWidgetItem *item;
    QList<IAdvUser*> advList = m_advContainer->advItems();
    for (int i = 0; i < advList.count(); i++) {
        ui->stackedWidget->addWidget(advList.at(i));
        item = new QListWidgetItem(advList.at(i)->name(), ui->listWidget);
        ui->listWidget->addItem(item);
    }
    ui->listWidget->setCurrentRow(0);
    ui->stackedWidget->setCurrentIndex(0);
}

DialogAdvUsr::~DialogAdvUsr()
{
    delete ui;
}

void DialogAdvUsr::closeEvent(QCloseEvent *event)
{
    QWidget *w;
    while (ui->stackedWidget->count()) {
        w = ui->stackedWidget->widget(0);
        w->setParent(0);
    }
    QDialog::closeEvent(event);
}

void DialogAdvUsr::onListWidgetRowChanged(int row)
{
    ui->stackedWidget->setCurrentIndex(row);
}

void DialogAdvUsr::onOkButtonClicked()
{
    AdvUserContainer *advc = AdvUserContainer::instance();
    bool ok = true;
    int errIndex = -1;
    int count = 0;
    QList<IAdvUser*> advList = advc->advItems();
    for (int i = 0; i < advList.count(); i++) {
        IAdvUser *adv = advList.at(i);
        ok = adv->execute();
        if (!ok) {
            errIndex = count;
        }
        count++;
    }
    if (errIndex != -1) {
        ui->stackedWidget->setCurrentIndex(errIndex);
        ui->listWidget->setCurrentRow(errIndex);
    } else {
        close();
    }
}

void DialogAdvUsr::onCancelButtonClicked()
{
    close();
}

void DialogAdvUsr::onApplyButtonClicked()
{
    QWidget *w = ui->stackedWidget->currentWidget();
    IAdvUser *adv = dynamic_cast<IAdvUser *>(w);
    adv->execute();
}
