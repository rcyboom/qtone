#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QDateTime>
#include "setdialog.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    tl.setCfgValue("AppName",qAppName());
    tl.setCfgValue("AppStartTime",QDateTime::currentDateTime());
    tl.setCfgValue("CustomMSG","自定义消息");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btnNTP_clicked()
{
    tl.nptdate("time.windows.com");
}

void Widget::on_btncfg_clicked()
{
    QString a;
    a.append("AppName=");
    a.append(tl.getCfgvalue("AppName").toString());
    a.append("\nAppStartTime=");
    a.append(tl.getCfgvalue("AppStartTime").toString());
    a.append("\nConfigFile=");
    a.append(tl.cfgFileName());
    a.append("\nCustomMSG=");
    a.append(tl.getCfgvalue("CustomMSG").toString());
    QMessageBox::information( QApplication::focusWidget(),"ReadSetting",a);
}

void Widget::on_btnGate_clicked()
{
    SetDialog set(this);
    set.exec();
}
