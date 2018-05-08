#include <QCoreApplication>
#include <QHash>
#include <QDebug>

class CurvePrm
{
public:
  CurvePrm(){}
  quint16 bytes;
  quint16 offtAddr;
  quint16 baseAddr;
};

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  QHash<int ,CurvePrm>prmHash;
  for(int i=0;i<6;i++)
  {
    CurvePrm prm;
    prm.baseAddr = 0;
    prm.bytes = 2;
    prm.offtAddr = 100+i;
    prmHash.insert(i,prm);
  }

  QHashIterator<int ,CurvePrm> it(prmHash);
  while (it.hasNext()) {
    it.next();
    qDebug()<<"key = "<<it.key()<<"offset = "<<it.value().offtAddr;
  }

  return a.exec();
}

