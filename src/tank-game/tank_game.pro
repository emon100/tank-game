#-------------------------------------------------
#
# Project created by QtCreator 2019-07-23T16:55:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mapmaker
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
         game/game_items.cpp \
         game/game_widget.cpp \
        interface/J_currentplayer.cpp \
        interface/J_idlogpage.cpp \
        interface/J_idregister.cpp \
        interface/J_loginpage.cpp \
        interface/J_mainpage.cpp \
        interface/J_mainwindow.cpp \
        interface/J_succeed.cpp \
        main.cpp \
        map_maker/mapmaker.cpp \
        map_maker/mymap.cpp \

HEADERS += \
         game/game_items.h \
         game/game_widget.h \
        interface/J_currentplayer.h \
        interface/J_idlogpage.h \
        interface/J_idregister.h \
        interface/J_loginpage.h \
        interface/J_mainpage.h \
        interface/J_mainwindow.h \
        interface/J_succeed.h \
        map_maker/mapmaker.h \
        map_maker/mymap.h \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    game/game_widget.ui \
    interface/currentplayer.ui \
    interface/idlogpage.ui \
    interface/idregister.ui \
    interface/loginpage.ui \
    interface/mainpage.ui \
    interface/mainwindow.ui \
    interface/succeed.ui \
    map_maker/mapmaker.ui \

RESOURCES += \
    resources.qrc
