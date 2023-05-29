//
// Created by Olcay Taner YILDIZ on 20.05.2023.
//

#ifndef CORPUS_CORPUSSTREAM_H
#define CORPUS_CORPUSSTREAM_H

#include <stdio.h>
#include "Sentence.h"

struct corpus_stream {
    FILE *input_stream;
    char *file_name;
};

typedef struct corpus_stream Corpus_stream;
typedef Corpus_stream *Corpus_stream_ptr;

Corpus_stream_ptr create_corpus_stream(const char* file_name);

void free_corpus_stream(Corpus_stream_ptr corpus_stream);

void corpus_stream_open(Corpus_stream_ptr corpus_stream);

void corpus_stream_close(Corpus_stream_ptr corpus_stream);

Sentence_ptr corpus_stream_get_sentence(const Corpus_stream* corpus_stream);

Array_list_ptr corpus_stream_get_sentence_batch(const Corpus_stream* corpus_stream, int line_count);

#endif //CORPUS_CORPUSSTREAM_H
