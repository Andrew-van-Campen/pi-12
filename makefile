project: dl sdi-12
dl: main.o settings.o help.o
	gcc -o dl main.o settings.o
main.o: main.c
	gcc -c main.c
settings.o: settings.c
	gcc -c settings.c
help.o:
	gcc -c help.c
sdi-12: sdi-12.o
	gcc -o sdi-12 sdi-12.o
sdi-12.o: sdi-12.c
	gcc -c sdi-12.c
