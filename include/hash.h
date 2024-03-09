#ifndef HASH_H
#define HASH_H


// facteur de charge 
#define LOAD_FACTOR 0.90
//calculer la taille en fonction de fact
#define TABLE_SIZE(maxNode) (size_t)(((maxNode) - 1) / LOAD_FACTOR + 1)

//liste des transitions
struct _list {
    int startNode;          //noeud de départ
    int targetNode;         //noeud cible
    unsigned char letter;   //lettre associé
    struct _list *next;     //pointure neud suivant
};

typedef struct _list *List;

// structure exit
typedef struct Exit Exit;
struct Exit{
    int count;             //nbr de sorties
    char **outs;           //mot

};

//structure trie
struct _trie {
    int maxNode;        // Nombre maximal de noeuds du trie
    int nextNode;       // Indice du prochain noeud disponible
    List *transition;   // list transition
    Exit *exits;        // Tableau des sorties
    int  *sup;          // Tableau de substituts
};
typedef struct _trie *Trie;


// aytre fonctions 

//Prend en parametre le nom de fichier et renvoi son contenue type string
char* lireFichierTexte(char *Fichier);     

Trie createTrie(int maxNode);                                           // create new trie
void trieAdd(Trie trie, unsigned char *w);                              // add word to trie
void freeTrie(struct _trie** trie);                                     // free allocated memory for trie
size_t hash(int node_p, unsigned char letter);                          // hash function
int nextState(struct _trie *trie, int node, unsigned char letter);      // get next state from node with letter
int addTransition(struct _trie *trie, int startNode,                    
        unsigned char letter, int targetNode);                          // add transition to trie transitions table
void tableState(struct _trie *trie);                                    // print transition table state informations

void calculateSup(Trie trie);                                           // calculate aho-corasik substitutes table
int acSearch(Trie trie, char *text);                                    // aho-corasik search

#endif
