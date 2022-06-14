#include "datatimeeditdemo.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // qRegisterMetaType<CustomButton::DayType>("CustomButton::DayType");

    DataTimeEditDemo w;
    w.show();
    return a.exec();
}
