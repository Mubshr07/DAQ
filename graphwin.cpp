#include "graphwin.h"
#include "ui_graphwin.h"

graphWin::graphWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::graphWin)
{
    ui->setupUi(this);
    this->setFixedSize(1024, 768);

    this->setWindowFlags(Qt::FramelessWindowHint);
    //this->setWindowState(Qt::WindowFullScreen);
    //this->setWindowFlag(Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_DeleteOnClose, true); //so that it will be deleted when closed

    qv_EnablChannels.clear();
    qv_availableList.clear();
    initial_bool = true;

    int lineSize = 2;
    QPen plot_0(plot0_Color);
    plot_0.setWidth(lineSize);
    QPen plot_1(plot1_Color);
    plot_1.setWidth(lineSize);
    QPen plot_2(plot2_Color);
    plot_2.setWidth(lineSize);
    QPen plot_3(plot3_Color);
    plot_3.setWidth(lineSize);

    ui->myPlot->addGraph(); // plot 0
    ui->myPlot->graph(0)->setPen(plot_0);
    ui->myPlot->addGraph(); // plot 1
    ui->myPlot->graph(1)->setPen(plot_1);
    ui->myPlot->addGraph(); // plot 2
    ui->myPlot->graph(2)->setPen(plot_2);
    ui->myPlot->addGraph(); // plot 3
    ui->myPlot->graph(3)->setPen(plot_3);


    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    ui->myPlot->xAxis->setTicker(timeTicker);
    ui->myPlot->axisRect()->setupFullAxesBox();
    ui->myPlot->yAxis->setRange(-5.0, 30.2);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->myPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->myPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->myPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->myPlot->yAxis2, SLOT(setRange(QCPRange)));

    timer_singleShot = new QTimer(this);
    connect(timer_singleShot, SIGNAL(timeout()), this, SLOT(on_timer_singleShot_Elapsed()));
    timer_singleShot->setSingleShot(true);
    timer_singleShot->start(350);


}

graphWin::~graphWin()
{
    delete ui;
}

void graphWin::on_timer_singleShot_Elapsed()
{
    emit tx_GraphWindowIsOpen(true);
    emit tx_giveMeEnablesChannels();

    ui->lbl_Channel_1->setText("");
    ui->pb_RemoveGraph_1->setEnabled(false);
    ui->lbl_Channel_2->setText("");
    ui->pb_RemoveGraph_2->setEnabled(false);
    ui->lbl_Channel_3->setText("");
    ui->pb_RemoveGraph_3->setEnabled(false);
}


void graphWin::rx_EnableChannelsAre(int chnlID)
{
    //qDebug()<<" enable channel is :"<<chnlID;
    qv_EnablChannels.append(chnlID);
    if(initial_bool)
    {
        initial_bool = false;
        availIndex[0] = true;
        graphedChannels[0] = chnlID;
        ui->lbl_Channel_0->setText(QString::number(chnlID));
        ui->pb_RemoveGraph_0->setEnabled(true);
    }
    else
    {
        qv_availableList.append(chnlID);
        ui->cmb_AddList->addItem(QString::number(chnlID, 10));
    }
}

void graphWin::rx_GraphChannelValue(int indx, int chnl, float val)
{
    //qDebug()<<" index:"<<indx<<" chnlID:"<<chnl<<" value:"<<val;




    static QTime time(QTime::currentTime());
    // calculate two new data points:
    double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
    static double lastPointKey = 0;
    if (key-lastPointKey > 0.002) // at most add point every 2 ms
    {
      // add data to lines:
        if(indx == 0) {
            ui->myPlot->graph(0)->addData(key, val);
        }
        else if(indx == 1) {
            ui->myPlot->graph(1)->addData(key, val);
        }
        else if(indx == 2) {
            ui->myPlot->graph(2)->addData(key, val);
        }
        else if(indx == 3) {
            ui->myPlot->graph(3)->addData(key, val);
        }

        lastPointKey = key;
      //ui->myPlot->graph(1)->addData(key, qCos(key)+qrand()/(double)RAND_MAX*0.5*qSin(key/0.4364));
      // rescale value (vertical) axis to fit the current data:
      //ui->customPlot->graph(0)->rescaleValueAxis();
      //ui->customPlot->graph(1)->rescaleValueAxis(true);

    }
    // make key axis range scroll with the data (at a constant range size of 8):
    ui->myPlot->xAxis->setRange(key, 8, Qt::AlignRight);
    ui->myPlot->replot();

    // calculate frames per second:
    static double lastFpsKey;
    static int frameCount;
    ++frameCount;
    if (key-lastFpsKey > 2) // average fps over 2 seconds
    {
      lastFpsKey = key;
      frameCount = 0;
    }
}


void graphWin::on_pb_Add_toGraph_clicked()
{
    int chnlInt = ui->cmb_AddList->currentText().toInt();
    chnl4thIsAppliable = false;
    int indx = 3;
    for(int i=0; i<4; i++)
    {
        if(availIndex[i] == false)
        {
            indx = i;
            if(i==3) chnl4thIsAppliable = true;
            break;
        }
    }
    //qDebug()<<" availIndex[indx] : "<<indx;

    emit tx_AddNewChannelToGraph(indx, chnlInt);
    graphedChannels[indx] = chnlInt;
    int already4thChannelID = 66;
    if(chnl4thIsEnable)
    {
      already4thChannelID = ui->lbl_Channel_3->text().toInt();
    }
    switch (indx) {
    case 0: {
        availIndex[indx] = true;
        ui->lbl_Channel_0->setText(QString::number(chnlInt));
        ui->pb_RemoveGraph_0->setEnabled(true);
        ui->pb_RemoveGraph_0->setText("Remove");
        ui->pb_RemoveGraph_0->setStyleSheet(style_removBtn_0);
        break;
    }
    case 1: {
        availIndex[indx] = true;
        ui->lbl_Channel_1->setText(QString::number(chnlInt));
        ui->pb_RemoveGraph_1->setEnabled(true);
        ui->pb_RemoveGraph_1->setText("Remove");
        ui->pb_RemoveGraph_1->setStyleSheet(style_removBtn_1);
        break;
    }
    case 2: {
        availIndex[indx] = true;
        ui->lbl_Channel_2->setText(QString::number(chnlInt));
        ui->pb_RemoveGraph_2->setEnabled(true);
        ui->pb_RemoveGraph_2->setText("Remove");
        ui->pb_RemoveGraph_2->setStyleSheet(style_removBtn_2);
        break;
    }
    case 3: {
        chnl4thIsEnable = true;
        ui->lbl_Channel_3->setText(QString::number(chnlInt));
        ui->pb_RemoveGraph_3->setEnabled(true);
        ui->pb_RemoveGraph_3->setText("Remove");
        ui->pb_RemoveGraph_3->setStyleSheet(style_removBtn_3);
        break;
    }
    } // end of switch statements

    int currentIndex = ui->cmb_AddList->currentIndex();
    int totalItems = ui->cmb_AddList->count();
    //qDebug()<<" currentIndex = "<<currentIndex<<" total: "<<totalItems;
    totalItems -= 1;
    qv_availableList.removeAt(currentIndex);

    ui->cmb_AddList->clear();
    for(int i=0; i<totalItems; i++)
    {
        ui->cmb_AddList->addItem(QString::number(qv_availableList.at(i)));
    }
    if(currentIndex < totalItems) ui->cmb_AddList->setCurrentIndex(currentIndex);

    if(chnl4thIsEnable && chnl4thIsAppliable)
    {
        qv_availableList.append(already4thChannelID);
        update_cmbBoxItems();
    }
}


void graphWin::on_pb_RemoveGraph_0_clicked()
{
    availIndex[0] = false;
    int chnlID = ui->lbl_Channel_0->text().toInt();
    emit tx_RemoveChannelToGraph(0, chnlID);
    ui->lbl_Channel_0->setText("  ");
    ui->pb_RemoveGraph_0->setText("");
    ui->pb_RemoveGraph_0->setEnabled(false);
    ui->pb_RemoveGraph_0->setStyleSheet(style_removBtn_Disabled);
    ui->myPlot->graph(0)->data()->clear();

    qv_availableList.append(chnlID);
    update_cmbBoxItems();
}
void graphWin::on_pb_RemoveGraph_1_clicked()
{
    availIndex[1] = false;
    int chnlID = ui->lbl_Channel_1->text().toInt();
    emit tx_RemoveChannelToGraph(1, chnlID);
    ui->lbl_Channel_1->setText("  ");
    ui->pb_RemoveGraph_1->setText("");
    ui->pb_RemoveGraph_1->setEnabled(false);
    ui->pb_RemoveGraph_1->setStyleSheet(style_removBtn_Disabled);
    ui->myPlot->graph(1)->data()->clear();

    qv_availableList.append(chnlID);
    update_cmbBoxItems();
}
void graphWin::on_pb_RemoveGraph_2_clicked()
{
    availIndex[2] = false;
    int chnlID = ui->lbl_Channel_2->text().toInt();
    emit tx_RemoveChannelToGraph(2, chnlID);
    ui->lbl_Channel_2->setText("  ");
    ui->pb_RemoveGraph_2->setText("");
    ui->pb_RemoveGraph_2->setEnabled(false);
    ui->pb_RemoveGraph_2->setStyleSheet(style_removBtn_Disabled);
    ui->myPlot->graph(2)->data()->clear();

    qv_availableList.append(chnlID);
    update_cmbBoxItems();
}
void graphWin::on_pb_RemoveGraph_3_clicked()
{
    availIndex[3] = false;
    chnl4thIsEnable = false;
    int chnlID = ui->lbl_Channel_3->text().toInt();
    emit tx_RemoveChannelToGraph(3, chnlID);
    ui->lbl_Channel_3->setText("  ");
    ui->pb_RemoveGraph_3->setText("");
    ui->pb_RemoveGraph_3->setEnabled(false);
    ui->pb_RemoveGraph_3->setStyleSheet(style_removBtn_Disabled);
    ui->myPlot->graph(3)->data()->clear();

    qv_availableList.append(chnlID);
    update_cmbBoxItems();
}

void graphWin::update_cmbBoxItems()
{
    int tempqt, i, j;
    for (i=0; i<qv_availableList.length(); i++)
    {
        for(j=(i+1); j<qv_availableList.length(); j++)
        {
            if (qv_availableList[i] >= qv_availableList[j])
            {
                tempqt = qv_availableList[i];
                qv_availableList[i] = qv_availableList[j];
                qv_availableList[j] = tempqt;
            }
        }
    }



    int currentIndex = ui->cmb_AddList->currentIndex();
    ui->cmb_AddList->clear();
    for(int i=0; i<qv_availableList.length(); i++)
    {
        ui->cmb_AddList->addItem(QString::number(qv_availableList.at(i)));
    }
    ui->cmb_AddList->setCurrentIndex(currentIndex);
}


void graphWin::on_pb_CloseWindow_clicked()
{
    emit tx_GraphWindowIsOpen(false);

    this->close();
}
