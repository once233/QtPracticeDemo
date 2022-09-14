#include "clickoutsizeclosedialog.h"
#include "qdebug.h"
#include "ui_clickoutsizeclosedialog.h"
#include <QCloseEvent>

ClickOutSizeCloseDialog::ClickOutSizeCloseDialog()
    : ui(new Ui::ClickOutSizeCloseDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Popup |
                   Qt::NoDropShadowWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
}

void ClickOutSizeCloseDialog::closeEvent(QCloseEvent *event)
{
    // event->ignore();
}

void ClickOutSizeCloseDialog::InsertText(
    QString text, /*QPlainTextEdit* plainTextEdit,*/ int fontSize,
    QColor fontColor, QColor backColor)
{
    QTextCharFormat fmt;
    //字体色
    fmt.setForeground(QBrush(fontColor));
    // fmt.setUnderlineColor("red");

    //背景色
    fmt.setBackground(QBrush(backColor));
    //字体大小
    fmt.setFontPointSize(fontSize);
    //文本框使用以上设定
    ui->plainTextEdit->mergeCurrentCharFormat(fmt);
    //文本框添加文本
    ui->plainTextEdit->appendPlainText(text);
}

bool ClickOutSizeCloseDialog::event(QEvent *event)
{
    if (event->type() == QEvent::ActivationChange) {
        if (QApplication::activeWindow() != this) {
            this->close();
        }
    }
    return QWidget::event(event);
}

ClickOutSizeCloseDialog::~ClickOutSizeCloseDialog()
{

}
