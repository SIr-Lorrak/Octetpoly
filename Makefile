CC = g++
debug = -g -Wall

obj = obj
bin = bin

core = $(obj)/core/Pion.o $(obj)/core/Joueur.o $(obj)/core/Ordi.o $(obj)/core/Case.o $(obj)/core/Plateau.o $(obj)/core/Jeu.o

exe_Test = Octetpoly_Test
src_Test = $(core) $(obj)/mainTest.o

#exe_TXT = Octetpoly_TXT
#src_TXT = $(core) $(obj)/TXT/mainTXT.o $(obj)/TXT/JeuTXT.o

#exe_SDL = Octetpoly_SDL
#src_SDL = $(core) $(obj)/SDL/mainSDL.o $(obj)/SDL/JeuSDL.o

exe = $(bin)/$(exe_Test) #$(bin)/$(exe_TXT) #$(bin)/$(exe_SDL)


ifeq ($(OS),Windows_NT)
	test = if not exist
	pipe =  
	rm = del
else
	test = test -d
	pipe =||
	rm = rm
endif

ALL: mkdir $(exe)

mkdir:
	$(test) $(obj) $(pipe) mkdir $(obj) ; $(test) $(obj)/core $(pipe) mkdir $(obj)/core ; $(test) $(obj)/TXT $(pipe) mkdir $(obj)/TXT ;$(test) $(obj)/SDL $(pipe) mkdir $(obj)/SDL
	$(test) bin $(pipe) mkdir bin

#$(bin)/$(exe_SDL): $(src_SDL)
#	$(CC) $+ -o $@

#$(bin)/$(exe_TXT): $(src_TXT)
#	$(CC) $+ -o $@

$(bin)/$(exe_Test): $(src_Test)
	$(CC) $+ -o $@

$(obj)/%.o: src/%.cpp
	$(CC) -c $(debug) $< -o $@

clean:
	$(rm) -r obj/;echo ok