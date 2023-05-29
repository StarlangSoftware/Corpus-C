//
// Created by Olcay Taner YILDIZ on 20.05.2023.
//

#include <stdio.h>
#include "../src/CorpusStream.h"

void test_number_of_words1(){
    int word_count = 0;
    Corpus_stream_ptr corpus = create_corpus_stream("corpus.txt");
    corpus_stream_open(corpus);
    Sentence_ptr sentence = corpus_stream_get_sentence(corpus);
    while (sentence != NULL){
        word_count += sentence_word_count(sentence);
        free_sentence(sentence);
        sentence = corpus_stream_get_sentence(corpus);
    }
    corpus_stream_close(corpus);
    if (word_count != 826680){
        printf("Error in number of words 1");
    }
    free_corpus_stream(corpus);
}

void test_number_of_words2(){
    int word_count = 0;
    Corpus_stream_ptr corpus = create_corpus_stream("corpus.txt");
    corpus_stream_open(corpus);
    Array_list_ptr sentence_batch = corpus_stream_get_sentence_batch(corpus, 100);
    while (sentence_batch->size > 0){
        for (int i = 0; i < sentence_batch->size; i++){
            word_count += sentence_word_count(array_list_get(sentence_batch, i));
        }
        free_array_list(sentence_batch, (void (*)(void *)) free_sentence);
        sentence_batch = corpus_stream_get_sentence_batch(corpus, 100);
    }
    free_array_list(sentence_batch, NULL);
    corpus_stream_close(corpus);
    if (word_count != 826680){
        printf("Error in number of words 2");
    }
    free_corpus_stream(corpus);
}

int main(){
    test_number_of_words1();
    test_number_of_words2();
}