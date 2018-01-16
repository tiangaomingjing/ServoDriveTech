#ifndef GLOBALDEF
#define GLOBALDEF
#include <QtCore>
#include <QApplication>
#include <QTime>
#include "Basetype_def.h"

class QTreeWidget;
class QTreeWidgetItem;

#define DEVICE_DESCRIBE "device"
#define DSP_NAME "dsp"
#define FPGA_NAME "fpga"
#define FILENAME_FUNCCMD "PrmFuncCmd"
#define XMLFILE_ROW_INDEX 0
#define XMLFILE_CHILD_VERSION_ROW_INDEX 0
#define XMLFILE_NODE_NAME "XmlFileInformation"
#define ICON_FILE_PATH QString("../resource/icon/")
#define RESOURCE_FILE_PATH QString("../resource/File/")
#define ICON_STATUS_DISCONNECT QString("disconnect.png")
#define ICON_STATUS_CONNECT QString("connect.png")

enum COL_FLASH_RAM_INDEX
{
  COL_NAME,
  COL_VALUE,
  COL_TYPE,
  COL_ADDRESS,
  COL_ISBIT,
  COL_BITSTART,
  COL_BITWIDTH,
  COL_AXISNUM,
  COL_HASCHILD,
  COL_CHILDNUM,
  COL_PARENT
};

enum COL_FUNC_EXTENSION_INDEX
{
  COL_FUNC_EXTENSION_NAME=0,
  COL_FUNC_EXTENSION_PARAMETER,
  COL_FUNC_EXTENSION_INTRODUCTION
};

enum TREE{
    TREE_NAME = 0,
    TREE_VALUE = 1,
    TREE_SCALE = 3,
    TREE_TYPE = 5,
    TREE_ADDRESS = 6,
};

enum IDMAP {
    IDMAP_ID = 0,
    IDMAP_TYPE = 1,
    IDMAP_MODE = 2,
    IDMAP_NICKNAME = 3
};

enum CMD_MODE{
  MODE_WRITE = 0,
  MODE_READ = 1
};

namespace GLO {
    void delayms(quint16 ms);
    QTreeWidgetItem* findItem(QString text, QTreeWidget* tree, int col);
    QTreeWidgetItem* findItemByValue(Uint8* value, Uint16 num, QTreeWidget *tree);
    QString getPath(QTreeWidgetItem *item);
}


#endif // GLOBALDEF

