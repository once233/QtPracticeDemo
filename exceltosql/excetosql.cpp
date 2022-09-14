#include "excetosql.h"
#include "./ui_excetosql.h"

ExceToSql::ExceToSql(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ExceToSql)
{
    ui->setupUi(this);
}

ExceToSql::~ExceToSql()
{
    delete ui;
}

