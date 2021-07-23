#include "firstwindow.h"
#include "ui_firstwindow.h"

FirstWindow::FirstWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FirstWindow)
{
    ui->setupUi(this);

    this->setFixedSize(1024, 768);

    this->setWindowFlags(Qt::FramelessWindowHint);
    //this->setWindowState(Qt::WindowFullScreen);
    //this->setWindowFlag(Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_DeleteOnClose, true); //so that it will be deleted when closed

    timer_clock = new QTimer(this);
    timer_clock->setInterval(1000);
    connect(timer_clock, SIGNAL(timeout()), this, SLOT(on_timer_clock_elapsed()));
    timer_clock->start();
    ui->pb_Config_Factors->hide();
}

FirstWindow::~FirstWindow()
{
    delete ui;
}

void FirstWindow::on_pb_Config_Logging_clicked()
{
    emit tx_generate_ThisGUI(gui_LOG_CONFIG_WIN);
    emit tx_ClosingWindow_FirstWin(false);
}
void FirstWindow::on_pb_Config_Factors_clicked()
{
    emit tx_generate_ThisGUI(gui_CONFIG_CH_WIN);
    emit tx_ClosingWindow_FirstWin(false);
}
void FirstWindow::on_pb_ShutDown_clicked()
{
    emit tx_ClosingWindow_FirstWin(true);
    this->close();
}




void FirstWindow::on_timer_clock_elapsed()
{
    ui->lbl_Date->setText(QDate::currentDate().toString("dd-MMM-yyyy"));
    ui->lbl_Time->setText(QTime::currentTime().toString("HH:mm:ss"));
}

void FirstWindow::on_pb_DebugWindow_clicked()
{
   emit tx_generate_ThisGUI(gui_DEBUG_WIN);
    emit tx_ClosingWindow_FirstWin(false);
}
