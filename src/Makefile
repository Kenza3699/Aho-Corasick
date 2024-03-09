include_dir =../include
CC=gcc
CFLAGS = -pedantic -Wconversion -Wextra -Wall -std=c11
INCLUDE_FLAGS = -I $(include_dir)
GENERAL_FLAGS =

obj_dir=../obj


_DEPS = hash.h generer_mots.h generer_texte.h 

_hash_objs = ac-hachage.o hash.o file.o
hash_objs = $(patsubst %,$(obj_dir)/%,$(_hash_objs))

_matrix_obj = ac-matrice.o matrix.o file.o
matrix_obj = $(patsubst %,$(obj_dir)/%,$(_matrix_obj))


all : ac-matrice ac-hachage genere-mots genere-texte  

# Générateurs
genere-texte : $(obj_dir)/genere-texte.o
	$(CC) $^ $(GENERAL_FLAGS) -o $@

$(obj_dir)/genere-texte.o : genere-texte.c $(include_dir)/generer_texte.h
	$(CC) -c $(CFLAGS) $(INCLUDE_FLAGS) genere-texte.c -o $@

genere-mots : $(obj_dir)/genere-mots.o $(include_dir)/generer_mots.h
	$(CC) $^ $(GENERAL_FLAGS) -o $@

$(obj_dir)/genere-mots.o : genere-mots.c $(include_dir)/generer_mots.h
	$(CC) -c $(CFLAGS) $(INCLUDE_FLAGS) genere-mots.c -o $@

# la file
$(obj_dir)/file.o: file.c $(include_dir)/file.h
	$(CC) -c -o $@ $< $(INCLUDE_FLAGS)
	
#Aho-corasik avec matrice
$(obj_dir)/matrix.o: matrix.c $(include_dir)/matrix.h $(include_dir)/file.h
	$(CC) -c -o $@ $< $(INCLUDE_FLAGS)


$(obj_dir)/ac-matrice.o: ac-matrice.c matrix.c file.c
	$(CC) $(INCLUDE_FLAGS) -c -o $@ $<

ac-matrice: $(matrix_obj)
	$(CC) -o $@ $^
	
#Aho-corasik avec table de hachage
$(obj_dir)/hash.o: hash.c $(include_dir)/hash.h $(include_dir)/file.h
	$(CC) -c -o $@ $< $(INCLUDE_FLAGS)


$(obj_dir)/ac-hachage.o: ac-hachage.c hash.c file.c
	$(CC) $(INCLUDE_FLAGS) -c -o $@ $< 

ac-hachage: $(hash_objs)
	$(CC) -o $@ $^


.PHONY: clean

clean:
	rm -f $(obj_dir)/*.o *~ core $(INCDIR)/*~ 