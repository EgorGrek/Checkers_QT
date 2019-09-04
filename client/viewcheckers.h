#ifndef VIEWCHECKERS_H
#define VIEWCHECKERS_H

#include <QGraphicsView>

class ViewCheckers: public QGraphicsView
{
    Q_OBJECT
public:
    ViewCheckers(QGraphicsScene* pScene, QWidget* pwgt = nullptr);

public slots:
    void slotZoomin();
    void slotZoomOut();
};

#endif // VIEWCHECKERS_H
