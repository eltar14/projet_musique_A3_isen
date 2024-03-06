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
    s_song mySong;
    FILE * fichier = NULL;
    fichier = fopen(fileName, "r"); // Ouverture du fichier
    if (fichier != NULL){
        printf("File %s opened successfully.\n", fileName);
        char temp[MAX_SIZE_TITLE]="";


        // lit la premiere ligne = titre et l'enregistre dans la struct
        char str_buffer[MAX_SIZE_TITLE];
        if (fgets(str_buffer, sizeof(str_buffer), fichier) == NULL)
        {
            printf("Fail to read the input stream");
        }
        else
        {
            str_buffer[strlen(str_buffer)-2]='\0';
            printf("titre str buffer : %s.\n", str_buffer);
            /*
            //find new line
            /*char *ptr;
            ptr = strchr(str_buffer, '\n');
            if (ptr){
                *ptr  = '\0';   // on remplace le \n par une fin de str \0
                //printf("on a NN\n");
                //printf("TITRE : %s.\n", str_buffer);
                //printf("len TITRE : %d.\n", strlen(temp));

            }
            char *ptr2;
            ptr2 = strchr(str_buffer, '\r');
            if(ptr2){
                //printf("on a ARRR\n");
                *ptr2  = '\0';   // on remplace le \r par une fin de str \0
                strncpy(temp, str_buffer, strlen(str_buffer));
            }
             */
        }
        //printf("Entered Data = %s\n",str_buffer);
        //sprintf(temp, "%s\0", temp);
        //temp[strlen(temp)-1]='\0';
        printf("LE TIIITRE : %s pas mal non ?\n", temp);
        printf("LEN : %d\n\n", strlen(temp));
        strcpy(mySong.title, temp);
        printf("LE TIIITRE struct : %s pas mal non ?\n", mySong.title);
        printf("LEN in struct : %d\n", strlen(mySong.title));

        //mySong.title[strlen(mySong.title)-1]='\0';*/


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
        mySong.tpm = 2* atoi(str_buffer2); // conversion en int puis enregistre

        //printf("Titre : %s\n", mySong.title);
        //printf("Tempo : %d\n", mySong.tpm);

        char l_temp[200]; // l max = 185 en pratique
        for (int i = 0; i < 2; ++i) {
            fgets(l_temp, 200, fichier);
        }
        char ligne[200];
        char ligne_sans_entete[200] = "";
        int compteur_ligne = 0;
        int num_note;
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
            //printf("Tick numero %d\n", compteur_ligne);

            while (tok != 0) {
                if(tok[0] != ' ' && tok[1] != '\n'){
                    //printf("%c\n", tok[0]);
                    if(tok[0] == '^'){
                        accentuation = 1;
                    }
                    t.note[place_note_dans_tick] = num_note;
                    place_note_dans_tick ++;
                    //printf("note : %d %s\n", num_note, tok);
                }

                tok = strtok(0, s);
                num_note ++;
            }
            t.accent = accentuation;
            mySong.tickTab[compteur_ligne-1] = t;
            mySong.nTicks = compteur_ligne;
        }


        fclose(fichier);
    }else{
        printf("Unable to open file %s .\n", fileName);
        strcpy(mySong.title, "");
        mySong.tpm = 0;
        mySong.nTicks = 0;
        s_tick t;
        for (int i = 0; i < 4; ++i) {// de base toutes les notes sur muet
            t.note[i] = 0;
        }
        mySong.tickTab[0] = t;
    }

    return mySong;
}




/**
 * Créer un fichier AMS d'après un fichier TXT
 * @param txtFileName
 * @param amsFileName
 */
void createAMS(char* txtFileName, char* amsFileName){
    FILE* fichierTXT = initTXT(txtFileName); // ouverture du fichier
    FILE* fichierAMS = initAMS_write(amsFileName); // ouverture du fichier en ecriture

    // On copie les 3 premières lignes identiques
    for (int i = 0; i < 3; i++) {
        char str_buffer[100];
        if (fgets(str_buffer, sizeof(str_buffer), fichierTXT) == NULL) {
            printf("Fail to read the input stream");
        }
        fputs(str_buffer, fichierAMS);
    }


    // affichage ligne numéros des notes
    for(int i = 0; i < 4; i++) {
        fputc(' ', fichierAMS);
    }
    for(int i = 1; i <= 60; i++) { // methode pour pouvoir les écrire en char
        int dizaine = i / 10;
        int unit = i % 10;
        fputc(dizaine+'0', fichierAMS);
        fputc(unit+'0', fichierAMS);
        fputc(' ', fichierAMS);
    }

    // écriture des notes

    char str_buffer2[500];
    int num_ligne = 1;
    const char delimitation[4] = ",";
    char *tok;
    int memoire_position_ligne = 1; // représente la case (la note) ou on se trouve
    int nbr_ticks[60] = {0}; // contient les ticks en fonction d'une note qu'on a du garder en mémoire
    int note_precedente = 0; // position de la note précédente sur une même ligne

    while (fgets(str_buffer2, sizeof(str_buffer2), fichierTXT) != NULL){ // Tant qu'on a pas lu toutes les lignes du fichier txt
        fputs("\r\n", fichierAMS);

        memoire_position_ligne = 1;
        note_precedente = 0; // on la réinitialise quand on change de ligne
        // affichage tick
        int centaine = num_ligne / 100;
        int dizaine = num_ligne / 10;
        int unit = num_ligne % 10;
        fputc(centaine + '0', fichierAMS);
        fputc(dizaine + '0', fichierAMS);
        fputc(unit + '0', fichierAMS);


        tok = strtok(str_buffer2, delimitation);
        while (tok != 0) {
            //printf("test note : %s ", tok); // vérifier si on est au bon tok

            // On a 12 note par octave, et 5 octaves en tout
            // C ; C# ; D ; D# ; E ; F ; F# ; G ; G# ; A ; A# ; B

            delete_space(tok); // enlève les espaces

            // liste des notes et leurs positions
            // C = 1 ; D = 3 ; E = 5 ; F = 6 ; G = 8 ; A = 10 ; B = 12
            // on pourra en déduire que C# = 2 ...

            int position_note = 0;

            // on cherche la position de la note
            if (tok[0] == 'C') {
                position_note = note_position(1, tok, (int *) nbr_ticks);
            }
            if (tok[0] == 'D') {
                position_note = note_position(3, tok, (int *) nbr_ticks);
            }
            if (tok[0] == 'E') {
                position_note = note_position(5, tok, (int *) nbr_ticks);
            }
            if (tok[0] == 'F') {
                position_note = note_position(6, tok, (int *) nbr_ticks);
            }
            if (tok[0] == 'G') {
                position_note = note_position(8, tok, (int *) nbr_ticks);
            }
            if (tok[0] == 'A') {
                position_note = note_position(10, tok, (int *) nbr_ticks);
            }
            if (tok[0] == 'B') {
                position_note = note_position(12, tok, (int *) nbr_ticks);
            }

            //affiches les ticks garder en mémoire (exemple si une note est joué sur 8 ticks on la garde en mémoire pour la prochaine ligne et on l'affiche comme ci-dessous)
            for (int i = 0; i < 60 ; i++){
                if (nbr_ticks[i] != 0 && i < position_note && i > note_precedente){
                    while (memoire_position_ligne < i) { // tant qu'on ne trouve pas à la note demandée on affiche des cases vides
                        fputs("|  ", fichierAMS);
                        memoire_position_ligne++;
                        //exit(1);
                    }
                    fputs("|x ", fichierAMS);
                    memoire_position_ligne++;
                    nbr_ticks[i]--; // on oublie pas d'enlever celui qu'on vient d'afficher
                }
            }

            while (memoire_position_ligne != position_note && memoire_position_ligne <= 60 ) { // tant qu'on ne trouve pas à la note demandée on affiche des cases vides
                fputs("|  ", fichierAMS);
                memoire_position_ligne++;
            }

            // on affiche la note
            fputs("|^ ", fichierAMS);
            memoire_position_ligne++;

            note_precedente = position_note;

            // à la fin du while
            tok = strtok(0, delimitation);
        }
        //printf("\n");
        for (int i = memoire_position_ligne; i <= 60; ++i) { // si il reste des cases à remplir jusqu'a la fin (60) on les affiche
            fputs("|  ", fichierAMS);
            memoire_position_ligne++;
        }

        fputs("|", fichierAMS); // affichage pipe de fin et retour a la ligne
        num_ligne++; // on passe à la ligne suivante

    }

    closeFile(fichierTXT);
    closeFile(fichierAMS);

}



FILE* initTXT(char* filename){
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

/**
 * Ouvrir un fichier en écriture
 * @param filename
 * @return
 */
FILE* initAMS_write(char* filename){
    FILE * pf = NULL;
    pf = fopen(filename, "w"); // Ouverture du fichier en écriture
    if (pf != NULL){
        printf("File %s opened successfully.\n", filename);
    }else{
        printf("Unable to open file %s .\n", filename);
    }
    return pf;
}


/**
 * delete les espace dans un string
 * @param str
 */
void delete_space(char *str){
    for (int i = 0 ; i < strlen(str); i++){
        if (str[i] == ' '){
            memmove(&str[i], &str[i + 1], (strlen(str) - (i + 1) + 1)); // merci antoine une super fonction
        }
    }
}


/**
 * permet de calculer la position de la note
 * @param numNote
 * @param str
 * @return
 */
int note_position(int numNote, char* str, int* nbr_ticks){
    int position = 0;
    char *ptr = strchr(str, '#'); // si oui alors on prend la position de la note au-dessus
    if (ptr) {
        position = numNote+1;
    } else {
        position = numNote; // sinon on garde sa position de base
    }

    int octave = str[1] - '0'; // on passe l'octave eb int
    position = (position + (12 * (octave-1))); // octave 1 : +12 * 0 , octave 2 : +12 * 1 ...

    char *ptr2 = strchr(str, 'R'); // calcul le nombre de ticks et les gardes en mémoire
    if (ptr2) {
        nbr_ticks[position] = 8 - 1; // -1 la ticks qu'on est en train d'écrire
    }

    return position;
}

/**
 * doit vérifier que le fichier pointé par pf existe bien et le fermer le cas échéant.
 * @param pf
 */
void closeFile(FILE* pf){
    if (pf != NULL)
    {
        fclose(pf); // On ferme le fichier qui a été ouvert
    }else{

    }
}

void print_s_tick(s_tick tick){
    printf("%02d, %02d, %02d, %02d acc:%d\n", tick.note[0], tick.note[1], tick.note[2], tick.note[3], tick.accent);
}


void print_s_song(s_song song){
    printf("Titre : %s\n", song.title);
    printf("Tempo : %d\n", song.tpm);
    printf("Nombre de ticks : %d\n", song.nTicks);

    for (int i = 0; i < song.nTicks; ++i) {
        print_s_tick(song.tickTab[i]);
    }
}