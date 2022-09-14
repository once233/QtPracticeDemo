#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_AcceptTouchEvents);
    ui->quickWidget->setAttribute(Qt::WA_AcceptTouchEvents);
}

MainWindow::~MainWindow()
{
    delete ui;
}
