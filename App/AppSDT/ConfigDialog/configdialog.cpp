#include "configdialog.h"
#include "ui_configdialog.h"
#include "deviceconfig.h"
#include "gtutils.h"
#include "qttreemanager.h"

#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>

#define CONFIG_SELECT_FILE_PATH "SysMap/ConfigSelectTree.ui"


ConfigDialog::ConfigDialog(QList<DeviceConfig *> *devList, QWidget *parent) :
  QDialog(parent),
  ui(new Ui::ConfigDialog),
  m_devListPtr(devList),
  m_curSd("SD61"),
  m_curSelectSta(SELECT_STATUS_RNNET),
  m_curDstTreeSta(DST_TREE_STATUS_EMPTY)
{
  ui->setupUi(this);
  ui->widget_deviceInfo->setFixedHeight(180);

  m_iconProductPath=GTUtils::iconPath()+"product/";

  setDevicePreview(m_curSd);

  loadSrcTreeWidget();

  createConnections();

  ui->treeWidget_dst->setColumnCount(4);
  ui->treeWidget_src->setColumnCount(3);

}

ConfigDialog::~ConfigDialog()
{
  delete ui;
  qDebug()<<"ConfigDialog destruct-->";
}

void ConfigDialog::createConnections()
{
  connect(ui->treeWidget_src,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(onSrcTreeItemClicked(QTreeWidgetItem*,int)));
  connect(ui->btn_add,SIGNAL(clicked(bool)),this,SLOT(onBtnAddClicked()));
  connect(ui->btn_remove,SIGNAL(clicked(bool)),this,SLOT(onBtnRemoveClicked()));
  connect(ui->btn_apply,SIGNAL(clicked(bool)),this,SLOT(onBtnApplyClicked()));
  connect(ui->btn_cancel,SIGNAL(clicked(bool)),this,SLOT(onBtnCancelClicked()));
}
void ConfigDialog::onSrcTreeItemClicked(QTreeWidgetItem *item, int column)
{
  Q_UNUSED(column);
  if(item->childCount()==0)
  {
    qDebug()<<"item name"<<item->text(0);
    QTreeWidgetItem *topItem=GTUtils::findTopLevelItem(item);
    m_curSelectSta=(SelectStatus)topItem->text(COL_PRM).toUInt();
    setCurrentUiSelectStatus(m_curSelectSta);//UiSelect状态机
    m_curSd=item->parent()->text(COL_NAME);
    setDevicePreview(m_curSd);

  }
}
void ConfigDialog::onBtnAddClicked()
{
  QTreeWidgetItem *item=ui->treeWidget_src->currentItem();
  qDebug()<<"current item"<<item->text(0);
  if(item->childCount()==0)
  {
    //目标树状态机
    switch (m_curDstTreeSta) {
    case DST_TREE_STATUS_EMPTY:
    {
      QTreeWidgetItem *topItem=GTUtils::findTopLevelItem(item);
      if(topItem->text(COL_PRM).toUInt()==1)
        m_curDstTreeSta=DST_TREE_STATUS_RNNET;
      else
        m_curDstTreeSta=DST_TREE_STATUS_PCDEBUG;
      createDstDevice(item);
    }
      break;
    case DST_TREE_STATUS_PCDEBUG:

      break;
    case DST_TREE_STATUS_RNNET:
      if(m_curSelectSta==SELECT_STATUS_RNNET)
        createDstDevice(item);
      break;
    default:
      break;
    }
  }
}

void ConfigDialog::onBtnRemoveClicked()
{
  switch (m_curDstTreeSta) {
  case DST_TREE_STATUS_EMPTY:

    break;
  case DST_TREE_STATUS_PCDEBUG:
    ui->treeWidget_dst->clear();
    m_curDstTreeSta=DST_TREE_STATUS_EMPTY;
    break;
  case DST_TREE_STATUS_RNNET:
  {
    QTreeWidgetItem *curItem=ui->treeWidget_dst->currentItem();
    if(curItem==NULL)
      return;
    QTreeWidgetItem *item=GTUtils::findTopLevelItem(ui->treeWidget_dst->currentItem());
    delete item;
    if(ui->treeWidget_dst->topLevelItemCount()==0)
      m_curDstTreeSta=DST_TREE_STATUS_EMPTY;
    resetDeviceId();
  }
    break;
  default:
    break;
  }
}
void ConfigDialog::onBtnCancelClicked()
{
  reject();
}
void ConfigDialog::onBtnApplyClicked()
{
//  m_devListPtr
  QTreeWidgetItem *devItem;
  QTreeWidgetItem *comItem;
  QTreeWidgetItem *typeItem;
  QTreeWidgetItem *modelItem;
  QTreeWidgetItem *versionItem;

  for(int i=0;i<ui->treeWidget_dst->topLevelItemCount();i++)
  {
    devItem=ui->treeWidget_dst->topLevelItem(i);
//    qDebug()<<"devItem"<<devItem->text(0);
    comItem=devItem->child(0);
//    qDebug()<<"comItem"<<comItem->text(0);
    typeItem=comItem->child(0);
//    qDebug()<<"typeItem"<<typeItem->text(0);
    modelItem=typeItem->child(0);
//    qDebug()<<"modelItem"<<modelItem->text(0);
    versionItem=modelItem->child(0);
//    qDebug()<<"versionItem"<<versionItem->text(0);
    DeviceConfig *device=new DeviceConfig;
    device->m_devId=devItem->text(COL_ID).toUInt();
    device->m_comType=comItem->text(COL_PRM).toUInt();
    device->m_rnStationId=comItem->text(COL_PRM_EX0).toUInt();
    device->m_typeName=typeItem->text(COL_NAME);
    device->m_axisNum=modelItem->text(COL_PRM).toUInt();
    device->m_modeName=modelItem->text(COL_NAME);
    device->m_version=versionItem->text(COL_NAME);

    //根据modeName typeName找到powerId
    device->m_pwrId=modelItem->text(COL_ID).toUInt();
    device->m_ctrId=versionItem->text(COL_ID).toUInt();
    device->m_fpgaId=comItem->text(COL_ID).toUInt();
    m_devListPtr->append(device);
  }
  accept();
}

QString ConfigDialog::readDeviceDescription(const QString &sdinfoPath)
{
  QFile file(sdinfoPath);
  QString sdInfo;
  if(file.open(QFile::ReadOnly|QFile::Text))
  {
    QTextStream in(&file);
    in.setCodec("UTF-8");//解决读中文时乱码
    sdInfo=in.readAll();
  }
  file.close();
  return sdInfo;
}
void ConfigDialog::setDevicePreview(const QString &sd)
{
  QString sd61IconPath=m_iconProductPath+sd+".png";
  ui->label_image->setPixmap(QPixmap(sd61IconPath));

  QString sdInfoPath=m_iconProductPath+sd+".txt";
  QString sdInfo=readDeviceDescription(sdInfoPath);
  ui->label_deviceInfo->setText(sdInfo);
}
//!
//! \brief ConfigDialog::loadSrcTreeWidget
//!
void ConfigDialog::loadSrcTreeWidget()
{
  QString selectTreePath=GTUtils::sysPath()+CONFIG_SELECT_FILE_PATH;
  QTreeWidget *tree=QtTreeManager::createTreeWidgetFromXmlFile(selectTreePath);
  QTreeWidgetItem *item;
  for(int i=0;i<tree->topLevelItemCount();i++)
  {
    item=tree->topLevelItem(i)->clone();
    ui->treeWidget_src->addTopLevelItem(item);
  }
  ui->treeWidget_src->expandToDepth(1);
  QTreeWidgetItem *itemSelectSD61=ui->treeWidget_src->topLevelItem(1)->child(1)->child(0);
  ui->treeWidget_src->expandItem(itemSelectSD61);
  QTreeWidgetItem *itemSelect=itemSelectSD61->child(0);
  itemSelect->setSelected(true);
  ui->treeWidget_src->setCurrentItem(itemSelect);

//  //TEST
//  QTreeWidgetItem *topItem=GTUtils::findTopLevelItem(itemSelect);
//  int top=ui->treeWidget_src->indexOfTopLevelItem(topItem);
//  qDebug()<<"TEST top index= "<<top;
  delete tree;
}

void ConfigDialog::setCurrentUiSelectStatus(SelectStatus sta)
{
  switch (sta) {
  case SELECT_STATUS_PCDEBUG:
    ui->widget_rnCtlPanel->setVisible(false);
    break;
  case SELECT_STATUS_RNNET:
    ui->widget_rnCtlPanel->setVisible(true);
    break;
  default:
    ui->widget_rnCtlPanel->setVisible(true);
    break;
  }
}
void ConfigDialog::createDstDevice(QTreeWidgetItem*curItem)
{
  QTreeWidgetItem *modelItem=curItem->parent();
  QTreeWidgetItem *typeItem=modelItem->parent();
  QTreeWidgetItem *comItem=typeItem->parent();
  QTreeWidgetItem *devItem=new QTreeWidgetItem(ui->treeWidget_dst);
  devItem->setText(COL_NAME,"Device");
  devItem->setText(COL_ID,QString::number(ui->treeWidget_dst->topLevelItemCount()-1));

  QTreeWidgetItem *modelItemDst;
  QTreeWidgetItem *typeItemDst;
  QTreeWidgetItem *comItemDst;
  QTreeWidgetItem *curItemDst;
  comItemDst=addChildItem(comItem,devItem);
  comItemDst->setText(COL_PRM_EX0,QString::number(ui->spinBox_rnStation->value()));
  typeItemDst=addChildItem(typeItem,comItemDst);
  modelItemDst=addChildItem(modelItem,typeItemDst);
  curItemDst=addChildItem(curItem,modelItemDst);

  ui->treeWidget_dst->expandAll();
}
QTreeWidgetItem* ConfigDialog::addChildItem(QTreeWidgetItem*child,QTreeWidgetItem*parent)
{
  QTreeWidgetItem *item=new QTreeWidgetItem(parent);
  for(int i=0;i<child->columnCount();i++)
    item->setText(i,child->text(i));
  return item;
}
void ConfigDialog::resetDeviceId()
{
  QTreeWidgetItem *item;
  for(int i=0;i<ui->treeWidget_dst->topLevelItemCount();i++)
  {
    item=ui->treeWidget_dst->topLevelItem(i);
    item->setText(COL_ID,QString::number(i));
  }
}
