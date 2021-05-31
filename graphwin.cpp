#include "graphwin.h"
#include "ui_graphwin.h"

graphWin::graphWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::graphWin)
{
    ui->setupUi(this);

    qv_EnablChannels.clear();
    qv_availableList.clear();
    qv_graphList.clear();
    initial_bool = true;





    ui->myPlot->addGraph(); // blue line
    ui->myPlot->graph(0)->setPen(QPen(QColor(40, 110, 255)));
    ui->myPlot->addGraph(); // red line
    ui->myPlot->graph(1)->setPen(QPen(QColor(255, 110, 40)));

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    ui->myPlot->xAxis->setTicker(timeTicker);
    ui->myPlot->axisRect()->setupFullAxesBox();
    ui->myPlot->yAxis->setRange(-5.0, 30.2);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->myPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->myPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->myPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->myPlot->yAxis2, SLOT(setRange(QCPRange)));









/*
    ui->myPlot->addGraph();
    ui->myPlot->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
    ui->myPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // first graph will be filled with translucent blue
    ui->myPlot->addGraph();
    ui->myPlot->graph(1)->setPen(QPen(Qt::red)); // line color red for second graph
    // generate some points of data (y0 for first, y1 for second graph):
    QVector<double> x(251), y0(251), y1(251);
    for (int i=0; i<251; ++i)
    {
      x[i] = i;
      y0[i] = qExp(-i/150.0)*qCos(i/10.0); // exponentially decaying cosine
      y1[i] = qExp(-i/150.0);              // exponential envelope
    }
    // configure right and top axis to show ticks but no labels:
    // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
    ui->myPlot->xAxis2->setVisible(true);
    ui->myPlot->xAxis2->setTickLabels(false);
    ui->myPlot->yAxis2->setVisible(true);
    ui->myPlot->yAxis2->setTickLabels(false);
    // make left and bottom axes always transfer their ranges to right and top axes:
    connect(ui->myPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->myPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->myPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->myPlot->yAxis2, SLOT(setRange(QCPRange)));
    // pass data points to graphs:
    ui->myPlot->graph(0)->setData(x, y0);
    ui->myPlot->graph(1)->setData(x, y1);
    // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
    ui->myPlot->graph(0)->rescaleAxes();
    // same thing for graph 1, but only enlarge ranges (in case graph 1 is smaller than graph 0):
    ui->myPlot->graph(1)->rescaleAxes(true);
    // Note: we could have also just called ui->myPlot->rescaleAxes(); instead
    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
    ui->myPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
*/



    timer_singleShot = new QTimer(this);
    connect(timer_singleShot, SIGNAL(timeout()), this, SLOT(on_timer_singleShot_Elapsed()));
    timer_singleShot->setSingleShot(true);
    timer_singleShot->start(150);


}

graphWin::~graphWin()
{
    delete ui;
}

void graphWin::on_timer_singleShot_Elapsed()
{
    emit tx_giveMeEnablesChannels();
}


void graphWin::rx_EnableChannelsAre(int chnlID)
{
    qDebug()<<" enable channel is :"<<chnlID;
    qv_EnablChannels.append(chnlID);
    if(initial_bool)
    {
        initial_bool = false;
        qv_graphList.append(chnlID);
        ui->cmb_graphList->addItem(QString::number(chnlID, 10));
    }
    else
    {
        qv_EnablChannels.append(chnlID);
        ui->cmb_AddList->addItem(QString::number(chnlID, 10));
    }
}
void graphWin::rx_GraphChannelValue(int indx, int chnl, float val)
{
    qDebug()<<" index:"<<indx<<" chnlID:"<<chnl<<" value:"<<val;




    static QTime time(QTime::currentTime());
    // calculate two new data points:
    double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
    static double lastPointKey = 0;
    if (key-lastPointKey > 0.002) // at most add point every 2 ms
    {
      // add data to lines:
      ui->myPlot->graph(0)->addData(key, qSin(key)+qrand()/(double)RAND_MAX*1*qSin(key/0.3843));
      ui->myPlot->graph(1)->addData(key, qCos(key)+qrand()/(double)RAND_MAX*0.5*qSin(key/0.4364));
      // rescale value (vertical) axis to fit the current data:
      //ui->customPlot->graph(0)->rescaleValueAxis();
      //ui->customPlot->graph(1)->rescaleValueAxis(true);
      lastPointKey = key;
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

