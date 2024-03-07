/**
* @authors Nom Prenom Nom Prenom Groupe Ville
*/

#ifndef AUDISEN2024_AMS_H
#define AUDISEN2024_AMS_H

#include "define.h"

struct song initSong();
struct song readAMS(char* fileName);

void createAMS(char* txtFileName, char* amsFileName);
FILE* initTXT(char* filename);
FILE* initAMS_write(char* filename);
void delete_space(char *str);
int note_position(int numNote, char* str, int* nbr_ticks);
void closeFile(FILE* pf);
int afficher_note_x(int note_precedente, int position_note, int* nbr_ticks, int memoire_position_ligne, FILE* fichierAMS);

FILE* initAMS(char* filename);
void print_s_tick(s_tick tick);
void print_s_song(s_song song);


#endif //AUDISEN2024