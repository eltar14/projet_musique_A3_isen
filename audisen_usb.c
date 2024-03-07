/**
 * @authors Antoine LE BOULCH / Julia AZEAU CIR3 Caen
 */
#define _WIN32
#include <stdio.h>
#include "amp.h"
#include "ams.h"
#include "frame.h"
#include "usb.h"
#include "ftd2xx.h"


void playlist_to_card(char* src_filename, FT_HANDLE ftHandle){
    FILE* pf;
        pf = initAMP(src_filename); // src = amp  playlist file
        char song_filename[MAX_SIZE_TITLE];
        char frame[INIT_FRAME_MAX_SIZE];

        char title2[MAX_SIZE_TITLE];

        while (!feof(pf)){
            readAMP(pf, song_filename);
            //sprintf(dest_str,"%s", song_filename);

            // creation du struct
            s_song song_struct = readAMS(song_filename);

            // creation des trames
            if (strlen(song_struct.title) > 0){
                song_struct.title[strlen(song_struct.title)-1]='\0';
                createInitFrame(song_struct, frame);
                // ENVOI TRAME INIT
                writeUSB(frame, ftHandle);
            }

            for (int i = 0; i < song_struct.nTicks; ++i) {
                createTickFrame(song_struct.tickTab[i], frame);
                // ENVOI TRAMES MUSIQUE
                writeUSB(frame, ftHandle);
            }
        }
        closeAMP(pf);

}


int main(){
    printf("Demarrage du projet AUDISEN USB\n");
    FT_HANDLE ftHandle;
    FT_STATUS ftStatus;
    ftHandle = initUSB();
    //playlist_to_card("Playlist.amp", ftHandle);
    //closeUSB(ftHandle);




    /*
    ftStatus = FT_Open(0, &ftHandle);

    if (ftStatus == FT_OK) {
        fprintf(stderr, "open USB ok\n");
    }else{
        fprintf(stderr, "open USB error\n");
    }
    */
    return 0;
}