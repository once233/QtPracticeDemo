#include "custombutton.h"
#include <QPainter>
#include <QDebug>
#include <QDate>
CustomButton::CustomButton(QWidget *parent)
    : QPushButton(parent), isSelected(false)
{
}

void CustomButton::setBgColor(const QColor &bg_color)
{
    bgcolor = bg_color;
}
void CustomButton::setTextColor(const QColor &t_color)
{
    textcolor = t_color;
}

void CustomButton::setDate(const QDate &date_)
{
    date = date_;
}

void CustomButton::mousePressEvent(QMouseEvent *ev)
{
    // isSelected = !isSelected;
    emit choiseDateInfo(date, daytype);
}

void CustomButton::setDayType(const DayType &daytype_)
{
    daytype = daytype_;
    update();
}

void CustomButton::setSelected(const bool &isSelect)
{
    isSelected = isSelect;
    update();
}

bool CustomButton::getSelected() const
{
    return isSelected;
}

QDate CustomButton::getDate() const
{
    return date;
}

void CustomButton::paintEvent(QPaintEvent *)
{
    QPainter *painter = new QPainter(this);
    painter->setRenderHint(QPainter::Antialiasing);
    if (date == QDate::currentDate()) {
        QPen pen;
        painter->fillRect(0, 0, this->width(), this->height(), QBrush(Qt::red));
        if (isSelected) {
            pen.setBrush(QColor(159, 197, 232));
            painter->setBrush(QColor(159, 197, 232));
            painter->setPen(pen);
            painter->drawEllipse(38, 28, 35, 35);
        }
        pen.setBrush(Qt::white);
        painter->setPen(pen);
    } else {
        painter->fillRect(0, 0, this->width(), this->height(), QBrush(bgcolor));
        QPen pen(textcolor);
        if (isSelected) {
            pen.setBrush(QColor(159, 197, 232));
            painter->setBrush(QColor(159, 197, 232));
            painter->setPen(pen);
            painter->drawEllipse(38, 28, 35, 35);
        }
        pen.setBrush(textcolor);
        painter->setPen(pen);
    }

    painter->drawText(QPoint(45, 50), date.toString("dd"));

    painter->end();
}
