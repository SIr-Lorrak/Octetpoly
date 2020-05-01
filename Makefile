CC = g++
debug = -g -Wall

obj = obj
bin = bin

core =  $(obj)/core/Case.o $(obj)/core/Joueur.o $(obj)/core/Ordi.o $(obj)/core/Plateau.o $(obj)/core/Jeu.o $(obj)/core/Evenement.o $(obj)/core/Pion.o $(obj)/core/Carte.o

exe_Test = Octetpoly_Test
src_Test = $(core) $(obj)/mainTest.o

exe_TXT = Octetpoly_TXT
src_TXT = $(core) $(obj)/TXT/JeuTXT.o $(obj)/TXT/mainTXT.o

exe_SDL = Octetpoly_SDL
src_SDL = $(core) $(obj)/SDL/JeuSDL.o $(obj)/SDL/mainSDL.o

exe = $(bin)/$(exe_Test) $(bin)/$(exe_TXT) $(bin)/$(exe_SDL)


ifeq ($(OS),Windows_NT)
	test = if not exist
	pipe =  
	rm = del

    INCLUDE_DIR_SDL =     -Iextern/SDL2_mingw/SDL2-2.0.3/include \
                        -Iextern/SDL2_mingw/SDL2_ttf-2.0.12/i686-w64-mingw32/include/SDL2 \
                        -Iextern/SDL2_mingw/SDL2_image-2.0.0/i686-w64-mingw32/include/SDL2 \
                        -Iextern/SDL2_mingw/SDL2_mixer-2.0.1/i686-w64-mingw32/include/SDL2

    LIBS_SDL = -Lextern \
            -Lextern/SDL2_mingw/SDL2-2.0.3/i686-w64-mingw32/lib \
            -Lextern/SDL2_mingw/SDL2_ttf-2.0.12/i686-w64-mingw32/lib \
            -Lextern/SDL2_mingw/SDL2_image-2.0.0/i686-w64-mingw32/lib \
            -Lextern/SDL2_mingw/SDL2_mixer-2.0.1/i686-w64-mingw32/lib \
            -lmingw32 -lSDL2main -lSDL2.dll -lSDL2_ttf.dll -lSDL2_image.dll -lSDL2_mixer.dll
else
	test = test -d
	pipe =||
	rm = rm

    INCLUDE_DIR_SDL = -I/usr/include/SDL2 -I/usr/local/include/SDL2
    LIBS_SDL = -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer
endif

INCLUDE_DIR			= -Isrc -Isrc/core -Isrc/SDL -Iobj -lpthread

ALL: mkdir $(exe)

mkdir:
	$(test) $(obj) $(pipe) mkdir $(obj) ; $(test) $(obj)/core $(pipe) mkdir $(obj)/core ; $(test) $(obj)/TXT $(pipe) mkdir $(obj)/TXT ;$(test) $(obj)/SDL $(pipe) mkdir $(obj)/SDL
	$(test) bin $(pipe) mkdir bin

$(bin)/$(exe_SDL): $(src_SDL) $(obj)/GetSet.o $(obj)/Touche.o $(obj)/Sauvegarde.o $(obj)/Action.o
	$(CC) $+ -o $@ $(LIBS_SDL)

$(bin)/$(exe_TXT): $(src_TXT) $(obj)/GetSet.o $(obj)/Touche.o $(obj)/Sauvegarde.o $(obj)/Action.o
	$(CC) $+ -o $@

$(bin)/$(exe_Test): $(src_Test) $(obj)/GetSet.o $(obj)/Touche.o $(obj)/Sauvegarde.o $(obj)/Action.o
	$(CC) $+ -o $@

$(obj)/GetSet.o: src/core/GetSet.cpp src/core/Jeu.h
	$(CC) -c $(debug) $(INCLUDE_DIR) $(INCLUDE_DIR_SDL) $< -o $@

$(obj)/Touche.o: src/core/Touche.cpp src/core/Jeu.h
	$(CC) -c $(debug) $(INCLUDE_DIR) $(INCLUDE_DIR_SDL) $< -o $@

$(obj)/Sauvegarde.o: src/core/Sauvegarde.cpp src/core/Jeu.h
	$(CC) -c $(debug) $(INCLUDE_DIR) $(INCLUDE_DIR_SDL) $< -o $@

$(obj)/Action.o: src/core/Action.cpp src/core/Jeu.h
	$(CC) -c $(debug) $(INCLUDE_DIR) $(INCLUDE_DIR_SDL) $< -o $@

$(obj)/%.o: src/%.cpp
	$(CC) -c $(debug) $(INCLUDE_DIR) $(INCLUDE_DIR_SDL) $< -o $@

clean:
	$(rm) -r obj/* data/sauvegarde/* bin/*;echo clean ok.