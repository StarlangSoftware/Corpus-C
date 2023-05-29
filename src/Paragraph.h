//
// Created by Olcay Taner YILDIZ on 20.05.2023.
//

#ifndef CORPUS_PARAGRAPH_H
#define CORPUS_PARAGRAPH_H

#include <ArrayList.h>
#include "Sentence.h"

struct paragraph {
    Array_list_ptr sentences;
};

typedef struct paragraph Paragraph;
typedef Paragraph *Paragraph_ptr;

Paragraph_ptr create_paragraph();

void free_paragraph(Paragraph_ptr paragraph);

void paragraph_add_sentence(Paragraph_ptr paragraph, Sentence_ptr sentence);

int paragraph_sentence_count(const Paragraph* paragraph);

Sentence_ptr paragraph_get_sentence(const Paragraph* paragraph, int index);

#endif //CORPUS_PARAGRAPH_H
