QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    classes/addressing.cpp \
    classes/chnlclass_simple.cpp \
    classes/qcustomplot.cpp \
    classes/globalvars.cpp \
    classes/loggerthread.cpp \
    configchwin.cpp \
    confirmationbox.cpp \
    debugwin.cpp \
    firstwindow.cpp \
    graphwin.cpp \
    main.cpp \
    mainhandler.cpp \
    mainwindow.cpp \
    newdebug.cpp

HEADERS += \
    classes/addressing.h \
    classes/chnlclass_simple.h \
    classes/qcustomplot.h \
    classes/globalvars.h \
    classes/loggerthread.h \
    configchwin.h \
    confirmationbox.h \
    debugwin.h \
    firstwindow.h \
    graphwin.h \
    mainhandler.h \
    mainwindow.h \
    newdebug.h

FORMS += \
    configchwin.ui \
    confirmationbox.ui \
    debugwin.ui \
    firstwindow.ui \
    graphwin.ui \
    mainwindow.ui \
    newdebug.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    pics.qrc


target.path = /home/root/
INSTALLS += target

