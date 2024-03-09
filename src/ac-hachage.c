#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "hash.h"


#define USAGE() fprintf(stderr, "SYNTAX: %s <words file> <text file>\n", argv[0])

int main(int argc, char **argv) {
     // Vérifie le nombre d'arguments et affiche l'usage en cas d'erreur
    if (argc != 3) {
        fprintf(stderr, "Non autorisé, nombre d'arguments erroné\n");
        USAGE();
        exit(EPERM);
    }

    char *wordsFile = argv[1];
    char *textFile = argv[2];
    
    // lire les mots
    char *wordsBuffer, *text;
    char **words = NULL;
    char delimiter[] = "\n";
    int numWords = 0, i;
    size_t totalNodes = 0;
    
    wordsBuffer = lireFichierTexte(wordsFile);
    text = lireFichierTexte(textFile);
    
    if (wordsBuffer) {
        wordsBuffer = strtok(wordsBuffer, delimiter);
        while (wordsBuffer != NULL) {
            words = realloc(words, sizeof(char*) * ++numWords);
            if (words == NULL) {
                fprintf(stderr, "Erreur d'allocation de mémoire\n");
                exit(ENOMEM);
            }
            
            words[numWords - 1] = wordsBuffer;
            totalNodes += strlen(words[numWords - 1]);
            wordsBuffer = strtok(NULL, delimiter);
        }
    } else {
        fprintf(stderr, "Erreur de fichier, fichier de mots introuvable ou vide\n");
        exit(EIO);
    }
    totalNodes = totalNodes + 1;
    free(wordsBuffer);

    // Cration du trie
    Trie trie = createTrie(totalNodes);
    
    // Ajoit des mots dans le trie
    for (i = 0; i < numWords; ++i) {
        trieAdd(trie, words[i]);
    }
    
    // Construire une table de substitution
    calculateSup(trie);
    
    // Recherche des mots
    i = acSearch(trie, text);
    printf("%d\n", i);
    
}
