#ifndef TREE_H
#define TREE_H

#include <QTreeWidget>

class Tree : public QTreeWidget
{
  Q_OBJECT
public:
  explicit Tree(QWidget *parent = 0);

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

signals:

public slots:
};

#endif // TREE_H
