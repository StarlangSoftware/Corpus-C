//
// Created by Olcay Taner YILDIZ on 20.05.2023.
//

#include <string.h>
#include "../src/Sentence.h"

void test_get_word(){
    char s[] = "ali topu at mehmet ayşeyle gitti";
    Sentence_ptr sentence = create_sentence3(s);
    if (strcmp(sentence_get_word(sentence, 0)->name, "ali") != 0){
        printf("Error in test_get_word 1");
    }
    if (strcmp(sentence_get_word(sentence, 2)->name, "at") != 0){
        printf("Error in test_get_word 2");
    }
    if (strcmp(sentence_get_word(sentence, 5)->name, "gitti") != 0){
        printf("Error in test_get_word 3");
    }
    free_sentence(sentence);
}

void test_get_index(){
    char s[] = "ali topu at mehmet ayşeyle gitti";
    Sentence_ptr sentence = create_sentence3(s);
    if (sentence_get_index(sentence, create_word("ali")) != 0){
        printf("Error in test_get_index 1");
    }
    if (sentence_get_index(sentence, create_word("at")) != 2){
        printf("Error in test_get_index 2");
    }
    if (sentence_get_index(sentence, create_word("gitti")) != 5){
        printf("Error in test_get_index 3");
    }
    free_sentence(sentence);
}

void test_word_count() {
    char s[] = "ali topu at mehmet ayşeyle gitti";
    Sentence_ptr sentence = create_sentence3(s);
    if (sentence_word_count(sentence) != 6){
        printf("Error in test_word_count");
    }
    free_sentence(sentence);
}

void test_char_count() {
    char s[] = "ali topu at mehmet ayşeyle gitti";
    Sentence_ptr sentence = create_sentence3(s);
    if (sentence_char_count(sentence) != 27){
        printf("Error in test_char_count");
    }
    free_sentence(sentence);
}

int main(){
    test_get_word();
    test_get_index();
    test_word_count();
    test_char_count();
}