datalogger: main.o command.o settings.o serial.o data.o
	gcc -o datalogger main.o command.o settings.o serial.o data.o
main.o: main.c command.h settings.h serial.h data.h global.h
	gcc -c main.c
command.o: command.c command.h settings.h global.h
	gcc -c command.c
settings.o: settings.c settings.h global.h
	gcc -c settings.c
serial.o: serial.c serial.h settings.h global.h
	gcc -c serial.c
data.o: data.c data.h settings.h global.h
	gcc -c data.c
