//
// Created by Olcay Taner YILDIZ on 20.05.2023.
//

#include <stdlib.h>
#include <stdio.h>
#include <FileUtils.h>
#include <Memory/Memory.h>
#include "Corpus.h"
#include "Dictionary/Word.h"
#include "Sentence.h"

/**
 * A constructor of Corpus class which creates new ArrayList for sentences and a CounterHashMap
 * for wordList.
 */
Corpus_ptr create_corpus() {
    Corpus_ptr result = malloc_(sizeof(Corpus), "create_corpus");
    result->sentences = create_array_list();
    result->paragraphs = create_array_list();
    result->word_list = create_counter_hash_map((unsigned int (*)(const void *, int)) hash_function_string,
                                                (int (*)(const void *, const void *)) compare_string);
    return result;
}

/**
 * Another constructor of Corpus class which takes a file name as an input. Then reads the input file line by line
 * and calls addSentence method with each read line.
 *
 * @param fileName String file name input that will be read.
 */
Corpus_ptr create_corpus2(const char *file_name) {
    Corpus_ptr result = create_corpus();
    FILE *infile = fopen(file_name, "r");
    result->file_name = str_copy(result->file_name, file_name);
    Sentence_ptr sentence = read_sentence(infile);
    while (sentence != NULL) {
        corpus_add_sentence(result, sentence);
        sentence = read_sentence(infile);
    }
    fclose(infile);
    return result;
}

/**
 * Another constructor of Corpus class which also takes is_valid_word input besides file name input.
 * It reads input file line by line and add each sentence also by using the is_valid_word input which simply checks
 * the validity of the sentence.
 *
 * @param fileName        String file name input that will be read.
 * @param is_valid_word Method that checks the validity of a word.
 */
Corpus_ptr create_corpus3(const char *file_name, bool (*is_valid_word)(const char *)) {
    Corpus_ptr result = create_corpus();
    FILE *infile = fopen(file_name, "r");
    result->file_name = str_copy(result->file_name, file_name);
    Sentence_ptr sentence = read_sentence2(infile, is_valid_word);
    while (sentence != NULL) {
        corpus_add_sentence(result, sentence);
        sentence = read_sentence2(infile, is_valid_word);
    }
    fclose(infile);
    return result;
}

/**
 * Another constructor of Corpus class which takes sentence_splitter  as an input besides the file name.
 * It reads input file line by line and calls the sentence_splitter method with each line, then calls addSentence method
 * with each sentence.
 *
 * @param fileName         String file name input that will be read.
 * @param sentence_splitter Method that splits the line read and splits the words.
 */
Corpus_ptr create_corpus4(const char *file_name, Array_list_ptr (*sentence_splitter)(const char *)) {
    char line[MAX_LINE_LENGTH];
    Corpus_ptr result = create_corpus();
    FILE *input_file = fopen(file_name, "r");
    result->file_name = str_copy(result->file_name, file_name);
    char* input = fgets(line, MAX_LINE_LENGTH, input_file);
    while (input != NULL){
        Array_list_ptr _sentences = sentence_splitter(line);
        Paragraph_ptr paragraph = create_paragraph();
        for (int i = 0; i < _sentences->size; i++){
            paragraph_add_sentence(paragraph, array_list_get(_sentences, i));
        }
        free_array_list(_sentences, NULL);
        corpus_add_paragraph(result, paragraph);
        input = fgets(line, MAX_LINE_LENGTH, input_file);
    }
    fclose(input_file);
    return result;
}

/**
 * Frees memory allocated for corpus. Frees memory for sentences, paragraphs, and word_list hash map.
 * @param corpus
 */
void free_corpus(Corpus_ptr corpus) {
    free_(corpus->file_name);
    free_array_list(corpus->sentences, (void (*)(void *)) free_sentence);
    free_array_list(corpus->paragraphs, (void (*)(void *)) free_paragraph);
    free_counter_hash_map(corpus->word_list);
    free_(corpus);
}

/**
 * The combine method takes a Corpus as an input and adds each sentence of sentences ArrayList.
 *
 * @param corpus Corpus type input.
 */
void corpus_combine(Corpus_ptr corpus1, const Corpus* corpus2) {
    for (int i = 0; i < corpus2->sentences->size; i++) {
        corpus_add_sentence(corpus1, array_list_get(corpus2->sentences, i));
    }
}

/**
 * The addSentence method takes a Sentence as an input. It adds given input to sentences ArrayList and loops
 * through the each word in sentence and puts these words into wordList CounterHashMap.
 *
 * @param s Sentence type input that will be added to sentences ArrayList and its words will be added to wordList
 *          CounterHashMap.
 */
void corpus_add_sentence(Corpus_ptr corpus, Sentence_ptr sentence) {
    array_list_add(corpus->sentences, sentence);
    for (int i = 0; i < sentence->words->size; i++) {
        put_counter_hash_map(corpus->word_list, sentence_get_word(sentence, i));
    }
}

/**
 * The numberOfWords method loops through the sentences ArrayList and accumulates the number of words in sentence.
 *
 * @return size which holds the total number of words.
 */
int corpus_number_of_words(const Corpus* corpus) {
    int size = 0;
    for (int i = 0; i < corpus->sentences->size; i++) {
        Sentence_ptr sentence = array_list_get(corpus->sentences, i);
        size += sentence_word_count(sentence);
    }
    return size;
}

/**
 * The contains method takes a String word as an input and checks whether wordList CounterHashMap has the
 * given word and returns true if so, otherwise returns false.
 *
 * @param word String input to check.
 * @return true if wordList has the given word, false otherwise.
 */
bool corpus_contains(const Corpus* corpus, const char *word) {
    return hash_map_contains(corpus->word_list->map, word);
}

/**
 * The addParagraph method takes a Paragraph type input. It gets the sentences in the given paragraph and
 * add these to the sentences vector and the words in the sentences to the wordList CounterHashMap.
 *
 * @param p Paragraph type input to add sentences and wordList.
 */
void corpus_add_paragraph(Corpus_ptr corpus, Paragraph_ptr paragraph) {
    array_list_add(corpus->paragraphs, paragraph);
    for (int i = 0; i < paragraph_sentence_count(paragraph); i++) {
        corpus_add_sentence(corpus, paragraph_get_sentence(paragraph, i));
    }
}

/**
 * Getter for the file name.
 *
 * @return file name.
 */
char *corpus_get_file_name(const Corpus* corpus) {
    return corpus->file_name;
}

/**
 * Getter for the wordList.
 *
 * @return the keySet of wordList.
 */
Array_list_ptr corpus_get_word_list(const Corpus* corpus) {
    return key_list(corpus->word_list->map);
}

/**
 * The wordCount method returns the size of the wordList CounterHashMap.
 *
 * @return the size of the wordList CounterHashMap.
 */
int corpus_word_count(const Corpus* corpus) {
    return corpus->word_list->map->count;
}

/**
 * The getCount method returns the count value of given word.
 *
 * @param word Word type input to check.
 * @return the count value of given word.
 */
int corpus_get_count(const Corpus* corpus, const char* word) {
    return count_counter_hash_map(corpus->word_list, word);
}

/**
 * The sentenceCount method returns the size of the sentences ArrayList.
 *
 * @return the size of the sentences ArrayList.
 */
int corpus_sentence_count(const Corpus* corpus) {
    return corpus->sentences->size;
}

/**
 * Getter for getting a sentence at given index.
 *
 * @param index to get sentence from.
 * @return the sentence at given index.
 */
Sentence_ptr corpus_get_sentence(const Corpus* corpus, int index) {
    return array_list_get(corpus->sentences, index);
}

/**
 * The paragraphCount method returns the size of the paragraphs ArrayList.
 *
 * @return the size of the paragraphs ArrayList.
 */
int corpus_paragraph_count(const Corpus* corpus) {
    return corpus->paragraphs->size;
}

/**
 * Getter for getting a paragraph at given index.
 *
 * @param index to get paragraph from.
 * @return the paragraph at given index.
 */
Paragraph_ptr corpus_get_paragraph(const Corpus* corpus, int index) {
    return array_list_get(corpus->paragraphs, index);
}

/**
 * The maxSentenceLength method finds the sentence with the maximum number of words and returns this number.
 *
 * @return maximum length.
 */
int corpus_max_sentence_length(const Corpus* corpus) {
    int max_length = 0;
    for (int i = 0; i < corpus->sentences->size; i++) {
        Sentence_ptr sentence = array_list_get(corpus->sentences, i);
        if (sentence_word_count(sentence) > max_length) {
            max_length = sentence_word_count(sentence);
        }
    }
    return max_length;
}

/**
 * The getAllWordsAsVector method creates new vector of vectors and adds each word in each sentence of sentences
 * vector into new vector.
 *
 * @return newly created and populated vector.
 */
Array_list_ptr get_all_words_as_vector(const Corpus* corpus) {
    Array_list_ptr result = create_array_list();
    for (int i = 0; i < corpus->sentences->size; i++) {
        Sentence_ptr sentence = array_list_get(corpus->sentences, i);
        array_list_add(result, sentence_get_words(sentence));
    }
    return result;
}

/**
 * The shuffleSentences method randomly shuffles sentences ArrayList with given seed value.
 *
 * @param seed value to randomize shuffling.
 */
void shuffle_sentences(Corpus_ptr corpus, int seed) {
    array_list_shuffle(corpus->sentences, seed);
}

/**
 * Returns next sentence in the sentences array list and increments
 * sentence pointer. If there are no sentences to be read, returns null.
 * @return Next sentence in the sentences array.
 */
Sentence_ptr corpus_get_sentence2(Corpus_ptr corpus) {
    int index = corpus->sentence_index;
    if (corpus->sentence_index < corpus->sentences->size) {
        corpus->sentence_index++;
        return array_list_get(corpus->sentences, index);
    }
    return NULL;
}

/**
 * Initializes sentence pointer to zero.
 */
void corpus_open(Corpus_ptr corpus) {
    corpus->sentence_index = 0;
}

/**
 * Initializes sentence pointer to zero.
 */
void corpus_close(Corpus_ptr corpus) {
    corpus->sentence_index = 0;
}

/**
 * The getTrainCorpus method takes two integer inputs foldNo and foldCount for determining train data size and count of fold respectively.
 * Initially creates a new empty Corpus, then finds the sentenceCount as N. Then, starting from the index 0 it loops through
 * the index (foldNo * N) / foldCount and add each sentence of sentences ArrayList to new Corpus. Later on,
 * starting from the index ((foldNo + 1) * N) / foldCount, it loops through the index N and add each sentence of
 * sentences ArrayList to new Corpus.
 *
 * @param foldNo    Integer input for train set size.
 * @param foldCount Integer input for counting fold.
 * @return the newly created and populated Corpus.
 */
Corpus_ptr get_train_corpus(const Corpus* corpus, int foldNo, int foldCount) {
    Corpus_ptr train_corpus = create_corpus();
    int N = corpus_sentence_count(corpus);
    for (int i = 0; i < (foldNo * N) / foldCount; i++) {
        corpus_add_sentence(train_corpus, corpus_get_sentence(corpus, i));
    }
    for (int i = ((foldNo + 1) * N) / foldCount; i < N; i++) {
        corpus_add_sentence(train_corpus, corpus_get_sentence(corpus, i));
    }
    return train_corpus;
}

/**
 * The getTestCorpus method takes two integer inputs foldNo and foldCount for determining test data size and count of
 * fold respectively.. Initially creates a new empty Corpus, then finds the sentenceCount as N.
 * Then, starting from the index (foldNo * N) / foldCount it loops through the index ((foldNo + 1) * N) / foldCount and
 * add each sentence of sentences ArrayList to new Corpus.
 *
 * @param foldNo    Integer input for test size.
 * @param foldCount Integer input counting fold.
 * @return the newly created and populated Corpus.
 */
Corpus_ptr get_test_corpus(const Corpus* corpus, int foldNo, int foldCount) {
    Corpus_ptr test_corpus = create_corpus();
    int N = corpus_sentence_count(corpus);
    for (int i = (foldNo * N) / foldCount; i < ((foldNo + 1) * N) / foldCount; i++) {
        corpus_add_sentence(test_corpus, corpus_get_sentence(corpus, i));
    }
    return test_corpus;
}
