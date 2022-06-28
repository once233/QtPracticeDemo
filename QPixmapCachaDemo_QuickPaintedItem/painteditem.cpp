#include "painteditem.h"

#include <QPixmapCache>
PaintedItem::PaintedItem() : drawp(840, 880)

{
    basemap = new QPixmap(":/093710484.png");
    drawp.fill(Qt::transparent);
    undo_index = 0;
    redo_index = 0;
    undocache.append(drawp);
}

void PaintedItem::paint(QPainter *painter)
{
    painter->drawPixmap(0, 0, 840, 880, *basemap);
    painter->drawPixmap(0, 0, 840, 880, drawp);
}

void PaintedItem::drawLine(const QPointF &pre_point, const QPointF &cur_point)
{
    QPainter mpaint(&drawp);
    mpaint.setPen(QPen(Qt::white, 10));
    mpaint.setCompositionMode(QPainter::CompositionMode_SourceOver);
    mpaint.drawLine(pre_point, cur_point);

    update();
}

void PaintedItem::saveMap()
{
    redocache.clear();
    undocache.clear();
    undocache.append(drawp);
    undo_index = 0;
    redo_index = 0;
    drawp.save("savemap.png");
}

void PaintedItem::eraserArea(const int &x, const int &y, const int &w,
                             const int &h)
{
    QPainter mpaint(&drawp);
    mpaint.setCompositionMode(QPainter::CompositionMode_Clear);
    mpaint.eraseRect(x, y, w, h);

    update();
}

void PaintedItem::undoDraw()
{
    if (undo_index != 0) {
        undo_index--;
        drawp = undocache[undo_index];
        redocache.append(undocache[undo_index + 1]);
        redo_index++;
        undocache.pop_back();
        update();
    }
}

void PaintedItem::redoDraw()
{
    if (redo_index > 0) {
        drawp = redocache.last();
        undocache.append(redocache.last());
        redocache.pop_back();
        redo_index--;
        undo_index++;
        update();
    }
}

void PaintedItem::cachePixmap()
{
    undo_index++;
    undocache.append(drawp);
}
