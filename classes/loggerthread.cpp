#include "loggerthread.h"

chnlClass_Simple chnlArray[TOTAL_CHANNEL];
loggerThread::loggerThread(QObject *parent) : QObject(parent)
{
    qDebug()<<" debug LoggerThread start ";
    initializeHWAddresses();

    globalVars::global_FPGA_ADDR = local_FPGA_ADDRESS;
    for(int i = 0; i< TOTAL_CHANNEL; i++)
    {
        chnlArray[i].setChannelEnableDisable(false);
        chnlArray[i].setChannelAddress(local_FPGA_ADDRESS, i);
        chnlArray[i].set_Channel_PGA_Type( CH_PGA_1, Accelerometer);
        //else chnlArray[i].set_Channel_Type(SINGEL_ENDED);
    }

    uint32_t fpgaID = *(local_FPGA_ADDRESS+78);

    qDebug()<<"\n\n\n";
    qDebug()<<" FPGA Addr:"<<local_FPGA_ADDRESS <<" Value :: "<<QString::number(fpgaID,16) <<" :: "<<QString::number(*(local_FPGA_ADDRESS+0x4E),16);
    qDebug()<<"\n\n\n";

    readChannelSettingsFile();
    qDebug()<<" debug LoggerThread 1 ";

    initialize_Dir_FileName();

    //  ----------------------------------------------------------------
    *(local_FPGA_ADDRESS + 0x06) = 0x00;
    usleep(8000);
    *(local_FPGA_ADDRESS + 0x07) = 0x00;
    usleep(8000);
    *(local_FPGA_ADDRESS + 0x07) = 0x01;
    usleep(8000);
    *(local_FPGA_ADDRESS + 0x07) = 0x00;
    usleep(10000);
    // -------- Set Clock
    uint32_t setClock = 2;
    setClock /= 0.02;
    *(local_FPGA_ADDRESS+ 0x00) = setClock;
    usleep(10000);
    // -------- Set DataRate
    uint32_t setRateInt = 500;   // uSec
    setRateInt /= 0.02;
    *(local_FPGA_ADDRESS + 14) = setRateInt;
    usleep(10000);
    *(local_FPGA_ADDRESS + 0x06) = 0x00;
    usleep(8000);
    *(local_FPGA_ADDRESS + 0x07) = 0x00;
    usleep(8000);
    *(local_FPGA_ADDRESS + 0x07) = 0x01;
    usleep(8000);
    *(local_FPGA_ADDRESS + 0x07) = 0x00;
    usleep(10000);
    //  ----------------------------------------------------------------


    local_logTime_MS = 0;
    local_log_sec = 0;
    local_log_min = 0;
    local_log_hours = 0;
    //qDebug()<<" debug LoggerThread 2 ";
    //qDebug()<<" before timer_graph initialize ";
    timer_graphValue = new QTimer(this);
    connect(timer_graphValue, SIGNAL(timeout()), SLOT(on_timer_graphValue_elapsed()));
    timer_graphValue->start(graphTimer_interval);

    //qDebug()<<" debug LoggerThread 3 ";
    timer_elapser = new QElapsedTimer();


    //qDebug()<<" before timer_logger initialize ";
    timer_logger = new QTimer(this);
    connect(timer_logger, SIGNAL(timeout()), SLOT(on_timer_logger_elapsed()));
    timer_logger->start(loggerTimer_interval);

    //qDebug()<<" debug LoggerThread 4 ";
    logging_isStarted = false;
}


void loggerThread::on_timer_logger_elapsed()
{
    //qDebug()<<" debug on_timer_logger_elapsed 1 ";
    fpgaCounterValue = *(local_FPGA_ADDRESS + fpgaCounterAddr);
    usleep(5);
    fpgaCounterValue = *(local_FPGA_ADDRESS + fpgaCounterAddr);
//    usleep(10);
//    fpgaCounterValue = *(local_FPGA_ADDRESS + fpgaCounterAddr);


    if(fpgaCounterValue != fpgaCounterValue_OLD)
    {
        fpgaCounterValue_OLD = fpgaCounterValue;
        /* for(int i=0; i<TOTAL_CHANNEL; i++)
        {
            if(chnlArray[i].isChnlEnable())
            {
                chnlArray[i].Get_RawValue_fromADDRESSAuto();
            }
        } */
        if(logging_isStarted)
        {
            // Logging to File
            logStr = "";
            logStr = QString(QString::number(logSerialNumber)+",");
            //logStr += QString(QTime::currentTime().toString("HH:mm:ss")+",");
            //logStr += QString(local_LogTime_Str+",");

            logStr += QString(QString::number(*(local_FPGA_ADDRESS + 81))+ ",");
            logStr += QString(QString::number(fpgaCounterValue)+ ",");


            for(int i=0; i<TOTAL_CHANNEL; i++)
            {
                if(chnlArray[i].isChnlEnable())
                {
                    chnlArray[i].Get_RawValue_fromADDRESSAuto();
                    logStr += QString(QString::number(chnlArray[i].autoScheme_endResult_Float_Factor, 'f', 3)+",");
                    //emit tx_channel_Value(i, chnlArray[i].autoScheme_endResult, chnlArray[i].autoScheme_endResult_Float, chnlArray[i].autoScheme_endResult_Float_Factor);
                }
            }
            logStr += "\n";
            writeThisToLogFile(logStr);
            logSerialNumber++;
        }
        else // Manual Methods
        {
            for(int i=0; i<TOTAL_CHANNEL; i++)
            {
                if(chnlArray[i].isChnlEnable())
                {
                    chnlArray[i].Get_RawValue_fromADDRESS();
                    emit tx_channel_Value(i, chnlArray[i].endResult, chnlArray[i].endResult_Float, chnlArray[i].endResult_Float_Factor);
                }
            }
        }


    } // end of FPGA-Counter Matched
    else
    {
        //qDebug()<<" Counter Value: "<<fpgaCounterValue;
        if(!logging_isStarted)
        {
            for(int i=0; i<TOTAL_CHANNEL; i++)
            {
                if(chnlArray[i].isChnlEnable())
                {
                    chnlArray[i].Get_RawValue_fromADDRESS();
                    emit tx_channel_Value(i, chnlArray[i].endResult, chnlArray[i].endResult_Float, chnlArray[i].endResult_Float_Factor);
                    usleep(100);
                }
            }
        }
    }


}
void loggerThread::on_timer_graphValue_elapsed()
{
    timer_elapser->restart();

    if(graphWindowIsOpen) {
        for(int i=0; i<4; i++)
        {
            if(graphChannels_idxBool[i])
            {
                //chnlArray[graphChannels_idx[i]].Get_RawValue_fromADDRESS();
                //qDebug()<<" graph Channel Indx:"<<i<<" CH#"<<graphChannels_idx[i]<<" value "<<chnlArray[graphChannels_idx[i]].autoScheme_endResult_Float_Factor;
                if(logging_isStarted)
                    emit tx_GraphChannelValue(i, graphChannels_idx[i], chnlArray[graphChannels_idx[i]].autoScheme_endResult_Float_Factor);
                else
                {
                    //chnlArray[graphChannels_idx[i]].Get_RawValue_fromADDRESS();
                    emit tx_GraphChannelValue(i, graphChannels_idx[i], chnlArray[graphChannels_idx[i]].endResult_Float_Factor);
                }
            }
        }
    }
    if(chnlSettingsWindowIsOpen)
    {
        //chnlArray[settingsCH_id].Get_RawValue_fromADDRESS();
        emit tx_channel_Value_Config(settingsCH_id, chnlArray[settingsCH_id].endResult, chnlArray[settingsCH_id].endResult_Float, chnlArray[settingsCH_id].endResult_Float_Factor);
    }
    if(logging_isStarted)
    {
        for(int i=0; i<TOTAL_CHANNEL; i++)
        {
            if(chnlArray[i].isChnlEnable())
            {
                emit tx_channel_Value(i, chnlArray[i].autoScheme_endResult, chnlArray[i].autoScheme_endResult_Float, chnlArray[i].autoScheme_endResult_Float_Factor);
            }
        }
    }


//    else if(!graphWindowIsOpen && !chnlSettingsWindowIsOpen)
//    {
//        if(logging_isStarted)
//        {
//            for(int i=0; i<TOTAL_CHANNEL; i++)
//            {
//                if(chnlArray[i].isChnlEnable())
//                {
//                    //chnlArray[i].Get_RawValue_fromADDRESSAuto();
//                    emit tx_channel_Value(i, chnlArray[i].autoScheme_endResult, chnlArray[i].autoScheme_endResult_Float, chnlArray[i].autoScheme_endResult_Float_Factor);
//                }
//            }
//        }
//        else
//        {
//            for(int i=0; i<TOTAL_CHANNEL; i++)
//            {
//                if(chnlArray[i].isChnlEnable())
//                {
//                    chnlArray[i].Get_RawValue_fromADDRESS();
//                    emit tx_channel_Value(i, chnlArray[i].endResult, chnlArray[i].endResult_Float, chnlArray[i].endResult_Float_Factor);
//                }
//            }
//        }
//    }


    if(logging_isStarted)
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
        nanoSec += timer_elapser->nsecsElapsed();
        if(nanoSec > 1000000)
        {
            nanoSec -= 1000000;
            local_logTime_MS++;
        }
        local_logTime_MS += +timer_graphValue->interval();
        //qDebug()<<" local_logTime_MS:: "<<local_logTime_MS;
    }

}


void loggerThread::rx_startReadingTimer(bool startReading)
{
    if(startReading) timer_graphValue->start(graphTimer_interval);
    else timer_graphValue->stop();
}


void loggerThread::rx_setChannelEnableDisable(int chnlIndex, bool enable)
{
    timer_logger->stop();
    timer_graphValue->stop();

    emit tx_channelisEnabled(chnlIndex, chnlArray[chnlIndex].setChannelEnableDisable(enable));

    timer_logger->start(loggerTimer_interval);
    timer_graphValue->start(graphTimer_interval);
}
void loggerThread::rx_setSampleTime(int mSec)
{
    //sampleRate_Sec = mSec/1000.0;
    //sampleRate_MS = mSec;

    // -------- Set DataRate
    //uint32_t setRateInt = 50000000;   // fpga Clock

    timer_logger->stop();
    timer_graphValue->stop();

    uint32_t setRateInt = 10000 / mSec / 0.02;   // fpga Clock
    //setRateInt /= mSec;
    *(local_FPGA_ADDRESS + 14) = setRateInt;
    *(local_FPGA_ADDRESS + 14) = setRateInt;
    *(local_FPGA_ADDRESS + 14) = setRateInt;
    usleep(10000);
    *(local_FPGA_ADDRESS + 14) = setRateInt;
    *(local_FPGA_ADDRESS + 14) = setRateInt;
    *(local_FPGA_ADDRESS + 14) = setRateInt;
    usleep(10000);


    timer_logger->start(loggerTimer_interval);
    timer_graphValue->start(graphTimer_interval);
    qDebug()<<" passing Rate : "<<mSec<<" make: "<<setRateInt;
}
void loggerThread::rx_loggingStartStop(bool start, QString filePth)
{
    timer_logger->stop();
    timer_graphValue->stop();
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
        // disable automatic system
        *(local_FPGA_ADDRESS + 0x06) = 0x00;
        *(local_FPGA_ADDRESS + 0x07) = 0x00;
        usleep(5000);
    }

    emit tx_loggingStarted_andFileOpenSuccess(logging_isStarted);

    timer_logger->start(loggerTimer_interval);
    timer_graphValue->start(graphTimer_interval);
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
        emit tx_sendingFactorsAndPGAs(i, chnlArray[i].give_Channel_Factor(), chnlArray[i].give_Channel_PGA(), chnlArray[i].isChnlEnable());
    }
}
void loggerThread::rx_AddNewChannelToGraph(int idx, int chnlID)
{
    timer_graphValue->stop();

    graphChannels_idx[idx] = chnlID;
    graphChannels_idxBool[idx] = true;

    timer_graphValue->start(graphTimer_interval);
}
void loggerThread::rx_RemoveChannelToGraph(int idx, int chnlID)
{
    timer_graphValue->stop();

    graphChannels_idx[idx] = chnlID;
    graphChannels_idxBool[idx] = false;

    timer_graphValue->start(graphTimer_interval);
}
void loggerThread::rx_GraphWindowIsOpen(bool windOpen)
{
    //qDebug()<<" Graph Window is Open : "<<windOpen;
    if(windOpen == false) addFirstEnableChannelinGraph = true;
    graphWindowIsOpen = windOpen;
    if(windOpen)
    {
        chnlSettingsWindowIsOpen = false;
//        *(local_FPGA_ADDRESS + 0x06) = 0x01;

//        *(local_FPGA_ADDRESS + 0x07) = 0x00;
//        *(local_FPGA_ADDRESS + 0x07) = 0x01;
//        *(local_FPGA_ADDRESS + 0x07) = 0x00;
    }
    else {
        //timer_graphValue->stop();
        timer_graphValue->start(graphTimer_interval);
        //*(local_FPGA_ADDRESS + 0x06) = 0x00;
    }
}
void loggerThread::rx_ChannelSettingsWindowIsOpen(bool windOpen)
{
    timer_graphValue->stop();

    //qDebug()<<" Channel Setting Window is Open : "<<windOpen;
    chnlSettingsWindowIsOpen = windOpen;
    if(windOpen)
    {
        for(int i=0; i<TOTAL_CHANNEL; i++)
        {
            if(chnlArray[i].isChnlEnable())
            {
                emit tx_EnableChannelsAre(i);
            }
        }
        emit tx_EnableChannelsAre(15179); // ;-)
    }
    else
    {
        timer_graphValue->start(graphTimer_interval);
        // send channel properties to mainWindow after channelConfiguration Changed.
        for(int i=0; i<TOTAL_CHANNEL; i++)
        {
            emit tx_sendingFactorsAndPGAs(i, chnlArray[i].give_Channel_Factor(), chnlArray[i].give_Channel_PGA(), chnlArray[i].isChnlEnable());
        }
    }

    timer_graphValue->start(graphTimer_interval);
}



// ---------------  DAC CHANNEL SETTINGS ---------------------
void loggerThread::rx_setChannelNewSettings(int chnl, float fac, CHANNEL_PGA pgaa, CHANNEL_TYPE typ, CHANNEL_REFERENCE ref, bool Enabled)
{
    qDebug()<<"\n\n##################################################";
    qDebug()<<" New Chanel Settings:: ID:"<<chnl<<" fac:"<<fac<<" pgaa:"<<pgaa<<" type:"<<typ<<" ref:"<<ref;
    timer_graphValue->stop();
    timer_logger->stop();
    chnlArray[chnl].set_Channel_Factor(fac);
    chnlArray[chnl].set_Channel_PGA_Type(pgaa, typ);
    chnlArray[chnl].set_Channel_Reference(ref);
    chnlArray[chnl].setChannelEnableDisable(Enabled);
    chnlArray[chnl].reConfigFPGA_forThisChannel();

    rx_saveChannelSettingsToFile();
    timer_graphValue->start(graphTimer_interval);
    timer_logger->start(loggerTimer_interval);
}
void loggerThread::rx_giveMechannelSettings(int chnl)
{
    settingsCH_id = chnl;
    emit tx_ChannelOLDSettings(chnl, chnlArray[chnl].give_Channel_Factor(), chnlArray[chnl].give_Channel_PGA(), chnlArray[chnl].give_Channel_Type(), chnlArray[chnl].give_Channel_Reference(), chnlArray[chnl].isChnlEnable());
}
void loggerThread::rx_saveChannelSettingsToFile()
{
    //qDebug()<<" now saving Settings to File:: "<<dacChannelSettingsfilePath;
    QString fileData = "$chnl,$PGA,$Factor,$Type,$Ref,$Enabled,\n";
    Settingsfile = new QFile(dacChannelSettingsfilePath);
    if(Settingsfile->open(QIODevice::WriteOnly))
    {
        for(int i=0; i<TOTAL_CHANNEL; i++)
        {
            /*
             * 1.   Channel ID      (int)
             * 2.   Channel PGA     (int)
             * 3.   Channel Factor  (float)
             * 4.   Channel Type    (int)
             * 5.   Channel Ref     (int)
             * 6.   Channel Enable  (int)
             * 7.
            */
            fileData += QString(QString::number(i)+",");
            fileData += QString(QString::number(chnlArray[i].give_Channel_PGA())+",");
            fileData += QString(QString::number(chnlArray[i].give_Channel_Factor(), 'f', 5)+",");
            fileData += QString(QString::number(chnlArray[i].give_Channel_Type())+",");
            fileData += QString(QString::number(chnlArray[i].give_Channel_Reference())+",");
            fileData += QString(QString::number(chnlArray[i].isChnlEnable())+",");
            fileData += QString("\n");
        }
        fileData += "$chnl,$PGA,$Factor,$Type,$Ref,$Enabled,\n";

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

        if(str.length() < 1) return;
        // -------- Channel pga
        okVariable = false;
        indxOfComa = str.indexOf(',');
        dataStr = str.left(indxOfComa);
        settingsCH_pga = (CHANNEL_PGA)dataStr.toInt(&okVariable);
        str.remove(0, indxOfComa+1);

        if(str.length() < 1) return;
        // -------- Channel Factor
        okVariable = false;
        indxOfComa = str.indexOf(',');
        dataStr = str.left(indxOfComa);
        settingsCH_factor = dataStr.toFloat(&okVariable);
        str.remove(0, indxOfComa+1);

        if(str.length() < 1) return;
        // -------- Channel Type
        okVariable = false;
        indxOfComa = str.indexOf(',');
        dataStr = str.left(indxOfComa);
        settingsCH_type = dataStr.toInt(&okVariable, 10);
        str.remove(0, indxOfComa+1);

        if(str.length() < 1) return;
        // -------- Channel ref
        okVariable = false;
        indxOfComa = str.indexOf(',');
        dataStr = str.left(indxOfComa);
        settingsCH_ref = dataStr.toInt(&okVariable, 10);
        str.remove(0, indxOfComa+1);

        if(str.length() < 1) return;
        // -------- Channel Enable
        okVariable = false;
        indxOfComa = str.indexOf(',');
        dataStr = str.left(indxOfComa);
        settingsCH_isEnable = dataStr.toInt(&okVariable, 10);
        //str.remove(0, indxOfComa+1);


        //qDebug()<<" ID:"<<settingsCH_id<<" pga:"<<settingsCH_pga<<" fac:"<<settingsCH_factor<<" type:"<<settingsCH_type<<" ref:"<<settingsCH_ref;

        chnlArray[settingsCH_id].set_Channel_Factor(settingsCH_factor);
        if(settingsCH_type == 0) chnlArray[settingsCH_id].set_Channel_PGA_Type(settingsCH_pga, Accelerometer);
        else if(settingsCH_type == 1) chnlArray[settingsCH_id].set_Channel_PGA_Type(settingsCH_pga, DT_Sensor);
        else if(settingsCH_type == 2) chnlArray[settingsCH_id].set_Channel_PGA_Type(settingsCH_pga, Volts_0_10);
        else if(settingsCH_type == 3) chnlArray[settingsCH_id].set_Channel_PGA_Type(settingsCH_pga, BridgeCH);

        if(settingsCH_ref == 0) chnlArray[settingsCH_id].set_Channel_Reference(INTERNAL_REF);
        else if(settingsCH_ref == 1) chnlArray[settingsCH_id].set_Channel_Reference(EXTERNAL_REF);
        if(settingsCH_isEnable == 1) chnlArray[settingsCH_id].setChannelEnableDisable(true);

        usleep(10000);
        chnlArray[settingsCH_id].reConfigFPGA_forThisChannel();
        usleep(10000);
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


    str = "S/N,";
    str += "Addr:81,";
    str += "Counter,";



    for(int i=0; i<TOTAL_CHANNEL;i++)
    {
        if(chnlArray[i].isChnlEnable())
        {
            str += QString("Ch#"+QString::number(i+1)+",");
        }
    }
    //qDebug()<<" initialFile: "<<str;

    str += "\n";
    logFile = new QFile(filePath);
    if(logFile->open(QIODevice::WriteOnly))
    {
        *(local_FPGA_ADDRESS + 0x06) = 0x01;
        usleep(10000);
        *(local_FPGA_ADDRESS + 0x07) = 0x00;
        usleep(10000);
        *(local_FPGA_ADDRESS + 0x07) = 0x01;
        usleep(10000);
        *(local_FPGA_ADDRESS + 0x07) = 0x00;
        usleep(10000);

        qDebug()<<"\n\n *********************\n \t AUTOMATIC TESTING \n *********************\n\n\n";
        logFile->write(str.toUtf8());
        logFile->close();

        logging_isStarted = true;
    }
    else
    {
        // disable automatic system
        *(local_FPGA_ADDRESS + 0x06) = 0x00;
        usleep(10000);
        *(local_FPGA_ADDRESS + 0x07) = 0x00;
        usleep(10000);
        qDebug()<<"\n\n *********************\n \t Error in open File \n *********************\n\n\n";
    }
}
void loggerThread::writeThisToLogFile(QString str)
{
    if(logFile->open(QIODevice::Append))
    {
        logFile->write(str.toUtf8());
        //qDebug()<<" File opened and data logged: "<<logSerialNumber;
        logFile->close();
    }
    else
    {
        qDebug()<<"Error in Writing str to File in Append mode";
    }
}

