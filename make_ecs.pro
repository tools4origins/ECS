TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    world.cpp \
    entity.cpp

QMAKE_CXXFLAGS += -std=c++14

INCLUDEPATH+= include

HEADERS += \
    world.hpp \
    polymorphicvector.hpp \
    entity.hpp

