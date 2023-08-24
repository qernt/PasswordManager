QT       += core gui
QT += sql

QT += network

LIBS += -L/opt/homebrew/Cellar/openssl@3/3.1.2/lib -lssl -lcrypto

INCLUDEPATH += /opt/homebrew/Cellar/openssl@3/3.1.2/include

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    authdialog.cpp \
    errordialog.cpp \
    main.cpp \
    mainwindow.cpp \
    passwordfield.cpp \
    registrationdialog.cpp

HEADERS += \
    authdialog.h \
    errordialog.h \
    mainwindow.h \
    passwordfield.h \
    registrationdialog.h

FORMS += \
    authdialog.ui \
    errordialog.ui \
    mainwindow.ui \
    passwordfield.ui \
    registrationdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
