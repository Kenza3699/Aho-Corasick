#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "hash.h"
#include "file.h"



/* -----------lireFichierTexte(): Prend en parametre le nom de fichier et renvoi son contenue type string --------------- */
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

    if (fread(contenu, 1, taille, fichier) != taille)
    {
        free(contenu);
        fclose(fichier);
        return NULL;
    }

    contenu[taille] = '\0';
    fclose(fichier);
    return contenu;
}

// CreateTrie:crée un nouveau Trie avec un nombre maximum de nœuds donné
Trie createTrie(int maxNode) {
    if (maxNode < 1) {
        return NULL;
    }
    struct _trie *newTrie = malloc(sizeof *newTrie);
    if (newTrie == NULL) {
        return NULL;
    }
    newTrie -> maxNode = maxNode;
    newTrie -> nextNode = 1;    
    newTrie -> transition = NULL;
    newTrie -> exits = NULL;
    
    size_t tableSize = TABLE_SIZE(maxNode);
    newTrie -> transition = malloc(tableSize * sizeof *newTrie -> transition);
    if (newTrie -> transition == NULL) {
        goto error;
    }
    for (List *t = newTrie -> transition;
            t < newTrie -> transition + tableSize; ++t) {
        *t = NULL;
    }
    
    newTrie -> exits = malloc((size_t)maxNode * sizeof (Exit));
    if (newTrie -> exits == NULL) {
        goto error;
    }
    for (Exit *p = newTrie -> exits; p < newTrie -> exits + maxNode; ++p) {
        p->count = 0;
        p->outs = NULL;
    }
    
    newTrie -> sup = malloc(tableSize * sizeof *newTrie -> sup);
    if (newTrie -> sup == NULL) {
        goto error;
    }
    for (int *t = newTrie -> sup;
            t < newTrie -> sup + tableSize; ++t) {
        *t = 0;
    }
    
    goto success;
    error:
    freeTrie(&newTrie);
    success:
    return newTrie;
}


// Cette fonction permet d'ajouter un mot dans le Trie
void trieAdd(Trie trie, unsigned char *word) {
    int oldState = 0;
    int currentState = 0;
    unsigned char *ptr = word;
    size_t newSize = 0;
    
    while (*ptr != '\0' && currentState != -1) {
        oldState = currentState;
        currentState = nextState(trie, currentState, *ptr);
        
        ++ptr;
    }

    if (currentState == -1) {
        currentState = oldState;
        --ptr;
        if (strlen((char*)ptr) > (size_t)(trie -> maxNode - trie -> nextNode)) {
            printf("le nœud n'a pas pu être inséré \n");
            return;
        }
        while (*ptr != '\0') {
            addTransition(trie, currentState, *ptr, trie -> nextNode);
            currentState = trie -> nextNode;
            trie -> nextNode++;
            ++ptr;
        }
    }
    
    if(trie -> exits[currentState].count == 0){
        trie -> exits[currentState].outs = malloc(sizeof (char *));
        trie -> exits[currentState].outs[0] = malloc(sizeof (word));
        //strcpy(trie->exits[currentState].outs[0], word);
        trie->exits[currentState].count ++;
    }
}



//freeTrie() permet de Libère la mémoire allouée pour le Trie

void freeTrie(struct _trie** triePtr) {
    if (*triePtr != NULL) {
        size_t tableSize = TABLE_SIZE((*triePtr) -> maxNode);
        for (List *listPtr = (*triePtr) -> transition;
                listPtr < (*triePtr) -> transition + tableSize; ++listPtr) {
            while (*listPtr != NULL) {
                struct _list *tmp = *listPtr;
                *listPtr = (*listPtr) -> next;
                free(tmp);
            }
        }
        free((*triePtr) -> transition);
        free((*triePtr) -> exits);
        free(*triePtr);
        *triePtr = NULL;
    }
}


//hash() permet de calculer l'indice dans la table de hachage pour une transition

size_t hash(int nodeValue, unsigned char letterValue) {
    return (size_t)nodeValue * ((size_t)UCHAR_MAX + 1) + (size_t)letterValue;
}


//nextState() permet d'obtenir l'état suivant à partir d'un nœud avec une lettre donnée

 
int nextState(struct _trie *trie, int currentNode, unsigned char currentLetter) {
    size_t index = hash(currentNode, currentLetter) % TABLE_SIZE(trie -> maxNode);
    int next = -1;
    struct _list *t = trie -> transition[index];
    while (t != NULL && next == -1) {
        if (t -> startNode == currentNode && t -> letter == currentLetter) {
            next = t -> targetNode;
        }
        t = t -> next;
    }
    
    return next;
}


//addTransition() permet d'ajouter une nouvelle transition dans le Trie

int addTransition(struct _trie *trie, int startNodeCustom,
        unsigned char letterCustom, int targetNodeCustom) {
    struct _list *newTransition = malloc(sizeof *newTransition);
    if (newTransition == NULL) {
        return -1;
    }
    newTransition -> startNode = startNodeCustom;
    newTransition -> targetNode = targetNodeCustom;
    newTransition -> letter = letterCustom;
    
    size_t tableSize = TABLE_SIZE(trie -> maxNode);
    size_t index = hash(startNodeCustom, letterCustom) % tableSize;
    newTransition -> next = trie -> transition[index];
    trie -> transition[index] = newTransition;
    return 0;
}


//tableState() permet d'afficher l'état de la table de transition

void tableState(struct _trie *trie) {
    size_t tableSize = TABLE_SIZE(trie -> maxNode);
    
    size_t longestList = 0;
    size_t count = 0;
    for (struct _list **p = trie -> transition;
            p < trie -> transition + tableSize; ++p) {
        size_t len = 0;
        for (struct _list *q = *p; q != NULL; q = q -> next) {
            count++;
            len++;
        }
        if (len > longestList) {
            longestList = len;
        }
    }

    double loadFactor = ((double)count) / (double) tableSize;

    printf("Size : %lu\n"
           "Load factor : %lf\n"
           "Load factor max : %lf\n"
           "Depth : %lu\n",tableSize,loadFactor,LOAD_FACTOR,longestList);
}


//transitions() permet d'obtient toutes les transitions à partir d'un nœud donné
 
List *transitions(struct _trie *trie, int node, int *listsize, int mode){
    List *l = NULL;
    int i = 0;
    size_t tableSize = TABLE_SIZE(trie->maxNode);
    
    int next=0;
    struct _list *current = NULL;
    
    for (List *t = trie -> transition;t < trie -> transition + tableSize; ++t) {
        if(*t != NULL){
            current = *t;
            while (current != NULL) {
                if((current->startNode == node) && ((mode == 0 && current->startNode != current->targetNode) ||mode != 0)){
                    l = realloc(l, i * sizeof *t);
                    l[i] = current;
                    i++;
                }
                current = current -> next;
            }

        }
    }
    *listsize = i;
    return l;
}

//mergeExits() permet de fusionner deux ensembles de sorties de nœuds 
void mergeExits(Exit *src, Exit *dest){
    size_t src_size = 0, dest_size = 0;
    size_t j = 0;
    if(src->count != 0){
        src_size = src->count;
        dest_size = dest->count;

        dest->outs = realloc(dest->outs, (src_size + dest_size) * sizeof (char *));
        
        for(size_t i = dest_size;i < dest_size + src_size;i++){
            dest->outs[i] = malloc(sizeof (src->outs[j]));
            strcpy(dest->outs[i],src->outs[j]);
            j++;
        }
        dest->count = dest_size + src_size;
    }
}

//calculateSup() permet de calculer la table des substitutions pour l'algorithme Aho-Corasick

void calculateSup(Trie trie){
    file *file = initfile();
    size_t tableSize = TABLE_SIZE(trie->maxNode);
    size_t i = 0;
    int r,s,listeSize = 0;
    List *l = NULL;
    List current = NULL;
    
    l = transitions(trie, 0, &listeSize,0);

    for(i = 0; i<listeSize;i++) {
        current = l[i];  
        fileEnfiler(file,current->targetNode);
        trie->sup[current->targetNode] = current->startNode;
            
    }
    while (!fileVide(*file)){
        r = fileDefiler(file);
        l = transitions(trie, r, &listeSize,1);
        for(i = 0; i<listeSize;i++) {
            current = l[i];
            fileEnfiler(file,current->targetNode);
            s = trie->sup[current->startNode];

            while(nextState(trie,s,current->letter) == -1 && s != 0){
                s = trie->sup[s];                
            }
            s = nextState(trie,s,current->letter);
            if(s != -1){
                trie->sup[current->targetNode] = s;
                if(trie->exits[s].count != 0){
                    mergeExits(&(trie->exits[s]),&(trie->exits[current->targetNode]));
                }
            }

        }
    }
    
    
}

//acSearch() permet d'effectuer la recherche selon l'algorithme Aho-Corasick dans le texte en utilisant le Trie

int acSearch(Trie trie, char *text){
    int e = 0;
    int cpt = 0;
    size_t exitSize = 0;
    for(int j = 0; j < strlen(text);j++){
        while(nextState(trie,e,text[j]) == -1 && e != 0){
            e = trie->sup[e];
        }
        e = nextState(trie,e,text[j]);
        if(e != -1 && trie->exits[e].count != 0){
            cpt += trie->exits[e].count;
        }else if(e == -1){
            e = 0;
        }
    }
    return cpt;
}
