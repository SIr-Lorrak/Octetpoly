CC = g++
debug = -g -Wall
exe = bin/Octetpoly
main = src/main.cpp
objs = obj/main.o

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

$(exe): $(main) $(objs)
	$(CC) -o $(exe) $(main) $(debug)

obj/main.o: $(main)
	$(CC) -o obj/main.o -c $(main) $(debug)

clean:
	$(rm) $(objs)