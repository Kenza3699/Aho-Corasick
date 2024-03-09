#include "generer_mots.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void genererMots(int nombreMots, int longueurMinMot, int longueurMaxMot, int tailleAlphabet) {
    srand((unsigned int)time(NULL));  // Conversion explicite de time_t en unsigned int

    for (int i = 0; i < nombreMots; i++) {
        int longueurMot = longueurMinMot + rand() % (longueurMaxMot - longueurMinMot + 1);
        for (int j = 0; j < longueurMot; j++) {
            char caractereAleatoire = 'a' + (char)(rand() % tailleAlphabet);  // Conversion explicite de int en char
            putchar(caractereAleatoire);
        }
        putchar('\n');
    }
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s <nombreMots> <longueurMinMot> <longueurMaxMot> <tailleAlphabet>\n", argv[0]);
        return 1;
    }

    int nombreMots = atoi(argv[1]);
    int longueurMinMot = atoi(argv[2]);
    int longueurMaxMot = atoi(argv[3]);
    int tailleAlphabet = atoi(argv[4]);

    genererMots(nombreMots, longueurMinMot, longueurMaxMot, tailleAlphabet);

    return 0;
}
