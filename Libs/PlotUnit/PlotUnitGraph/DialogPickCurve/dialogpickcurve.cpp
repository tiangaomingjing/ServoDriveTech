#include "dialogpickcurve.h"
#include "ui_dialogpickcurve.h"
#include "Option"
#include "gtutils.h"
#include "icurve.h"
#include "sevdevice.h"

#include <QButtonGroup>
#include <QDebug>
#include <QComboBox>
#include <QStyledItemDelegate>

#define ICON_NAME_USR         "plot_curve_usr.png"
#define ICON_NAME_EXPERT      "plot_curve_expert.png"
#define ICON_NAME_CUSTOM      "plot_curve_custom.png"

enum UsrRoleIndex{
  USR_ROLE_USR,
  USR_ROLE_EXPERT,
  USR_ROLE_CUSTOM
};
enum UsrCurveColumn{
  COL_USR_CURVE_NAME,
  COL_USR_CURVE_NOTE,
  COL_USR_CURVE_UNIT,
  COL_USR_CURVE_SIZE
};
typedef enum{
  ROLE_USR_TABLE_CURVE_ICURVE_PTR = Qt::UserRole+1
}UsrCurveTableDataRole;

Q_DECLARE_METATYPE(ICurve*)

DialogPickCurve::DialogPickCurve(SevDevice *sev,QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogPickCurve),
  m_sev(sev)
{
  ui->setupUi(this);

  m_face=dynamic_cast<OptFace *>(OptContainer::instance()->optItem("optface"));
  setIcons();

  ui->tableWidget_axis->setMaximumHeight(3*qApp->font().pixelSize());
  QButtonGroup *group=new QButtonGroup(this);
  group->addButton(ui->btn_curve_custom);
  group->addButton(ui->btn_curve_user);
  group->addButton(ui->btn_curve_expert);
  ui->btn_curve_user->setChecked(true);
  ui->stackedWidget_plotCurve->setCurrentIndex(USR_ROLE_USR);

  ui->tableWidget_usr->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  ui->tableWidget_usr->setEditTriggers(QTableView::NoEditTriggers);
  ui->tableWidget_usr->setAlternatingRowColors(true);
  ui->tableWidget_usr->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式

  connect(ui->btn_curve_custom,SIGNAL(clicked(bool)),this,SLOT(onUserSelectChanged()));
  connect(ui->btn_curve_user,SIGNAL(clicked(bool)),this,SLOT(onUserSelectChanged()));
  connect(ui->btn_curve_expert,SIGNAL(clicked(bool)),this,SLOT(onUserSelectChanged()));
  connect(ui->treeWidgetExpert,SIGNAL(itemExpanded(QTreeWidgetItem*)),this,SLOT(onTreeWidgetExpertExpandedClicked()));
  connect(ui->treeWidgetExpert,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(onExpertTreeWidgetDoubleClicked(QTreeWidgetItem*,int)));
  connect(ui->tableWidget_usr,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(onUsrTableCellDoubleClicked(int,int)));
}

DialogPickCurve::~DialogPickCurve()
{
  ui->treeWidgetExpert->clear();
  delete ui;
}

void DialogPickCurve::expertTreeWidgetInit(const QTreeWidget *tree)
{
  QTreeWidgetItem *item;
  for(int i=0;i<tree->topLevelItemCount();i++)
  {
    item=tree->topLevelItem(i)->clone();
    ui->treeWidgetExpert->addTopLevelItem(item);
  }
  QTreeWidgetItem *itemHeader;
  itemHeader=tree->headerItem()->clone();
  ui->treeWidgetExpert->setHeaderItem(itemHeader);
  ui->treeWidgetExpert->hideColumn(1);
  ui->treeWidgetExpert->hideColumn(3);
  ui->treeWidgetExpert->hideColumn(4);
  ui->treeWidgetExpert->hideColumn(5);
  ui->treeWidgetExpert->hideColumn(6);
  ui->treeWidgetExpert->hideColumn(7);
  ui->treeWidgetExpert->expandToDepth(1);

  ui->treeWidgetExpert->resizeColumnToContents(0);
  ui->treeWidgetExpert->resizeColumnToContents(1);
}

void DialogPickCurve::axisTableInit(int axisCount)
{
  //各个轴号的选择表
  QTableWidgetItem *tableItem;
  ui->tableWidget_axis->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  ui->tableWidget_axis->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  ui->tableWidget_axis->setRowCount(1);
  ui->tableWidget_axis->setColumnCount(axisCount);
  ui->tableWidget_axis->setEditTriggers(QTableView::NoEditTriggers);
  ui->tableWidget_axis->setSelectionMode(QAbstractItemView::ExtendedSelection);
  for(int i=0;i<axisCount;i++)
  {
    tableItem=new QTableWidgetItem;
    tableItem->setText(tr("Axis_%1").arg(i+1));
//    tableItem->setIcon(QIcon(":/user_curve_axis.png"));
    tableItem->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_axis->setItem(0,i,tableItem);
  }
  ui->tableWidget_axis->item(0,0)->setSelected(true);
}

void DialogPickCurve::usrCurveTableInit(QList<ICurve *> curves)
{
  ICurve *c = NULL;
  QTableWidgetItem *item = NULL;
  qDebug()<<"curves size = "<<curves.size();
  for(int i=0;i<curves.size();i++)
  {
    c = curves.at(i);
    ui->tableWidget_usr->insertRow(i);
    for(int col = 0;col <COL_USR_CURVE_SIZE;col++)
    {

      switch(col)
      {
      case COL_USR_CURVE_NAME:
      {
        QVariant v;
        item = new QTableWidgetItem;
        item->setText(c->name());
        v.setValue(c);
        item->setData(ROLE_USR_TABLE_CURVE_ICURVE_PTR,v);
        ui->tableWidget_usr->setItem(i,col,item);
      }
      break;

      case COL_USR_CURVE_NOTE:
        item = new QTableWidgetItem;
        item->setText(c->note());
        item->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_usr->setItem(i,col,item);
      break;

      case COL_USR_CURVE_UNIT:
      {
        QComboBox *comboBox = new QComboBox;
        QStyledItemDelegate* itemDelegate = new QStyledItemDelegate(comboBox);
        comboBox->setItemDelegate(itemDelegate);
        qDebug()<<"unit names = "<<c->unitNames().size();
        for(int inx=0;inx<c->unitNames().size();inx++)
        {
          QString key = c->unitNames().at(inx);
          double factor = c->unitValue(key);
          comboBox->addItem(key,factor);
        }
        ui->tableWidget_usr->setCellWidget(i,col,comboBox);
      }
      break;

      }
    }
  }
}


void DialogPickCurve::onUserSelectChanged()
{
  QToolButton *btn=qobject_cast<QToolButton *>(sender());
  if(btn == ui->btn_curve_user)
    ui->stackedWidget_plotCurve->setCurrentIndex(USR_ROLE_USR);
  else if(btn == ui->btn_curve_expert)
    ui->stackedWidget_plotCurve->setCurrentIndex(USR_ROLE_EXPERT);
  else
    ui->stackedWidget_plotCurve->setCurrentIndex(USR_ROLE_CUSTOM);
}

void DialogPickCurve::onTreeWidgetExpertExpandedClicked()
{

  ui->treeWidgetExpert->resizeColumnToContents(0);
}

void DialogPickCurve::onExpertTreeWidgetDoubleClicked(QTreeWidgetItem *item, int column)
{
  Q_UNUSED(column);

  emit expertTreeItemDoubleClicked(ui->tableWidget_axis,item);
}

void DialogPickCurve::onUsrTableCellDoubleClicked(int row, int column)
{
  Q_UNUSED(column);
  int axisCount = ui->tableWidget_axis->columnCount();
  for(int axis=0;axis<axisCount;axis++)
  {
    if(ui->tableWidget_axis->item(0,axis)->isSelected())
    {
      ICurve *c = ui->tableWidget_usr->item(row,COL_USR_CURVE_NAME)->data(ROLE_USR_TABLE_CURVE_ICURVE_PTR).value<ICurve *>();
      QComboBox *box =dynamic_cast<QComboBox * >(ui->tableWidget_usr->cellWidget(row,COL_USR_CURVE_UNIT)) ;
      double k = box->currentData().toDouble();
      QString uName = box->currentText();
      ICurve *newCurve = c->clone();

      qDebug()<<"unit k = "<<k;
      newCurve->setUnit(uName);
      newCurve->setAxisInx(axis);
      newCurve->setAxisCount(axisCount);
      newCurve->setDevInx(m_sev->devId());
      qDebug()<<newCurve->curUnitName()<<" curve unit k = "<<newCurve->curUnitK() <<"axis = "<<newCurve->axisInx();
      emit addUsrCurveRequest(newCurve);
    }
  }
}

void DialogPickCurve::setIcons()
{
  QSize iconSize(24,24);
  QString css=m_face->css();
  QString iconPath=GTUtils::customPath()+"option/style/"+css+"/icon/";

  ui->btn_curve_custom->setIcon(QIcon(QPixmap(iconPath+ICON_NAME_CUSTOM)));
  ui->btn_curve_custom->setIconSize(iconSize);

  ui->btn_curve_user->setIcon(QIcon(QPixmap(iconPath+ICON_NAME_USR)));
  ui->btn_curve_user->setIconSize(iconSize);

  ui->btn_curve_expert->setIcon(QIcon(QPixmap(iconPath+ICON_NAME_EXPERT)));
  ui->btn_curve_expert->setIconSize(iconSize);
}
