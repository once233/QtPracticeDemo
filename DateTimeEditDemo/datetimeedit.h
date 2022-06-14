#ifndef DATATIMEEDITDEMO_H
#define DATATIMEEDITDEMO_H

#include <QWidget>
#include <QDate>
#include <QLabel>
#include <QPushButton>
#include <QVector>

#include "custombutton.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class DataTimeEditDemo;
}
QT_END_NAMESPACE

class DataTimeEditDemo : public QWidget
{
    Q_OBJECT

public:
    DataTimeEditDemo(QWidget *parent = nullptr);
    ~DataTimeEditDemo();

private:
    //计算是否闰年
    bool isLoopYear(int year);

    //计算指定年月该月共多少天
    int getMonthDays(int year, int month);

    //计算指定年月对应到该月共多少天
    int getTotalMonthDays(int year, int month);

    //计算指定年月对应星期几
    int getFirstDayOfWeek(int year, int month);

    void initDate();
    void initConnect();

    void yearChanged(const QString &arg1);
    void monthChanged(const QString &arg1);
    void dateChanged(int year, int month, int day);

    void showPreviousMonth();
    void showNextMonth();
    void showPreviousYear();
    void showNextYear();
    void showToday();

    void clearSelectedInfo();
    void setChoisedSelected(QObject *sender, const QDate &date);
    void setChoisedDate(); //设置已选择日期提示

    // void setChoisedSelected(QVector<QDate> selectedDate);
private slots:

    void onDayChoised(const QDate &date, const CustomButton::DayType &daytype);

    void on_btn_lastmonth_clicked();

    void on_btn_nextmonth_clicked();

    void on_btn_nextyear_clicked();

    void on_btn_lastyear_clicked();

    void on_btn_curday_clicked();

private:
    Ui::DataTimeEditDemo *ui;
    QDate date; //当前日期
    QDate tmpdate;
    QVector<CustomButton *> datelabel;
    QVector<QString> stylelist;
    QVector<CustomButton *> selected_btnlist;
    QVector<QDate> choised_date;

    bool is_seconddate;
};
#endif // DATATIMEEDITDEMO_H
