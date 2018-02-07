#-------------------------------------------------
#
# Project created by QtCreator 2018-01-18T13:30:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CoreWarGui
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11
INCLUDEPATH += ../CoreWar/include
INCLUDEPATH += ../CoreWar/src
SOURCES += main.cpp\
        mainwindow.cpp \
    renderarea.cpp \
    controller.cpp \
    ../CoreWar/src/arithmeticInstr.cpp \
    ../CoreWar/src/boolComand.cpp \
    ../CoreWar/src/core.cpp \
    ../CoreWar/src/datComand.cpp \
    ../CoreWar/src/executionContext.cpp \
    ../CoreWar/src/instruction.cpp \
    ../CoreWar/src/jumpComand.cpp \
    ../CoreWar/src/mars.cpp \
    ../CoreWar/src/movInstruction.cpp \
    ../CoreWar/src/parser.cpp \
    ../CoreWar/src/splCommand.cpp \
    warrior.cpp \
    scalearea.cpp \
    caravanpage.cpp \
    settingpage.cpp \
    ../CoreWar/include/model.cpp

HEADERS  += mainwindow.h \
    renderarea.h \
    controller.h \
    ../CoreWar/include/core.hpp \
    ../CoreWar/include/executionContext.hpp \
    ../CoreWar/include/factory.hpp \
    ../CoreWar/include/instruction.hpp \
    ../CoreWar/include/mars.hpp \
    ../CoreWar/include/parser.hpp \
    warrior.h \
    scalearea.h \
    caravanpage.h \
    settingpage.h \
    ../CoreWar/include/model.h

FORMS    += mainwindow.ui \
    scalearea.ui \
    caravanpage.ui \
    settingpage.ui
