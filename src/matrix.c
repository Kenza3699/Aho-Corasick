#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "matrix.h"
#include "file.h"

/* -----------lireFichierTexte(): Prend en paramètre le nom de fichier et renvoie son contenu type string --------------- */
char* lireFichierTexte(char *Fichier)
{
    FILE *fichier = fopen(Fichier, "r");
    if (!fichier) return NULL;

    fseek(fichier, 0, SEEK_END);
    long taille = ftell(fichier);
    rewind(fichier);

    char *contenu = malloc(taille + 1);
    if (!contenu)
    {
        fclose(fichier);
        return NULL;
    }

    if (fread(contenu, 1, taille, fichier) != (size_t)taille)
    {
        free(contenu);
        fclose(fichier);
        return NULL;
    }

    contenu[taille] = '\0';
    fclose(fichier);
    return contenu;
}

//createTrie() permet de  creer  un nouveau trie
   
Trie createTrie(int maximumNodes) {
    if (maximumNodes < 1) {
        return NULL;
    }
    struct _trie *customTrie = malloc(sizeof *customTrie);
    if (customTrie == NULL) {
        return NULL;
    }
    customTrie->maxNode = maximumNodes;
    customTrie->nextNode = 1;
    customTrie->transition = NULL;
    customTrie->exits = NULL;
    customTrie->sup = NULL;

    customTrie->transition = malloc((size_t)maximumNodes * sizeof (*customTrie->transition));
    if (customTrie->transition == NULL) {
        goto error;
    }
    for (int **pointer = customTrie->transition; 
            pointer < customTrie->transition + maximumNodes;
            ++pointer) {
        *pointer = malloc(((int)UCHAR_MAX + 1) * sizeof **pointer);
        if (*pointer == NULL) {
            goto error;
        }
        for (int *q = *pointer; q <= *pointer + UCHAR_MAX; ++q) {
            *q = -1;
        }
    }

    customTrie->exits = malloc((size_t)maximumNodes * sizeof (Exit));
    if (customTrie->exits == NULL) {
        goto error;
    }
    for (Exit *p = customTrie->exits; p < customTrie->exits + maximumNodes; ++p) {
        p->count = 0;
        p->outs = NULL;
    }

    customTrie->sup = malloc((size_t)maximumNodes * sizeof *customTrie->sup);
    if (customTrie->sup == NULL) {
        goto error;
    }
    for (int *t = customTrie->sup;
            t < customTrie->sup + maximumNodes; ++t) {
        *t = 0;
    }

    goto success;
    error:
    freeTrie(&customTrie);
    success:
    return customTrie;
}

//trieAdd() permet d'ajouter des mots dans le trie 
  
void trieAdd(Trie customTrie, unsigned char *word) {
    int oldState = 0;
    int currentState = 0;
    unsigned char *ptr = word;
    size_t newSize = 0;

    while (*ptr != '\0' && currentState != -1) {
        oldState = currentState;
        currentState = nextState(customTrie, currentState, *ptr);
        ++ptr;
    }

    if (currentState == -1) {
        currentState = oldState;
        --ptr;

        if (strlen((char *)ptr) > (size_t)(customTrie->maxNode - customTrie->nextNode)) {
            fprintf(stderr, "Overflow, node could not be inserted\n");
            return;
        }

        while (*ptr != '\0') {
            addTransition(customTrie, currentState, *ptr, customTrie->nextNode);
            currentState = customTrie->nextNode;
            customTrie->nextNode++;
            ++ptr;
        }
    }

    if (customTrie->exits[currentState].count == 0) {
        customTrie->exits[currentState].outs = malloc(sizeof (char *));
        customTrie->exits[currentState].outs[0] = malloc(strlen((char *)word) + 1);
        strcpy(customTrie->exits[currentState].outs[0], (char *)word);
        customTrie->exits[currentState].count++;
    }
}

//freeTrie() permet de Libère la mémoire allouée pour le Trie
void freeTrie(struct _trie** customTrie) {
    if (*customTrie != NULL) {
        for (int **pointer = (*customTrie)->transition;
                pointer < (*customTrie)->transition + (*customTrie)->maxNode;
                ++pointer) {
            free(*pointer);
        }
        free((*customTrie)->transition);
        free((*customTrie)->exits);
        free((*customTrie)->sup);
        free(*customTrie);
        *customTrie = NULL;
    }
}

//nextState() permet d'obtenir l'état suivant à partir d'un nœud avec une lettre donnée

int nextState(struct _trie *customTrie, int node, unsigned char letter) {
    return customTrie->transition[node][letter];
}

//addTransition() permet d'ajouter une nouvelle transition dans le Trie

int addTransition(struct _trie *customTrie, int startNode,
        unsigned char letter, int targetNode) {
    
    customTrie->transition[startNode][letter] = targetNode;
    return 0;
}

//transitions() permet d'obtient toutes les transitions à partir d'un nœud donné

int *transitions(struct _trie *customTrie, int node, int *listSize, int mode) {
    int *transitionList = NULL;
    int i = 0;
    size_t j = 0;

    for (int *q = customTrie->transition[node]; q <= customTrie->transition[node] + UCHAR_MAX; ++q) {
        if (*q != -1 && ((mode == 0 && *q != node) || mode != 0)) {
            transitionList = realloc(transitionList, (i + 1) * sizeof (int));
            transitionList[i] = j;
            i++;
        }
        j++;
    }
    *listSize = i;
    return transitionList;
}
//mergeExits() permet de fusionner deux ensembles de sorties de nœuds 

void mergeExits(Exit *src, Exit *dest){
    size_t src_size = 0, dest_size = 0;
    size_t j = 0;
    if (src->count != 0) {
        src_size = src->count;
        dest_size = dest->count;

        dest->outs = realloc(dest->outs, (src_size + dest_size) * sizeof (char *));
        
        for (size_t i = dest_size; i < dest_size + src_size; i++) {
            dest->outs[i] = malloc(strlen(src->outs[j]) + 1);
            strcpy(dest->outs[i], src->outs[j]);
            j++;
        }
        dest->count = dest_size + src_size;
    }
}

//calculateSup() permet de calculer la table des substitutions pour l'algorithme Aho-Corasick

void calculateSup(Trie trie) {
    file *file = initfile();
    size_t i = 0, j = 0;
    char curr_letter;
    int r, s, listeSize = 0;
    int *l = NULL, curr_ind, curr_target;

    l = transitions(trie, 0, &listeSize, 0);
    for (i = 0; i < (size_t)listeSize; i++) {
        curr_ind = l[i];
        curr_target = trie->transition[0][curr_ind];
        curr_letter = (char) curr_ind;
        fileEnfiler(file, curr_target);
        trie->sup[curr_target] = 0;
    }
    free(l);
    while (!fileVide(*file)) {
        r = fileDefiler(file);
        l = transitions(trie, r, &listeSize, 1);
        for (i = 0; i < (size_t)listeSize; i++) {
            curr_ind = l[i];
            curr_target = trie->transition[r][curr_ind];
            curr_letter = (char) curr_ind;
            fileEnfiler(file, curr_target);
            s = trie->sup[r];
            while (nextState(trie, s, curr_letter) == -1 && s != 0) {
                s = trie->sup[s];
            }
            s = nextState(trie, s, curr_letter);
            if (s != -1) {
                trie->sup[curr_target] = s;
                if (trie->exits[s].count != 0) {
                    mergeExits(&(trie->exits[s]), &(trie->exits[curr_target]));
                }
            }
        }
    }
}

//acSearch() permet d'effectuer la recherche selon l'algorithme Aho-Corasick dans le texte en utilisant le Trie

int acSearch(Trie trie, char *text) {
    int e = 0;
    int cpt = 0;
    size_t exitSize = 0;
    for (int j = 0; j < (int)strlen(text); j++) {
        while (nextState(trie, e, text[j]) == -1 && e != 0) {
            e = trie->sup[e];
        }
        e = nextState(trie, e, text[j]);
        if (e != -1 && trie->exits[e].count != 0) {
            cpt += trie->exits[e].count;
        } else if (e == -1) {
            e = 0;
        }
    }
    return cpt;
}
