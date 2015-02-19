TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp \
    individual.cpp \
    population.cpp

HEADERS += \
    individual.h \
    parameters.h \
    population.h

