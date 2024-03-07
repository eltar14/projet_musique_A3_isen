/**
 * @authors Antoine LE BOULCH / Julia AZEAU CIR3 Caen
 */

#include <stdio.h>
#include "autotests.h"
#include "amp.h"
#include "ams.h"
#include "frame.h"




void playlist_to_frm(char* src_filename, char* dest_filename){
    FILE* pf;
    pf = initAMP(src_filename); // src = amp  playlist file
    char song_filename[MAX_SIZE_TITLE];
    char frame[INIT_FRAME_MAX_SIZE];

    char title2[MAX_SIZE_TITLE];
    FILE* pf_dest = fopen(dest_filename, "w");
    while (!feof(pf)){
        readAMP(pf, song_filename);
        //sprintf(dest_str,"%s", song_filename);

        // creation du struct
        s_song song_struct = readAMS(song_filename);

        // creation des trames
        if (strlen(song_struct.title) > 0){
            song_struct.title[strlen(song_struct.title)-1]='\0';
            createInitFrame(song_struct, frame);

            fprintf(pf_dest, "%s", frame);
        }

        for (int i = 0; i < song_struct.nTicks; ++i) {
            createTickFrame(song_struct.tickTab[i], frame);
            fprintf(pf_dest, "%s", frame);
        }
    }
    fclose(pf_dest);
    closeAMP(pf);
}

int main(){
    printf("Demarrage du projet AUDISEN\n");

    /*
    testFrame(); // 100%
    testReadAMP(); // 100%
    testReadAMS(); // 100%
    testCreateAMS(); // 100%
    */

    //char strr[999] = "";
    //getAMP("Playlist.amp", strr);
    //printf("%s\n", strr);

    //playlist_to_frm("Playlist.amp", "test1.frm");

    createAMS("cantina.txt", "cantina.ams");
    createAMS("kerosene.txt", "kerosene.ams");
    playlist_to_frm("pl2.amp", "test2.frm");


    return 0;
}