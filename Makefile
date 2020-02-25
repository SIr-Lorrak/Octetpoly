CC = g++
debug = -g -Wall
exe = bin/Octetpoly
main = src/main.cpp
objs = obj/main.o obj/Pion.o obj/Joueur.o obj/Ordi.o obj/Case.o obj/Plateau.o

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

bin/Octetpoly: src/main.cpp $(objs)
	$(CC) -o $(exe) $(main) $(debug)

obj/%.o: src/core/%.cpp
	$(CC) -o $@ -c $+ $(debug)

clean:
	$(rm) $(objs)

superclean:
	$(rm) -r obj/ bin/