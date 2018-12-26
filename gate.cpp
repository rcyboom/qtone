#include "gate.h"


Gate::Gate(QObject *parent) : QObject(parent)
{

}

bool Gate::init(QString portName)
{
    //1) 通信速率：9600bps；
    //2) 数据格式：1起始位，8数据位，1停止位，无校验位。
    port = new QSerialPort(this);
    port->setPortName("/dev/pts/2");  // 指定端口
    port->setBaudRate(QSerialPort::Baud9600); // 设置波特率
    port->setDataBits(QSerialPort::Data8); // 设置位数
    port->setStopBits(QSerialPort::OneStop); // 设置一个停止位
    port->setParity(QSerialPort::NoParity);// 设置偶校验
    port->setFlowControl(QSerialPort::NoFlowControl); // 设置无流控制
    return  port->open(QIODevice::ReadWrite);// 读写模式打开串口
}

bool Gate::sendData(const QByteArray &data, QByteArray &resultData)
{
    gatePort=new GatePort(port,this);
    return gatePort->sendMsg(data,resultData);
}
