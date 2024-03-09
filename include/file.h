#ifndef file_H
#define file_H

// Structure d'élément de file

typedef struct fileElement fileElement;
struct fileElement
{
    int data;             // Donnée stockée
    fileElement *suivant; // Pointeur vers l'élément suivant
};

//Structure de la file

typedef struct
{
    fileElement *tete;   // Pointeur vers le premier élément
} file;

//Déclarations de fonctions
file *initfile();                   // Création d'une nouvelle file
void fileEnfiler(file *file, int p);  // Ajouter un élément à la file
int fileDefiler(file *file);         // Retirer et retourner le premier élément
int fileVide(file file);            // Tester si la file est vide

#endif
