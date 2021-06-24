#ifndef LOGGERTHREAD_H
#define LOGGERTHREAD_H


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

    void tx_EnableChannelsAre(int chnlID);
    void tx_GraphChannelValue(int indx, int chnl, float val);

    void tx_ramdomOP(int idx, float val, QString str);


public slots:
    void rx_setChannelEnableDisable(int chnlIndex, bool enable);
    void rx_setSampleTime(int mSec);
    void rx_loggingStartStop(bool start);

    void rx_AddNewChannelToGraph(int idx, int chnlID);
    void rx_RemoveChannelToGraph(int idx, int chnlID);
    void rx_GraphWindowIsOpen(bool windOpen);

    void rx_giveMeEnablesChannels();


    void on_timer_logger_elapsed();
    void on_timer_graphValue_elapsed();

private:
    QTimer *timer_logger;
    QElapsedTimer *timer_elapser;
    QElapsedTimer *timer_elapser2;
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

    //QVector<int> qv_graphChannels;
    int graphChannels_idx[4] = {232, 232, 232, 232};
    bool graphChannels_idxBool[4] = {false, false, false, false};

    bool graphWindowIsOpen = false;
    bool logging_isStarted = false;
    bool addFirstEnableChannelinGraph = true;

    int sampleRate_Sec = 2;
    int sampleRate_MS = 100;
    int sampleRate_MS_Calculated = 0;
    bool local_logging = false;
    qint64 elapsed_timeNanoSec = 0;
    int elapsed_timeMS = 0;
    QString logStr = "";
    long logSerialNumber = 0;

    int local_logTime_MS = 0;



    void initialize_Dir_FileName();
    QString folderPath = QString(QDir::homePath()+"/DAQ_Logs");
    QString filePath = "";
    int LogFileNumber = 0;
    QString logFileExtension =  ".csv";
    QFile *logFile;
    void writeThisToLogFile(QString str);



    // ---------- Log Time spend
    long local_log_sec = 0;
    int local_log_min = 0;
    int local_log_hours = 0;
    QString local_LogTime_Str = "";
};

#endif // LOGGERTHREAD_H
