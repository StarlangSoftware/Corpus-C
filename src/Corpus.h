//
// Created by Olcay Taner YILDIZ on 20.05.2023.
//

#ifndef CORPUS_CORPUS_H
#define CORPUS_CORPUS_H

#include <ArrayList.h>
#include <CounterHashMap.h>
#include "Sentence.h"
#include "Paragraph.h"

struct corpus {
    char *file_name;
    int sentence_index;
    Array_list_ptr sentences;
    Array_list_ptr paragraphs;
    Counter_hash_map_ptr word_list;
};

typedef struct corpus Corpus;
typedef Corpus *Corpus_ptr;

Corpus_ptr create_corpus();

Corpus_ptr create_corpus2(const char *file_name);

Corpus_ptr create_corpus3(const char *file_name, bool (*is_valid_word)(const char*));

Corpus_ptr create_corpus4(const char *file_name, Array_list_ptr (*sentence_splitter)(const char* line));

void free_corpus(Corpus_ptr corpus);

void corpus_combine(Corpus_ptr corpus1, const Corpus* corpus2);

void corpus_add_sentence(Corpus_ptr corpus, Sentence_ptr sentence);

int corpus_number_of_words(const Corpus* corpus);

bool corpus_contains(const Corpus* corpus, const char *word);

void corpus_add_paragraph(Corpus_ptr corpus, Paragraph_ptr paragraph);

char *corpus_get_file_name(const Corpus* corpus);

Array_list_ptr corpus_get_word_list(const Corpus* corpus);

int corpus_word_count(const Corpus* corpus);

int corpus_get_count(const Corpus* corpus, const char* word);

int corpus_sentence_count(const Corpus* corpus);

Sentence_ptr corpus_get_sentence(const Corpus* corpus, int index);

int corpus_paragraph_count(const Corpus* corpus);

Paragraph_ptr corpus_get_paragraph(const Corpus* corpus, int index);

int corpus_max_sentence_length(const Corpus* corpus);

Array_list_ptr get_all_words_as_vector(const Corpus* corpus);

void shuffle_sentences(Corpus_ptr corpus, int seed);

void corpus_open(Corpus_ptr corpus);

void corpus_close(Corpus_ptr corpus);

Sentence_ptr corpus_get_sentence2(Corpus_ptr corpus);

Corpus_ptr get_train_corpus(const Corpus* corpus, int foldNo, int foldCount);

Corpus_ptr get_test_corpus(const Corpus* corpus, int foldNo, int foldCount);

#endif //CORPUS_CORPUS_H
