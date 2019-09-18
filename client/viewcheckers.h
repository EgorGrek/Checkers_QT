#ifndef VIEWCHECKERS_H
#define VIEWCHECKERS_H

#include <QGraphicsView>

class ViewCheckers: public QGraphicsView
{
    Q_OBJECT
public:
    ViewCheckers(QGraphicsScene* pScene, QWidget* pwgt = nullptr);

protected:
    void wheelEvent(QWheelEvent * event);

public slots:
    void slotZoomIn();
    void slotZoomOut();
};

#endif // VIEWCHECKERS_H
