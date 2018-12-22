#include "tools.h"
#include <QMessageBox>
#include <QApplication>

tools::tools(QObject *parent) : QObject(parent)
{

}

bool tools::nptdate(QString host)
{
    QProcess *p=new QProcess;
    p->start("ntpdate -u "+host);
    p->waitForStarted(-1);
    p->waitForFinished(-1);
 #ifdef TEST_MODE
    QString msg(p->readAllStandardOutput());
    if(msg=="")
        msg=QString(p->readAllStandardError());
    QMessageBox::warning( QApplication::focusWidget(),"title", msg);
#endif
    return true;
}
