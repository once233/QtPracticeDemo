#ifndef INSTANCE_H
#define INSTANCE_H

#include <QObject>

class Instance : public QObject
{
    Q_OBJECT
public:
    explicit Instance(QObject *parent = nullptr);
    static Instance *instance();
    void ouputText();
signals:
};

#endif // INSTANCE_H
