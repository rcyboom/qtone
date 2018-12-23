#ifndef GATE_H
#define GATE_H

#include <QObject>

class Gate : public QObject
{
    Q_OBJECT
public:
    explicit Gate(QObject *parent = nullptr);

signals:

public slots:
};

#endif // GATE_H