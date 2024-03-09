#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void genererTexte(int longueur, int tailleAlphabet) {
    srand((unsigned int)time(NULL));  // Conversion explicite de time_t en unsigned int

    for (int i = 0; i < longueur; i++) {
        char caractereAleatoire = 'a' + (char)(rand() % tailleAlphabet);  // Conversion explicite de int en char
        putchar(caractereAleatoire);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <longueur> <tailleAlphabet>\n", argv[0]);
        return 1;
    }

    int longueur = atoi(argv[1]);
    int tailleAlphabet = atoi(argv[2]);

    if (longueur <= 0 || tailleAlphabet <= 0) {
        fprintf(stderr, "Les paramètres doivent être des nombres positifs.\n");
        return 1;
    }

    genererTexte(longueur, tailleAlphabet);

    return 0;
}





