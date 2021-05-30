#ifndef GLOBALVARS_H
#define GLOBALVARS_H

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
#include <QThread>
#include <QVariant>

#include "qdebug.h"


class globalVars : public QObject
{
    Q_OBJECT
public:
    explicit globalVars(QObject *parent = nullptr);

    static QString logFile;

};

#endif // GLOBALVARS_H
