datalogger: main.o command.o settings.o sdi12.o data.o
	gcc -o datalogger main.o command.o settings.o sdi12.o data.o
main.o: main.c global.h command.h settings.h sdi12.h data.h
	gcc -c main.c
command.o: command.c global.h command.h
	gcc -c command.c
settings.o: settings.c global.h settings.h
	gcc -c settings.c
sdi12.o: sdi12.c global.h sdi12.h
	gcc -c sdi12.c
data.o: data.c global.h data.h
	gcc -c data.c
