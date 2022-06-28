#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "instance.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Instance::instance()->ouputText();
}

MainWindow::~MainWindow()
{
    delete ui;
}
