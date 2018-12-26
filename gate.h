#ifndef GATE_H
#define GATE_H

#include <QObject>
#include <QSerialPort>
#include "gateport.h"

class Gate : public QObject
{
    Q_OBJECT
public:
    explicit Gate(QObject *parent = nullptr);
    bool init(QString portName);
    bool sendData(const QByteArray &data, QByteArray &resultData);


signals:

public slots:
private:
    QSerialPort* port;
    GatePort *gatePort;
};

#endif // GATE_H
