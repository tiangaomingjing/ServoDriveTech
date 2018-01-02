#include "formmain.h"
#include "ui_formmain.h"
#include "widgetmainwindow.h"

FormMain::FormMain(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FormMain)
{
  ui->setupUi(this);
  WidgetMainWindow *w=new WidgetMainWindow;
  ui->verticalLayout->addWidget(w);
}

FormMain::~FormMain()
{
  delete ui;
}
