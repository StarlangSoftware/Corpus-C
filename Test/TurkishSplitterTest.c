//
// Created by Olcay Taner YILDIZ on 29.05.2023.
//

#include <ArrayList.h>
#include <stdio.h>
#include <string.h>
#include <Memory/Memory.h>

#include "../src/TurkishSplitter.h"
#include "../src/Sentence.h"

void testSplit1(){
    Array_list_ptr result = sentence_split_turkish(":Cin Ali, bak! At. "
                                                   "Bak, Cin Ali, bak. "
                                                   "Bu at. "
                                                   "Baba, o atı bana al. "
                                                   "Cin Ali, bu at. "
                                                   "O da ot. "
                                                   "Baba, bu ata ot al. "
                                                   "Cin Ali, bu ot, o da at. "
                                                   "Otu al, ata ver. "
                                                   "Bak, Suna! "
                                                   "Cin Ali, ata ot verdi. "
                                                   "Su verdi. "
                                                   "Cin Ali, ata bir kova da su verdi.");
    if (result->size != 14){
        printf("Error in test split 1");
    }
    free_array_list(result, (void (*)(void *)) free_sentence);
}

void testSplit2(){
    Array_list_ptr result = sentence_split_turkish("WWW.GOOGLE.COM");
    if (result->size != 1){
        printf("Error in test split 2");
    }
    free_array_list(result, (void (*)(void *)) free_sentence);
}

void testSplit3(){
    Array_list_ptr result = sentence_split_turkish("www.google.com");
    if (result->size != 1){
        printf("Error in test split 3");
    }
    free_array_list(result, (void (*)(void *)) free_sentence);
}

void testSplit4(){
    Array_list_ptr result = sentence_split_turkish("1. adımda ve 2. adımda ne yaptın");
    if (result->size != 1){
        printf("Error in test split 4");
    }
    free_array_list(result, (void (*)(void *)) free_sentence);
}

void testSplit5(){
    Array_list_ptr result = sentence_split_turkish("1.adımda ve 2.adımda ne yaptın");
    if (result->size != 1){
        printf("Error in test split 5");
    }
    free_array_list(result, (void (*)(void *)) free_sentence);
}

void testSplit6(){
    Array_list_ptr result = sentence_split_turkish("Burada II. Murat ve I. Ahmet oyun oynadı");
    if (result->size != 1){
        printf("Error in test split 6");
    }
    free_array_list(result, (void (*)(void *)) free_sentence);
}

void testSplit7(){
    Array_list_ptr result = sentence_split_turkish("1.87 cm boyunda ve 84 kg ağırlığındaydı");
    if (result->size != 1){
        printf("Error in test split 7");
    }
    free_array_list(result, (void (*)(void *)) free_sentence);
}

void testSplit8(){
    Array_list_ptr result = sentence_split_turkish("AA piller, AAA pillerin yaklaşık üç kat kapasitesine sahiptir");
    Sentence_ptr sentence = array_list_get(result, 0);
    if (strcmp(sentence_get_word(sentence, 3), "AAA") != 0){
        printf("Error in test split 8 with word AAA");
    }
    free_array_list(result, (void (*)(void *)) free_sentence);
    result = sentence_split_turkish("Topu atıp yakalaaaa diye bağırdı");
    sentence = array_list_get(result, 0);
    if (strcmp(sentence_get_word(sentence, 2), "yakala") != 0){
        printf("Error in test split 8 with word yakala");
    }
    free_array_list(result, (void (*)(void *)) free_sentence);
}

void testSplit9() {
    Array_list_ptr result = sentence_split_turkish("Bunun yanı sıra erkek t-shirt modellerini klasik giyim tarzına uyarlayarak kullanmak da mümkündür");
    Sentence_ptr sentence = array_list_get(result, 0);
    if (sentence_word_count(sentence) != 13){
        printf("Error in test split 9 in sentence 1");
    }
    free_array_list(result, (void (*)(void *)) free_sentence);
    result = sentence_split_turkish("USB-C, USB-A’ya göre çok daha yüksek hızlarda aktarım sağlayabilir");
    sentence = array_list_get(result, 0);
    if (sentence_word_count(sentence) != 10){
        printf("Error in test split 9 in sentence 2");
    }
    free_array_list(result, (void (*)(void *)) free_sentence);
}

int main(){
    testSplit1();
    testSplit2();
    testSplit3();
    testSplit4();
    testSplit5();
    testSplit6();
    testSplit7();
    testSplit8();
    testSplit9();
}