project: datalogger sdi-12
datalogger: main.o command.o settings.o
	gcc -o datalogger main.o command.o settings.o
main.o: main.c
	gcc -c main.c
command.o: command.c
	gcc -c command.c
settings.o: settings.c
	gcc -c settings.c
sdi-12: sdi-12.o
	gcc -o sdi-12 sdi-12.o
sdi-12.o: sdi-12.c
	gcc -c sdi-12.c
