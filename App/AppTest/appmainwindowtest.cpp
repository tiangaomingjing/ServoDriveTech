#include "appmainwindowtest.h"
#include "ui_appmainwindowtest.h"
#include "icom.h"

AppMainWindowTest::AppMainWindowTest(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::AppMainWindowTest)
{
  ui->setupUi(this);
  initial();
}

AppMainWindowTest::~AppMainWindowTest()
{
  delete ui;
}

/**
 * @brief AppMainWindowTest::initial
 * //加载配置
 */
void AppMainWindowTest::initial()
{
  //1 根据最近配置文件，生成device ，如果初次打开使用默认设备
  //2 根据device ,生成界面
  //3 加载首选项配置信息
}
