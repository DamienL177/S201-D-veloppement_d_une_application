QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chifoumi.cpp \
    database.cpp \
    identification.cpp \
    main.cpp \
    chifoumivue.cpp \
    parametre.cpp \
    presentation.cpp

HEADERS += \
    chifoumi.h \
    chifoumivue.h \
    database.h \
    identification.h \
    parametre.h \
    presentation.h

FORMS += \
    chifoumivue.ui \
    identification.ui \
    parametre.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
