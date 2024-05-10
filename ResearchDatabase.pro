QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets sql

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    InsertResearchSourceForm.cpp \
    ResearchAPI/FileID.cpp \
    ResearchAPI/ResearchDB.cpp \
    ResearchAPI/ResearchID.cpp \
    filetools.cpp \
    main.cpp \
    mainwindow.cpp \
    researchitem.cpp

HEADERS += \
    InsertResearchSourceForm.h \
    ResearchAPI/FileID.h \
    ResearchAPI/ResearchDB.h \
    ResearchAPI/ResearchID.h \
    filetools.h \
    mainwindow.h \
    researchitem.h

FORMS += \
    InsertResearchSourceForm.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    sql.qrc
