#include "datatimeeditdemo.h"
#include "./ui_datatimeeditdemo.h"
#include <QMetaEnum>
#include <QDebug>
DataTimeEditDemo::DataTimeEditDemo(QWidget *parent)
    : QWidget(parent), ui(new Ui::DataTimeEditDemo), is_seconddate(false)
{
    ui->setupUi(this);

    datelabel << ui->lb_date1 << ui->lb_date2 << ui->lb_date3 << ui->lb_date4
              << ui->lb_date5 << ui->lb_date6 << ui->lb_date7 << ui->lb_date8
              << ui->lb_date9 << ui->lb_date10 << ui->lb_date11 << ui->lb_date12
              << ui->lb_date13 << ui->lb_date14 << ui->lb_date15
              << ui->lb_date16 << ui->lb_date17 << ui->lb_date18
              << ui->lb_date19 << ui->lb_date20 << ui->lb_date21
              << ui->lb_date22 << ui->lb_date23 << ui->lb_date24
              << ui->lb_date25 << ui->lb_date26 << ui->lb_date27
              << ui->lb_date28 << ui->lb_date29 << ui->lb_date30
              << ui->lb_date31 << ui->lb_date32 << ui->lb_date33
              << ui->lb_date34 << ui->lb_date35 << ui->lb_date36
              << ui->lb_date37 << ui->lb_date38 << ui->lb_date39
              << ui->lb_date40 << ui->lb_date41 << ui->lb_date42;

    date = QDate::currentDate();

    initDate();
    initConnect();
}

void DataTimeEditDemo::initConnect()
{ //批量连接信号槽，所有对象指针记录在datelabel
    for (CustomButton *sender : datelabel) {
        connect(sender, SIGNAL(choiseDateInfo(QDate, CustomButton::DayType)),
                SLOT(onDayChoised(QDate, CustomButton::DayType)));
    }
}

void DataTimeEditDemo::onDayChoised(const QDate &date,
                                    const CustomButton::DayType &daytype)
{
    switch (daytype) {
    case CustomButton::NEXT_MONTH: {
        showNextMonth();
        break;
    }

    case CustomButton::PRE_MONTH: {
        showPreviousMonth();
        break;
    }
    case CustomButton::CUR_MONTH: {
        //选择日期为当月日期

        setChoisedSelected(sender(), date);

        setChoisedDate();
        //选择日期为上月日期

        //选择日期为下月日期

        //选择第三个日期

        //选择日期为已选择的日期1

        //选择日期为已选择的日期2

        break;
    }
    }
}
//计算是否闰年
bool DataTimeEditDemo::isLoopYear(int year)
{
    return (((0 == (year % 4)) && (0 != (year % 100))) || (0 == (year % 400)));
}

//计算指定年月该月共多少天
int DataTimeEditDemo::getMonthDays(int year, int month)
{
    int countDay = 0;
    int loopDay = isLoopYear(year) ? 1 : 0;

    switch (month) {
    case 1:
        countDay = 31;
        break;
    case 2:
        countDay = 28 + loopDay;
        break;
    case 3:
        countDay = 31;
        break;
    case 4:
        countDay = 30;
        break;
    case 5:
        countDay = 31;
        break;
    case 6:
        countDay = 30;
        break;
    case 7:
        countDay = 31;
        break;
    case 8:
        countDay = 31;
        break;
    case 9:
        countDay = 30;
        break;
    case 10:
        countDay = 31;
        break;
    case 11:
        countDay = 30;
        break;
    case 12:
        countDay = 31;
        break;
    default:
        countDay = 30;
        break;
    }

    return countDay;
}

//计算指定年月对应到该月共多少天
int DataTimeEditDemo::getTotalMonthDays(int year, int month)
{
    int countDay = 0;
    int loopDay = isLoopYear(year) ? 1 : 0;

    switch (month) {
    case 1:
        countDay = 0;
        break;
    case 2:
        countDay = 31;
        break;
    case 3:
        countDay = 59 + loopDay;
        break;
    case 4:
        countDay = 90 + loopDay;
        break;
    case 5:
        countDay = 120 + loopDay;
        break;
    case 6:
        countDay = 151 + loopDay;
        break;
    case 7:
        countDay = 181 + loopDay;
        break;
    case 8:
        countDay = 212 + loopDay;
        break;
    case 9:
        countDay = 243 + loopDay;
        break;
    case 10:
        countDay = 273 + loopDay;
        break;
    case 11:
        countDay = 304 + loopDay;
        break;
    case 12:
        countDay = 334 + loopDay;
        break;
    default:
        countDay = 0;
        break;
    }

    return countDay;
}

//计算指定年月对应星期几
int DataTimeEditDemo::getFirstDayOfWeek(int year, int month)
{
    int week = 0;
    week = (year + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400) % 7;
    week += getTotalMonthDays(year, month);
    week = week % 7;
    return week;
}

//初始化日期面板
void DataTimeEditDemo::initDate()
{
    int year = date.year();
    int month = date.month();
    // int day = date.day();

    ui->lb_date->setText(QString("%1年%2月").arg(year).arg(month));

    //首先判断当前月的第一天是星期几
    int week = getFirstDayOfWeek(year, month);
    //当前月天数
    int countDay = getMonthDays(year, month);
    //上月天数
    int countDayPre =
        getMonthDays(1 == month ? year - 1 : year, 1 == month ? 12 : month - 1);

    //如果上月天数上月刚好一周则另外处理
    int startPre, endPre, startNext, endNext, index, tempYear, tempMonth,
        tempDay;
    if (0 == week) {
        startPre = 0;
        endPre = 7;
        startNext = 0;
        endNext = 42 - (countDay + 7);
    } else {
        startPre = 0;
        endPre = week;
        startNext = week + countDay;
        endNext = 42;
    }

    //纠正1月份前面部分偏差,1月份前面部分是上一年12月份
    tempYear = year;
    tempMonth = month - 1;
    if (tempMonth < 1) {
        tempYear--;
        tempMonth = 12;
    }

    //显示上月天数
    for (int i = startPre; i < endPre; i++) {
        index = i;
        tempDay = countDayPre - endPre + i + 1;
        QDate date(tempYear, tempMonth, tempDay);
        datelabel[index]->setDate(date);
        datelabel[index]->setBgColor(QColor(213, 213, 213));
        datelabel[index]->setTextColor(QColor());
        datelabel[index]->setDayType(CustomButton::DayType::PRE_MONTH);
        datelabel[index]->setSelected(false);
    }

    //纠正12月份后面部分偏差,12月份后面部分是下一年1月份
    tempYear = year;
    tempMonth = month + 1;
    if (tempMonth > 12) {
        tempYear++;
        tempMonth = 1;
    }

    //显示下月天数
    for (int i = startNext; i < endNext; i++) {
        index = 42 - endNext + i;
        tempDay = i - startNext + 1;
        QDate date(tempYear, tempMonth, tempDay);
        datelabel[index]->setDate(date);
        datelabel[index]->setBgColor(QColor(213, 213, 213));
        datelabel[index]->setDayType(CustomButton::DayType::NEXT_MONTH);
        datelabel[index]->setSelected(false);
    }

    //重新置为当前年月
    tempYear = year;
    tempMonth = month;

    //显示当前月
    for (int i = week; i < (countDay + week); i++) {
        index = (0 == week ? (i + 7) : i);
        tempDay = i - week + 1;

        QDate date(tempYear, tempMonth, tempDay);
        if (0 == (i % 7) || 6 == (i % 7)) {
            if (choised_date.isEmpty()) {
                datelabel[index]->setDate(date);
                datelabel[index]->setBgColor(QColor(250, 250, 250));
                datelabel[index]->setTextColor("red");
                datelabel[index]->setDayType(CustomButton::DayType::CUR_MONTH);
                datelabel[index]->setSelected(false);
            } else {
                datelabel[index]->setSelected(false);
                datelabel[index]->setDate(date);
                datelabel[index]->setBgColor(QColor(250, 250, 250));
                datelabel[index]->setTextColor("red");
                datelabel[index]->setDayType(CustomButton::DayType::CUR_MONTH);
                for (QDate cdate : choised_date)
                    if (date == cdate) {
                        qDebug() << date << cdate;
                        datelabel[index]->setSelected(true);
                    }
            }
        }

        else {
            if (choised_date.isEmpty()) {
                datelabel[index]->setDate(date);
                datelabel[index]->setBgColor(QColor(250, 250, 250));
                datelabel[index]->setDayType(CustomButton::DayType::CUR_MONTH);
                datelabel[index]->setSelected(false);
            } else {
                datelabel[index]->setSelected(false);
                datelabel[index]->setDate(date);
                datelabel[index]->setBgColor(QColor(250, 250, 250));
                datelabel[index]->setDayType(CustomButton::DayType::CUR_MONTH);
                for (QDate cdate : choised_date)
                    if (date == cdate) {
                        qDebug() << date << cdate;
                        datelabel[index]->setSelected(true);
                    }
            }
        }
    }
}

void DataTimeEditDemo::yearChanged(const QString &arg1)
{
    int year = arg1.mid(0, arg1.length() - 1).toInt();
    int month = date.month();
    int day = date.day();
    dateChanged(year, month, day);
}

void DataTimeEditDemo::monthChanged(const QString &arg1)
{
    int year = date.year();
    int month = arg1.mid(0, arg1.length() - 1).toInt();
    int day = date.day();
    dateChanged(year, month, day);
}

void DataTimeEditDemo::dateChanged(int year, int month, int day)
{
    // 如果原有天大于28则设置为1,防止出错
    date.setDate(year, month, day > 28 ? 1 : day);
    initDate();
}

void DataTimeEditDemo::showPreviousMonth()
{
    int year = date.year();
    int month = date.month();
    int day = date.day();
    if (year <= 1901 && month == 1) {
        return;
    }
    month--;
    if (month < 1) {
        month = 12;
        year--;
    }
    dateChanged(year, month, day);
}

void DataTimeEditDemo::showNextMonth()
{
    int year = date.year();
    int month = date.month();
    int day = date.day();
    if (year >= 2099 && month == 12) {
        return;
    }

    month++;
    if (month > 12) {
        month = 1;
        year++;
    }
    dateChanged(year, month, day);
}

DataTimeEditDemo::~DataTimeEditDemo()
{
    delete ui;
}

void DataTimeEditDemo::on_btn_lastmonth_clicked()
{
    showPreviousMonth();
}

void DataTimeEditDemo::on_btn_nextmonth_clicked()
{
    showNextMonth();
}

void DataTimeEditDemo::showPreviousYear()
{
    int year = date.year();
    int month = date.month();
    int day = date.day();
    if (year <= 1901) {
        return;
    }
    year--;
    dateChanged(year, month, day);
}
void DataTimeEditDemo::showNextYear()
{
    int year = date.year();
    int month = date.month();
    int day = date.day();
    if (year >= 2099) {
        return;
    }
    year++;
    dateChanged(year, month, day);
}

void DataTimeEditDemo::showToday()
{
    date = QDate::currentDate();
    initDate();
}

void DataTimeEditDemo::on_btn_nextyear_clicked()
{
    showNextYear();
}

void DataTimeEditDemo::on_btn_lastyear_clicked()
{
    showPreviousYear();
}

void DataTimeEditDemo::on_btn_curday_clicked()
{
    showToday();
}

void DataTimeEditDemo::setChoisedSelected(QObject *sender, const QDate &date)
{
    CustomButton *pbtn = dynamic_cast<CustomButton *>(sender);
    // 当前日期为选择的状态，如果当前按钮未选中，则设置选中
    if (!pbtn->getSelected()) {
        // 因为只会选择两个日期，数组永远保持只有两个元素
        if (selected_btnlist.size() == 2)
            clearSelectedInfo();
        pbtn->setSelected(true);
        // 保存选中按钮信息
        selected_btnlist.push_back(pbtn);
        choised_date.push_back(date);
    }
    // 如果按钮已选中，则取消选中
    else {
        pbtn->setSelected(false);
        // 取消选中时，去除取消按钮信息
        // 如果要取消选中的日期记录在数组的第一个位置
        if (date == selected_btnlist.at(0)->getDate()) {
            selected_btnlist.removeFirst();
            choised_date.removeFirst();
        }
        // 否则就是在第二个位置
        else {
            selected_btnlist.removeLast();
            choised_date.removeLast();
        }
    }
}

void DataTimeEditDemo::clearSelectedInfo()
{
    for (CustomButton *pbtn : selected_btnlist)
        pbtn->setSelected(false);
    selected_btnlist.clear();
    choised_date.clear();
}
// 设置已选择日期提示
void DataTimeEditDemo::setChoisedDate()
{
    if (choised_date.isEmpty()) {
        ui->lb_choiseddate1->clear();
        ui->lb_choiseddate2->clear();
    } else if (choised_date.size() == 1) {
        ui->lb_choiseddate1->setText(
            choised_date.front().toString("yyyy年MM月dd日"));
        ui->lb_choiseddate2->clear();
    } else {
        if (choised_date.front() < choised_date.last()) {
            ui->lb_choiseddate1->setText(
                choised_date.front().toString("yyyy年MM月dd日"));
            ui->lb_choiseddate2->setText(
                choised_date.last().toString("yyyy年MM月dd日"));
        } else {
            ui->lb_choiseddate1->setText(
                choised_date.last().toString("yyyy年MM月dd日"));
            ui->lb_choiseddate2->setText(
                choised_date.front().toString("yyyy年MM月dd日"));
        }
    }
}
// void DataTimeEditDemo::clearSelected()
//{
//     for (QObject *obj : selectedlist) {
//         CustomButton *pBtn = dynamic_cast<CustomButton *>(obj);
//         pBtn->setSelected(false);
//     }
//     selectedlist.clear();
// }

// void setChoisedSelected(QVector<QDate> selectedDate);
