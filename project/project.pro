TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    ../graph.cpp \
    ../main.cpp \
    ../getpart.cpp \
    ../dfs.cpp

include(deployment.pri)
qtcAddDeployment()

DISTFILES += \
    ../test.txt

HEADERS += \
    ../graph.h \
    ../getpart.h \
    ../dfs.h

