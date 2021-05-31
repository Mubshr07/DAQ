#include "loggerthread.h"

chnlClass_Simple chnlArray[TOTAL_CHANNEL];
loggerThread::loggerThread(QObject *parent) : QObject(parent)
{
    initializeHWAddresses();
    for(int i = 0; i< TOTAL_CHANNEL; i++)
    {
        chnlArray[i].setChannelEnableDisable(false);
        chnlArray[i].setChannelAddress(i);
    }

    qDebug()<<" before timer_logger initialize ";
    timer_logger = new QTimer(this);
    connect(timer_logger, SIGNAL(timeout()), SLOT(on_timer_logger_elapsed()));
    timer_logger->start(sampleRate_MS);

    qDebug()<<" before timer_graph initialize ";
    timer_graphValue = new QTimer(this);
    connect(timer_graphValue, SIGNAL(timeout()), SLOT(on_timer_graphValue_elapsed()));
    timer_graphValue->start(500);
    timer_elapser = new QElapsedTimer();
}


void loggerThread::on_timer_logger_elapsed()
{
    //qDebug()<<" 111111111111 ";
    timer_elapser->start();

    for(int i=0; i<TOTAL_CHANNEL; i++)
    {
        if(chnlArray[i].isChnlEnable())
        {
            emit tx_channel_Value(i, chnlArray[i].giveCurrentValue());
        }
    }

    elapsed_timeNanoSec = timer_elapser->nsecsElapsed();
    sampleRate_MS_Calculated = (sampleRate_MS - (elapsed_timeNanoSec/1000000.0));
    timer_logger->setInterval(sampleRate_MS_Calculated);
    //qDebug()<<" 2222222222 ";
}
void loggerThread::on_timer_graphValue_elapsed()
{
    for(int i=0; i<qv_graphChannels.length(); i++)
    {
        emit tx_GraphChannelValue(i, qv_graphChannels.at(i), chnlArray[qv_graphChannels.at(i)].giveCurrentValue());
    }
}


void loggerThread::rx_setChannelEnableDisable(int chnlIndex, bool enable)
{
    emit tx_channelisEnabled(chnlIndex, chnlArray[chnlIndex].setChannelEnableDisable(enable));
}
void loggerThread::rx_setSampleTime(int sec)
{
    sampleRate_Sec = sec;
    sampleRate_MS = (sampleRate_Sec * 1000.0);
}
void loggerThread::rx_loggingStartStop(bool start)
{
    local_logging = start;
    emit tx_loggingStarted(local_logging);
}


void loggerThread::rx_giveMeEnablesChannels()
{
    for(int i=0; i<TOTAL_CHANNEL; i++)
    {
        if(chnlArray[i].isChnlEnable())
        {
            if(addFirstEnableChannelinGraph)
            {
                addFirstEnableChannelinGraph = false;
                qv_graphChannels.append(i);
            }
            emit tx_EnableChannelsAre(i);
        }
    }
}
void loggerThread::rx_AddNewChannelToGraph(int chnlID)
{
    if(qv_graphChannels.length() >= 4)
    {
        qv_graphChannels.pop_back();
        qv_graphChannels.append(chnlID);
    }
    else
    {
        qv_graphChannels.append(chnlID);
    }
}
void loggerThread::rx_RemoveChannelToGraph(int chnlID)
{
    int indx = 0;
    if(qv_graphChannels.length() > 0)
    {
        indx = qv_graphChannels.indexOf(chnlID);
        qv_graphChannels.removeAt(indx);
    }
}
void loggerThread::rx_GraphWindowIsOpen(bool windOpen)
{
    graphWindowIsOpen = windOpen;
}



// ---------------  ONE Time Used Methods --------------------
void loggerThread::initializeHWAddresses()
{
    addrss_Obj = new Addressing();
    addrss_Obj->get_address_of_peripherals();

    local_ADC0_ADDRESS = addrss_Obj->givemeaddr(0);
    local_ADC1_ADDRESS = addrss_Obj->givemeaddr(1);
    local_ADC2_ADDRESS = addrss_Obj->givemeaddr(2);
    local_ADC3_ADDRESS = addrss_Obj->givemeaddr(3);
    local_ADC4_ADDRESS = addrss_Obj->givemeaddr(4);
    local_ADC5_ADDRESS = addrss_Obj->givemeaddr(5);
    local_ADC6_ADDRESS = addrss_Obj->givemeaddr(6);
    local_ADC7_ADDRESS = addrss_Obj->givemeaddr(7);

}
