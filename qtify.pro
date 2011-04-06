# -------------------------------------------------
# Project created by QtCreator 2010-01-23T15:15:14
# -------------------------------------------------
TARGET = qtify
TEMPLATE = app

SOURCES += main.cpp \
    mainwindow.cpp \
    spwrap.cpp \
    spcallback.cpp \
    spmain.cpp \
    sprootlist.cpp \
    spsession.cpp \
    spplaylist.cpp \
    sptoplist.cpp \
    spimage.cpp \
    queue.cpp \
    spsearch.cpp \
    audio.cpp \
    playback.cpp \
    mnenc.cpp
HEADERS += mainwindow.h \
    spwrap.h \
    spcallback.h \
    spotify_cpp.h \
    spmain.h \
    sprootlist.h \
    spsession.h \
    spplaylist.h \
    sptoplist.h \
    spimage.h \
    queue.h \
    spsearch.h \
    audio.h \
    playback.h \
    mnenc.h
FORMS += mainwindow.ui

RESOURCES += resources.qrc
OTHER_FILES += asd.txt

LIBS += -lspotify \
    -lpulse \
    -lpulse-simple
