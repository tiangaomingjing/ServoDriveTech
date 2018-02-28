//#include "anchormainwindow.h"
//#include <QApplication>

//int main(int argc, char *argv[])
//{
//  QApplication a(argc, argv);
//  AnchorMainWindow w;
//  w.show();

//  return a.exec();
//}


#include <QtWidgets>

class Widget : public QGraphicsWidget
{
public:
    Widget(const QColor &color, const QColor &textColor, const QString &caption,
           QGraphicsItem *parent = 0)
        : QGraphicsWidget(parent)
        , caption(caption)
        , color(color)
        , textColor(textColor)
    {
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget * = 0) Q_DECL_OVERRIDE
    {
        QFont font;
        font.setPixelSize(0.75 * qMin(boundingRect().width(), boundingRect().height()));

        painter->fillRect(boundingRect(), color);
        painter->save();
        painter->setFont(font);
        painter->setPen(textColor);
        painter->drawText(boundingRect(), Qt::AlignCenter, caption);
        painter->restore();
    }

private:
    QString caption;
    QColor color;
    QColor textColor;
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QGraphicsScene *scene = new QGraphicsScene();

    Widget *a = new Widget(Qt::blue, Qt::white, "a");
    a->setPreferredSize(100, 100);
    Widget *b = new Widget(Qt::green, Qt::black, "b");
    b->setPreferredSize(100, 100);
    Widget *c = new Widget(Qt::red, Qt::black, "c");
    c->setPreferredSize(100, 100);

    QGraphicsAnchorLayout *layout = new QGraphicsAnchorLayout();
/*
    //! [adding a corner anchor in two steps]
    layout->addAnchor(a, Qt::AnchorTop, layout, Qt::AnchorTop);
    layout->addAnchor(a, Qt::AnchorLeft, layout, Qt::AnchorLeft);
    //! [adding a corner anchor in two steps]
*/
    //! [adding a corner anchor]
    layout->addCornerAnchors(a, Qt::TopLeftCorner, layout, Qt::TopLeftCorner);
    //! [adding a corner anchor]

    layout->setSpacing(5);
    //! [adding anchors]
    layout->addAnchor(b, Qt::AnchorLeft, a, Qt::AnchorRight);
    layout->addAnchor(b, Qt::AnchorTop, a, Qt::AnchorBottom);
    //! [adding anchors]

    layout->setSpacing(60);
    // Place a third widget below the second.
    layout->addAnchor(b, Qt::AnchorBottom, c, Qt::AnchorTop);

/*
    //! [adding anchors to match sizes in two steps]
    layout->addAnchor(b, Qt::AnchorLeft, c, Qt::AnchorLeft);
    layout->addAnchor(b, Qt::AnchorRight, c, Qt::AnchorRight);
    //! [adding anchors to match sizes in two steps]
*/

    //! [adding anchors to match sizes]
    layout->addAnchors(b, c, Qt::Horizontal);
    //! [adding anchors to match sizes]

    // Anchor the bottom-right corner of the third widget to the bottom-right
    // corner of the layout.
    layout->setSpacing(0);
    layout->addCornerAnchors(c, Qt::BottomRightCorner, layout, Qt::BottomRightCorner);

    QGraphicsWidget *w = new QGraphicsWidget(0, Qt::Window | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    w->setPos(20, 20);
    w->setMinimumSize(100, 100);
    w->setPreferredSize(320, 240);
    w->setLayout(layout);
    w->setWindowTitle(QApplication::translate("simpleanchorlayout", "QGraphicsAnchorLayout in use"));
    scene->addItem(w);


    QGraphicsView *view = new QGraphicsView();
    view->setScene(scene);
    view->setWindowTitle(QApplication::translate("simpleanchorlayout", "Simple Anchor Layout"));

    view->resize(360, 320);
    view->show();

    return app.exec();
}
