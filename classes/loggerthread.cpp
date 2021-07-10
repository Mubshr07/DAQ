#include "loggerthread.h"

chnlClass_Simple chnlArray[TOTAL_CHANNEL];
loggerThread::loggerThread(QObject *parent) : QObject(parent)
{
    qDebug()<<" debug LoggerThread start ";
    initializeHWAddresses();

    for(int i = 0; i< TOTAL_CHANNEL; i++)
    {
        chnlArray[i].setChannelEnableDisable(false);
        chnlArray[i].setChannelAddress(i);
        if(i<24) chnlArray[i].set_Channel_Type(BRIDGE);
        else chnlArray[i].set_Channel_Type(SINGEL_ENDED);
    }

    uint32_t fpgaID = *(local_FPGA_ADDRESS+78);

    qDebug()<<"\n\n\n";
    qDebug()<<" FPGA Addr:"<<local_FPGA_ADDRESS <<" Value :: "<<QString::number(fpgaID,16) <<" :: "<<QString::number(*(local_FPGA_ADDRESS+0x4E),16);
    qDebug()<<"\n\n\n";
    globalVars::global_FPGA_ADDR = local_FPGA_ADDRESS;

    readChannelSettingsFile();
    qDebug()<<" debug LoggerThread 1 ";

    //qDebug()<<" before timer_logger initialize ";
    timer_logger = new QTimer(this);
    connect(timer_logger, SIGNAL(timeout()), SLOT(on_timer_logger_elapsed()));
    timer_logger->start(sampleRate_MS);

    local_logging = false;
    local_logTime_MS = 0;
    local_log_sec = 0;
    local_log_min = 0;
    local_log_hours = 0;
    //qDebug()<<" debug LoggerThread 2 ";
    //qDebug()<<" before timer_graph initialize ";
    timer_graphValue = new QTimer(this);
    connect(timer_graphValue, SIGNAL(timeout()), SLOT(on_timer_graphValue_elapsed()));
    timer_graphValue->start(100);

    //qDebug()<<" debug LoggerThread 3 ";
    timer_elapser = new QElapsedTimer();
    timer_elapser2 = new QElapsedTimer();
    timer_elapser2->start();

    qDebug()<<" debug LoggerThread 4 ";
}


void loggerThread::on_timer_logger_elapsed()
{
    //qDebug()<<" debug on_timer_logger_elapsed 1 ";
    timer_elapser->start();
    logStr = QString(QString::number(logSerialNumber)+",");
    logStr += QString(QTime::currentTime().toString("HH:mm:ss")+",");
    logStr += QString(local_LogTime_Str+",");

    for(int i=0; i<TOTAL_CHANNEL; i++)
    {
        if(chnlArray[i].isChnlEnable())
        {
            if(!graphWindowIsOpen) {
                emit tx_channel_Value(i, chnlArray[i].Get_RawValue_fromADDRESS(), chnlArray[i].giveCurrentValue());
            } else if(graphWindowIsOpen && local_logging) {
                logStr += QString(QString::number(chnlArray[i].giveCurrentValue(), 'f', 3)+",");
            }
        }
    }

    if(local_logging)
    {
        logStr += "\n";
        writeThisToLogFile(logStr);
        logSerialNumber++;
    }


    if(!graphWindowIsOpen)
    {
           timer_logger->setInterval(300);
    }
    else
    {
        elapsed_timeNanoSec = timer_elapser->nsecsElapsed();
        sampleRate_MS_Calculated = (sampleRate_MS - (elapsed_timeNanoSec/1000000.0));
        timer_logger->setInterval(sampleRate_MS_Calculated);
    }
    //qDebug()<<" 2222222222 ";
}
void loggerThread::on_timer_graphValue_elapsed()
{
    timer_elapser2->restart();
    for(int i=0; i<4; i++)
    {
        if(graphChannels_idxBool[i])
        {
            emit tx_GraphChannelValue(i, graphChannels_idx[i], chnlArray[graphChannels_idx[i]].giveCurrentValue());
        }
    }
    if(chnlSettingsWindowIsOpen) emit tx_channel_Value(settingsCH_id, chnlArray[settingsCH_id].Get_RawValue_fromADDRESS(), chnlArray[settingsCH_id].giveCurrentValue());

    if(local_logging)
    {
        if(local_logTime_MS >= 1000)
        {
            local_logTime_MS -= 1000;
            local_log_sec++;
            if(local_log_hours<100)
                local_LogTime_Str = QString("00"+QString::number(local_log_hours)+ ":");
            else if(local_log_hours<10)
                local_LogTime_Str = QString("0"+QString::number(local_log_hours)+ ":");
            else
                local_LogTime_Str = QString(QString::number(local_log_hours)+ ":");

            if(local_log_min<10)
                local_LogTime_Str += QString("0"+QString::number(local_log_min)+ ":");
            else
                local_LogTime_Str += QString(QString::number(local_log_min)+ ":");

            if(local_log_sec<10)
                local_LogTime_Str += QString("0"+QString::number(local_log_sec));
            else
                local_LogTime_Str += QString(QString::number(local_log_sec));

            emit tx_ramdomOP(1, 1.0, local_LogTime_Str);
        }
        if(local_log_sec > 59)
        {
            local_log_sec = 0;
            local_log_min++;
        }
        if(local_log_min > 59)
        {
            local_log_min = 0;
            local_log_hours++;
        }

        local_logTime_MS += (timer_graphValue->interval()+timer_elapser2->elapsed());

        //qDebug()<<" local_logTime_MS:: "<<local_logTime_MS;
    }

}


void loggerThread::rx_setChannelEnableDisable(int chnlIndex, bool enable)
{
    emit tx_channelisEnabled(chnlIndex, chnlArray[chnlIndex].setChannelEnableDisable(enable));
}
void loggerThread::rx_setSampleTime(int mSec)
{
    sampleRate_Sec = mSec/1000.0;
    sampleRate_MS = mSec;
}
void loggerThread::rx_loggingStartStop(bool start, QString filePth)
{
    qDebug()<<" Logging Status : "<<start<<" filePath: "<<filePth;
    logging_isStarted = false;
    if(start){
        filePath = filePth;
        initialize_User_FileName();
        local_log_sec = 0;
        local_log_min = 0;
        local_log_hours = 0;
        emit tx_ramdomOP(0, 0.0, filePath);
    }
    else
    {
        emit tx_ramdomOP(0, 0.0, "");
    }

    local_logging = start;
    emit tx_loggingStarted(logging_isStarted);
}


void loggerThread::rx_giveMeEnablesChannels()
{
    for(int i=0; i<TOTAL_CHANNEL; i++)
    {
        if(chnlArray[i].isChnlEnable())
        {
            if(addFirstEnableChannelinGraph)
            {
                qDebug()<<" First channel is added "<<i;
                addFirstEnableChannelinGraph = false;
                graphChannels_idx[0] = i;
                graphChannels_idxBool[0] = true;
            }
            emit tx_EnableChannelsAre(i);
        }
    }
}
void loggerThread::rx_sendFactorsAndPGAs_AllChnls()
{
    for(int i=0; i<TOTAL_CHANNEL; i++)
    {
        emit tx_sendingFactorsAndPGAs(i, chnlArray[i].give_Channel_Factor(), chnlArray[i].give_Channel_PGA());
    }
}
void loggerThread::rx_AddNewChannelToGraph(int idx, int chnlID)
{
    graphChannels_idx[idx] = chnlID;
    graphChannels_idxBool[idx] = true;
}
void loggerThread::rx_RemoveChannelToGraph(int idx, int chnlID)
{
    graphChannels_idx[idx] = chnlID;
    graphChannels_idxBool[idx] = false;
}
void loggerThread::rx_GraphWindowIsOpen(bool windOpen)
{
    //qDebug()<<" Graph Window is Open : "<<windOpen;
    if(windOpen == false) addFirstEnableChannelinGraph = true;
    graphWindowIsOpen = windOpen;
    if(windOpen)
    {
        initialize_Dir_FileName();
        logSerialNumber=0;
    }
}
void loggerThread::rx_ChannelSettingsWindowIsOpen(bool windOpen)
{
    //qDebug()<<" Channel Setting Window is Open : "<<windOpen;
    chnlSettingsWindowIsOpen = windOpen;
}



// ---------------  DAC CHANNEL SETTINGS ---------------------
void loggerThread::rx_setChannelNewSettings(int chnl, float fac, float pgaa, CHANNEL_TYPE typ, CHANNEL_REFERENCE ref)
{
    qDebug()<<" New Chanel Settings:: ID:"<<chnl<<" fac:"<<fac<<" pgaa:"<<pgaa<<" type:"<<typ<<" ref:"<<ref;
    chnlArray[chnl].set_Channel_Factor(fac);
    chnlArray[chnl].set_Channel_PGA(pgaa);
    chnlArray[chnl].set_Channel_Type(typ);
    chnlArray[chnl].set_Channel_Reference(ref);

    rx_saveChannelSettingsToFile();
}
void loggerThread::rx_giveMechannelSettings(int chnl)
{
    settingsCH_id = chnl;
    emit tx_ChannelOLDSettings(chnl, chnlArray[chnl].give_Channel_Factor(), chnlArray[chnl].give_Channel_PGA(), chnlArray[chnl].give_Channel_Type(), chnlArray[chnl].give_Channel_Reference());
}
void loggerThread::rx_saveChannelSettingsToFile()
{
    //qDebug()<<" now saving Settings to File:: "<<dacChannelSettingsfilePath;
    QString fileData = "$chnl,$PGA,$Factor,$BridgeChnl,\n";
    Settingsfile = new QFile(dacChannelSettingsfilePath);
    if(Settingsfile->open(QIODevice::WriteOnly))
    {
        for(int i=0; i<TOTAL_CHANNEL; i++)
        {

            fileData += QString(QString::number(i)+",");
            fileData += QString(QString::number(chnlArray[i].give_Channel_PGA(), 'f', 5)+",");
            fileData += QString(QString::number(chnlArray[i].give_Channel_Factor(), 'f', 5)+",");
            fileData += QString(QString::number(chnlArray[i].give_Channel_Type())+",");
            fileData += QString(QString::number(chnlArray[i].give_Channel_Reference())+",");
            fileData += QString("\n");
        }
        fileData += "$chnl,$PGA,$Factor,$BridgeChnl,\n";

        Settingsfile->write(fileData.toUtf8());
        emit tx_ramdomOP(15179, 1.1, "New Settings Saved.");
        Settingsfile->close();
    }
    else
    {
        qDebug()<<"Error in open File";
        emit tx_ramdomOP(15179, 1.1, "Error in File Opening to save channels settings.");
    }
}


void loggerThread::readChannelSettingsFile()
{
    qDebug()<<" dacSettingsFile: "<<dacChannelSettingsfilePath;

    if(QFile::exists(dacChannelSettingsfilePath))
    {
        Settingsfile = new QFile(dacChannelSettingsfilePath);
        if(Settingsfile->open(QIODevice::ReadOnly))
        {
            QTextStream in(Settingsfile);
            while(!in.atEnd()){
                processChannelSettingsStr(in.readLine());
            }
            Settingsfile->close();
        }
        else
        {
            qDebug()<<"Error in open OLD File Settings";
        }
    }
    else
    {
        qDebug()<<"File did not Exist.";
    }
}
void loggerThread::processChannelSettingsStr(QString str)
{
    //qDebug()<<"Passing SettingsFile String:: "<<str;
    int indxOfComa = 0;
    QString dataStr;
    okVariable = false;
    if(!str.contains("$"))
    {
        // -------- Channel ID
        indxOfComa = str.indexOf(',');
        dataStr = str.left(indxOfComa);
        settingsCH_id = dataStr.toInt(&okVariable, 10);
        str.remove(0, indxOfComa+1);

        // -------- Channel pga
        indxOfComa = str.indexOf(',');
        dataStr = str.left(indxOfComa);
        settingsCH_pga = dataStr.toFloat(&okVariable);
        str.remove(0, indxOfComa+1);

        // -------- Channel Factor
        indxOfComa = str.indexOf(',');
        dataStr = str.left(indxOfComa);
        settingsCH_factor = dataStr.toFloat(&okVariable);
        str.remove(0, indxOfComa+1);

        // -------- Channel Type
        indxOfComa = str.indexOf(',');
        dataStr = str.left(indxOfComa);
        settingsCH_type = dataStr.toInt(&okVariable, 10);
        str.remove(0, indxOfComa+1);

        // -------- Channel ref
        indxOfComa = str.indexOf(',');
        dataStr = str.left(indxOfComa);
        settingsCH_ref = dataStr.toInt(&okVariable, 10);

        //qDebug()<<" ID:"<<settingsCH_id<<" pga:"<<settingsCH_pga<<" fac:"<<settingsCH_factor<<" type:"<<settingsCH_type<<" ref:"<<settingsCH_ref;

        chnlArray[settingsCH_id].set_Channel_PGA(settingsCH_pga);
        chnlArray[settingsCH_id].set_Channel_Factor(settingsCH_factor);
        if(settingsCH_type == 0) chnlArray[settingsCH_id].set_Channel_Type(BRIDGE);
        else if(settingsCH_type == 1) chnlArray[settingsCH_id].set_Channel_Type(SINGEL_ENDED);

        if(settingsCH_ref == 0) chnlArray[settingsCH_id].set_Channel_Reference(INTERNAL);
        else if(settingsCH_ref == 1) chnlArray[settingsCH_id].set_Channel_Reference(EXTERNAL);

    }

}

// ---------------  ONE Time Used Methods --------------------
void loggerThread::initializeHWAddresses()
{
    addrss_Obj = new Addressing();
    qDebug()<<" Address Generate Reply: "<<addrss_Obj->get_address_of_peripherals();

    local_FPGA_ADDRESS = addrss_Obj->givemeaddr(0);
}

void loggerThread::initialize_Dir_FileName()
{
    //qDebug()<<"Home Directory String:: "<<LogDirPath;
    QDir mainDir(folderPath);
    if (!mainDir.exists())
    {
        mainDir.mkdir(folderPath);
    }
    LogFileNumber = 0;
/*
    while (true)
    {
        if(!(QFileInfo::exists(folderPath +"/LogFile_"+ QString::number(LogFileNumber) + logFileExtension))) {
            filePath = QString(folderPath +"/LogFile_"+ QString::number(LogFileNumber) + logFileExtension);
            break;
        } else {
            LogFileNumber++;
        }
    }

    qDebug()<<" New File Path : "<<filePath;

    QString str = "S/N,";
    str += "Log Time,";
    //str += "Log Time,";


    for(int i=0; i<TOTAL_CHANNEL;i++)
    {
        if(chnlArray[i].isChnlEnable())
        {
            str += QString("Ch#"+QString::number(i)+",");
        }
    }
    //qDebug()<<" initialFile: "<<str;

    str += "\n";
    logFile = new QFile(filePath);
    if(logFile->open(QIODevice::ReadWrite))
    {
        logFile->write(str.toUtf8());
        logFile->close();
    }
    else
    {
        qDebug()<<"Error in open File";
    } */
    //qDebug()<<" initial Log File Path is:  "<<localFilePath;
}
void loggerThread::initialize_User_FileName()
{
    logSerialNumber = 0;
    qDebug()<<" New File Path : "<<filePath;

    QString str = "S/N,";
    str += "Time,";
    str += "Log Time,";


    for(int i=0; i<TOTAL_CHANNEL;i++)
    {
        if(chnlArray[i].isChnlEnable())
        {
            str += QString("Ch#"+QString::number(i)+",");
        }
    }
    //qDebug()<<" initialFile: "<<str;

    str += "\n";
    logFile = new QFile(filePath);
    if(logFile->open(QIODevice::WriteOnly))
    {
        logging_isStarted = true;
        logFile->write(str.toUtf8());
        logFile->close();
    }
    else
    {
        qDebug()<<"Error in open File";
    }
}
void loggerThread::writeThisToLogFile(QString str)
{
    if(logFile->open(QIODevice::Append))
    {
        logFile->write(str.toUtf8());
        logFile->close();
    }
    else
    {
        qDebug()<<"Error in Writing str to File in Append mode";
    }
}

