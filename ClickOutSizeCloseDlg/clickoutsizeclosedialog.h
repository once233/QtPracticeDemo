#ifndef CLICKOUTSIZECLOSEDIALOG_H
#define CLICKOUTSIZECLOSEDIALOG_H

#include <QDialog>
#include <QObject>
#include "plaintextwidget.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class ClickOutSizeCloseDialog;
}
QT_END_NAMESPACE
class ClickOutSizeCloseDialog : public QDialog
{
    Q_OBJECT

public:
    ClickOutSizeCloseDialog();
    ~ClickOutSizeCloseDialog();
    void InsertText(QString text,
                    /*QPlainTextEdit* plainTextEdit,*/ int fontSize,
                    QColor fontColor, QColor backColor = QColor(0xffffff));

protected:
    void closeEvent(QCloseEvent *event);
    bool event(QEvent *);

private:
    Ui::ClickOutSizeCloseDialog *ui;
};

#endif // CLICKOUTSIZECLOSEDIALOG_H
