#include "icurve.h"
#include "gtutils.h"

#include <QHash>
#include <QVector>
#include <QDebug>
#include <QTreeWidgetItem>
#include <QDebug>

#define XML_NODE_CURVE            "Curve"
#define XML_NODE_DEVINX           "DevIndex"
#define XML_NODE_AXISINX          "AxisIndex"
#define XML_NODE_AXISCOUNT        "AxisCount"
#define XML_NODE_NAME             "Name"
#define XML_NODE_NOTE             "Note"
#define XML_NODE_COLOR            "Color"
#define XML_NODE_ISDRAW           "IsDraw"
#define XML_NODE_UNIT             "Unit"
#define XML_NODE_CONSTINPUTS      "ConstInputs"
#define XML_NODE_VARINPUTS        "VarInputs"

class UnitKeyValue{
public:
  QString key;
  double value;
};

ICurve::~ICurve()
{
  qDebug()<<"ICurve destruct -->";
}
/**
 * @brief ICurve::prepare
 * 客户端使用时，新建对象后须先调用prepare函数进行初始化
 */
void ICurve::prepare()
{
  setName(name());
  setNote(note());
  init();
  dd.m_pluginName = pluginName();
  qDebug()<<name()<<"prepare";
}

void ICurve::exec()
{
  updateCurrentTime();
  calculate();
  adjustData();
}

void ICurve::setName(const QString &name)
{
  dd.m_name=name;
}

void ICurve::setNote(const QString &note)
{
  dd.m_note=note;
}

QString ICurve::displayName()
{
  QString dname ;
  if(dd.m_unitName == "NULL")
    dname = QObject::tr("%1").arg(dd.m_name);
  else
    dname = QObject::tr("%1(%2)").arg(dd.m_name).arg(dd.m_unitName);

  return dname;
}

QString ICurve::fullName()
{
  QString fname ;
  if(dd.m_unitName == "NULL")
    fname = QObject::tr("%1.%2").arg(name()).arg(note());
  else
    fname = QObject::tr("%1.%2(%3)").arg(name()).arg(note()).arg(dd.m_unitName);

  return fname;
}

/**
 * @brief ICurve::write
 * 序列化对象到 QTreeWidgetItem
 * @param treeItem
 */
void ICurve::write(QTreeWidgetItem *treeItem)
{
  treeItem->setText(COL_CURVE_XML_NAME,XML_NODE_CURVE);
  treeItem->setText(COL_CURVE_XML_VALUE,dd.m_pluginName);

  QTreeWidgetItem *devItem = new QTreeWidgetItem(treeItem);
  devItem->setText(COL_CURVE_XML_NAME,XML_NODE_DEVINX);
  devItem->setText(COL_CURVE_XML_VALUE,QString::number(dd.m_devInx));

  QTreeWidgetItem *axisItem = new QTreeWidgetItem(treeItem);
  axisItem->setText(COL_CURVE_XML_NAME,XML_NODE_AXISINX);
  axisItem->setText(COL_CURVE_XML_VALUE,QString::number(dd.m_axisInx));

  QTreeWidgetItem *axisCountItem = new QTreeWidgetItem(treeItem);
  axisCountItem->setText(COL_CURVE_XML_NAME,XML_NODE_AXISCOUNT);
  axisCountItem->setText(COL_CURVE_XML_VALUE,QString::number(dd.m_axisCount));

  QTreeWidgetItem *nameItem = new QTreeWidgetItem(treeItem);
  nameItem->setText(COL_CURVE_XML_NAME,XML_NODE_NAME);
  nameItem->setText(COL_CURVE_XML_VALUE,dd.m_name);

  QTreeWidgetItem *noteItem = new QTreeWidgetItem(treeItem);
  noteItem->setText(COL_CURVE_XML_NAME,XML_NODE_NOTE);
  noteItem->setText(COL_CURVE_XML_VALUE,dd.m_note);

  QTreeWidgetItem *colorItem = new QTreeWidgetItem(treeItem);
  colorItem->setText(COL_CURVE_XML_NAME,XML_NODE_COLOR);
  QTreeWidgetItem * colorItem_R=new QTreeWidgetItem(colorItem);//R
  colorItem_R->setText(COL_CURVE_XML_NAME,"ColorR");
  colorItem_R->setText(COL_CURVE_XML_VALUE,QString::number(dd.m_color.red()));
  QTreeWidgetItem * colorItem_G=new QTreeWidgetItem(colorItem);//G
  colorItem_G->setText(COL_CURVE_XML_NAME,"ColorR");
  colorItem_G->setText(COL_CURVE_XML_VALUE,QString::number(dd.m_color.green()));
  QTreeWidgetItem * colorItem_B=new QTreeWidgetItem(colorItem);//B
  colorItem_B->setText(COL_CURVE_XML_NAME,"ColorR");
  colorItem_B->setText(COL_CURVE_XML_VALUE,QString::number(dd.m_color.blue()));

  QTreeWidgetItem *isDrawItem = new QTreeWidgetItem(treeItem);
  isDrawItem->setText(COL_CURVE_XML_NAME,XML_NODE_ISDRAW);
  if(dd.m_isDraw)
    isDrawItem->setText(COL_CURVE_XML_VALUE,"1");
  else
    isDrawItem->setText(COL_CURVE_XML_VALUE,"0");

  //单位
  QTreeWidgetItem *unitItem = new QTreeWidgetItem(treeItem);
  unitItem->setText(COL_CURVE_XML_NAME,XML_NODE_UNIT);
  if(dd.m_unitNameList.isEmpty())
    unitItem->setText(COL_CURVE_XML_VALUE,"-1");
  else
  {
    int uinx = 0;
    for(int i = 0;i<dd.m_unitNameList.size();i++)
    {
      if(dd.m_unitName == dd.m_unitNameList.at(i))
      {
        uinx = i;
        break;
      }
    }
    unitItem->setText(COL_CURVE_XML_VALUE,QString::number(uinx));
  }

  QString unitName;
  for(int i = 0;i<dd.m_unitNameList.size();i++)
  {
    unitName = dd.m_unitNameList.at(i);
    if(dd.m_unitsHash.contains(unitName))
    {
      QTreeWidgetItem * item=new QTreeWidgetItem(unitItem);//B
      item->setText(COL_CURVE_XML_NAME,unitName);
      double value = dd.m_unitsHash.value(unitName);
      item->setText(COL_CURVE_XML_VALUE,QString::number(value,'f',5));
    }
  }
  //常量输入
  QTreeWidgetItem *constItem = new QTreeWidgetItem(treeItem);
  constItem->setText(COL_CURVE_XML_NAME,XML_NODE_CONSTINPUTS);
  for(int i = 0;i<dd.m_constInputs.size();i++)
  {
    QTreeWidgetItem * item=new QTreeWidgetItem(constItem);
    item->setText(COL_CURVE_XML_NAME,"const");
    item->setText(COL_CURVE_XML_VALUE,dd.m_constInputs.at(i).keyName);

    quint16 base = dd.m_constInputs.at(i).prm.baseAddr;
    quint16 offt = dd.m_constInputs.at(i).prm.offtAddr;
    quint16 bytes = dd.m_constInputs.at(i).prm.bytes;
    QTreeWidgetItem * prmItem=new QTreeWidgetItem(item);
    prmItem->setText(COL_CURVE_XML_NAME,"BaseAddr");
    prmItem->setText(COL_CURVE_XML_VALUE,QString::number(base));
    prmItem=new QTreeWidgetItem(item);
    prmItem->setText(COL_CURVE_XML_NAME,"OffsetAddr");
    prmItem->setText(COL_CURVE_XML_VALUE,QString::number(offt));
    prmItem=new QTreeWidgetItem(item);
    prmItem->setText(COL_CURVE_XML_NAME,"Bytes");
    prmItem->setText(COL_CURVE_XML_VALUE,QString::number(bytes));
  }

  //变量输入
  QTreeWidgetItem *varItem = new QTreeWidgetItem(treeItem);
  varItem->setText(COL_CURVE_XML_NAME,XML_NODE_VARINPUTS);
  for(int i = 0;i<dd.m_varInputs.size();i++)
  {
    QTreeWidgetItem * item=new QTreeWidgetItem(varItem);
    item->setText(COL_CURVE_XML_NAME,"Var");
    item->setText(COL_CURVE_XML_VALUE,dd.m_varInputs.at(i).keyName);

    quint16 base = dd.m_varInputs.at(i).prm.baseAddr;
    quint16 offt = dd.m_varInputs.at(i).prm.offtAddr;
    quint16 bytes = dd.m_varInputs.at(i).prm.bytes;
    QTreeWidgetItem * prmItem=new QTreeWidgetItem(item);
    prmItem->setText(COL_CURVE_XML_NAME,"BaseAddr");
    prmItem->setText(COL_CURVE_XML_VALUE,QString::number(base));
    prmItem=new QTreeWidgetItem(item);
    prmItem->setText(COL_CURVE_XML_NAME,"OffsetAddr");
    prmItem->setText(COL_CURVE_XML_VALUE,QString::number(offt));
    prmItem=new QTreeWidgetItem(item);
    prmItem->setText(COL_CURVE_XML_NAME,"Bytes");
    prmItem->setText(COL_CURVE_XML_VALUE,QString::number(bytes));

  }
}

/**
 * @brief ICurve::read
 * 从QTreeWidgetItem 中反序列化生成对象
 * @param treeItem
 */
bool ICurve::read(QTreeWidgetItem *treeItem)
{
  int devInx = 0;
  int axisInx = 0;
  int axisCount = 0;
  QString name;
  QString note;
  QColor color;
  int clrR,clrG,clrB;
  bool isDraw = true;
  int unitInx;
  QList<UnitKeyValue> unitList;
  QList<CurveConst> curveConstInputList;
  QList<CurveVar> curveVarInputList;


  clrR = clrG = clrB = 0;

  QTreeWidgetItem *item = NULL;
  item = GTUtils::findItemInItem(XML_NODE_CURVE,treeItem,COL_CURVE_XML_NAME);
  if(item != NULL)
    devInx = item->text(COL_CURVE_XML_VALUE).toInt();
  else
    return false;

  item = GTUtils::findItemInItem(XML_NODE_AXISINX,treeItem,COL_CURVE_XML_NAME);
  if(item != NULL)
    axisInx = item->text(COL_CURVE_XML_VALUE).toInt();
  else
    return false;

  item = GTUtils::findItemInItem(XML_NODE_AXISCOUNT,treeItem,COL_CURVE_XML_NAME);
  if(item != NULL)
    axisCount = item->text(COL_CURVE_XML_VALUE).toInt();
  else
    return false;

  item = GTUtils::findItemInItem(XML_NODE_NAME,treeItem,COL_CURVE_XML_NAME);
  if(item != NULL)
    name = item->text(COL_CURVE_XML_VALUE);
  else
    return false;

  item = GTUtils::findItemInItem(XML_NODE_NOTE,treeItem,COL_CURVE_XML_NAME);
  if(item != NULL)
    note = item->text(COL_CURVE_XML_VALUE);
  else
    return false;

  //color
  item = GTUtils::findItemInItem(XML_NODE_COLOR,treeItem,COL_CURVE_XML_NAME);
  if(item != NULL)
  {
    clrR = item->child(0)->text(COL_CURVE_XML_VALUE).toInt();
    clrG = item->child(1)->text(COL_CURVE_XML_VALUE).toInt();
    clrB = item->child(2)->text(COL_CURVE_XML_VALUE).toInt();
    color.setRgb(clrR,clrG,clrB);
  }
  else
    return false;

  item = GTUtils::findItemInItem(XML_NODE_ISDRAW,treeItem,COL_CURVE_XML_NAME);
  if(item != NULL)
  {
    int d = item->text(COL_CURVE_XML_VALUE).toInt();
    isDraw = (d == 1);
  }
  else
    return false;

  //单位
  item = GTUtils::findItemInItem(XML_NODE_UNIT,treeItem,COL_CURVE_XML_NAME);
  if(item != NULL)
  {
    unitInx = 0;
    unitInx = item->text(COL_CURVE_XML_VALUE).toInt();

    UnitKeyValue uk;
    for(int i=0;i<item->childCount();i++)
    {
      uk.key = item->child(i)->text(COL_CURVE_XML_NAME);
      uk.value = item->child(i)->text(COL_CURVE_XML_VALUE).toDouble();
      unitList.append(uk);
    }
  }
  else
    return false;

  //const inputs
  item = GTUtils::findItemInItem(XML_NODE_CONSTINPUTS,treeItem,COL_CURVE_XML_NAME);
  if(item != NULL)
  {
    CurveConst cconst;
    QTreeWidgetItem *constItem = NULL;
    for(int i=0;i<item->childCount();i++)
    {
      constItem = item->child(i);
      cconst.keyName = constItem->text(COL_CURVE_XML_VALUE);
      cconst.prm.baseAddr = constItem->child(0)->text(COL_CURVE_XML_VALUE).toUShort();
      cconst.prm.offtAddr = constItem->child(1)->text(COL_CURVE_XML_VALUE).toUShort();
      cconst.prm.bytes = constItem->child(2)->text(COL_CURVE_XML_VALUE).toUShort();
      curveConstInputList.append(cconst);
    }
  }
  else
    return false;

  //var inputs
  item = GTUtils::findItemInItem(XML_NODE_VARINPUTS,treeItem,COL_CURVE_XML_NAME);
  if(item != NULL)
  {
    CurveVar var;
    QTreeWidgetItem *varItem = NULL;
    for(int i=0;i<item->childCount();i++)
    {
      varItem = item->child(i);
      var.keyName = varItem->text(COL_CURVE_XML_VALUE);
      var.prm.baseAddr = varItem->child(0)->text(COL_CURVE_XML_VALUE).toUShort();
      var.prm.offtAddr = varItem->child(1)->text(COL_CURVE_XML_VALUE).toUShort();
      var.prm.bytes = varItem->child(2)->text(COL_CURVE_XML_VALUE).toUShort();
      curveVarInputList.append(var);
    }
  }
  else
    return false;

  setDevInx(devInx);
  setAxisInx(axisInx);
  setAxisCount(axisCount);
  setName(name);
  setNote(note);
  setColor(color);
  setIsDraw(isDraw);

  dd.m_unitsHash.clear();
  dd.m_unitNameList.clear();
  for(int i =0;i<unitList.size();i++)
  {
    addUnit(unitList.at(i).key,unitList.at(i).value);
  }
  setUnit(unitList.at(unitInx).key);

  dd.m_constInputs.clear();
  dd.m_constInputs = curveConstInputList;

  dd.m_varInputs.clear();
  dd.m_varInputs = curveVarInputList;


  return true;
}

void ICurve::saveCurve(QTextStream &text)
{
    savePrepare();
    text<<"Plugin Name: "<<dd.m_pluginName<<"\n";
    text<<"Device Index: "<<dd.m_devInx<<"\n";
    text<<"Axis Index: "<<dd.m_axisInx<<"\n";
    text<<"Axis Count: "<<dd.m_axisCount<<"\n";
    text<<"Curve Name: "<<dd.m_name<<"\n";
    text<<"Note: "<<dd.m_note<<"\n";
    text<<"Color: "<<"\n";
    text<<"Red: "<<dd.m_color.red()<<"\n";
    text<<"Green: "<<dd.m_color.green()<<"\n";
    text<<"Blue: "<<dd.m_color.blue()<<"\n";
    text<<"IsDraw: "<<dd.m_isDraw<<"\n";
    text<<"Unit Name: "<<dd.m_unitName<<"\n";

    for (int i = 0; i < dd.m_unitNameList.size(); i++) {
        text<<qSetFieldWidth(15) << left<< dd.m_unitNameList.at(i);
        if (dd.m_unitsHash.contains(dd.m_unitNameList.at(i))) {
            text<<dd.m_unitsHash.value(dd.m_unitNameList.at(i));
        } else {
            text<<0;
        }
        text<<qSetFieldWidth(0) << left<<endl;
    }

    text<<"Const Inputs:"<<"\n";
    for (int i = 0; i < dd.m_constInputs.size(); i++) {
        text<<"KeyName: "<<dd.m_constInputs.at(i).keyName<<"\n";
        text<<"----Base Addr: "<<dd.m_constInputs.at(i).prm.baseAddr<<"\n";
        text<<"----Offset Addr:"<<dd.m_constInputs.at(i).prm.offtAddr<<"\n";
        text<<"----Bytes: "<<dd.m_constInputs.at(i).prm.bytes<<"\n";
    }

    text<<"Var Inputs:"<<"\n";
    for (int i = 0; i < dd.m_varInputs.size(); i++) {
        text<<"KeyName: "<<dd.m_varInputs.at(i).keyName<<"\n";
        text<<"----Base Addr: "<<dd.m_varInputs.at(i).prm.baseAddr<<"\n";
        text<<"----Offset Addr:"<<dd.m_varInputs.at(i).prm.offtAddr<<"\n";
        text<<"----Bytes: "<<dd.m_varInputs.at(i).prm.bytes<<"\n";
    }

    text<<"Curve Data:"<<"\n";
    text <<qSetFieldWidth(15) << left <<"time(s)"<<"values";
    text<<qSetFieldWidth(0) << left<<endl;
    for (int i = 0; i < dd.m_sData.keys.size(); i++) {
        text <<qSetFieldWidth(15) << left <<dd.m_sData.keys.at(i)<<dd.m_sData.values.at(i);
        text<<qSetFieldWidth(0) << left<<endl;
    }
}

void ICurve::saveCurve(QDataStream &data)
{
    savePrepare();
    data<<dd;
}

void ICurve::readCurve(QDataStream &data)
{
    data>>dd;
}


void ICurve::fillConstInputsPrm(int inx, const CurvePrm &prm)
{
  if(inx<dd.m_constInputs.size())
   dd.m_constInputs[inx].prm=prm;
}

void ICurve::fillVarInputsPrm(int inx, const CurvePrm &prm)
{
  if(inx<dd.m_varInputs.size())
    dd.m_varInputs[inx].prm=prm;
}

void ICurve::setConstInputK(int channel, double value)
{
  if(channel<dd.m_constInputs.size())
  {
    dd.m_constInputs[channel].constK=value;
  }
}

void ICurve::setVarInputVector(int channel, const QVector<double> &in)
{
  if(channel<dd.m_varInputs.size())
  {
    dd.m_varInputs[channel].datas.clear();
    dd.m_varInputs[channel].datas.append(in);
  }
}

int ICurve::devInx() const
{
  return dd.m_devInx;
}

void ICurve::setDevInx(int devInx)
{
  dd.m_devInx = devInx;
}

QString ICurve::devName() const
{
  QByteArray byte;
  byte.append(65+dd.m_devInx);
  qDebug()<<"devInx "<<dd.m_devInx<<"name "<<QString::fromLatin1(byte);
  return QString::fromLatin1(byte);
}

double ICurve::samplInterval() const
{
  return dd.m_samplInterval;
}

void ICurve::setSamplInterval(int samplIntervalScale)
{
  dd.m_samplInterval = samplIntervalScale*SAMPLING_INTERVAL_US*0.000001;
  dd.m_currentTime = 0;
  dd.m_cData.keys.clear();
  dd.m_cData.values.clear();
  dd.m_sData.keys.clear();
  dd.m_sData.values.clear();
}

void ICurve::adjustData()
{
  //乘以单位
  for(int i=0;i<dd.m_cData.values.size();i++)
  {
    double v=dd.m_cData.values.at(i)*dd.m_k;
    dd.m_cData.values.replace(i,v);
  }
  dd.m_sData.values.append(dd.m_cData.values);


  qint32 overSize=dd.m_sData.values.size()- dd.m_storePointCount;
  if(overSize>0)
  {
//    dd.m_sData.keys.remove(0,overSize);
    dd.m_sData.values.remove(0,overSize);
//    qDebug()<<"store data size = "<<dd.m_sData.values.size();
  }

}

void ICurve::updateCurrentTime()
{
  quint32 size=dd.m_varInputs.at(0).datas.size();
//  qDebug()<<"curve size"<<size;

  dd.m_cData.keys.clear();
  for(quint32 i=0;i<size;i++)
  {
    dd.m_currentTime = dd.m_currentTime+dd.m_samplInterval;//坐标s显示
//    dd.m_sData.keys.append(dd.m_currentTime);
    dd.m_cData.keys.append(dd.m_currentTime);
  }
//  qDebug()<<"dd.m_currentTime"<<dd.m_currentTime;
}

void ICurve::setStorePointCount(quint32 storePointCount)
{
  dd.m_storePointCount = storePointCount;
}

int ICurve::axisInx() const
{
    return dd.m_axisInx;
}

void ICurve::setAxisInx(int axisInx)
{
    dd.m_axisInx = axisInx;
    dd.m_dspInx = axisInx/2;
}

QColor ICurve::color() const
{
  return dd.m_color;
}

void ICurve::setColor(const QColor &color)
{
  dd.m_color = color;
}

bool ICurve::isDraw() const
{
  return  dd.m_isDraw;
}

void ICurve::setIsDraw(bool isDraw)
{
  dd.m_isDraw = isDraw;
}

QList<CurveVar> &ICurve::varInputs()
{
  return dd.m_varInputs;
}


QList<CurveConst> &ICurve::constInputs()
{
  return dd.m_constInputs;
}

int ICurve::dspInx() const
{
  return dd.m_dspInx;
}

void ICurve::setDspInx(int dspInx)
{
  dd.m_dspInx = dspInx;
}

void ICurve::setAxisCount(int axisCount)
{
  dd.m_axisCount = axisCount;
}

int ICurve::axisCount() const
{
  return dd.m_axisCount;
}

CurveData *ICurve::cData()
{
  return &(dd.m_cData);
}

CurveData *ICurve::sData()
{
  return &(dd.m_sData);
}

void ICurve::savePrepare()
{
  dd.m_sData.keys.clear();
  for(int i = dd.m_sData.values.size();i >0; i--)
  {
    double time = dd.m_currentTime - dd.m_samplInterval*i;
    dd.m_sData.keys.append(time);
  }
}

//QString ICurve::pluginName() const
//{
//  return dd.m_pluginName;
//}

//void ICurve::setPluginName(const QString &name)
//{
//  dd.m_pluginName = name;
//}

QStringList ICurve::constInputKeys()
{
  QStringList list;
  for(int i=0;i<dd.m_constInputs.size();i++)
    list.append(dd.m_constInputs.at(i).keyName);
  return list;
}

QStringList ICurve::varInputsKeys()
{
  QStringList list;
  for(int i=0;i<dd.m_varInputs.size();i++)
    list.append(dd.m_varInputs.at(i).keyName);
  return list;
}

void ICurve::addConstInputByName(const QString &name)
{
  CurveConst constPrm;
  constPrm.keyName=name;
  dd.m_constInputs.append(constPrm);
}

void ICurve::addVarInputByName(const QString &name)
{
  CurveVar var;
  var.keyName=name;
  dd.m_varInputs.append(var);
}

void ICurve::addUnit(const QString &uName, double k)
{
  dd.m_unitsHash.insert(uName,k);
  dd.m_unitNameList.append(uName);
}

void ICurve::setUnit(const QString &uName)
{
  if(dd.m_unitsHash.contains(uName))
  {
    dd.m_unitName=uName;
    dd.m_k=dd.m_unitsHash.value(uName);
  }
}

double ICurve::unitValue(const QString &uName)
{
  double v = 1;
  if(dd.m_unitsHash.contains(uName))
  {
    v=dd.m_unitsHash.value(uName);
  }
  return v;
}

double ICurve::curUnitK()
{
  return dd.m_k;
}

QString ICurve::curUnitName()
{
  return dd.m_unitName;
}

QStringList ICurve::unitNames()
{
  return dd.m_unitNameList;
}

ICurvePrivate::ICurvePrivate()
{
  m_sData.keys.append(0);
  m_sData.values.append(0);
  m_k = 1;
  m_isDraw=true;
  m_color=QColor(Qt::black);
  m_currentTime = 0;
  m_samplInterval=62.5*0.000001;
  m_storePointCount=10*1000000/62.5;
  m_axisCount = 4;
  m_unitName = "NULL";
}

QDataStream &operator<<(QDataStream &out, const ICurvePrivate &par)
{
    out<<par.m_pluginName;
    qDebug()<<"pluginName"<<par.m_pluginName;
    out<<par.m_devInx;
    qDebug()<<"devInx"<<par.m_devInx;
    out<<par.m_axisInx;
    qDebug()<<"axisInx"<<par.m_axisInx;
    out<<par.m_axisCount;
    qDebug()<<"axisCount"<<par.m_axisCount;
    out<<par.m_name;
    qDebug()<<"name"<<par.m_name;
    out<<par.m_note;
    qDebug()<<"note"<<par.m_note;
    out<<par.m_color;
    out<<par.m_isDraw;
    qDebug()<<"isDraw"<<par.m_isDraw;
    out<<par.m_unitName;
    qDebug()<<"unitName"<<par.m_unitName;

    out<<par.m_unitNameList;
    //out<<par.m_unitNameList.at(0)<<par.m_unitNameList.at(1);
    qDebug()<<"unitname size"<<par.m_unitNameList.size();

//    out<<par.m_unitsHash;
//    qDebug()<<"unithash size"<<par.m_unitsHash.keys().size();

    for (int i = 0; i < par.m_unitNameList.size(); i++) {
    //for (int i = 0; i < 2; i++) {
        qDebug()<<"unitName"<<par.m_unitNameList.at(i);
        qDebug()<<"unitValue"<<par.m_unitsHash.value(par.m_unitNameList.at(i), 1);
        out<<par.m_unitsHash.value(par.m_unitNameList.at(i), 1);
    }

    out<<par.m_constInputs.size();
    qDebug()<<"constSize"<<par.m_constInputs.size();
    for (int i = 0; i < par.m_constInputs.size(); i++) {
        out<<par.m_constInputs.at(i).keyName;
        qDebug()<<"key"<<par.m_constInputs.at(i).keyName;
        out<<par.m_constInputs.at(i).prm.baseAddr;
        qDebug()<<"baseAdd"<<par.m_constInputs.at(i).prm.baseAddr;
        out<<par.m_constInputs.at(i).prm.offtAddr;
        qDebug()<<"offAdd"<<par.m_constInputs.at(i).prm.offtAddr;
        out<<par.m_constInputs.at(i).prm.bytes;
        qDebug()<<"bytes"<<par.m_constInputs.at(i).prm.bytes;
    }

    out<<par.m_varInputs.size();
    qDebug()<<"varSize"<<par.m_varInputs.size();
    for (int i = 0; i < par.m_varInputs.size(); i++) {
        out<<par.m_varInputs.at(i).keyName;
        qDebug()<<"key"<<par.m_varInputs.at(i).keyName;
        out<<par.m_varInputs.at(i).prm.baseAddr;
        qDebug()<<"baseAdd"<<par.m_varInputs.at(i).prm.baseAddr;
        out<<par.m_varInputs.at(i).prm.offtAddr;
        qDebug()<<"offAdd"<<par.m_varInputs.at(i).prm.offtAddr;
        out<<par.m_varInputs.at(i).prm.bytes;
        qDebug()<<"bytes"<<par.m_varInputs.at(i).prm.bytes;
    }

    out<<par.m_sData.keys;
    qDebug()<<"key count"<<par.m_sData.keys.count();
    out<<par.m_sData.values;
    qDebug()<<"value count"<<par.m_sData.values.count();
  return out;
}

QDataStream &operator>>(QDataStream &in, ICurvePrivate &par)
{
    in>>par.m_devInx>>par.m_axisInx>>par.m_axisCount;
    qDebug()<<"dev Index"<<par.m_devInx;
    qDebug()<<"axis Index"<<par.m_axisInx;
    qDebug()<<"axis Count"<<par.m_axisCount;
    in>>par.m_name>>par.m_note;
    qDebug()<<"name"<<par.m_name;
    qDebug()<<"note"<<par.m_note;
    in>>par.m_color;
    in>>par.m_isDraw>>par.m_unitName;
    qDebug()<<"isDraw"<<par.m_isDraw;
    qDebug()<<"unitname"<<par.m_unitName;

    in>>par.m_unitNameList;
//    QString unit1;
//    QString unit2;
//    in>>unit1>>unit2;

//    par.m_unitNameList.append(unit1);
//    par.m_unitNameList.append(unit2);
    qDebug()<<"unitname size"<<par.m_unitNameList.size();
//    in>>par.m_unitsHash;
//    qDebug()<<"unithash size"<<par.m_unitsHash.keys().size();

    for (int i = 0; i < par.m_unitNameList.size(); i++) {
    //for (int i = 0; i < 2; i++) {
        qDebug()<<"unitName"<<par.m_unitNameList.at(i);
        double temp;
        in>>temp;
        qDebug()<<"unit value"<<temp;
        par.m_unitsHash.insert(par.m_unitNameList.at(i), temp);
    }

    int constInputSize;
    in>>constInputSize;
    qDebug()<<"constInputSize"<<constInputSize;
    for (int i = 0; i < constInputSize; i++) {
        CurveConst curConst;
        in>>curConst.keyName;
        qDebug()<<"keyName"<<curConst.keyName;
        in>>curConst.prm.baseAddr;
        qDebug()<<"baseAdd"<<curConst.prm.baseAddr;
        in>>curConst.prm.offtAddr;
        qDebug()<<"offtAdd"<<curConst.prm.offtAddr;
        in>>curConst.prm.bytes;
        qDebug()<<"bytes"<<curConst.prm.bytes;
        par.m_constInputs.append(curConst);
    }

    int varInputSize;
    in>>varInputSize;
    qDebug()<<"varInputSize"<<varInputSize;
    for (int i = 0; i < varInputSize; i++) {
        CurveVar curVar;
        in>>curVar.keyName;
        qDebug()<<"keyName"<<curVar.keyName;
        in>>curVar.prm.baseAddr;
        qDebug()<<"baseAdd"<<curVar.prm.baseAddr;
        in>>curVar.prm.offtAddr;
        qDebug()<<"offtAdd"<<curVar.prm.offtAddr;
        in>>curVar.prm.bytes;
        qDebug()<<"bytes"<<curVar.prm.bytes;
        par.m_varInputs.append(curVar);
    }

    in>>par.m_sData.keys;
    qDebug()<<"key count"<<par.m_sData.keys.count();
    in>>par.m_sData.values;
    qDebug()<<"value count"<<par.m_sData.values.count();
  return in;
}
