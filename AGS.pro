QT =
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

LIBS += -lncurses

SOURCES += main.cpp \
    ags.cpp \
    individual.cpp \
    population.cpp \
    tester.cpp

HEADERS += \
    ags.h \
    individual.h \
    parameters.h \
    population.h \
    tester.h
