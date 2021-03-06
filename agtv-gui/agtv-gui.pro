#-------------------------------------------------
#
# Project agtv-gui
#
#-------------------------------------------------

CONFIG += c++11

QMAKE_CXXFLAGS += -Wall

include(project/version.pri)

DEFINES += IRC_SHARED

DEPLOYMENT = no
CONFIG += winternalvlc
CONFIG += internalirc

BUILDBASE = ../

include(project/developer.pri)

include(project/app.pri)

equals(DEVELOPER, "scuq") {
    include(project/developer_scuq.pri)
}

equals(DEVELOPER, "hps") {
    include(project/developer_hps.pri)
}

equals(DEVELOPER, "DAS") {
    include(project/developer_nowx.pri)
}

include(project/macosx.pri)

include(project/win32.pri)

include(project/vlcqt.pri)

include(project/libcommuni.pri)

QT       += core gui network multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = agtv
TEMPLATE = app

SOURCES +=  main.cpp\
            tpmainwindow.cpp \
            generichelper.cpp \
            processlauncher.cpp \
            dialogoauthsetup.cpp \
            dialogpositioner.cpp \
            dialoglaunch.cpp \
            dialogoptions.cpp \
            advqsortfilterproxymodel.cpp \
            imageloader.cpp \
            updatecheck.cpp \
            dialogshowlogfile.cpp \
            filedownloader.cpp \
            agtvdefaultitemdelegate.cpp \
            dialoggamebrowser.cpp \
            advqsortfilterproxylistmodel.cpp \
            twitchobject.cpp \
            twitchchannel.cpp \
            twitchuser.cpp \
            twitchuserlocal.cpp \
            twitchgamebrowser.cpp \
            twitchchannelmodel.cpp

HEADERS  += tpmainwindow.h \
            generichelper.h \
            processlauncher.h \
            dialogoauthsetup.h \
            dialogpositioner.h \
            dialoglaunch.h \
            dialogoptions.h \
            advqsortfilterproxymodel.h \
            imageloader.h \
            updatecheck.h \
            dialogshowlogfile.h \
            filedownloader.h \
            agtvdefaultitemdelegate.h \
            dialoggamebrowser.h \
            advqsortfilterproxylistmodel.h \
            twitchobject.h \
            twitchchannel.h \
            version.h \
            twitchuser.h \
            twitchuserlocal.h \
            twitchgamebrowser.h \
            twitchchannelmodel.h

FORMS    += tpmainwindow.ui \
            dialogoauthsetup.ui \
            dialogpositioner.ui \
            dialoglaunch.ui \
            dialogoptions.ui \
            dialogshowlogfile.ui \
            dialoggamebrowser.ui

RESOURCES += \
            agtv.qrc

DISTFILES += \
            README.md \
            agtv.nsi
