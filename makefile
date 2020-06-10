datalogger: main.o command.o settings.o sdi-12.o data.o
	gcc -o datalogger main.o command.o settings.o sdi-12.o data.o
main.o: main.c global.h command.h settings.h sdi-12.h data.h
	gcc -c main.c
command.o: command.c global.h command.h
	gcc -c command.c
settings.o: settings.c global.h settings.h
	gcc -c settings.c
sdi-12.o: sdi-12.c global.h sdi-12.h
	gcc -c sdi-12.c
data.o: data.c global.h data.h
	gcc -c data.c
