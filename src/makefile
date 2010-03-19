CC=g++
SOURCES       = f_main.cpp f_sdlfrontend.cpp b_picross.cpp b_picexception.cpp \
                b_picpoint.cpp f_sdlsprite.cpp f_sdltext.cpp b_picstreak.cpp \
                b_picsettings.cpp b_picpngloader.cpp b_pictimer.cpp
OBJECTS       = f_main.o f_sdlfrontend.o b_picross.o b_picexception.o \
                b_picpoint.o f_sdlsprite.o f_sdltext.o b_picstreak.o \
                b_picsettings.o b_picpngloader.o b_pictimer.o
LIBS= -lSDL -lSDL_image -lSDL_gfx -lSDL_ttf -lMagick++ -lpng -lpthread
INCLUDEDIRS= -I/usr/include/ImageMagick -I/usr/include/SDL
EXECUTABLE= tuxpicross
DESTDIR= /
 
all:
	sed -i 's_#define QTENABLED__' f_main.cpp
	sed -i \
		"s_#define FILEPREFIX.*_#define FILEPREFIX \"/usr/share/tuxpicross/\"_" \
		f_sdldefines.h
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
