TEMPLATE = app

QT += core gui widgets concurrent

CONFIG += c++17

SOURCES += \
    factorialprovider.cpp \
    main.cpp \
    mainwidget.cpp \
    primenumberprovider.cpp

HEADERS += \
    biginteger.h \
    factorialprovider.h \
    integersequence.h \
    mainwidget.h \
    primenumberprovider.h \
    valueprovider.h
