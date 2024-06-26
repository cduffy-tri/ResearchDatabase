QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets sql

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ResearchAPI/FileID.cpp \
    ResearchAPI/Keyword.cpp \
    ResearchAPI/ResearchDB.cpp \
    ResearchAPI/ResearchID.cpp \
    filetools.cpp \
    forms/InsertResearchSourceForm/GeneralPageForm.cpp \
    forms/InsertResearchSourceForm/InsertResearchSourceForm.cpp \
    forms/InsertResearchSourceForm/KeywordsPageForm.cpp \
    forms/InsertResearchSourceForm/SelectKeywordsDialog.cpp \
    forms/WordProcessorWidget.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ResearchAPI/FileID.h \
    ResearchAPI/Keyword.h \
    ResearchAPI/ResearchDB.h \
    ResearchAPI/ResearchID.h \
    filetools.h \
    forms/InsertResearchSourceForm/GeneralPageForm.h \
    forms/InsertResearchSourceForm/InsertResearchSourceForm.h \
    forms/InsertResearchSourceForm/KeywordsPageForm.h \
    forms/InsertResearchSourceForm/SelectKeywordsDialog.h \
    forms/WordProcessorWidget.h \
    mainwindow.h

FORMS += \
    forms/InsertResearchSourceForm/GeneralPageForm.ui \
    forms/InsertResearchSourceForm/InsertResearchSourceForm.ui \
    forms/InsertResearchSourceForm/KeywordsPageForm.ui \
    forms/InsertResearchSourceForm/SelectKeywordsDialog.ui \
    forms/WordProcessorWidget.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc \
    sql.qrc
