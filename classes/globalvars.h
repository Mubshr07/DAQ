#ifndef GLOBALVARS_H
#define GLOBALVARS_H

#define TOTAL_CHANNEL 48

enum GUI_WIN {
    gui_CONFIG_CH_WIN,
    gui_CONFIRMATION_WIN,
    gui_FIRST_WIN,
    gui_GRAPH_WIN,
    gui_LOG_CONFIG_WIN,
    gui_DEBUG_WIN
};

enum CHANNEL_TYPE {
    Accelerometer,
    DT_Sensor,
    Volts_0_10,
    BridgeCH
};

enum CHANNEL_REFERENCE {
    INTERNAL_REF,
    EXTERNAL_REF
};

enum CHANNEL_PGA {
    CH_PGA_1,
    CH_PGA_2,
    CH_PGA_4,
    CH_PGA_8,
    CH_PGA_16,
    CH_PGA_32,
    CH_PGA_64,
    CH_PGA_128
};


#include <QObject>
#include <math.h>
#include <unistd.h>
#include <QDateTime>
#include <QTimer>
#include <QElapsedTimer>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QFileInfoList>
#include <QFileDialog>
#include <QThread>
#include <QVariant>
#include <QMap>
#include <QVector>
#include <QMetaType>

#include <iostream>
#include <unistd.h>
#include <stdlib.h>

#include "qdebug.h"
#include "confirmationbox.h"

class globalVars : public QObject
{
    Q_OBJECT
public:
    explicit globalVars(QObject *parent = nullptr);

    static QString logFile;
    static uint32_t *global_FPGA_ADDR;

};

Q_DECLARE_METATYPE(uint32_t);
Q_DECLARE_METATYPE(int32_t);

Q_DECLARE_METATYPE(GUI_WIN);
Q_DECLARE_METATYPE(CHANNEL_TYPE);
Q_DECLARE_METATYPE(CHANNEL_REFERENCE);
Q_DECLARE_METATYPE(CHANNEL_PGA);

#endif // GLOBALVARS_H
