#include "plaintextwidget.h"
#include <QPainter>
#include <QPainterPath>
#include <QtMath>
#define SHADOW_WIDTH 10
PlainTextWidget::PlainTextWidget(QWidget *parent) : QWidget{ parent }
{
}

void PlainTextWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QPainterPath path;
    path.addRoundedRect(
        QRect(SHADOW_WIDTH, SHADOW_WIDTH, this->width() - 2 * SHADOW_WIDTH,
              this->height() - 2 * SHADOW_WIDTH),
        15, 15);
    painter.fillPath(path, QBrush(Qt::white));
    QColor color(92, 118, 255, 50);
    for (int i = 0; i < SHADOW_WIDTH; i++) {
        color.setAlpha(120 - qSqrt(i) * 40);
        painter.setPen(color);
        painter.drawRoundedRect(SHADOW_WIDTH - i, SHADOW_WIDTH - i,
                                this->width() - (SHADOW_WIDTH - i) * 2,
                                this->height() - (SHADOW_WIDTH - i) * 2, 15,
                                15);
    }

    // painter.fillRect(this->rect(), Qt::red);
}
