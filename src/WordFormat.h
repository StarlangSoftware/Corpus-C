//
// Created by Olcay Taner YILDIZ on 3.04.2023.
//

#ifndef CORPUS_WORDFORMAT_H
#define CORPUS_WORDFORMAT_H

enum word_format{
    /**
 * Surface/Original form
 */
    SURFACE,
    /**
     * Create 2-Gram words as output.
     */
    LETTER_2,
    /**
     * Create 3-Gram words as output.
     */
    LETTER_3,
    /**
     * Create 4-Gram words as output.
     */
    LETTER_4
};

typedef enum word_format Word_format;

#endif //CORPUS_WORDFORMAT_H
