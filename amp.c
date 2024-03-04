/**
 * @authors Antoine LE BOULCH / Julia AZEAU CIR3 Caen
 */

#include <ctype.h>
#include "define.h"
#include "amp.h"

/**
 * initAMP doit tenter d’ouvrir le fichier dont le nom sur le disque est dans la variable filename :
 * "playlist.amp". Si le fichier s’ouvre en lecture, on renvoie un pointeur vers ce fichier. Sinon on
 * renvoie NULL.
 *
 * attention à l'emplacement du fichier (le fichier out est execute dans un repertoire, donc ajouter ../ avant le nom du *.amp)
 * @param filename
 * @return
 */
FILE* initAMP(char* filename){
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
 * readAMP consiste à lire une ligne du fichier pointé par pf et renvoyer une chaine de caractère. Cette
 * chaine de caractère doit absolument respecter les critères exigés plus haut. Si la lecture du fichier se
 * termine, la fonction doit renvoyer NULL. A l’usage, le renvoi de NULL indique à celui qui utilise
 * readAMP qu’il n’y a plus de titre à lire.
 * @param pf
 * @param song_filename
 */
void readAMP(FILE* pf, char * song_filename){
    fgets(song_filename, 99, pf);
    str_to_lower(song_filename);
    delete_special_chars(song_filename);
    refactor_multiple_underscores(song_filename);

}

/**
 * passe sur place une chaine de caractere en minuscules
 * @param ma_string
 */
void str_to_lower(char *ma_string){
    //Tout mettre en minuscule
    int len = strlen(ma_string);
    for ( int i = 0; i < len; i++)
    {
        ma_string[i] = tolower( (unsigned char) ma_string[i]);
    }
}


/**
 *
 * source : https://stackoverflow.com/questions/20049661/remove-adjacent-duplicates-in-a-string-in-c
 * @param str
 */
void refactor_multiple_underscores(char *str){
    size_t len = strlen(str); // size t la taille en octets

    if(len <= 1) // ne peut pas avoir de doublon, on change rien
        return;

    for(size_t i = 1; i < len; ){ // on parcourt la string en commencant au 2e caractere
        if(str[i] == str[i - 1] && str[i]=='_'){ // si le caractere _ apparait deux fois ou plus consecutivement, en comparant avec le precedent
            memmove(&str[i], &str[i + 1], (len - (i + 1) + 1)); // on bouge le bloc memoire memmove(dest, source, taille du bloc a deplacer)
            --len; // pour rester sur l'index apres avoir deplace la suite
        }
        else
            ++i; // on passe au suivant sinon
    }
}

//TODO not alphanumeric


void delete_special_chars(char *titre){
    //Enlever les caractère
    //Espace = _
    for(int i = 0; i < strlen(titre)-1; ++i){
        if (titre[i] == ' ' || titre[i] == ';' || titre[i] == '!' || titre[i] == '+' || titre[i] == '.' || titre[i] == ',' || titre[i] == '\''){
            titre[i] = '_';
        }
    }
}



/**
 * closeAMP doit vérifier que le fichier pointé par pf existe bien et le fermer le cas échéant.
 * @param pf
 */
void closeAMP(FILE* pf){
    if (pf != NULL)
    {
        fclose(pf); // On ferme le fichier qui a été ouvert
    }else{

    }
}