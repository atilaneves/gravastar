OBJS = $(patsubst %.cpp, %.o, $(wildcard src/*.cpp))
APIOBJS = $(patsubst %.cpp, %.o, $(wildcard src/AllegroAPI/*.cpp))
MENUOBJS = $(patsubst %.cpp, %.o, $(wildcard src/menu/*.cpp))
SHIPSOBJS  = $(patsubst %.cpp, %.o, $(wildcard src/ships/*.cpp))
AIOBJS  = $(patsubst %.cpp, %.o, $(wildcard src/ai/*.cpp))
POWERUPSOBJS  = $(patsubst %.cpp, %.o, $(wildcard src/powerups/*.cpp))
MP3OBJS = $(patsubst %.c, %.o, $(wildcard src/AllegroMP3/*.c))
ALLOBJS = $(OBJS) $(APIOBJS) $(MENUOBJS)  $(SHIPSOBJS) $(AIOBJS) $(POWERUPSOBJS)
HDRS = $(wildcard src/*.hpp)
APIHDRS = $(wildcard src/AllegroAPI/*.hpp)
MENUHDRS = $(wildcard src/menu/*.hpp)
POWERUPSHDRS = $(wildcard src/powerups/*.hpp)
SHIPSHDRS = $(wildcard src/ships/*.hpp)
AIHDRS = $(wildcard src/ai/*.hpp)
MP3HDRS = $(wildcard src/AllegroMP3/*.hpp)
CPPS = $(wildcard src/*.cpp)
#CPPFLAGS += -Wall -g -pg -fno-inline
CPPFLAGS += -Wall
CPPFLAGS += -Isrc -Isrc/menu -Isrc/ships -Isrc/AllegroAPI -Isrc/AllegroMP3
CPPFLAGS += -Isrc/ai -Isrc/powerups
EXE = gravastar
ALLEGROLIB = `allegro-config --libs`
#LFLAGS = $(ALLEGROLIB) -pg 
LFLAGS =  $(ALLEGROLIB)
MP3LIB = lib/libalmp3.a

all: $(EXE)
$(EXE): $(ALLOBJS) $(MP3LIB)
	g++ $(ALLOBJS)  $(MP3LIB) -o $(EXE) $(LFLAGS)
$(OBJS): $(APIHDRS) $(HDRS)
$(APIOBJS): $(APIHDRS) $(HDRS)
$(MENUOBJS): $(APIHDRS) $(HDRS) $(MENUHDRS)
$(POWERUPSOBJS): $(APIHDRS) $(HDRS) $(POWERUPSHDRS)
$(SHIPSOBJS): $(APIHDRS) $(HDRS) $(SHIPSHDRS)
$(AIOBJS): $(APIHDRS) $(HDRS) $(AIHDRS)
$(MP3OBJS): $(MP3HDRS)
$(MP3LIB): $(MP3OBJS)
	ar rs $(MP3LIB) $(MP3OBJS)


.PHONY: clean
clean:
	-rm -f $(ALLOBJS) $(EXE) lib/* $(MP3OBJS)
