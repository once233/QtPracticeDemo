#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QPushButton>
#include <QDate>
class CustomButton : public QPushButton
{
    Q_OBJECT
public:
    enum DayType
    {
        PRE_MONTH = 1,
        CUR_MONTH,
        NEXT_MONTH
    };

    // Q_ENUMS(DayType)

public:
    CustomButton(QWidget *parent = nullptr);
    void setDate(const QDate &date_);
    void setBgColor(const QColor &bg_color);
    void setTextColor(const QColor &t_color);
    void setDayType(const DayType &daytype_);
    void setSelected(const bool &isSelect);

    bool getSelected() const;
    QDate getDate() const;

signals:
    void choiseDateInfo(const QDate &date,
                        const CustomButton::DayType &daytype);

private:
    QDate date;
    QColor bgcolor;
    QColor textcolor;
    DayType daytype;
    QDate curDate;
    bool isSelected;

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *ev);
};

#endif // CUSTOMBUTTON_H
