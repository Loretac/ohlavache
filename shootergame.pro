#-------------------------------------------------
#
# Project created by QtCreator 2018-03-21T17:35:15
#
#-------------------------------------------------

QT       += core gui \
            multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = shootergame
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


SOURCES += \
        main.cpp \
    game.cpp \
    score.cpp \
    player.cpp \
    button.cpp \
    levels.cpp \
    target.cpp \
    enemy.cpp \
    foe1.cpp \
    boss1.cpp \
    foe2.cpp \
    enemybullet.cpp \
    bulletsimple.cpp \
    playerbullet.cpp \
    bulletdirected.cpp \
    boss2.cpp \
    bullettargetedlarge.cpp \
    foe3.cpp \
    bullettargetedsmall.cpp \
    boss3.cpp \
    bulletminelarge.cpp \
    foe4.cpp \
    bulletminesmall.cpp \
    boss4left.cpp \
    laser.cpp

HEADERS += \
    game.h \
    score.h \
    player.h \
    button.h \
    levels.h \
    target.h \
    enemy.h \
    foe1.h \
    boss1.h \
    foe2.h \
    enemybullet.h \
    bulletsimple.h \
    playerbullet.h \
    bulletdirected.h \
    boss2.h \
    bullettargetedlarge.h \
    foe3.h \
    bullettargetedsmall.h \
    boss3.h \
    bulletminelarge.h \
    foe4.h \
    bulletminesmall.h \
    boss4left.h \
    laser.h

FORMS += \
        mainwindow.ui

RESOURCES += \
    res.qrc
