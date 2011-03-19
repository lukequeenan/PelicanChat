#-------------------------------------------------
#
# Project created by QtCreator 2011-03-12T10:20:41
#
#-------------------------------------------------

QT       += core gui

TARGET = PelicanChatClient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ../network/network.c \
    joinserver.cpp \
    listenthread.cpp

HEADERS  += mainwindow.h \
    ../network/network.h \
    joinserver.h \
    listenthread.h

FORMS    += mainwindow.ui \
    joinserver.ui
