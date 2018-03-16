#ifndef CONTROL_H
#define CONTROL_H
#include <QCoreApplication>

class Control : public QObject
{
    Q_OBJECT
public:
    explicit Control(QObject *parent = 0);

signals:

public slots:
};

#endif // CONTROL_H
