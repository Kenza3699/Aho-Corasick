#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "matrix.h"

//definir syntx
#define MAN() fprintf(stderr, "SYNTAX: %s <words file> <text file>\n", argv[0])

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Non autorisé, nombre d'arguments erroné\n");
        MAN();
        exit(EPERM);
    }
    char *wfile = argv[1];
    char *tfile = argv[2];
    
    //lire les mots
    char *words_buff,*text;
    char **words = NULL;
    char delim[] = "\n";
    int n_spaces = 0,i;
    size_t maxNodes = 0;
    
    words_buff = lireFichierTexte(wfile);
    text = lireFichierTexte(tfile);
    
    if (words_buff)
    {
        words_buff = strtok(words_buff, delim);
        while (words_buff != NULL)
        {
            words = realloc (words, sizeof (char*) * ++n_spaces);
            if (words == NULL){
                fprintf(stderr, "Erreur d'allocation de mémoire\n");
                exit(ENOMEM);
            }
            
            words[n_spaces-1] = words_buff;
            maxNodes += strlen(words[n_spaces-1]);
            words_buff = strtok (NULL, delim);
        }
    }else{
        fprintf(stderr, "Erreur de fichier, fichier de mots introuvable ou vide\n");
        exit(EIO);
    }
    maxNodes = maxNodes + 1;
    free(words_buff);

    //creation des tries
    Trie trie = createTrie(maxNodes);

    //Ajout des mots dans le trie
    for (i = 0; i < n_spaces; ++i){
        trieAdd(trie, words[i]);
    }
    
    //Construire une table de substitution
    calculateSup(trie);
    
    //Recherche des mots
    i = acSearch(trie,text);
    printf ("%d\n", i);
    
}
