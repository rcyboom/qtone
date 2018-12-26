#ifndef GATEPORT_H
#define GATEPORT_H

#include <QObject>
#include <QSerialPort>

class GatePort : public QObject
{
    Q_OBJECT
public:
   GatePort(QSerialPort *serialPort,QObject *parent);
   bool sendMsg(const QByteArray &data, QByteArray &resultData);
private:
   QSerialPort *serialPort;
   qint8 BCC(const QByteArray &data);
   bool checkResultData(QByteArray data);
};

#endif // GATEPORT_H
