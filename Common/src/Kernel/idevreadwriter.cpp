#include "idevreadwriter.h"
#include "gtutils.h"
#include "qttreemanager.h"

#define IDMAPNAME "IdMap.ui"
#define IDMAPNAME_COPY "IdMap_copy.ui"

IDevReadWriter::IDevReadWriter(QObject *parent):QObject(parent)
{
  QString idMapPath=GTUtils::databasePath()+IDMAPNAME;
  bool ok=createIdMapTree(idMapPath);
  Q_ASSERT(ok);
}

bool IDevReadWriter::createIdMapTree(const QString &fileName)
{
  m_idMapTree=QtTreeManager::createTreeWidgetFromXmlFile(fileName);
  return m_idMapTree!=NULL;
}
