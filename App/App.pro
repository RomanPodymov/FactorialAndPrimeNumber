TEMPLATE = app

QT += core gui widgets concurrent

CONFIG += c++17

SOURCES += \
    factorialprovider.cpp \
    factorialproviderwidget.cpp \
    main.cpp \
    mainwidget.cpp \
    primenumberprovider.cpp \
    primenumberproviderwidget.cpp

HEADERS += \
    biginteger.h \
    factorialprovider.h \
    factorialproviderwidget.h \
    integersequence.h \
    mainwidget.h \
    primenumberprovider.h \
    primenumberproviderwidget.h \
    valueprovider.h \
    valueproviderwidget.h
