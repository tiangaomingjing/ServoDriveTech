#include "tree.h"

#include <QDebug>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QUrl>
#include <QMimeData>
#include <QMessageBox>

Tree::Tree(QWidget *parent) : QTreeWidget(parent)
{
  setAcceptDrops(true);
  setDragDropMode(QAbstractItemView::DragDrop);
  setDragEnabled(true);
  setDropIndicatorShown(true);
}

void Tree::dragEnterEvent(QDragEnterEvent *event)
{
//  __super::dragEnterEvent(event);
//  if (event->mimeData()->hasUrls())
      event->acceptProposedAction();
      qDebug()<<"enter ..................";
      QList<QUrl> urls = event->mimeData()->urls();
      for(int i=0;i<urls.size();i++)
        QMessageBox::information(0,tr("aaa"),urls.at(i).toString());
}

void Tree::dropEvent(QDropEvent *event)
{
//  __super::dropEvent(event);
  if (event->mimeData()->hasUrls())
  {
      QList<QUrl> urls = event->mimeData()->urls();
      foreach (QUrl url , urls)
      {

        QMessageBox::information(0,tr("aaa"),url.toString());
      }
  }
  qDebug()<<"dropEvent--------------";
}

