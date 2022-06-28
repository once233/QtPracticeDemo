#ifndef PAINTEDITEM_H
#define PAINTEDITEM_H

#include <QQuickPaintedItem>
#include <QPainter>
#include <QPixmap>
#include <QStack>

class PaintedItem : public QQuickPaintedItem
{
    Q_OBJECT
    QPixmap *basemap;
    QPixmap drawp;

    // QPainter *mpaint;
    QVector<QPixmap> undocache;
    QVector<QPixmap> redocache;

    int undo_index;
    int redo_index;

public:
    PaintedItem();
    void paint(QPainter *painter);

    Q_INVOKABLE void eraserArea(const int &x, const int &y, const int &w,
                                const int &h);
    Q_INVOKABLE void drawLine(const QPointF &pre_point,
                              const QPointF &cur_point);
    Q_INVOKABLE void saveMap();

    Q_INVOKABLE void cachePixmap();

    Q_INVOKABLE void undoDraw();
    Q_INVOKABLE void redoDraw();
};

#endif // PAINTEDITEM_H
