#ifndef MATRIX_H
#define MATRIX_H

// structure exit
typedef struct Exit Exit;

struct Exit {
    int count;    // Nombre de sorties
    char **outs;   // Tableau de sorties
};

//la structure de trie
struct _trie {
    int maxNode;        // Nombre maximal de noeuds du trie
    int nextNode;       // Indice du prochain noeud disponible
    int **transition;   // Matrice de transition
    Exit *exits;        // Tableau des sorties
    int *sup;           // Tableau de substituts pour Aho-corasik
};

typedef struct _trie *Trie;

//les fonction

// Prend en paramètre le nom de fichier et renvoie son contenu sous forme de chaîne de caractères
char* lireFichierTexte(char *Fichier);

// Crée un nouveau trie
Trie createTrie(int maxNode);

// Ajoute un mot au trie
void trieAdd(Trie trie, unsigned char *w);

// Libère la mémoire allouée pour le trie
void freeTrie(struct _trie** trie);

// Obtient le prochain état à partir d'un nœud avec une lettre
int nextState(struct _trie *trie, int node, unsigned char letter);

// Ajoute une transition à la table des transitions du trie
int addTransition(struct _trie *trie, int startNode, unsigned char letter, int targetNode);

// Calcule la table de substitutions Aho-corasik
void calculateSup(Trie trie);

// Effectue une recherche Aho-corasik dans le texte en utilisant le trie
int acSearch(Trie trie, char *text);

#endif
