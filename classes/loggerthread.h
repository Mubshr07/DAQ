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
    void tx_channel_Value(int chnl,uint32_t raw, float fVal, float facVal);
    void tx_channel_Value_Config(int chnl,uint32_t raw, float fVal, float facVal);
    void tx_loggingStarted_andFileOpenSuccess(bool started);
    void tx_graphChnlValue(int chnl, float val);
    void tx_channelisEnabled(int chnl, bool enableVal);

    void tx_EnableChannelsAre(int chnlID);
    void tx_GraphChannelValue(int indx, int chnl, float val);

    void tx_sendingFactorsAndPGAs(int chnl, float fac, float pgaa, bool enabled);

    void tx_ramdomOP(int idx, float val, QString str);
    void tx_ChannelOLDSettings(int chnl, float fac, CHANNEL_PGA pgaa, CHANNEL_TYPE typ, CHANNEL_REFERENCE ref, bool enb);

public slots:
    void rx_setChannelEnableDisable(int chnlIndex, bool enable);
    void rx_setSampleTime(int mSec);
    void rx_loggingStartStop(bool start, QString filePth);

    void rx_AddNewChannelToGraph(int idx, int chnlID);
    void rx_RemoveChannelToGraph(int idx, int chnlID);
    void rx_GraphWindowIsOpen(bool windOpen);
    void rx_ChannelSettingsWindowIsOpen(bool windOpen);

    void rx_giveMeEnablesChannels();
    void rx_sendFactorsAndPGAs_AllChnls();

    void rx_setChannelNewSettings(int chnl, float fac, CHANNEL_PGA pgaa, CHANNEL_TYPE typ, CHANNEL_REFERENCE ref, bool Enabled);
    void rx_giveMechannelSettings(int chnl);
    void rx_saveChannelSettingsToFile();

    void rx_startReadingTimer(bool startReading);



    void on_timer_logger_elapsed();
    void on_timer_graphValue_elapsed();

private:
    QTimer *timer_logger;
    QElapsedTimer *timer_elapser;
    QTimer *timer_graphValue;
    int graphTimer_interval = 400;
    int loggerTimer_interval = 0;
    void readChannelSettingsFile();
    void processChannelSettingsStr(QString str);
    Addressing *addrss_Obj;
    void initializeHWAddresses();
    uint32_t *local_FPGA_ADDRESS;
    //int32_t *local_LED_ADDRESS;
    int fpgaCounterAddr = 54;
    uint16_t fpgaCounterValue = 0x0000;
    uint16_t fpgaCounterValue_OLD = 0x0000;

    //QVector<int> qv_graphChannels;
    int graphChannels_idx[4] = {232, 232, 232, 232};
    bool graphChannels_idxBool[4] = {false, false, false, false};

    bool graphWindowIsOpen = false;
    bool chnlSettingsWindowIsOpen = false;
    bool logging_isStarted = false;
    bool addFirstEnableChannelinGraph = true;

    int sampleRate_Sec = 2;
    int sampleRate_MS = 100;
    int sampleRate_MS_Calculated = 0;
    qint64 elapsed_timeNanoSec = 0;
    int elapsed_timeMS = 0;
    QString logStr = "";
    long logSerialNumber = 0;

    int local_logTime_MS = 0;
    long nanoSec = 0;




    // -------------- Channel settings File things ------------
    QString dacChannelSettingsfilePath = QString(QDir::homePath()+"/settingsDAC");
    QFile *Settingsfile;
    bool okVariable = false;
    int settingsCH_id = 0;
    CHANNEL_PGA settingsCH_pga = CH_PGA_1;
    float settingsCH_factor = 1.1;
    int settingsCH_type = 0;
    int settingsCH_ref = 0;
    int settingsCH_isEnable = 0;




    // -------------- Log File things ------------
    void initialize_Dir_FileName();
    void initialize_User_FileName();
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
    QString local_LogTime_Str = "000:00:00";
};

#endif // LOGGERTHREAD_H
