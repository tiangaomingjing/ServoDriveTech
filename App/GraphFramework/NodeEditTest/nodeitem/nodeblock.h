#ifndef NODEBLOCK_H
#define NODEBLOCK_H

#include <QGraphicsProxyWidget>
class NodePort;
class NodeBlock :  public QGraphicsProxyWidget
{
  Q_OBJECT
public:
  explicit NodeBlock(QGraphicsItem *parent = 0);
  ~NodeBlock();

  void setCenterWidget(QWidget *widget,bool hasWrapWidget = false);

  NodePort *leftPort() const;

  NodePort *rightPort() const;

  NodePort *topPort() const;

  NodePort *bottomPort() const;

signals:

public slots:

private slots:
  void onGeometryChanged();

private:
  void setPortsPosition();
private:
  NodePort *m_leftPort;
  NodePort *m_rightPort;
  NodePort *m_topPort;
  NodePort *m_bottomPort;
};

#endif // NODEBLOCK_H
