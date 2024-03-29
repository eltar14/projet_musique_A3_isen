#MakeFile squelette à modifier par les étudiants
# Antoine LE BOULCH / Julia AZEAU CIR3 Caen

#TARGET = audisen_usb.exe # pour la partie USB
TARGET = audisen_sim.out


all: $(TARGET)

run: all
	@./$(TARGET)

#Etudiants : creez les cibles de votre makefile ICI, et completez
audisen_sim.o: audisen_sim.c define.h
	gcc -Wall -c audisen_sim.c

amp.o: amp.c amp.h define.h
	gcc -Wall -c amp.c -o amp.o

ams.o: ams.c ams.h define.h
	gcc -Wall -c ams.c -o ams.o

#audisen_usb.o: audidsen_usb.c
#	gcc -c audisen_usb.c

frame.o: frame.c frame.h define.h
	gcc -Wall -c frame.c -o frame.o

usb.o: usb.c usb.h
	gcc -Wall -c usb.c -o usb.o

autotests.o: autotests.c autotests.h define.h
	gcc -Wall -c autotests.c -o autotests.o

audisen_sim.out: audisen_sim.o amp.o ams.o frame.o autotests.o # audisen_usb.o usb.o
	gcc -Wall audisen_sim.o amp.o ams.o frame.o autotests.o -o audisen_sim.out # ne pas oublier les USB



#CIBLE a garder pour la partie USB
# Commande de compilation pour Windows mingw a copier en console PowerShell
#  mingw32-make -f Makefile clear test_usb.exe
audisen_usb.exe : audisen_usb.c amp.o ams.o frame.o usb.o ftd2xx.h ftd2xx.lib
	gcc -Wall audisen_usb.c amp.o ams.o frame.o usb.o ftd2xx.lib -o audisen_usb.exe

clean:
	rm *.o *.out *.exe

clear:
	del *.o *.exe


