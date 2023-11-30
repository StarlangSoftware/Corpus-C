//
// Created by Olcay Taner YILDIZ on 22.05.2023.
//

#ifndef CORPUS_SENTENCESPLITTER_H
#define CORPUS_SENTENCESPLITTER_H

#include <ArrayList.h>
#include "StringUtils.h"

static char *SEPARATORS = "\n()[]{}\"'\u05F4\uFF02\u055B’”‘“–\u00AD\u200B\t&\u2009\u202F\uFEFF";
static char *SENTENCE_ENDERS = ".?!…";
static char *PUNCTUATION_CHARACTERS = ",:;‚";
static char *APOSTROPHES = "'’‘\u055B";

bool shortcut_list_contains(const Array_list* shortcuts, const char* current_word);

bool is_next_char_upper_case_or_digit(const char* upper_case_letters, const char* line, int i);

bool is_previous_word_upper_case(const char* lower_case_letters, const char* upper_case_letters, const char* line, int i);

bool is_next_char_upper_case(const char* upper_case_letters, const char* line, int i);

bool is_name_shortcut(const char* upper_case_letters, const char* current_word);

String_ptr repeat_control(const char* word, bool exceptionMode);

bool is_apostrophe(const char* lower_case_letters, const char* upper_case_letters, const char* line, int i);

bool number_exists_before_and_after(const char* line, int i);

bool is_in_time_string(const char* line, int i);

Array_list_ptr sentence_split(const char* upper_case_letters, const char* lower_case_letters, const Array_list* shortcuts, const char* line);

bool is_digit(const char *line, int index);

bool is_equal_to_char(const char *line, int index, char* _ch);

#endif //CORPUS_SENTENCESPLITTER_H
