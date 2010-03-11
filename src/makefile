CC=g++
SOURCES       = f_main.cpp f_sdlfrontend.cpp b_picross.cpp b_picexception.cpp \
                b_picpoint.cpp f_sdlsprite.cpp f_sdltext.cpp b_picstreak.cpp \
                b_picsettings.cpp
OBJECTS       = f_main.o f_sdlfrontend.o b_picross.o b_picexception.o \
                b_picpoint.o f_sdlsprite.o f_sdltext.o b_picstreak.o \
                b_picsettings.o
LIBS= -lSDL -lSDL_image -lSDL_gfx -lSDL_mixer -lSDL_ttf
EXECUTABLE= tuxpicross
 
all:
	$(CC) -c `sdl-config --cflags` $(SOURCES)
	$(CC) `sdl-config --libs` $(LIBS) $(OBJECTS) -o $(EXECUTABLE)
 
clean:
	rm -f $(OBJECTS)
 
uninstall:
	rm -f $(EXECUTABLE)
