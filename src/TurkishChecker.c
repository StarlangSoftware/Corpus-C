//
// Created by Olcay Taner YILDIZ on 22.05.2023.
//

#include <Language/TurkishLanguage.h>
#include <Language/Language.h>
#include <Dictionary/Word.h>
#include <string.h>
#include "TurkishChecker.h"
#include "SentenceSplitter.h"

/**
 * The isValidWord method takes an input String as a word than define all valid characters as a validCharacters String which has
 * letters (abcçdefgğhıijklmnoöprsştuüvyzABCÇDEFGĞHIİJKLMNOÖPRSŞTUÜVYZ),
 * extended language characters (âàáäãèéêëíîòóôûúqwxÂÈÉÊËÌÒÛQWX),
 * digits (0123456789),
 * separators ({@literal ()[]{}"'״＂՛}),
 * sentence enders (.?!…),
 * arithmetic chars (+-/=\*),
 * punctuation chars (,:;),
 * special-meaning chars
 * <p>
 * Then, loops through input word's each char and if a char in word does not in the validCharacters string it returns
 * false, true otherwise.
 *
 * @param word String to check validity.
 * @return true if each char in word is valid, false otherwise.
 */
bool turkish_checker_is_valid_word(const char *word) {
    char *specialMeaningCharacters = "$\\_|@%#£§&><";
    for (int i = 0; i < word_size(word); i++) {
        String_ptr string = char_at(word, i);
        if (strstr(LETTERS, string->s) == NULL
            && strstr(EXTENDED_LANGUAGE_CHARACTERS, string->s) == NULL
            && strstr(DIGITS, string->s) == NULL
            && strstr(SEPARATORS, string->s) == NULL
            && strstr(SENTENCE_ENDERS, string->s) == NULL
            && strstr(ARITHMETIC_CHARACTERS, string->s) == NULL
            && strstr(PUNCTUATION_CHARACTERS, string->s) == NULL
            && strstr(specialMeaningCharacters, string->s) == NULL) {
            return false;
        }
        free_string_ptr(string);
    }
    return true;
}
