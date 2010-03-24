CC=g++
SOURCES       = src/f_main.cpp \
                src/b_picross.cpp \
                src/b_picstreak.cpp \
                src/b_picpngloader.cpp \
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
                src/b_sweepinputhandler.cpp
OBJECTS       = src/f_main.o \
                src/b_picross.o \
                src/b_picstreak.o \
                src/b_picpngloader.o \
                src/b_boardgame.o \
                src/b_picpainter.o \
                src/b_sdltext.o \
                src/b_sdlsprite.o \
                src/b_picinputhandler.o \
                src/b_gamemanager.o \
                src/b_sweeper.o \
                src/b_boardsettings.o \
                src/b_timer.o \
                src/b_point.o \
                src/b_exception.o \
                src/b_sweeppainter.o \
                src/b_painter.o \
                src/b_sweepinputhandler.o
LIBS= -lSDL -lSDL_image -lSDL_gfx -lSDL_ttf -lMagick++ -lpng -lpthread
INCLUDEDIRS= -I/usr/include/ImageMagick -I/usr/include/SDL
EXECUTABLE= tuxpicross
DESTDIR= /
 
all:
	sed -i 's_#define QTENABLED__' f_main.cpp
	sed -i \
		"s_#define FILEPREFIX.*_#define FILEPREFIX \"/usr/share/tuxpicross/\"_" \
                b_picpainter.h
	$(CC) -c $(INCLUDEDIRS) $(SOURCES)
	$(CC) $(LIBS) $(OBJECTS) -o $(EXECUTABLE)
 
clean:
	rm -f $(OBJECTS)
 
install:
	mkdir -p ${DESTDIR}/usr/{bin,share/{applications,${EXECUTABLE}/gfx}}
	install -D -m755 ${EXECUTABLE} ${DESTDIR}/usr/bin/
	install -D -m644 tuxpicross.desktop ${DESTDIR}/usr/share/applications/tuxpicross.desktop
	install -D -m644 \
		../gfx/*  \
		${DESTDIR}/usr/share/${EXECUTABLE}/gfx/
