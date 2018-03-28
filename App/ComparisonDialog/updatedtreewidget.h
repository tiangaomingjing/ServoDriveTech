#ifndef UPDATEDTREEWIDGET_H
#define UPDATEDTREEWIDGET_H

#include <QWidget>
#include <QDropEvent>
#include <QTreeWidget>
#include <QMimeData>

class UpdatedTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit UpdatedTreeWidget(QWidget *parent = 0);

signals:
    void sendPath(const QString &path);
protected:
    bool dropMimeData(QTreeWidgetItem *, int /*index*/, const QMimeData *data, Qt::DropAction /*action*/);
    QStringList mimeTypes () const;
    Qt::DropActions supportedDropActions () const;
//    void dragEnterEvent(QDragEnterEvent *event);
//    void dropEvent(QDropEvent *event);
public slots:
};

#endif // UPDATEDTREEWIDGET_H
