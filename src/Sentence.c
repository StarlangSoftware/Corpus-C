//
// Created by Olcay Taner YILDIZ on 20.05.2023.
//
#include <stdlib.h>
#include <Dictionary/Word.h>
#include <FileUtils.h>
#include <string.h>
#include "Sentence.h"

/**
 * An empty constructor of {@link Sentence} class. Creates an {@link vector} of words.
 */
Sentence_ptr create_sentence() {
    Sentence_ptr result = malloc(sizeof(Sentence));
    result->words = create_array_list();
    return result;
}

void free_sentence(Sentence_ptr sentence) {
    free_array_list(sentence->words, (void (*)(void *)) free_word);
    free(sentence);
}

/**
 * Another constructor of {@link Sentence} class which takes a file as an input. It reads each word in the file
 * and adds to words {@link vector}.
 *
 * @param infile input file to read words from.
 */
Sentence_ptr create_sentence2(FILE *infile) {
    Sentence_ptr result = read_sentence(infile);
    fclose(infile);
    return result;
}

Sentence_ptr read_sentence(FILE *infile) {
    Array_list_ptr tokens = read_items(infile, ' ');
    if (tokens->size == 0){
        free_array_list(tokens, free);
        return NULL;
    }
    Sentence_ptr result = malloc(sizeof(Sentence));
    result->words = create_array_list();
    for (int i = 0; i < tokens->size; i++){
        array_list_add(result->words, create_word(array_list_get(tokens, i)));
    }
    free_array_list(tokens, free);
    return result;
}


Sentence_ptr read_sentence2(FILE *infile, bool (*is_valid_word)(const char *)) {
    Array_list_ptr tokens = read_items(infile, ' ');
    if (tokens->size == 0){
        free_array_list(tokens, free);
        return NULL;
    }
    Sentence_ptr result = malloc(sizeof(Sentence));
    result->words = create_array_list();
    for (int i = 0; i < tokens->size; i++){
        if (is_valid_word(array_list_get(tokens, i))){
            array_list_add(result->words, create_word(array_list_get(tokens, i)));
        }
    }
    free_array_list(tokens, free);
    return result;
}

/**
 * Another constructor of {@link Sentence} class which takes a sentence String as an input. It parses the sentence by
 * " " and adds each word to the newly created {@link vector} words.
 *
 * @param sentence String input to parse.
 */
Sentence_ptr create_sentence3(char* sentence) {
    Array_list_ptr tokens = split(sentence);
    Sentence_ptr result = malloc(sizeof(Sentence));
    result->words = create_array_list();
    for (int i = 0; i < tokens->size; i++){
        String_ptr string = array_list_get(tokens, i);
        array_list_add(result->words, create_word(string->s));
    }
    free_array_list(tokens, (void (*)(void *)) free_string_ptr);
    return result;
}

/**
 * Another constructor of {@link Sentence} class with two inputs; a String sentence and a {@link LanguageChecker}
 * languageChecker. It parses a sentence by " " and then check the language considerations. If it is a valid word,
 * it adds this word to the newly created {@link vector} words.
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
Word_ptr sentence_get_word(const Sentence* sentence, int index) {
    return array_list_get(sentence->words, index);
}

/**
 * The getWords method returns the {@link vector} words.
 *
 * @return words vector.
 */
Array_list_ptr sentence_get_words(const Sentence* sentence) {
    return sentence->words;
}

/**
 * The getIndex method takes a word as an input and finds the index of that word in the words {@link ArrayList} if it exists.
 *
 * @param word Word type input to search for.
 * @return index of the found input, -1 if not found.
 */
int sentence_get_index(const Sentence* sentence, const Word* word) {
    for (int i = 0; i < sentence->words->size; i++){
        Word_ptr current = array_list_get(sentence->words, i);
        if (strcmp(current->name, word->name) == 0){
            return i;
        }
    }
    return -1;
}

/**
 * The wordCount method finds the size of the words {@link vector}.
 *
 * @return the size of the words {@link vector}.
 */
int sentence_word_count(const Sentence* sentence) {
    return sentence->words->size;
}

/**
 * The addWord method takes a word as an input and adds this word to the words {@link vector}.
 *
 * @param word Word to add words {@link vector}.
 */
void sentence_add_word(Sentence_ptr sentence, Word_ptr word) {
    array_list_add(sentence->words, word);
}

/**
 * The charCount method finds the total number of chars in each word of words {@link vector}.
 *
 * @return sum of the chars.
 */
int sentence_char_count(const Sentence* sentence) {
    int sum = 0;
    for (int i = 0; i < sentence->words->size; i++){
        Word_ptr word = array_list_get(sentence->words, i);
        sum += char_count(word);
    }
    return sum;
}

/**
 * The replaceWord method takes an index and a word as inputs. It removes the word at given index from words
 * {@link vector} and then adds the given word to given index of words.
 *
 * @param i       index.
 * @param newWord to add the words {@link vector}.
 */
void sentence_replace_word(Sentence_ptr sentence, int i, Word_ptr new_word){
    array_list_replace(sentence->words, i, new_word, (void (*)(void *)) free_word);
}

/**
 * The insertWord method takes an index and a word as inputs. It inserts the word at given index to words
 * {@link ArrayList}.
 *
 * @param i       index.
 * @param newWord to add the words {@link ArrayList}.
 */
void sentence_insert_word(Sentence_ptr sentence, int i, Word_ptr new_word) {
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
 * The toWords method returns an accumulated string of each word's names in words {@link ArrayList}.
 *
 * @return String result which has all the names of each item in words {@link ArrayList}.
 */
String_ptr to_words(const Sentence* sentence) {
    Word_ptr word = array_list_get(sentence->words, 0);
    String_ptr result = create_string2(word->name);
    for (int i = 1; i < sentence->words->size; i++){
        word = array_list_get(sentence->words, i);
        string_append_char(result, ' ');
        string_append(result, word->name);
    }
    return result;
}
