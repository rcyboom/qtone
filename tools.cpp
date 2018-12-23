#include "tools.h"
#include <QMessageBox>
#include <QApplication>
#include <QSettings>

tools::tools(QObject *parent) : QObject(parent)
{

}

bool tools::nptdate(QString host)
{
    QProcess p(this);
    p.start("ntpdate -u "+host);
    p.waitForStarted(1000);
    p.waitForFinished(-1);
#ifdef TEST_MODE
    QString msg(p.readAllStandardOutput());
    if(msg=="")
        msg=QString(p.readAllStandardError());
    QMessageBox::warning( QApplication::focusWidget(),"title", msg);
#endif
    return true;
}

void tools::setCfgValue(const QString &key, const QVariant &value)
{
   QSettings cfg(QSettings::IniFormat, QSettings::UserScope,"GitDream", "QGateClient");
   cfg.setValue(key,value);
}

QVariant tools::getCfgvalue(const QString &key, const QVariant &defaultValue) const
{
    QSettings cfg(QSettings::IniFormat, QSettings::UserScope,"GitDream", "QGateClient");
    return cfg.value(key,defaultValue);
}

QString tools::cfgFileName() const
{
    QSettings cfg(QSettings::IniFormat, QSettings::UserScope,"GitDream", "QGateClient");
    return cfg.fileName();
}
