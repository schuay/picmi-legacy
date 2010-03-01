# -------------------------------------------------
# Project created by QtCreator 2010-03-01T00:05:51
# -------------------------------------------------
QT -= core \
    gui
TARGET = picross
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += SDL_rotozoom.cpp \
    main.cpp \
    GB_VideoSystem.cpp \
    GB_TextEngine.cpp \
    GB_System.cpp \
    GB_Sprites.cpp \
    GB_Events.cpp \
    GB_Backgrounds.cpp \
    GB_AudioSystem.cpp \
    Game.cpp \
    Puzzle.cpp
HEADERS += SDL_rotozoom.h \
    GB_VideoSystem.h \
    GB_TextEngine.h \
    GB_Definitions.h \
    GB_Backgrounds.h \
    GB_AudioSystem.h \
    GB_System.h \
    GB_Sprites.h \
    GB_Globals.h \
    GB_Events.h \
    Game.h \
    GameBlade.h \
    Puzzle.h
unix:LIBS += -lSDL \
    -lSDL_image \
    -lSDL_mixer
