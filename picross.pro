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
    GB_System.cpp \
    Game.cpp \
    Puzzle.cpp \
    PicrossException.cpp \
    Point.cpp \
    Sprite.cpp \
    Text.cpp
HEADERS += GB_VideoSystem.h \
    GB_Definitions.h \
    GB_System.h \
    GB_Globals.h \
    Game.h \
    GameBlade.h \
    Puzzle.h \
    PicrossException.h \
    Point.h \
    Sprite.h \
    Text.h
unix:LIBS += -lSDL \
    -lSDL_image \
    -lSDL_mixer \
    -lSDL_gfx \
    -lSDL_ttf
