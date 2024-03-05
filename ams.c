/**
 * @authors Antoine LE BOULCH / Julia AZEAU CIR3 Caen
 */

#include "define.h"
#include "ams.h"

/**
 *  readAMS() lit le fichier nommé fileName qui est de type .ams et renvoie une
 * structure de type s_song contenant tous les informations sur le morceau. Si le fichier ne peut être
 * ouvert la fonction doit renvoyer une structure contenant un titre vide (« ») et que des ‘0’ sur tous les
 * champs.
 * @param fileName
 * @return
 */
s_song readAMS(char* fileName){
    FILE* fichier = initAMS(fileName); // ouverture du fichier
    s_song mySong;

    // lit la premiere ligne = titre et l'enregistre dans la struct
    char str_buffer[40];
    if (fgets(str_buffer, sizeof(str_buffer), fichier) == NULL)
    {
        printf("Fail to read the input stream");
    }
    else
    {
        //find new line
        char *ptr = strchr(str_buffer, '\n');
        if (ptr)
        {
            *ptr  = '\0';   // on remplace le \n par une fin de str \0
        }
    }
    //printf("Entered Data = %s\n",str_buffer);
    strcpy(mySong.title, str_buffer);


    // lit la ligne suivante = tempo et l'enregistre dans la struct
    char str_buffer2[5];
    if (fgets(str_buffer2, sizeof(str_buffer2), fichier) == NULL)
    {
        printf("Fail to read the input stream");
    }
    else
    {
        //find new line
        char *ptr = strchr(str_buffer2, '\n'); // renvoie la premiere occurence
        if (ptr) // si occurrence :
        {
            *ptr  = '\0';   // on remplace le \n par une fin de str \0
        }
    }
    mySong.tpm = atoi(str_buffer2); // conversion en int puis enregistre

    printf("Titre : %s\n", mySong.title);
    printf("Tempo : %d\n", mySong.tpm);

    char l_temp[200]; // l max = 185 en pratique
    for (int i = 0; i < 2; ++i) {
        fgets(l_temp, 200, fichier);
    }
    char ligne[200];
    char ligne_sans_entete[200] = "";
    int compteur_ligne = 0;
    int num_note;
    int c;
    const char s[4] = "|";
    char* tok;
    int accentuation;

    while (fgets(ligne, 200, fichier)) // pour chaque tick
    {
        s_tick t;
        for (int i = 0; i < 4; ++i) {// de base toutes les notes sur muet
            t.note[i] = 0;
        }

        compteur_ligne ++; // = compteur de tick
        accentuation = 0;
        for (int i = 2; i < strlen(ligne); ++i) { // on commence apres le numero de ligne
            ligne_sans_entete[i-3] = ligne[i];
        }
        int place_note_dans_tick = 0;
        tok = strtok(ligne_sans_entete, s);
        num_note = 1;
        printf("Tick numero %d\n", compteur_ligne);

        while (tok != 0) {
            if(tok[0] != ' ' && tok[1] != '\n'){
                //printf("%c\n", tok[0]);
                if(tok[0] == '^'){
                    accentuation = 1;
                }
                t.note[place_note_dans_tick] = num_note; //TODO verifier si correct
                place_note_dans_tick ++;
                printf("note : %d %s\n", num_note, tok);
            }

            tok = strtok(0, s);
            num_note ++;
        }
        t.accent = accentuation; // temporaire pour tester TODO
        mySong.tickTab[compteur_ligne-1] = t; //TODO
        mySong.nTicks = compteur_ligne;
        printf("\n");

    }
    return mySong;
}


void createAMS(char* txtFileName, char* amsFileName){


}

FILE* initAMS(char* filename){
    FILE * pf = NULL;
    pf = fopen(filename, "r"); // Ouverture du fichier
    if (pf != NULL){
        printf("File %s opened successfully.\n", filename);
    }else{
        printf("Unable to open file %s .\n", filename);
        exit(1);
    }
    return pf;
}


void print_s_tick(s_tick tick){
    printf("%d, %d, %d, %d acc:%d\n", tick.note[0], tick.note[1], tick.note[2], tick.note[3], tick.accent);
}


void print_s_song(s_song song){
    printf("Titre : %s\n", song.title);
    printf("Tempo : %d\n", song.tpm);
    printf("Nombre de ticks : %d\n", song.nTicks);

    for (int i = 0; i < song.nTicks; ++i) {
        print_s_tick(song.tickTab[i]);
    }
}