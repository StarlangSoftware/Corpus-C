//
// Created by Olcay Taner YILDIZ on 20.05.2023.
//

#include <Memory/Memory.h>
#include "Paragraph.h"
#include "Sentence.h"

/**
 * A constructor of Paragraph class which creates an vector sentences.
 */
Paragraph_ptr create_paragraph() {
    Paragraph_ptr result = malloc_(sizeof(Paragraph), "create_paragraph");
    result->sentences = create_array_list();
    return result;
}

/**
 * Frees memory allocated for paragraph. Frees memory for sentences.
 * @param paragraph Current paragraph.
 */
void free_paragraph(Paragraph_ptr paragraph) {
    free_array_list(paragraph->sentences, (void (*)(void *)) free_sentence);
    free_(paragraph);
}

/**
 * The addSentence method adds given sentence to sentences vector.
 *
 * @param paragraph Current paragraph.
 * @param sentence Sentence type input to add sentences.
 */
void paragraph_add_sentence(Paragraph_ptr paragraph, Sentence_ptr sentence) {
    array_list_add(paragraph->sentences, sentence);
}

/**
 * The sentenceCount method finds the size of the vector sentences.
 *
 * @param paragraph Current paragraph.
 * @return the size of the vector sentences.
 */
int paragraph_sentence_count(const Paragraph* paragraph) {
    return paragraph->sentences->size;
}

/**
 * The getSentence method finds the sentence from sentences ArrayList at given index.
 *
 * @param paragraph Current paragraph.
 * @param index used to get a sentence.
 * @return sentence at given index.
 */
Sentence_ptr paragraph_get_sentence(const Paragraph* paragraph, int index) {
    return array_list_get(paragraph->sentences, index);
}
