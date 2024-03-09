#include <stdlib.h>
#include <stdio.h>
#include "file.h"

// Création d'une file vide 
file *initfile()
{
    file *file = malloc(sizeof(*file));
    if (file != NULL)
    {
        file->tete = NULL;
    }
    return file;
}

// Ajouter un élément à la file 
void fileEnfiler(file *file, int item)
{
    if (file == NULL)
    {
        return;
    }

    fileElement *nouveau = malloc(sizeof(*nouveau));
    if (nouveau == NULL)
    {
        return;
    }
    nouveau->data = item;
    nouveau->suivant = NULL;

    if (file->tete == NULL)
    {
        file->tete = nouveau;
    }
    else
    {
        fileElement *temp = file->tete;
        while (temp->suivant != NULL)
        {
            temp = temp->suivant;
        }
        temp->suivant = nouveau;
    }
}

//Retirer et retourner le premier élément 
int fileDefiler(file *file)
{
    if (file == NULL || file->tete == NULL)
    {
        exit(EXIT_FAILURE);
    }

    fileElement *elementSupprime = file->tete;
    int item = elementSupprime->data;
    file->tete = elementSupprime->suivant;
    free(elementSupprime);

    return item;
}

// si la file est vide
int fileVide(file file)
{
    return (file.tete == NULL);
}
