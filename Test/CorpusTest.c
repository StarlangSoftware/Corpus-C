//
// Created by Olcay Taner YILDIZ on 22.05.2023.
//

#include "../src/Corpus.h"

void testNumberOfWords(Corpus_ptr corpus, Corpus_ptr simple_corpus){
    if (corpus_number_of_words(corpus) != 826680){
        printf("Error in number of words 1");
    }
    if (corpus_number_of_words(simple_corpus) != 24){
        printf("Error in number of words 2");
    }
}

void testContains(Corpus_ptr corpus, Corpus_ptr simple_corpus){
    if (!corpus_contains(corpus, "atatürk")){
        printf("Error in contains 1");
    }
    if (!corpus_contains(simple_corpus, "mehmet")){
        printf("Error in contains 2");
    }
}

void testWordCount(Corpus_ptr corpus, Corpus_ptr simple_corpus){
    if (corpus_word_count(corpus) != 98199){
        printf("Error in word count 1");
    }
    if (corpus_word_count(simple_corpus) != 12){
        printf("Error in word count 2");
    }
}

void testGetCount(Corpus_ptr corpus, Corpus_ptr simple_corpus){
    if (corpus_get_count(corpus, create_word("mustafa")) != 309){
        printf("Error in get count 1");
    }
    if (corpus_get_count(corpus, create_word("kemal")) != 109){
        printf("Error in get count 2");
    }
    if (corpus_get_count(corpus, create_word("atatürk")) != 122){
        printf("Error in get count 3");
    }
    if (corpus_get_count(simple_corpus, create_word("ali")) != 4){
        printf("Error in get count 4");
    }
    if (corpus_get_count(simple_corpus, create_word("gitti")) != 3){
        printf("Error in get count 5");
    }
    if (corpus_get_count(simple_corpus, create_word("at")) != 4){
        printf("Error in get count 6");
    }
}

void testSentenceCount(Corpus_ptr corpus, Corpus_ptr simple_corpus) {
    if (corpus_sentence_count(corpus) != 50000) {
        printf("Error in sentence count 1");
    }
    if (corpus_sentence_count(simple_corpus) != 5) {
        printf("Error in sentence count 2");
    }
}

void testMaxSentenceLength(Corpus_ptr corpus, Corpus_ptr simple_corpus) {
    if (corpus_max_sentence_length(corpus) != 1092) {
        printf("Error in max sentence length 1");
    }
    if (corpus_max_sentence_length(simple_corpus) != 6) {
        printf("Error in max sentence length 2");
    }
}

int main(){
    Corpus_ptr corpus = create_corpus2("corpus.txt");
    Corpus_ptr simple_corpus = create_corpus2("simplecorpus.txt");
    testNumberOfWords(corpus, simple_corpus);
    testContains(corpus, simple_corpus);
    testWordCount(corpus, simple_corpus);
    testGetCount(corpus, simple_corpus);
    testSentenceCount(corpus, simple_corpus);
    testMaxSentenceLength(corpus, simple_corpus);
    free_corpus(corpus);
    free_corpus(simple_corpus);
}