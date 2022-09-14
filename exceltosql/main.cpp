#include "excetosql.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ExceToSql w;
    w.show();
    return a.exec();
}
