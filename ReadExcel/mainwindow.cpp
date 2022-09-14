#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAxObject>
#include <QDebug>
#include <QFileDialog>
#include <QStandardPaths>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QSqlError>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // QMap<QString, float> map;
    //  readEnvXlsFile("1", map);
}

// 批量讀取xls到map
int MainWindow::readEnvXlsFile(QString FileName, QMap<QString, float> &map)
{
    QAxObject *excel = NULL;
    QAxObject *workbooks = NULL;
    QAxObject *workbook = NULL;
    excel = new QAxObject("Excel.Application");
    if (!excel) {
        qDebug() << "EXCEL對象丟失!";
    }
    excel->dynamicCall("SetVisible(bool)", false);
    workbooks = excel->querySubObject("WorkBooks");
    workbook = workbooks->querySubObject("Open(QString, QVariant)", FileName);
    QAxObject *worksheet =
        workbook->querySubObject("WorkSheets(int)", 1); //打開第一個sheet
    QAxObject *usedrange =
        worksheet->querySubObject("UsedRange"); //獲取該sheet的使用範圍對象
    QAxObject *rows = usedrange->querySubObject("Rows");
    QAxObject *columns = usedrange->querySubObject("Columns");
    int intRows = rows->property("Count").toInt();
    int intCols = columns->property("Count").toInt();
    qDebug() << "xls行數：" << intRows;
    qDebug() << "xls列數：" << intCols;

    // 批量載入數據，這裏默認讀取B13:C最後
    QString Range = "B13:C" + QString::number(intRows);
    QAxObject *allEnvData = worksheet->querySubObject("Range(QString)", Range);
    QVariant allEnvDataQVariant = allEnvData->property("Value");
    QVariantList allEnvDataList = allEnvDataQVariant.toList();

    for (int i = 0; i <= intRows - 13; i++) {
        QVariantList allEnvDataList_i = allEnvDataList[i].toList();
        // qDebug()<< allEnvDataList_i[0].toString()<<
        // allEnvDataList_i[1].toFloat();
        map.insert(allEnvDataList_i[0].toString(),
                   allEnvDataList_i[1].toFloat());
    }
    workbooks->dynamicCall("Close()");
    return 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QAxObject *excel = new QAxObject(this); //建立excel操作对象
    excel->setControl("Excel.Application"); //连接Excel控件
    excel->setProperty("Visible",
                       false); //显示窗体看效果,选择ture将会看到excel表格被打开
    excel->setProperty("DisplayAlerts", true); //显示警告看效果
    QAxObject *workbooks =
        excel->querySubObject("WorkBooks"); //获取工作簿(excel文件)集合
    QString str = QFileDialog::getOpenFileName(
        this, "打开",
        QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),
        "Excel 文件(*.xls *.xlsx)");
    workbooks->dynamicCall("Open(const QString&)", str); //打开刚才选定的excel
    QAxObject *workbook = excel->querySubObject("ActiveWorkBook");
    QAxObject *worksheet = workbook->querySubObject("WorkSheets(int)", 5);
    QAxObject *usedRange =
        worksheet->querySubObject("UsedRange"); //获取表格中的数据范围

    QVariant var =
        usedRange->dynamicCall("Value"); //将所有的数据读取刀QVariant容器中保存
    QList<QList<QVariant>> excel_list; //用于将QVariant转换为Qlist的二维数组
    QVariantList varRows = var.toList();
    if (varRows.isEmpty()) {
        return;
    }
    const int row_count = varRows.size();
    QVariantList rowData;
    for (int i = 0; i < row_count; ++i) {
        rowData = varRows[i].toList();
        excel_list.push_back(rowData);
    } //转换完毕

    QSqlDatabase db;
    if (QSqlDatabase::contains("qt_sql_default_connection"))
        db = QSqlDatabase::database("qt_sql_default_connection");
    else
        db = QSqlDatabase::addDatabase("QSQLITE");

    //设置数据库路径，不存在则创建
    db.setDatabaseName(QApplication::applicationDirPath() + "/alpha.db");

    if (db.open()) {
        QSqlQuery query(db);
        for (int i = 1; i < excel_list.count(); i++) {
            //方式一，直接执行SQL语句

            QStringList list = excel_list.at(i).at(0).toString().split("_");
            qDebug() << list;
            if (list.size() > 1) {
                QString str;
                for (int i = 0; i < list.size(); i++) {
                    str.append(list.at(i));
                }
                query.exec(
                    QString(
                        "INSERT OR IGNORE INTO "
                        "state_code(statecode,discribecn,discribeen,"
                        "operation,level) VALUES('%1','%2','%3','%4','%5');")
                        .arg(str)
                        .arg(excel_list.at(i).at(3).toString())
                        .arg(excel_list.at(i).at(4).toString())
                        .arg(excel_list.at(i).at(7).toString())
                        .arg(excel_list.at(i).at(9).toString()));
            } else
                query.exec(
                    QString(
                        "INSERT OR IGNORE INTO "
                        "state_code(statecode,discribecn,discribeen,"
                        "operation,level) VALUES('%1','%2','%3','%4','%5');")
                        .arg(excel_list.at(i).at(0).toString())
                        .arg(excel_list.at(i).at(3).toString())
                        .arg(excel_list.at(i).at(4).toString())
                        .arg(excel_list.at(i).at(7).toString())
                        .arg(excel_list.at(i).at(9).toString()));

            qDebug() << excel_list.at(i).at(0).toString()
                     << excel_list.at(i).at(3).toString()
                     << excel_list.at(i).at(4).toString()
                     << excel_list.at(i).at(7).toString()
                     << excel_list.at(i).at(9).toString();
        }
    }

    //然后将二维数组Qlist<Qlist<QVariant>>中的数据读取出来，到表格或者数据模型中，具体在这里过程省略

    workbook->dynamicCall("Close(Boolean)", false);
    excel->dynamicCall("Quit(void)");
    delete excel; //因为前面选择了不显示excel窗口，如果这里不删除excel的话，excel依然是打开的，只是我们看不见（因为被隐藏起来了）
}
