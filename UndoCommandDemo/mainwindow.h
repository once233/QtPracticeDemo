#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qpen.h"
#include <QMainWindow>
#include <QUndoCommand>
#include <QUndoStack>
#include <QPixmap>
#include <QObject>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *);

private slots:
    void on_revoke_clicked();

    void on_recover_clicked();

    void on_add_clicked();

private:
    Ui::MainWindow *ui;

    QUndoStack undo_stack;
    QPixmap pix_base;
    //    QPixmap pix_draw;
    QPixmap pix_base_last;

    QPixmap copy;
    bool is_copy;
    //    QPixmap pix_draw_last;
};

class AddLineCommand : public QUndoCommand
{
public:
    AddLineCommand(QPixmap *add_line_pix, const QVector<QLineF> &lines,
                   const QPen &pen, QUndoCommand *parent = 0);
    ~AddLineCommand();
    void redo() override; //重写这两个函数
    void undo() override;

private:
    QPixmap *add_pix;
    QPixmap undo_pix;
    QPen pen;
    QVector<QLineF> line_vec;
    float max_x;
    float max_y;
    float min_x;
    float min_y;
};

#endif // MAINWINDOW_H
