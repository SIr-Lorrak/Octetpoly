CC = g++
debug = -g -Wall
exe = bin/Octetpoly
main = src/main.cpp
objs = obj/main.o obj/core/Pion.o obj/core/Joueur.o obj/core/Ordi.o obj/core/Case.o obj/core/Jeu.o obj/core/Plateau.o obj/core/Evenement.o obj/TXT/jeuTXT.o

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
	$(test) obj $(pipe) mkdir obj
	$(test) bin $(pipe) mkdir bin
	$(test) obj/core $(pipe) mkdir obj/core
	$(test) obj/TXT $(pipe) mkdir obj/TXT

bin/Octetpoly: $(objs)
	$(CC) -o $(exe) $(objs) $(debug)

obj/%.o: src/%.cpp
	$(CC) -o $@ -c $< $(debug)

clean:
	$(rm) -r obj/;echo ok

superclean:
	$(rm) -r obj/ bin/