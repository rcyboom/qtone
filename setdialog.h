#ifndef SETDIALOG_H
#define SETDIALOG_H

#include <QDialog>
#include "gate.h"

namespace Ui {
class SetDialog;
}

class SetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetDialog(QWidget *parent = nullptr);
    ~SetDialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::SetDialog *ui;
    Gate *gate;
};

#endif // SETDIALOG_H
