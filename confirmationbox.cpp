#include "confirmationbox.h"
#include "ui_confirmationbox.h"

ConfirmationBox::ConfirmationBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfirmationBox)
{
    ui->setupUi(this);
    this->setFixedSize(530, 300);
//    int msgBox_width = 530;
//    int msgBox_height = 300;
//    int x =  (parentWidget()->window()->frameGeometry().topLeft().x()+ parentWidget()->window()->rect().y()) - (msgBox_width);
//    int y =  parentWidget()->window()->frameGeometry().topLeft().y() + parentWidget()->window()->rect().y() - (msgBox_height);

    //this->setGeometry(x, y, msgBox_width, msgBox_height);
    //qDebug()<<" x:"<<x<<" y:"<<y<<" width:"<<msgBox_width<<" Height:"<<msgBox_height;

    this->setWindowFlags(Qt::FramelessWindowHint);
    //this->setWindowState(Qt::WindowFullScreen);
    this->setWindowFlag(Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_DeleteOnClose, true); //so that it will be deleted when closed



}

ConfirmationBox::~ConfirmationBox()
{
    delete ui;
}

void ConfirmationBox::on_pb_Yes_clicked()
{
    emit tx_confirmationBoxClosed(true, localParam);
    this->close();
}
void ConfirmationBox::on_pb_No_clicked()
{
    emit tx_confirmationBoxClosed(false, localParam);
    this->close();
}


// ---------------- slots -------------------------
void ConfirmationBox::rx_MessageBoxVariables(int parm, QString title, QString msg)
{
    localParam = parm;
    ui->lbl_Title->setText(title);
    ui->lbl_Message->setText(msg);
}
void ConfirmationBox::rx_MessageBoxVariables(int parm, QString title, QString msg, QString yesBtnText, bool yesBtnShow, QString noBtnText, bool noBtnShow)
{
    localParam = parm;
    ui->lbl_Title->setText(title);
    ui->lbl_Message->setText(msg);

    ui->pb_Yes->setText(yesBtnText);
    ui->pb_Yes->setVisible(yesBtnShow);

    ui->pb_No->setText(noBtnText);
    ui->pb_No->setVisible(noBtnShow);
}
