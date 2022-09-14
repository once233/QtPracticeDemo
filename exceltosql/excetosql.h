#ifndef EXCETOSQL_H
#define EXCETOSQL_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class ExceToSql; }
QT_END_NAMESPACE

class ExceToSql : public QMainWindow
{
    Q_OBJECT

public:
    ExceToSql(QWidget *parent = nullptr);
    ~ExceToSql();

private:
    Ui::ExceToSql *ui;
};
#endif // EXCETOSQL_H
