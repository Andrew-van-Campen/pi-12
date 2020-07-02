pi-12: main.o command.o settings.o serial.o data.o process.o
	gcc -o pi-12 main.o command.o settings.o serial.o data.o process.o
main.o: main.c global.h command.h settings.h serial.h data.h
	gcc -c main.c
command.o: command.c global.h command.h
	gcc -c command.c
settings.o: settings.c global.h settings.h
	gcc -c settings.c
serial.o: serial.c global.h serial.h
	gcc -c serial.c
data.o: data.c global.h data.h
	gcc -c data.c
process.o: process.c global.h process.h
	gcc -c process.c
