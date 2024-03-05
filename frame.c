/**
 * @authors Antoine LE BOULCH / Julia AZEAU CIR3 Caen
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "frame.h"
#include "define.h"


/**
 *
 * @param mySong
 * @param frame
 */
void createInitFrame(s_song mySong, char* frame){
    char init_frame[99] = ""; // Initialisation avec une chaîne vide

    strncat(init_frame, "#", sizeof(init_frame) - strlen(init_frame) - 1); // Utilisation de strncat avec une taille maximale
    //printf("init_frame after adding #: %s\n", init_frame); //debug


    strncat(init_frame, mySong.title, sizeof(init_frame) - strlen(init_frame) - 1);
    //printf("init_frame after titke : %s\n", init_frame); // debug

    strncat(init_frame, ",", sizeof(init_frame) - strlen(init_frame) - 1);
    //printf("init_frame after adding virgule : %s\n", init_frame); // debug

    char buffer[8];
    sprintf(buffer, "%d,", mySong.tpm);
    strncat(init_frame, buffer, sizeof(init_frame) - strlen(init_frame) - 1);
    //printf("init_frame after adding tpm et virgule : %s\n", init_frame); // debug

    char buffer2[8];
    sprintf(buffer2, "%d*", mySong.nTicks);
    strncat(init_frame, buffer2, sizeof(init_frame) - strlen(init_frame) - 1);
    //printf("init_frame after adding nTicks et etoile : %s\n", init_frame); // debug

    // checksum
    int sum = 0;
    for (int i = 1; i < strlen(init_frame)-1; ++i) { // on ignore le # et le *
        //printf("cs : %c\n", init_frame[i]); // debug
        sum ^= init_frame[i];
    }
    //printf("CheckSum : %d\n", sum);

    char buffer3[8];
    sprintf(buffer3, "%02x\r\n\0", sum); // en hexa + ><CR><LF>\0
    strncat(init_frame, buffer3, sizeof(init_frame) - strlen(init_frame) - 1);
    //printf("init_frame after adding checksum : %s\n", init_frame); // debug

    strcpy(frame, init_frame);
}

void createTickFrame(s_tick myTick, char* frame){
    sprintf(frame, "#0,%d,%02d,%02d,%02d,%02d*", myTick.accent, myTick.note[0],myTick.note[1],myTick.note[2],myTick.note[3]);
    //checksum:
    int sum = 0;
    for (int i = 1; i < strlen(frame)-1; ++i) {
        sum ^= frame[i];
    }
    sprintf(frame, "%s%02x\r\n\0", frame, sum);// 2e moitie
}
