datalogger: main.o settings.o sdi-12
	gcc -o datalogger main.o settings.o
main.o: main.c
	gcc -c main.c
settings.o: settings.c
	gcc -c settings.c
sdi-12: sdi-12.c
	gcc -o sdi-12 sdi-12.c
