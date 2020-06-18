include(gtest_dependency.pri)

INCLUDEPATH += ../project
TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

HEADERS += \
        ../project/IKeypad.h \
        ../project/ILatch.h \
        ../project/lockcontroller.h \
        tst_sometest.h

SOURCES += \
        ../project/lockcontroller.cpp \
        main.cpp
