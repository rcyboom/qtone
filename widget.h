#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "tools.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    tools tl;

private slots:
    void on_btnNTP_clicked();

    void on_btncfg_clicked();

    void on_btnGate_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
