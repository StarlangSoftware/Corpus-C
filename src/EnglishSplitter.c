//
// Created by Olcay Taner YILDIZ on 29.05.2023.
//

#include <stddef.h>
#include "EnglishSplitter.h"
#include "SentenceSplitter.h"
#include "Language/EnglishLanguage.h"

/**
 * Returns shortcut words in English language as an array list.
 * @param line Shortcut word list.
 * @return Shortcut words in English language as an array list.
 */
Array_list_ptr sentence_split_english(const char *line) {
    Array_list_ptr shortcuts = create_array_list();
    array_list_add(shortcuts, "dr");
    array_list_add(shortcuts, "prof");
    array_list_add(shortcuts, "org");
    array_list_add(shortcuts, "II");
    array_list_add(shortcuts, "III");
    array_list_add(shortcuts, "IV");
    array_list_add(shortcuts, "VI");
    array_list_add(shortcuts, "VII");
    array_list_add(shortcuts, "VIII");
    array_list_add(shortcuts, "IX");
    array_list_add(shortcuts, "X");
    array_list_add(shortcuts, "XI");
    array_list_add(shortcuts, "XII");
    array_list_add(shortcuts, "XIII");
    array_list_add(shortcuts, "XIV");
    array_list_add(shortcuts, "XV");
    array_list_add(shortcuts, "XVI");
    array_list_add(shortcuts, "XVII");
    array_list_add(shortcuts, "XVIII");
    array_list_add(shortcuts, "XIX");
    array_list_add(shortcuts, "XX");
    array_list_add(shortcuts, "min");
    array_list_add(shortcuts, "km");
    array_list_add(shortcuts, "jr");
    array_list_add(shortcuts, "mrs");
    array_list_add(shortcuts, "sir");
    Array_list_ptr result = sentence_split(ENGLISH_UPPERCASE_LETTERS, ENGLISH_LOWERCASE_LETTERS, shortcuts, line);
    free_array_list(shortcuts, NULL);
    return result;
}
