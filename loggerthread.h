#ifndef LOGGERTHREAD_H
#define LOGGERTHREAD_H
#define TOTAL_CHANNEL 48


#include <QObject>

#include "globalvars.h"
#include "chnlclass_simple.h"
#include "addressing.h"

class loggerThread : public QObject
{
    Q_OBJECT
public:
    explicit loggerThread(QObject *parent = nullptr);

signals:
    void tx_channel_Value(int chnl, float val);
    void tx_loggingStarted(bool started);
    void tx_graphChnlValue(int chnl, float val);
    void tx_channelisEnabled(int chnl, bool enableVal);


public slots:

    void rx_setChannelEnableDisable(int chnlIndex, bool enable);
    void rx_setSampleTime(int sec);
    void rx_loggingStartStop(bool start);
    void rx_addGraphChannel(int index);

    void on_timer_logger_elapsed();
    void on_timer_graphValue_elapsed();

private:
    QTimer *timer_logger;
    QElapsedTimer *timer_elapser;
    QTimer *timer_graphValue;

    Addressing *addrss_Obj;
    void initializeHWAddresses();
    int32_t *local_ADC0_ADDRESS;
    int32_t *local_ADC1_ADDRESS;
    int32_t *local_ADC2_ADDRESS;
    int32_t *local_ADC3_ADDRESS;
    int32_t *local_ADC4_ADDRESS;
    int32_t *local_ADC5_ADDRESS;
    int32_t *local_ADC6_ADDRESS;
    int32_t *local_ADC7_ADDRESS;



    int sampleRate_Sec = 2;
    int sampleRate_MS = 100;
    int sampleRate_MS_Calculated = 0;
    bool local_logging = false;
    qint64 elapsed_timeNanoSec = 0;
    int elapsed_timeMS = 0;


};

#endif // LOGGERTHREAD_H
