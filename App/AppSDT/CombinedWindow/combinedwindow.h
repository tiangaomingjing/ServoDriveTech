#ifndef COMBINEDWINDOW_H
#define COMBINEDWINDOW_H

#include <QMainWindow>
class QVBoxLayout;
class QDesktopWidget;
class QSizeGrip;

namespace Ui {
class CombinedWindow;
}

class CombinedWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CombinedWindow(QWidget *parent = 0);
    ~CombinedWindow();

    void insertWindow(QMainWindow *w);
    void showMaximized();
protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);
    void closeEvent(QCloseEvent *event);
    //void paintEvent(QPaintEvent *event);


private:
    Ui::CombinedWindow *ui;
    QPoint m_mousePoint;
    bool m_mousePressed;
    bool m_isMax;
    QSize m_size;
    QPixmap m_closePix;
    QPixmap m_maxPix;
    QPixmap m_minPix;
    QPixmap m_normalPix;
    QMainWindow *m_bottomWindow;
    QDesktopWidget *m_desktop;
    QSizeGrip *m_sizeGrip;

private:
    void setWidgetIcon();
private slots:
    void onActionMaxClicked();
    void onActionMinClicked();
    void onOptFaceCssChanged(const QString &css);

    void onTitleChanged(const QString &title);
};

#endif // COMBINEDWINDOW_H
