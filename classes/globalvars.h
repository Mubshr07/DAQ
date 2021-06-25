#ifndef GLOBALVARS_H
#define GLOBALVARS_H

#define TOTAL_CHANNEL 48

enum GUI_WIN {
    gui_CONFIG_CH_WIN,
    gui_CONFIRMATION_WIN,
    gui_FIRST_WIN,
    gui_GRAPH_WIN,
    gui_LOG_CONFIG_WIN
};

enum CHANNEL_TYPE {
    BRIDGE,
    SINGEL_ENDED
};

enum CHANNEL_REFERENCE {
    INTERNAL,
    EXTERNAL
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
#include <QVector>

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

};
Q_DECLARE_METATYPE(GUI_WIN);
Q_DECLARE_METATYPE(CHANNEL_TYPE);
Q_DECLARE_METATYPE(CHANNEL_REFERENCE);

#endif // GLOBALVARS_H
