import subprocess
import time


def generate_text(text_length, alphabet_size):
    #creation fichier avec un nom significatif
    text_file = f"text_{text_length}_{alphabet_size}.txt"
    #appelle a genere-texte
    cmd_text = f"./genere-texte {text_length} {alphabet_size}"
    with open(text_file, "w") as file:
        subprocess.run(cmd_text.split(), stdout=file)
        print(f"{text_file} générés")
    return text_file

def generate_words(num_words, word_min_length, word_max_length, alphabet_size, text_file):
    #creation fichier avec un nom significatif
    words_file = f"mots_{num_words}_{word_min_length}_{word_max_length}_{alphabet_size}.txt"
    #appelle a genere-mots
    cmd_words = f"./genere-mots {num_words} {word_min_length} {word_max_length} {alphabet_size}"
    with open(words_file, "w") as file:
        subprocess.run(cmd_words.split(), stdout=file)
    print(f"{words_file} générés")
    return words_file
# Longueur du texte
text_length = 5000000  

# Différentes tailles d'alphabet

alphabet_sizes = [2, 4, 20, 70]  

for alphabet_size in alphabet_sizes:
    # Générer le fichier de texte
    text_file = generate_text(text_length, alphabet_size)  
    # Ensembles de mots
    word_sets = [(100, 5, 15), (100, 15, 30), (100, 30, 60)]  
    for num_words, word_min_length, word_max_length in word_sets:
        words_file = generate_words(num_words, word_min_length, word_max_length, alphabet_size, text_file)
