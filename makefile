project: datalogger sdi-12
datalogger: main.o settings.o
	gcc -o datalogger main.o settings.o
main.o: main.c
	gcc -c main.c
settings.o: settings.c
	gcc -c settings.c
sdi-12: sdi-12.o
	gcc -o sdi-12 sdi-12.o
sdi-12.o: sdi-12.c
	gcc -c sdi-12.c
