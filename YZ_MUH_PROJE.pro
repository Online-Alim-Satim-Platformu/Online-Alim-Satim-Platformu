QT += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    anasayfa.cpp \
    databasemanager.cpp \
    girisekrani.cpp \
    ilanekle.cpp \
    kayitekrani.cpp \
    main.cpp \
    profil.cpp \
    session.cpp

HEADERS += \
    anasayfa.h \
    databasemanager.h \
    girisekrani.h \
    ilanekle.h \
    kayitekrani.h \
    profil.h \
    session.h

FORMS += \
    anasayfa.ui \
    girisekrani.ui \
    ilanekle.ui \
    kayitekrani.ui \
    profil.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
