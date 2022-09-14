#ifndef PLAINTEXTWIDGET_H
#define PLAINTEXTWIDGET_H

#include <QWidget>

class PlainTextWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlainTextWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *);
signals:
};

#endif // PLAINTEXTWIDGET_H
