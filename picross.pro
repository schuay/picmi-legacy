# -------------------------------------------------
# Project created by QtCreator 2010-03-01T00:05:51
# -------------------------------------------------
QT -= core \
    gui
TARGET = picross
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += src/f_main.cpp \
    src/f_sdlfrontend.cpp \
    src/b_picross.cpp \
    src/b_picexception.cpp \
    src/b_picpoint.cpp \
    src/f_sdlsprite.cpp \
    src/f_sdltext.cpp \
    src/b_picstreak.cpp \
    src/b_picsettings.cpp
HEADERS += src/f_sdlfrontend.h \
    src/b_picross.h \
    src/b_picexception.h \
    src/b_picpoint.h \
    src/f_sdlsprite.h \
    src/f_sdltext.h \
    src/f_sdlglobals.h \
    src/b_picstreak.h \
    src/b_picsettings.h \
    src/b_picdefines.h
unix:LIBS += -lSDL \
    -lSDL_image \
    -lSDL_mixer \
    -lSDL_gfx \
    -lSDL_ttf
OTHER_FILES += src/makefile
