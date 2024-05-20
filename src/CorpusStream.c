//
// Created by Olcay Taner YILDIZ on 20.05.2023.
//

#include <stdlib.h>
#include <StringUtils.h>
#include <Memory/Memory.h>
#include "CorpusStream.h"

/**
 * Constructor for CorpusStream. CorpusStream is used for reading very large corpora that does not fit in memory as
 * a whole. For that reason, sentences are read one by one.
 * @param file_name File name of the corpus stream.
 */
Corpus_stream_ptr create_corpus_stream(const char *file_name) {
    Corpus_stream_ptr result = malloc_(sizeof(Corpus_stream), "create_corpus_stream");
    result->file_name = str_copy(result->file_name, file_name);
    return result;
}

/**
 * Frees memory allocated for corpus stream.
 * @param corpus_stream Corpus stream
 */
void free_corpus_stream(Corpus_stream_ptr corpus_stream) {
    free_(corpus_stream->file_name);
    free_(corpus_stream);
}

/**
 * Initializes file reader.
 * @param corpus_stream Corpus stream
 */
void corpus_stream_open(Corpus_stream_ptr corpus_stream) {
    corpus_stream->input_stream = fopen(corpus_stream->file_name, "r");
}

/**
 * Closes the file reader.
 * @param corpus_stream Corpus stream
 */
void corpus_stream_close(Corpus_stream_ptr corpus_stream) {
    fclose(corpus_stream->input_stream);
}

/**
 * Reads from the file buffer next sentence and returns it. If
 * there are no sentences to be read, returns null.
 * @param corpus_stream Corpus stream
 * @return Next read sentence from file buffer or null.
 */
Sentence_ptr corpus_stream_get_sentence(const Corpus_stream* corpus_stream) {
    return read_sentence(corpus_stream->input_stream);
}

/**
 * Reads more than one line (lineCount lines) from the buffer, stores them in an array list and returns that
 * array list. If there are no lineCount lines to be read, the method reads only available lines and returns them.
 * @param corpus_stream Corpus stream
 * @param line_count Maximum number of lines to read.
 * @return An array list of read lines.
 */
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
