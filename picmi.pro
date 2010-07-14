# -------------------------------------------------
# Project created by QtCreator 2010-03-01T00:05:51
# -------------------------------------------------
TARGET = picmi
QT += xml
TEMPLATE = app

# DEFINES += SOLVERDEBUG
SOURCES += src/f_main.cpp \
    src/b_picross.cpp \
    src/b_picstreak.cpp \
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
    src/f_qtsettings.cpp \
    src/b_statsmanager.cpp \
    src/b_statselement.cpp \
    src/b_sweepstatselement.cpp \
    src/b_picstatselement.cpp \
    src/f_qthelp.cpp \
    src/b_sweepsolver.cpp \
    src/b_tetris.cpp \
    src/b_tetrispiece.cpp \
    src/b_tetrisinputhandler.cpp \
    src/b_tetrispainter.cpp \
    src/b_tetrisstatselement.cpp
HEADERS += src/b_picross.h \
    src/b_picstreak.h \
    src/b_picdefines.h \
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
    src/f_qtsettings.h \
    src/b_statsmanager.h \
    src/b_statselement.h \
    src/b_sweepstatselement.h \
    src/b_enums.h \
    src/b_picstatselement.h \
    src/b_statscollection.h \
    src/f_qthelp.h \
    src/b_sweepsolver.h \
    src/b_tetris.h \
    src/b_tetrisdefines.h \
    src/b_tetrispiece.h \
    src/b_tetrisinputhandler.h \
    src/b_tetrispainter.h \
    src/b_tetrisstatselement.h
unix:LIBS += -lSDL \
    -lSDL_image \
    -lSDL_gfx \
    -lSDL_ttf \
    -lboost_thread-mt
OTHER_FILES += README \
    PKGBUILD \
    AUTHORS \
    INSTALL \
    COPYING \
    src/picmi.desktop
FORMS += src/f_qtmainwindow.ui \
    src/f_qtsettings.ui \
    src/f_qthelp.ui
setpath.commands = $(SED) \
    -i \
    \'s_define \
    FILEPREFIX.*_define \
    FILEPREFIX \
    \"/usr/share/picmi/\"_\' \
    src/b_painter.h \
    || \
    return \
    1
QMAKE_EXTRA_TARGETS += setpath
gfx.path = /usr/share/picmi/gfx
gfx.files = gfx/*
desktop.path = /usr/share/applications
desktop.files = src/picmi.desktop
target.path = /usr/bin
INSTALLS += gfx \
    desktop \
    target
