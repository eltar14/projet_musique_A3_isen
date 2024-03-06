/**
 * @authors Antoine LE BOULCH / Julia AZEAU CIR3 Caen
 */

#ifndef AUDISEN2024_AMP_H
#define AUDISEN2024_AMP_H

#include "define.h"


FILE* initAMP(char* filename);

void readAMP(FILE* pf, char * song_filename);

void str_to_lower(char* ma_string);

void delete_special_chars(char *titre);
void delete_special_chars_2(char* title);

void closeAMP(FILE* pf);

void refactor_multiple_underscores(char *str);

void getAMP(char* filename, char* dest_str);

#endif //AUDISEN2024_AMP_H