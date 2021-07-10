#ifndef CONFIRMATIONBOX_H
#define CONFIRMATIONBOX_H

#include <QDialog>

#include "qdebug.h"

namespace Ui {
class ConfirmationBox;
}

class ConfirmationBox : public QDialog
{
    Q_OBJECT

public:
    explicit ConfirmationBox(QWidget *parent = nullptr);
    ~ConfirmationBox();

signals:
    void tx_confirmationBoxClosed(bool yesBTN, int param);



public slots:
    void rx_MessageBoxVariables(int parm, QString title, QString msg);
    void rx_MessageBoxVariables(int parm, QString title, QString msg, QString yesBtnText, bool yesBtnShow, QString noBtnText, bool noBtnShow);



private slots:
    void on_pb_Yes_clicked();
    void on_pb_No_clicked();

private:
    Ui::ConfirmationBox *ui;

    int localParam = 0;
};

#endif // CONFIRMATIONBOX_H
