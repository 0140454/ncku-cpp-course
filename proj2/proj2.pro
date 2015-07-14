TEMPLATE = app
TARGET = proj2

QT = core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

HEADERS += \
    src/Common.h \
    src/Human.h \
    src/MainWindow.h \
    src/MessagePanel.h \
    src/Paused.h \
    src/ScorePanel.h \
    src/ShaftGame.h \
    src/Spiked.h \
    src/Stair.h \
    src/StairLeft.h \
    src/StairNormal.h \
    src/StairOnetime.h \
    src/StairRight.h \
    src/Stairs.h \
    src/StairSpiked.h \
    src/StairSpring.h

SOURCES += \
    src/Human.cpp \
    src/main.cpp \
    src/MainWindow.cpp \
    src/MessagePanel.cpp \
    src/Paused.cpp \
    src/ScorePanel.cpp \
    src/ShaftGame.cpp \
    src/Spiked.cpp \
    src/Stair.cpp \
    src/StairLeft.cpp \
    src/StairNormal.cpp \
    src/StairOnetime.cpp \
    src/StairRight.cpp \
    src/Stairs.cpp \
    src/StairSpiked.cpp \
    src/StairSpring.cpp

RESOURCES = resources.qrc
