#include "graphwin.h"
#include "ui_graphwin.h"

graphWin::graphWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::graphWin)
{
    ui->setupUi(this);
}

graphWin::~graphWin()
{
    delete ui;
}
