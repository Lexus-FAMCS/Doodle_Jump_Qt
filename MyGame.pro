QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    abstractcontroller.cpp \
    bullet.cpp \
    characterchoice.cpp \
    creature.cpp \
    customscene.cpp \
    enemy.cpp \
    main.cpp \
    controller.cpp \
    menu_ufo.cpp \
    model.cpp \
    painter.cpp \
    platform.cpp \
    player.cpp \
    ufo.cpp \
    updater.cpp \
    view.cpp

HEADERS += \
    abstractcontroller.h \
    bullet.h \
    characterchoice.h \
    controller.h \
    creature.h \
    customscene.h \
    enemy.h \
    menu_ufo.h \
    model.h \
    painter.h \
    platform.h \
    player.h \
    ufo.h \
    updater.h \
    view.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
