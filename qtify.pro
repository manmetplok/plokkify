# -------------------------------------------------
# Project created by QtCreator 2010-01-23T15:15:14
# -------------------------------------------------
TARGET = qtify
TEMPLATE = app

SOURCES += main.cpp \
    roundrectitem.cpp \
    flippablepad.cpp \
    padnavigator.cpp \
    mainwindow.cpp \
    spwrap.cpp \
    spcallback.cpp \
    spmain.cpp \
    spsession.cpp \
    sptoplist.cpp \
    spimage.cpp \
    queue.cpp \
    spsearch.cpp \
    audio.cpp \
    playback.cpp \
    mnenc.cpp \
    playlistcontainer.cpp \
    playlist.cpp
HEADERS += mainwindow.h \
    roundrectitem.h \
    flippablepad.h \
    padnavigator.h \
    spwrap.h \
    spcallback.h \
    spotify_cpp.h \
    spmain.h \
    spsession.h \
    sptoplist.h \
    spimage.h \
    queue.h \
    spsearch.h \
    audio.h \
    playback.h \
    mnenc.h \
    playlistcontainer.h \
    playlist.h
FORMS += mainwindow.ui

RESOURCES += resources.qrc
OTHER_FILES += asd.txt

LIBS += -lspotify \
    -lpulse \
    -lpulse-simple
