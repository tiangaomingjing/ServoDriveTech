#ifndef SDTGLOBALDEF
#define SDTGLOBALDEF
#include <QObject>

#define GT_NAMESPACE_BEGIN namespace GT {
#define GT_NAMESPACE_END }
#define GT_USE_NAMESPACE using namespace GT;

GT_NAMESPACE_BEGIN
class DeviceConfig
{
public:
  DeviceConfig(){}
  ~DeviceConfig(){}

  quint32 m_devId;
  quint8 m_comType;
  quint8 m_axisNum;
  QString m_typeName;//SD4x
  QString m_modeName;//SD42
  quint32 m_version;

  quint32 m_pwrId;   //id->SD?? 通过一个id映射表获得名字
  quint32 m_ctrId;   //id->SD?? 通过一个id映射表获得名字
};
class GlobalConfig
{
public:
  GlobalConfig();
  ~GlobalConfig();
};
GT_NAMESPACE_END
#endif // SDTGLOBALDEF

