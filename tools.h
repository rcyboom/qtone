#ifndef TOOLS_H
#define TOOLS_H

#define TEST_MODE

#include <QObject>
#include <QProcess>

class tools : public QObject
{
    Q_OBJECT
public:
    explicit tools(QObject *parent = nullptr);
    bool nptdate(QString host);

signals:

public slots:
};

#endif // TOOLS_H
