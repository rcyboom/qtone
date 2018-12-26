#include "gateport.h"
//#include <qdebug.h>


GatePort::GatePort(QSerialPort *serialPort, QObject *parent):QObject (parent)
{
    this->serialPort=serialPort;
}

bool GatePort::sendMsg(const QByteArray &data, QByteArray &resultData)
{
    resultData.clear();

    if(data.length()<4)
    {
        resultData.append("发送数据包必须大于4字节!");
        return false;
    }

    //组装发送数据包
    /*
    名称          类型	长度          说明
    STX         Byte	1           包起始 = 0x7E
    DataLen		Byte	1           数据长度
    Data		Bytes	DataLen     数据
    BCC         Byte	1           Data中数据的BCC校验
    ETX         Byte	1           包结束符 =0x7A
    */
    QByteArray sendData;
    sendData.append(qint8(0x7E));
    sendData.append(qint8(data.length()));
    sendData.append(data);
    sendData.append(qint8(BCC(data)));
    sendData.append(qint8(0x7A));
    //qDebug()<<"组装发送数据："<<sendData.toHex(':');
    //阻塞发送数据
    const qint64 bytesWritten = serialPort->write(sendData);
    if (bytesWritten == -1) {
        resultData.append( QObject::tr("发送失败，往端口%1, error: %2")
                           .arg(serialPort->portName()).arg(serialPort->errorString()));
        return  false;
    } else if (bytesWritten != sendData.size()) {
        resultData.append( QObject::tr("未全部发送完毕，往端口%1, error: %2")
                           .arg(serialPort->portName()).arg(serialPort->errorString()));
        return  false;
    } else if (!serialPort->waitForBytesWritten(5000)) {
        resultData.append( QObject::tr("发送超时，往端口%1, error: %2")
                           .arg(serialPort->portName()).arg(serialPort->errorString()));
        return  false;

    }

    //阻塞接收数据，最多等待5秒钟
    serialPort->waitForReadyRead(5000);
    resultData = serialPort->readAll();
    while (serialPort->waitForReadyRead(100))
        resultData.append(serialPort->readAll());

    if (serialPort->error() == QSerialPort::ReadError) {
        resultData.clear();
        resultData.append(QObject::tr("读取失败，在端口%1, error: %2")
                          .arg(serialPort->portName()).arg(serialPort->errorString()));
        return  false;
    } else if (serialPort->error() == QSerialPort::TimeoutError && resultData.length()<4) {
        resultData.clear();
        resultData.append(QObject::tr("已超时5秒，未读取到一个完整的数据包，在端口%2")
                          .arg(serialPort->portName()));
        return  false;
    }

    //校验和提取数据
    return checkResultData(resultData);
}

qint8 GatePort::BCC(const QByteArray &data)
{
    qint8 bcc=0;
    for (int i=0;i<data.length();i++) {
        bcc^=data[i];
    }
    return bcc;
}

bool GatePort::checkResultData(QByteArray data)
{
    /*
    名称          类型	长度          说明
    STX         Byte	1           包起始 = 0x7E       i
    DataLen		Byte	1           数据长度            1
    Data		Bytes	DataLen7     数据                7
    BCC         Byte	1           Data中数据的BCC校验  1
    ETX         Byte	1           包结束符 =0x7A      1
    */
    QByteArray msg;
    QByteArray tmp;
    qint8 length,bcc,etx;
    for (int i = 0; i < data.length()-3; i++) {
        if(data.at(i) == qint8(0x7E))
        {
            length=data.at(i+1);
            tmp=data.mid(i+2,length);
            if((i+3+length)<data.length())
            {
                bcc=data.at(i+2+length);
                etx=data.at(i+3+length);
                if(etx== qint8(0x7A))
                {
                    if(BCC(tmp) == bcc)
                    {
                        data=tmp;
                        return true;
                    }
                    else
                        msg=QByteArray("数据包BCC校验失败！");
                }
                else
                    msg=QByteArray("数据包找不到结尾标志0x7A！");
            }
            else
                msg=QByteArray("数据包长度不足！");
        }
    }
    if(msg.isEmpty())
        data=QByteArray("数据包找不到开头标志0x7E！");
    return false;
}






















