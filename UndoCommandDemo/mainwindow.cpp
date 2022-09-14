#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPainter>
#include <QLineF>
#include <QPolygonF>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), is_copy(false)
{
    ui->setupUi(this);
    pix_base.load(
        "F:/AICproject/build-aic_alpha-Desktop_Qt_5_15_2_MinGW_32_bit-Debug/"
        "Maps/office1/office1/map.png");

    QPen pen(Qt::red);
    QVector<QLineF> lines;
    lines.append(QLineF(20, 20, 30, 30));
    lines.append(QLineF(30, 30, 40, 40));
    lines.append(QLineF(40, 40, 50, 50));
    AddLineCommand *add = new AddLineCommand(&pix_base, lines, pen);
    undo_stack.push(add);

    update();
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, pix_base);
    if (is_copy)
        painter.drawPixmap(pix_base.width(), 0, copy);
}

void MainWindow::on_revoke_clicked()
{
    undo_stack.undo();
    update();
}

void MainWindow::on_recover_clicked()
{
    undo_stack.redo();
    update();
}
void MainWindow::on_add_clicked()
{
    QPen pen(Qt::red);
    QVector<QLineF> lines;
    pen.setColor(Qt::green);
    lines.clear();
    lines.append(QLineF(200, 200, 190, 190));
    lines.append(QLineF(190, 190, 180, 180));
    lines.append(QLineF(180, 180, 170, 170));
    AddLineCommand *add1 = new AddLineCommand(&pix_base, lines, pen);
    undo_stack.push(add1);
    qDebug() << "undo_stack.count()" << undo_stack.count();

    copy = pix_base.copy(20, 20, 30, 30);
    is_copy = true;
    update();
}
MainWindow::~MainWindow()
{
    delete ui;
}

AddLineCommand::AddLineCommand(QPixmap *add_line_pix,
                               const QVector<QLineF> &lines, const QPen &pen_,
                               QUndoCommand *parent)
    : max_x(lines.front().x1()), max_y(lines.front().y1()),
      min_x(lines.front().x1()), min_y(lines.front().y1())
{
    add_pix = add_line_pix;
    line_vec = lines;

    //    QVector<QPointF> p_v;
    //    p_v.append(line_vec.front().p1());
    //    p_v.append(line_vec.last().p2());
    //    p_v.append(line_vec.last().p2());
    //    QPolygonF pl(p_v);
    //    qDebug() << pl.boundingRect() << pl.boundingRect().width();
    pen = pen_;

    for (int i = 1; i < line_vec.length(); i++) {
        if (i != line_vec.length() - 1) {
            if (line_vec.at(i).p1().x() < min_x)
                min_x = line_vec.at(i).p1().x();
            else if (line_vec.at(i).p1().x() > max_x)
                max_x = line_vec.at(i).p1().x();

            if (line_vec.at(i).p1().y() < min_y)
                min_y = line_vec.at(i).p1().y();
            else if (line_vec.at(i).p1().y() > max_y)
                max_y = line_vec.at(i).p1().y();
        } else {
            if (line_vec.at(i).p2().x() < min_x)
                min_x = line_vec.at(i).p2().x();
            else if (line_vec.at(i).p2().x() > max_x)
                max_x = line_vec.at(i).p2().x();

            if (line_vec.at(i).p2().y() < min_y)
                min_y = line_vec.at(i).p2().y();
            else if (line_vec.at(i).p2().y() > max_y)
                max_y = line_vec.at(i).p2().y();
        }
    }
    qDebug() << min_x << min_y << max_x << max_y;
}
void AddLineCommand::redo()
{
    undo_pix = add_pix->copy(min_x, min_y, max_x - min_x, max_y - min_y);
    QPainter painter(add_pix);
    painter.setPen(pen);
    painter.drawLines(line_vec);
    qDebug() << "redo()";
}
void AddLineCommand::undo()
{
    QPainter painter(add_pix);
    painter.drawPixmap(min_x, min_y, undo_pix);
}

AddLineCommand::~AddLineCommand()
{
}
