# -------------------------------------------------
# Project created by QtCreator 2010-03-01T00:05:51
# -------------------------------------------------
QT -= core \
    gui
TARGET = picross
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += main.cpp \
    GB_VideoSystem.cpp \
    GB_TextEngine.cpp \
    GB_System.cpp \
    GB_Sprites.cpp \
    GB_Backgrounds.cpp \
    GB_AudioSystem.cpp \
    Game.cpp \
    Puzzle.cpp \
    PicrossException.cpp
HEADERS += GB_VideoSystem.h \
    GB_TextEngine.h \
    GB_Definitions.h \
    GB_Backgrounds.h \
    GB_AudioSystem.h \
    GB_System.h \
    GB_Sprites.h \
    GB_Globals.h \
    Game.h \
    GameBlade.h \
    Puzzle.h \
    PicrossException.h
unix:LIBS += -lSDL \
    -lSDL_image \
    -lSDL_mixer \
    -lSDL_gfx
