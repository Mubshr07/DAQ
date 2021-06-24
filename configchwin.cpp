#include "configchwin.h"
#include "ui_configchwin.h"

ConfigChWin::ConfigChWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigChWin)
{
    ui->setupUi(this);
}

ConfigChWin::~ConfigChWin()
{
    delete ui;
}
