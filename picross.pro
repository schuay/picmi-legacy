# -------------------------------------------------
# Project created by QtCreator 2010-03-01T00:05:51
# -------------------------------------------------
TARGET = tuxpicross
TEMPLATE = app
SOURCES += src/f_main.cpp \
    src/b_picross.cpp \
    src/b_picstreak.cpp \
    src/b_picpngloader.cpp \
    src/f_qtmainwindow.cpp \
    src/f_qtpicthread.cpp \
    src/b_boardgame.cpp \
    src/b_picpainter.cpp \
    src/b_sdltext.cpp \
    src/b_sdlsprite.cpp \
    src/b_picinputhandler.cpp \
    src/b_gamemanager.cpp \
    src/b_sweeper.cpp \
    src/b_boardsettings.cpp \
    src/b_timer.cpp \
    src/b_point.cpp \
    src/b_exception.cpp \
    src/b_sweeppainter.cpp \
    src/b_painter.cpp \
    src/b_sweepinputhandler.cpp \
    src/f_qtsettings.cpp
HEADERS += src/b_picross.h \
    src/b_picstreak.h \
    src/b_picdefines.h \
    src/b_picpngloader.h \
    src/f_qtmainwindow.h \
    src/f_qtpicthread.h \
    src/b_boardgame.h \
    src/b_painter.h \
    src/b_picpainter.h \
    src/b_sdlsprite.h \
    src/b_sdltext.h \
    src/b_inputhandler.h \
    src/b_picinputhandler.h \
    src/b_gamemanager.h \
    src/b_sweeper.h \
    src/b_sweepdefines.h \
    src/b_boardsettings.h \
    src/b_timer.h \
    src/b_point.h \
    src/b_exception.h \
    src/b_sweeppainter.h \
    src/b_sweepinputhandler.h \
    src/f_qtsettings.h
unix:INCLUDEPATH += /usr/include/ImageMagick
unix:LIBS += -lSDL \
    -lSDL_image \
    -lSDL_gfx \
    -lSDL_ttf \
    -lMagick++ \
    -lpng
OTHER_FILES += src/makefile \
    README \
    PKGBUILD \
    AUTHORS \
    INSTALL \
    COPYING
FORMS += src/f_qtmainwindow.ui \
    src/f_qtsettings.ui
