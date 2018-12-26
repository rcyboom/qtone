#include "setdialog.h"
#include "ui_setdialog.h"
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QTime>


SetDialog::SetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetDialog)
{
    ui->setupUi(this);
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos)
    {
        ui->portList->addItem(info.portName());
    }
    ui->pushButton_2->setEnabled(false);
}

SetDialog::~SetDialog()
{
    delete ui;
}

void SetDialog::on_pushButton_clicked()
{
    if(ui->portList->currentIndex()<0)
    {
        QMessageBox::information(this,"提示","请选择一个串口","ok");
    }
    gate=new Gate(this);
    if(!gate->init(ui->portList->currentText()))
    {
        QMessageBox::information(this,"提示","串口打开失败！","ok");
        gate->deleteLater();
        ui->pushButton_2->setEnabled(false);
    }
    ui->pushButton_2->setEnabled(true);
}

qint8 BCC(const QByteArray &data)
{
    qint8 bcc=0;
    for (int i=0;i<data.length();i++) {
        bcc^=data[i];
    }
    return bcc;
}

void SetDialog::on_pushButton_2_clicked()
{
    QByteArray data,rs;
    data.append(qint8(ui->DestAddress->value()));
    data.append(qint8(ui->SourceAddress->value()));
    data.append(qint8(ui->Command->value()));
    data.append(qint8(ui->Param->value()));
    if(ui->cdata1->isChecked())
        data.append(qint8(ui->data1->value()));
    if(ui->cdata2->isChecked())
        data.append(qint8(ui->data2->value()));
    ui->resultext->append(QTime::currentTime().toString("mm:ss.zzz")+"---待发送命令："+data.toHex(':'));
    QByteArray sendData;
    sendData.append(qint8(0x7E));
    sendData.append(qint8(data.length()));
    sendData.append(data);
    sendData.append(qint8(BCC(data)));
    sendData.append(qint8(0x7A));
    ui->resultext->append("组装后的发送数据："+sendData.toHex(':'));
    if(gate->sendData(data,rs))
    {
        ui->resultext->append("成功接收返回："+rs.toHex(':'));
    }else {
    ui->resultext->append("发生异常："+rs);
}
}
