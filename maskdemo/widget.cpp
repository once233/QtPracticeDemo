﻿#include "widget.h"
#include "ui_widget.h"
#include "maskwidget.h"
#include "screenwidget.h"
#include "frm1.h"
#include "frm2.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setProperty("CanMove", true);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);

    //第一步,设置需要遮罩的父窗体
    MaskWidget::Instance()->setMainWidget(this);
    //第二步,设置哪些弹窗窗体需要被遮罩
    QStringList dialogNames;
    dialogNames << "frm1" << "frm2";
    MaskWidget::Instance()->setDialogNames(dialogNames);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    ScreenWidget::Instance()->showFullScreen();
}

void Widget::on_pushButton_2_clicked()
{
    frm1 *w = new frm1;
    w->setAttribute(Qt::WA_ShowModal, true);
    w->setAttribute(Qt::WA_DeleteOnClose, true);
    w->show();
}

void Widget::on_pushButton_3_clicked()
{
    frm2 *w = new frm2;
    w->setAttribute(Qt::WA_ShowModal, true);
    w->setAttribute(Qt::WA_DeleteOnClose, true);
    w->show();
}

void Widget::on_pushButton_4_clicked()
{
    this->close();
}
