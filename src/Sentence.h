//
// Created by Olcay Taner YILDIZ on 20.05.2023.
//

#ifndef CORPUS_SENTENCE_H
#define CORPUS_SENTENCE_H

#include <ArrayList.h>
#include <stdio.h>
#include <Dictionary/Word.h>

struct sentence {
    Array_list_ptr words;
};

typedef struct sentence Sentence;
typedef Sentence *Sentence_ptr;

Sentence_ptr create_sentence();

Sentence_ptr create_sentence2(FILE* infile);

Sentence_ptr create_sentence3(char* sentence);

Sentence_ptr read_sentence(FILE* infile);

Sentence_ptr read_sentence2(FILE* infile, bool (*is_valid_word)(const char*));

void free_sentence(Sentence_ptr sentence);

char* sentence_get_word(const Sentence* sentence, int index);

Array_list_ptr sentence_get_words(const Sentence* sentence);

int sentence_get_index(const Sentence* sentence, const char* word);

int sentence_word_count(const Sentence* sentence);

void sentence_add_word(Sentence_ptr sentence, char* word);

void sentence_add_word_copy(Sentence_ptr sentence, char* word);

int sentence_char_count(const Sentence* sentence);

void sentence_replace_word(Sentence_ptr sentence, int i, char* new_word);

void sentence_insert_word(Sentence_ptr sentence, int i, char* new_word);

bool sentence_safe_index(const Sentence* sentence, int index);

String_ptr to_words(const Sentence* sentence);

char* sentence_to_string(const Sentence* sentence);

#endif //CORPUS_SENTENCE_H
