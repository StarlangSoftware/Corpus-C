//
// Created by Olcay Taner YILDIZ on 20.05.2023.
//
#include <stdlib.h>
#include <Dictionary/Word.h>
#include <FileUtils.h>
#include <string.h>
#include "Sentence.h"
#include "Memory/Memory.h"

/**
 * An empty constructor of Sentence class. Creates an vector of words.
 */
Sentence_ptr create_sentence() {
    Sentence_ptr result = malloc_(sizeof(Sentence), "create_sentence");
    result->words = create_array_list();
    return result;
}

/**
 * Frees memory allocated for sentence. Frees words array list.
 * @param sentence Current sentence.
 */
void free_sentence(Sentence_ptr sentence) {
    free_array_list(sentence->words, (void (*)(void *)) free_);
    free_(sentence);
}

/**
 * Another constructor of Sentence class which takes a file as an input. It reads each word in the file
 * and adds to words vector.
 *
 * @param infile input file to read words from.
 */
Sentence_ptr create_sentence2(FILE *infile) {
    Sentence_ptr result = read_sentence(infile);
    fclose(infile);
    return result;
}

/**
 * Reads a sentence from an input file. Returns the sentence.
 * @param infile Input file.
 * @return Sentence read.
 */
Sentence_ptr read_sentence(FILE *infile) {
    Array_list_ptr tokens = read_items(infile, ' ');
    if (tokens->size == 0){
        free_array_list(tokens, free_);
        return NULL;
    }
    Sentence_ptr result = malloc_(sizeof(Sentence), "read_sentence");
    result->words = create_array_list();
    for (int i = 0; i < tokens->size; i++){
        array_list_add(result->words, array_list_get(tokens, i));
    }
    free_array_list(tokens, NULL);
    return result;
}


/**
 * Reads a sentence from an input file. Checks also each token for validity. If the token is not valid, it is not added
 * to the sentence. Returns the sentence.
 * @param infile Input file.
 * @param is_valid_word Method checking the validity of a word.
 * @return Sentence read.
 */
Sentence_ptr read_sentence2(FILE *infile, bool (*is_valid_word)(const char *)) {
    Array_list_ptr tokens = read_items(infile, ' ');
    if (tokens->size == 0){
        free_array_list(tokens, free_);
        return NULL;
    }
    Sentence_ptr result = malloc_(sizeof(Sentence), "read_sentence2");
    result->words = create_array_list();
    for (int i = 0; i < tokens->size; i++){
        if (is_valid_word(array_list_get(tokens, i))){
            array_list_add(result->words, array_list_get(tokens, i));
        }
    }
    free_array_list(tokens, NULL);
    return result;
}

/**
 * Another constructor of Sentence class which takes a sentence String as an input. It parses the sentence by
 * " " and adds each word to the newly created vector words.
 *
 * @param sentence String input to parse.
 */
Sentence_ptr create_sentence3(char* sentence) {
    Array_list_ptr tokens = str_split(sentence, ' ');
    Sentence_ptr result = malloc_(sizeof(Sentence), "create_sentence3");
    result->words = create_array_list();
    for (int i = 0; i < tokens->size; i++){
        char* string = array_list_get(tokens, i);
        array_list_add(result->words, string);
    }
    free_array_list(tokens, NULL);
    return result;
}

/**
 * Another constructor of Sentence class with two inputs; a String sentence and a LanguageChecker
 * languageChecker. It parses a sentence by " " and then check the language considerations. If it is a valid word,
 * it adds this word to the newly created vector words.
 *
 * @param sentence        String input.
 * @param is_valid_word  Checks if the word is valid or not.
 */

/**
 * The getWord method takes an index input and gets the word at that index.
 *
 * @param index is used to get the word.
 * @return the word in given index.
 */
char* sentence_get_word(const Sentence* sentence, int index) {
    return array_list_get(sentence->words, index);
}

/**
 * The getWords method returns the vector words.
 *
 * @return words vector.
 */
Array_list_ptr sentence_get_words(const Sentence* sentence) {
    return sentence->words;
}

/**
 * The getIndex method takes a word as an input and finds the index of that word in the words ArrayList if it exists.
 *
 * @param word Word type input to search for.
 * @return index of the found input, -1 if not found.
 */
int sentence_get_index(const Sentence* sentence, const char* word) {
    for (int i = 0; i < sentence->words->size; i++){
        char* current = array_list_get(sentence->words, i);
        if (strcmp(current, word) == 0){
            return i;
        }
    }
    return -1;
}

/**
 * The wordCount method finds the size of the words vector.
 *
 * @return the size of the words vector.
 */
int sentence_word_count(const Sentence* sentence) {
    return sentence->words->size;
}

/**
 * The addWord method takes a word as an input and adds this word to the words vector.
 *
 * @param word Word to add words vector.
 */
void sentence_add_word(Sentence_ptr sentence, char* word) {
    array_list_add(sentence->words, word);
}

/**
 * The charCount method finds the total number of chars in each word of words vector.
 *
 * @return sum of the chars.
 */
int sentence_char_count(const Sentence* sentence) {
    int sum = 0;
    for (int i = 0; i < sentence->words->size; i++){
        char* word = array_list_get(sentence->words, i);
        sum += char_count(word);
    }
    return sum;
}

/**
 * The replaceWord method takes an index and a word as inputs. It removes the word at given index from words
 * vector and then adds the given word to given index of words.
 *
 * @param i       index.
 * @param newWord to add the words vector.
 */
void sentence_replace_word(Sentence_ptr sentence, int i, char* new_word){
    array_list_replace(sentence->words, i, new_word, (void (*)(void *)) free_);
}

/**
 * The insertWord method takes an index and a word as inputs. It inserts the word at given index to words
 * ArrayList.
 *
 * @param i       index.
 * @param newWord to add the words ArrayList.
 */
void sentence_insert_word(Sentence_ptr sentence, int i, char* new_word) {
    array_list_insert(sentence->words, i, new_word);
}

/**
 * The safeIndex method takes an index as an input and checks whether this index is between 0 and the size of the words.
 *
 * @param index is used to check the safety.
 * @return true if an index is safe, false otherwise.
 */
bool sentence_safe_index(const Sentence* sentence, int index) {
    return index >= 0 && index < sentence->words->size;
}

/**
 * The toWords method returns an accumulated string of each word's names in words ArrayList.
 *
 * @return String result which has all the names of each item in words ArrayList.
 */
String_ptr to_words(const Sentence* sentence) {
    char* word = array_list_get(sentence->words, 0);
    String_ptr result = create_string2(word);
    for (int i = 1; i < sentence->words->size; i++){
        word = array_list_get(sentence->words, i);
        string_append_char(result, ' ');
        string_append(result, word);
    }
    return result;
}

/**
 * The sentence_to_string method returns an accumulated string of each word's names in words ArrayList.
 *
 * @return String result which has all the names of each item in words ArrayList.
 */
char* sentence_to_string(const Sentence* sentence) {
    char tmp[MAX_LINE_LENGTH];
    sprintf(tmp, "%s", (char*) array_list_get(sentence->words, 0));
    for (int i = 1; i < sentence->words->size; i++){
        char* word = array_list_get(sentence->words, i);
        sprintf(tmp, "%s %s", tmp, word);
    }
    return clone_string(tmp);
}

/**
 * Clones a word and adds it to the sentence.
 * @param sentence Sentence to be added.
 * @param word Word to be cloned.
 */
void sentence_add_word_copy(Sentence_ptr sentence, char *word) {
    char* copy = str_copy(copy, word);
    array_list_add(sentence->words, copy);
}
