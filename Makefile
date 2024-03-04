#MakeFile squelette à modifier par les étudiants
# Nom Prenom Nom Prenom Groupe Ville

#TARGET = audisen_usb.exe # pour la partie USB
TARGET = audisen_sim.out


all: $(TARGET)

run: all
	@./$(TARGET)

#Etudiants : creez les cibles de votre makefile ICI, et completez
audisen_sim.o: audisen_sim.c
	gcc -c audisen_sim.c

amp.o: amp.c
	gcc -c amp.c

ams.o: ams.c
	gcc -c ams.c

#audisen_usb.o: audidsen_usb.c
#	gcc -c audisen_usb.c

frame.o: frame.c
	gcc -c frame.c

#usb.o: usb.c
#	gcc -c usb.c



audisen_sim.out: audisen_sim.o amp.o ams.o frame.o # audisen_usb.o usb.o
	gcc -Wall audisen_sim.o amp.o ams.o frame.o -o audisen_sim.out # ne pas oublier les USB



#CIBLE a garder pour la partie USB
# Commande de compilation pour Windows mingw a copier en console PowerShell
#  mingw32-make -f Makefile clear test_usb.exe
#audisen_usb.exe : audisen_usb.c ftd2xx.h ftd2xx.lib
#	gcc audisen_usb.c ftd2xx.lib -o audisen_usb.exe

clean:
	rm *.o *.out *.exe

clear:
	del *.o *.exe


