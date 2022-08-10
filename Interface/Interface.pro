QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    button.cpp \
    main.cpp \
    mainwindow.cpp \
    receivedata.cpp \
    sendcommands.cpp \
    threadcontroller.cpp

HEADERS += \
    button.h \
    mainwindow.h \
    receivedata.h \
    sendcommands.h \
    socket_local.h \
    threadcontroller.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images/resources.qrc

DISTFILES += \
    images/light_history.png
