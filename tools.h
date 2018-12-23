#ifndef TOOLS_H
#define TOOLS_H

#define TEST_MODE

#include <QObject>
#include <QProcess>
#include <QVariant>

class tools : public QObject
{
    Q_OBJECT
public:
    explicit tools(QObject *parent = nullptr);
    bool nptdate(QString host);
    void setCfgValue(const QString &key, const QVariant &value);
    QVariant getCfgvalue(const QString &key, const QVariant &defaultValue = QVariant()) const;
    QString cfgFileName()const;

signals:

public slots:
};

#endif // TOOLS_H
