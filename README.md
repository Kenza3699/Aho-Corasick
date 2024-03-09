*------------------------------------Exécution sans scripts ------------------------------------------*

1. cd src : acceder au fichiers source 

2. make : afin de compiler le projet

3. Donner le droit d'execution pour les fichiers : sudo chmod +x script.sh / sudo chmod +x genere-mot / sudo chmod +x genere-texte
                                                   sudo chmod +x ac-hachage /sudo chmod +x ac-matrice 

4. Generer les mots : ./genere-mots <nbr mots> <taille min> <taille max> <taille de l'alphabet>

5. Generer les textes : ./genere-texte <nbr mots> <taille min> <taille max> <taille de l'alphabet>

4. Recherche avec ac-hachage : ./ac-hachage <fichier des mots> <fichier du texte>

5. Recherche avec ac-matrice : ./ac-matrice <fichier des mots> <fichier du texte>


 
*------------------------------------Exécution avec script : Generer_fichier.py ------------------------------------------*

Un script python de generation des fichier est met en place:

1. cd src : acceder au fichiers source 

2. make : afin de compiler le projet

3. Ce script nécessite Python3. Si vous n'avez pas Python 3 installé voici le commande d'instalation sudo apt-get install python3

4. Execution de script : python3 Generer_fichier.py

5. Les fichiers générés seront dans le meme dossier src




*-------------------------------------Appelle au fonctions-----------------------------------------------*

Appelle des fonctions ac-hachage ac-matrice avec les fichier générés:

1. cd src : acceder au fichiers source 

2. make : afin de compiler le projet

3. Ce script nécessite Python3. Si vous n'avez pas Python 3 installé voici le commande d'instalation sudo apt-get install python3

4. Execution de script Generer_fichier.py est obligatoire car les fichiers génerés seront utilisés dans le script qui suit

4. Execution de script : python3 appelle_fonctions.py

5. Les fichiers générés contiendront le temps d'execution, les noms des fichiers sont significatifs.
