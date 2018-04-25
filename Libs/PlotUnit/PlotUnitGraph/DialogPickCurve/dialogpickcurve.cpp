#include "dialogpickcurve.h"
#include "ui_dialogpickcurve.h"
#include "Option"
#include "gtutils.h"

#include <QButtonGroup>
#include <QDebug>

#define ICON_NAME_USR         "plot_curve_usr.png"
#define ICON_NAME_EXPERT      "plot_curve_expert.png"
#define ICON_NAME_CUSTOM      "plot_curve_custom.png"

enum UsrRoleIndex{
  USR_ROLE_USR,
  USR_ROLE_EXPERT,
  USR_ROLE_CUSTOM
};

DialogPickCurve::DialogPickCurve(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogPickCurve)
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

  connect(ui->btn_curve_custom,SIGNAL(clicked(bool)),this,SLOT(onUserSelectChanged()));
  connect(ui->btn_curve_user,SIGNAL(clicked(bool)),this,SLOT(onUserSelectChanged()));
  connect(ui->btn_curve_expert,SIGNAL(clicked(bool)),this,SLOT(onUserSelectChanged()));
  connect(ui->treeWidgetExpert,SIGNAL(itemExpanded(QTreeWidgetItem*)),this,SLOT(onTreeWidgetExpertExpandedClicked()));
  connect(ui->treeWidgetExpert,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(onExpertTreeWidgetDoubleClicked(QTreeWidgetItem*,int)));

}

DialogPickCurve::~DialogPickCurve()
{
  ui->treeWidgetExpert->clear();
  delete ui;
}

void DialogPickCurve::addExpertTreeWidget(const QTreeWidget *tree)
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

void DialogPickCurve::setAxisTable(int axisCount)
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
