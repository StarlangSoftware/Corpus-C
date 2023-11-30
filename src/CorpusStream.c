//
// Created by Olcay Taner YILDIZ on 20.05.2023.
//

#include <stdlib.h>
#include <StringUtils.h>
#include <Memory/Memory.h>
#include "CorpusStream.h"

Corpus_stream_ptr create_corpus_stream(const char *file_name) {
    Corpus_stream_ptr result = malloc_(sizeof(Corpus_stream), "create_corpus_stream");
    result->file_name = str_copy(result->file_name, file_name);
    return result;
}

void free_corpus_stream(Corpus_stream_ptr corpus_stream) {
    free_(corpus_stream->file_name);
    free_(corpus_stream);
}

void corpus_stream_open(Corpus_stream_ptr corpus_stream) {
    corpus_stream->input_stream = fopen(corpus_stream->file_name, "r");
}

void corpus_stream_close(Corpus_stream_ptr corpus_stream) {
    fclose(corpus_stream->input_stream);
}

Sentence_ptr corpus_stream_get_sentence(const Corpus_stream* corpus_stream) {
    return read_sentence(corpus_stream->input_stream);
}

Array_list_ptr corpus_stream_get_sentence_batch(const Corpus_stream* corpus_stream, int line_count) {
    Array_list_ptr result = create_array_list();
    for (int i = 0; i < line_count; i++){
        Sentence_ptr sentence = read_sentence(corpus_stream->input_stream);
        if (sentence != NULL){
            array_list_add(result, sentence);
        } else {
            break;
        }
    }
    return result;
}
