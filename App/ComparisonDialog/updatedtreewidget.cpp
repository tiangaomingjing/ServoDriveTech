#include "updatedtreewidget.h"
#include <QDebug>
#include <QFileInfo>

UpdatedTreeWidget::UpdatedTreeWidget(QWidget *parent) : QTreeWidget(parent)
{
    setAcceptDrops(true);
    setDragDropMode(QAbstractItemView::DragDrop);
    setDragEnabled(true);
    setDropIndicatorShown(true);
}

bool UpdatedTreeWidget::dropMimeData(QTreeWidgetItem *, int, const QMimeData *data, Qt::DropAction)
{
    QList<QUrl> list = data->urls();
    const QFileInfo info(list.first().toLocalFile());
    QString path = info.filePath();
    QString suffix = info.suffix();
    if (suffix.compare("xml") == 0 || suffix.compare("ui") == 0) {
        emit sendPath(path);
    }
    return true;
}

QStringList UpdatedTreeWidget::mimeTypes() const
{
    return QStringList()<<"text/uri-list";
}

Qt::DropActions UpdatedTreeWidget::supportedDropActions() const
{
    return Qt::CopyAction;
}
