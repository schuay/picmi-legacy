CC=g++
SOURCES       = f_main.cpp f_sdlfrontend.cpp b_picross.cpp b_picexception.cpp \
                b_picpoint.cpp f_sdlsprite.cpp f_sdltext.cpp b_picstreak.cpp \
                b_picsettings.cpp b_picpngloader.cpp
OBJECTS       = f_main.o f_sdlfrontend.o b_picross.o b_picexception.o \
                b_picpoint.o f_sdlsprite.o f_sdltext.o b_picstreak.o \
                b_picsettings.o b_picpngloader.o
LIBS= -lSDL -lSDL_image -lSDL_gfx -lSDL_ttf -lMagick++ \
    -lMagickWand -lMagickCore -llcms -ltiff -lfreetype -ljasper \
    -ljpeg -lgs -lpng -lfontconfig -lwmflite -lXext -lXt -lSM \
    -lICE -lX11 -lbz2 -pthread -lIlmImf -lz -lImath -lHalf -lIex \
    -lIlmThread -lrsvg-2 -lgdk_pixbuf-2.0 -lcairo -lgobject-2.0 \
    -lgmodule-2.0 -lglib-2.0 -lxml2 -lz -lm -lgomp -lpthread -lltdl
EXECUTABLE= tuxpicross
DESTDIR= /
 
all:
	sed -i \
		"s_#define FILEPREFIX.*_#define FILEPREFIX \"/usr/share/tuxpicross/\"_" \
		f_sdldefines.h
	$(CC) -c `sdl-config --cflags` $(SOURCES)
	$(CC) `sdl-config --libs` $(LIBS) $(OBJECTS) -o $(EXECUTABLE)
 
clean:
	rm -f $(OBJECTS)
 
install:
	mkdir -p ${DESTDIR}/usr/{bin,share/{applications,${EXECUTABLE}/gfx}}
	install -D -m755 ${EXECUTABLE} ${DESTDIR}/usr/bin/
	install -D -m644 tuxpicross.desktop ${DESTDIR}/usr/share/applications/tuxpicross.desktop
	install -D -m644 \
		../gfx/*  \
		${DESTDIR}/usr/share/${EXECUTABLE}/gfx/
