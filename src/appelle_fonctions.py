import subprocess
import time

#fonction qui fait appelle a ac-matrice
def call_ac_matrice(words_file, text_file, alphabet_size, word_min_length, word_max_length):
    #l'appelle en utilisant les fichiers en parametres en mesurant le temp
    start_time = time.time()
    cmd_ac_matrice = f"./ac-matrice {words_file} {text_file}"
    subprocess.run(cmd_ac_matrice.split())
    end_time = time.time()
    elapsed_time = end_time - start_time
    result_file_name = f"result_matrice{alphabet_size}_{word_max_length}_{word_min_length}.txt"
    with open(result_file_name, "w") as file:
        file.write(str(elapsed_time))
        #affichage cmd
    print(f"occurences ttrouvés avec ./ac-matrice en {elapsed_time} secondes, les fichiers utillisés: {words_file}, {text_file}")

#fonction qui fait appelle a ac-hachage
def call_ac_hachage(words_file, text_file, alphabet_size, word_min_length, word_max_length):
    #l'appelle en utilisant les fichiers en parametres en mesurant le temp
    start_time = time.time()
    cmd_ac_hachage = f"./ac-hachage {words_file} {text_file}"
    subprocess.run(cmd_ac_hachage.split())
    end_time = time.time()

    elapsed_time = end_time - start_time
    result_file_name = f"result_hachage{alphabet_size}_{word_max_length}_{word_min_length}.txt"
    with open(result_file_name, "w") as file:
        file.write(str(elapsed_time))
        #affichage cmd
    print(f"occurences ttrouvés avec ./ac-hachage en {elapsed_time} secondes, les fichiers utillisés: {words_file}, {text_file}")

# Longueur du texte
text_length = 5000000  
#tailles d'alphabet
alphabet_sizes = [2, 4, 20, 70]  

for alphabet_size in alphabet_sizes:
    # Générer le nom du fichier de texte basé sur la taille de l'alphabet
    text_file = f"text_5000000_{alphabet_size}.txt"
    # Ensembles de mots
    word_sets = [(100, 5, 15), (100, 15, 30), (100, 30, 60)]  # Ensembles de mots
    for num_words, word_min_length, word_max_length in word_sets:
        #pur chaque combinaison on appelle les deux fonctions
        words_file = f"mots_{num_words}_{word_min_length}_{word_max_length}_{alphabet_size}.txt"
        call_ac_matrice(words_file, text_file, alphabet_size, word_min_length, word_max_length)
        call_ac_hachage(words_file, text_file, alphabet_size, word_min_length, word_max_length)
