//
// Created by Olcay Taner YILDIZ on 28.05.2023.
//
#include <stdbool.h>
#include <string.h>
#include <Dictionary/Word.h>
#include <Language/Language.h>
#include <RegularExpression.h>
#include <Memory/Memory.h>
#include "SentenceSplitter.h"
#include "Sentence.h"

/**
 * The listContains method has a String array shortcuts which holds the possible abbreviations that might end with a '.' but not a
 * sentence finisher word. It also takes a String as an input and loops through the shortcuts array and returns
 * true if given String has any matching item in the shortcuts array.
 *
 * @param shortcuts Shortcut list
 * @param current_word String input to check.
 * @return true if contains any abbreviations, false otherwise.
 */
bool shortcut_list_contains(const Array_list *shortcuts, const char *current_word) {
    for (int i = 0; i < shortcuts->size; i++) {
        if (strcmp(array_list_get(shortcuts, i), current_word) == 0) {
            return true;
        }
    }
    return false;
}

/**
 * The isNextCharUpperCaseOrDigit method takes a String line and an int i as inputs. First it compares each char in
 * the input line with " " and SEPARATORS ({@literal ()[]{}"'״＂՛}) and increment i by one until a mismatch or end of line.
 * <p>
 * When i equals to line length or contains one of the uppercase letters or digits it returns true, false otherwise.
 *
 * @param line String to check.
 * @param i    int defining starting index.
 * @return true if next char is uppercase or digit, false otherwise.
 */
bool is_next_char_upper_case_or_digit(const char *upper_case_letters, const char *line, int i) {
    bool result = false;
    String_ptr current_char = char_at(line, i);
    while (i < word_size(line) && (string_equals2(current_char, " ") || str_contains(SEPARATORS, current_char->s))) {
        free_string_ptr(current_char);
        i++;
        current_char = char_at(line, i);
    }
    String_ptr upper_case_or_digit = create_string4(upper_case_letters, DIGITS, "-");
    if (i == word_size(line) || string_contains(upper_case_or_digit, current_char)) {
        result = true;
    }
    free_string_ptr(upper_case_or_digit);
    free_string_ptr(current_char);
    return result;
}

/**
 * The isPreviousWordUpperCase method takes a String line and an int i as inputs. First it compares each char in
 * the input line with " " and checks each char whether they are lowercase letters or one of the qxw. And decrement
 * input i by one till this condition is false.
 * <p>
 * When i equals to -1 or contains one of the uppercase letters or one of the QXW it returns true, false otherwise.
 *
 * @param line String to check.
 * @param i    int defining ending index.
 * @return true if previous char is uppercase or one of the QXW, false otherwise.
 */
bool is_previous_word_upper_case(const char *lower_case_letters, const char *upper_case_letters, const char *line,
                                 int i) {
    bool result = false;
    String_ptr current_char = char_at(line, i);
    String_ptr lower_case_w = create_string3(lower_case_letters, "qwx");
    while (i >= 0 && (string_equals2(current_char, " ") || string_contains(lower_case_w, current_char))) {
        i--;
    }
    free_string_ptr(lower_case_w);
    String_ptr upper_case_w = create_string3(upper_case_letters, "QWX");
    if (i == -1 || string_contains(upper_case_w, current_char)) {
        result = true;
    }
    free_string_ptr(upper_case_w);
    free_string_ptr(current_char);
    return result;
}

/**
 * The isNextCharUpperCase method takes a String line and an int i as inputs. First it compares each char in
 * the input line with " " and increment i by one until a mismatch or end of line.
 * <p>
 * When i equals to line length or contains one of the uppercase letters it returns true, false otherwise.
 *
 * @param line String to check.
 * @param i    int defining starting index.
 * @return true if next char is uppercase, false otherwise.
 */
bool is_next_char_upper_case(const char *upper_case_letters, const char *line, int i) {
    bool result = false;
    String_ptr current_char = char_at(line, i);
    while (i < word_size(line) && string_equals2(current_char, " ")) {
        i++;
    }
    String_ptr upper_case = create_string3(upper_case_letters, "\"\'");
    if (i == word_size(line) || string_contains(upper_case, current_char)) {
        result = true;
    }
    free_string_ptr(upper_case);
    free_string_ptr(current_char);
    return result;
}

/**
 * The isNameShortcut method takes a String word as an input. First, if the word length is 1, and currentWord
 * contains UPPERCASE_LETTERS letters than it returns true.
 * <p>
 * Secondly, if the length of the word is 3 (i.e it is a shortcut) and it has a '.' at its 1st index and
 * currentWord's 2nd  index is an uppercase letter it also returns true. (Ex : m.A)
 *
 * @param current_word String input to check whether it is a shortcut.
 * @return true if given input is a shortcut, false otherwise.
 */
bool is_name_shortcut(const char *upper_case_letters, const char *current_word) {
    bool result = false;
    if (word_size(current_word) == 1 && str_contains(upper_case_letters, current_word)) {
        return true;
    }
    String_ptr ch2 = char_at(current_word, 2);
    if (word_size(current_word) == 3 && is_equal_to_char(current_word, 1, ".") && str_contains(
            upper_case_letters, ch2->s)) {
        result = true;
    }
    free_string_ptr(ch2);
    return result;
}

/**
 * The repeatControl method takes a String word as an input, and a boolean exceptionMode and compress the repetitive chars. With
 * the presence of exceptionMode it directly returns the given word. Then it declares a counter i and loops till the end of the
 * given word. It compares the char at index i with the char at index (i+2) if they are equal then it compares the char at index i
 * with the char at index (i+1) and increments i by one and returns concatenated  result String with char at index i.
 *
 * @param word          String input.
 * @param exceptionMode boolean input for exceptional cases.
 * @return String result.
 */
String_ptr repeat_control(const char *word, bool exceptionMode) {
    if (exceptionMode) {
        return create_string2(word);
    }
    int i = 0;
    String_ptr result = create_string();
    while (i < word_size(word)) {
        String_ptr ch1 = char_at(word, i);
        String_ptr ch2 = char_at(word, i + 1);
        String_ptr ch3 = char_at(word, i + 2);
        String_ptr ch4 = char_at(word, i + 3);
        if (i < word_size(word) - 3 && string_equals(ch1, ch2) && string_equals(ch1, ch3) && string_equals(ch1, ch4)) {
            while (i < word_size(word) - 1 && string_equals(ch1, ch2)) {
                i++;
            }
        }
        string_append_s(result, ch1);
        free_string_ptr(ch1);
        free_string_ptr(ch2);
        free_string_ptr(ch3);
        free_string_ptr(ch4);
        i++;
    }
    return result;
}

/**
 * The isApostrophe method takes a String line and an integer i as inputs. Initially declares a String apostropheLetters
 * which consists of abcçdefgğhıijklmnoöprsştuüvyzABCÇDEFGĞHIİJKLMNOÖPRSŞTUÜVYZ, âàáäãèéêëíîòóôûúqwxÂÈÉÊËÌÒÛQWX and 0123456789.
 * Then, it returns true if the result of contains method which checks the existence of previous char and next char
 * at apostropheLetters returns true, returns false otherwise.
 *
 * @param line String input to check.
 * @param i    index.
 * @return true if apostropheLetters contains previous char and next char, false otherwise.
 */
bool is_apostrophe(const char *lower_case_letters, const char *upper_case_letters, const char *line, int i) {
    bool result = false;
    String_ptr apostrophe_letters =
            create_string4(lower_case_letters, upper_case_letters, EXTENDED_LANGUAGE_CHARACTERS);
    string_append(apostrophe_letters, DIGITS);
    if (i > 0 && i + 1 < word_size(line)) {
        String_ptr previous = char_at(line, i - 1);
        String_ptr next = char_at(line, i + 1);
        result = string_contains(apostrophe_letters, previous) && string_contains(apostrophe_letters, next);
        free_string_ptr(previous);
        free_string_ptr(next);
    }
    free_string_ptr(apostrophe_letters);
    return result;
}

/**
 * The numberExistsBeforeAndAfter method takes a String line and an integer i as inputs. Then, it returns true if
 * the result of contains method, which compares the previous char and next char with 0123456789, returns true and
 * false otherwise.
 *
 * @param line String input to check.
 * @param i    index.
 * @return true if previous char and next char is a digit, false otherwise.
 */
bool number_exists_before_and_after(const char *line, int i) {
    bool result = false;
    if (i > 0 && i + 1 < word_size(line)) {
        result = is_digit(line, i - 1) && is_digit(line, i + 1);
    }
    return result;
}

/**
 * The isTime method takes a String line and an integer i as inputs. Then, it returns true if
 * the result of the contains method, which compares the previous char, next char and two next chars with 0123456789,
 * returns true and false otherwise.
 *
 * @param line String input to check.
 * @param i    index.
 * @return true if previous char, next char and two next chars are digit, false otherwise.
 */
bool is_in_time_string(const char *line, int i) {
    bool result = false;
    if (i > 0 && i + 2 < word_size(line)) {
        result = is_digit(line, i - 1) && is_digit(line, i + 1) && is_digit(line, i + 2);
    }
    return result;
}

/**
 * The onlyOneLetterExistsBeforeOrAfter method takes a String line and an integer i as inputs. Then, it returns true if
 * only one letter exists before or after the given index, false otherwise.
 *
 * @param line String input to check.
 * @param i    index.
 * @return true if only one letter exists before or after the given index, false otherwise.
 */
bool only_one_letter_exists_before_or_after(const char *lower_case_letters, const char *upper_case_letters,
                                            const char *line, int i) {
    bool result;
    if (i > 1 && i < word_size(line) - 2) {
        String_ptr two_previous = char_at(line, i - 2);
        String_ptr two_next = char_at(line, i + 2);
        result = str_contains(PUNCTUATION_CHARACTERS, two_previous->s) || str_contains(SEPARATORS, two_previous->s) ||
                 string_equals2(two_previous, " ") || (str_contains(SENTENCE_ENDERS, two_previous->s) || str_contains(
                                                           PUNCTUATION_CHARACTERS, two_next->s) ||
                                                       str_contains(SEPARATORS, two_next->s)) ||
                 string_equals2(two_next, " ") || str_contains(SENTENCE_ENDERS, two_next->s);
        free_string_ptr(two_previous);
        free_string_ptr(two_next);
    } else {
        String_ptr first = char_at(line, 0);
        String_ptr last = char_at(line, word_size(line) - 1);
        if (i == 1 && str_contains(lower_case_letters, first->s) || str_contains(upper_case_letters, first->s)) {
            result = true;
        } else {
            result = i == word_size(line) - 2 && str_contains(lower_case_letters, last->s);
        }
        free_string_ptr(first);
        free_string_ptr(last);
    }
    return result;
}

/**
 * The split method takes a String line as an input. Firstly it creates a new sentence as currentSentence a new ArrayList
 * as sentences. Then loops till the end of the line and checks some conditions;
 * If the char at ith index is a separator;
 * <p>
 * ' : assigns currentWord as currentWord'
 * { : increment the curlyBracketCount
 * } : decrement the curlyBracketCount
 * " : increment the specialQuotaCount
 * " : decrement the specialQuotaCount
 * ( : increment roundParenthesisCount
 * ) : decrement roundParenthesisCount
 * [ : increment bracketCount
 * ] : decrement bracketCount
 * " : assign quotaCount as 1- quotaCount
 * ' : assign apostropheCount as 1- apostropheCount
 * <p>
 * If the currentWord is not empty, it adds the currentWord after repeatControl to currentSentence.
 * <p>
 * If the char at index i is " and  bracketCount, specialQuotaCount, curlyBracketCount, roundParenthesisCount, and
 * quotaCount equal to 0 and also the next char is uppercase or digit, it adds currentSentence to sentences.
 * <p>
 * If the char at ith index is a sentence ender;
 * <p>
 * . and currentWord is www : assigns webMode as true. Ex: www.google.com
 * . and currentWord is a digit or in web or e-mail modes : assigns currentWord as currentWord+char(i) Ex: 1.
 * . and currentWord is a shortcut or an abbreviation : assigns currentWord as currentWord+char(i) and adds currentWord to currentSentence. Ex : bkz.
 * ' and next char is uppercase or digit: add word to currentSentence as ' and add currentSentence to sentences.
 *
 * <p>
 * If the char at index i is ' ', i.e space, add word to currentSentence and assign "" to currentSentence.
 * If the char at index i is -,  add word to currentSentence and add sentences when the wordCount of currentSentence greater than 0.
 * <p>
 * If the char at ith index is a punctuation;
 * : and if currentWord is "https" : assign webMode as true.
 * , and there exists a number before and after : assign currentWord as currentWord+char(i) Ex: 1,2
 * : and if line is a time : assign currentWord as currentWord+char(i) Ex: 12:14:24
 * - and there exists a number before and after : assign currentWord as currentWord+char(i) Ex: 12-1
 * {@literal @} : assign emailMode as true.
 *
 * @param line String input to split.
 * @return sentences ArrayList which holds split line.
 */
Array_list_ptr sentence_split(const char *upper_case_letters, const char *lower_case_letters,
                              const Array_list *shortcuts, const char *line) {
    bool emailMode = false, webMode = false;
    int i = 0, specialQuotaCount = 0, roundParenthesisCount = 0, bracketCount = 0, curlyBracketCount = 0, quotaCount = 0
            , apostropheCount = 0;
    Sentence_ptr currentSentence = create_sentence();
    String_ptr currentWord = create_string();
    Array_list_ptr sentences = create_array_list();
    while (i < word_size(line)) {
        String_ptr ch = char_at(line, i);
        if (str_contains(SEPARATORS, ch->s)) {
            if (str_contains(HYPHENS, ch->s) && only_one_letter_exists_before_or_after(
                    lower_case_letters, upper_case_letters, line, i)) {
                string_append_s(currentWord, ch);
            } else {
                if (str_contains(APOSTROPHES, ch->s) && !string_empty(currentWord) && is_apostrophe(
                        lower_case_letters, upper_case_letters, line, i)) {
                    string_append_s(currentWord, ch);
                } else {
                    if (!string_empty(currentWord)) {
                        String_ptr tmp = repeat_control(currentWord->s, webMode || emailMode);
                        sentence_add_word_copy(currentSentence, tmp->s);
                        free_string_ptr(tmp);
                    }
                    if (!string_equals2(ch, "\n")) {
                        sentence_add_word_copy(currentSentence, ch->s);
                    }
                    clean_string(currentWord);
                    if (string_equals2(ch, "{")) {
                        curlyBracketCount++;
                    } else {
                        if (string_equals2(ch, "}")) {
                            curlyBracketCount--;
                        } else {
                            if (string_equals2(ch, "\uFF02")) {
                                specialQuotaCount++;
                            } else {
                                if (string_equals2(ch, "\u05F4")) {
                                    specialQuotaCount--;
                                } else {
                                    if (string_equals2(ch, "“")) {
                                        specialQuotaCount++;
                                    } else {
                                        if (string_equals2(ch, "”")) {
                                            specialQuotaCount--;
                                        } else {
                                            if (string_equals2(ch, "‘")) {
                                                specialQuotaCount++;
                                            } else {
                                                if (string_equals2(ch, "‘")) {
                                                    specialQuotaCount--;
                                                } else {
                                                    if (string_equals2(ch, "(")) {
                                                        roundParenthesisCount++;
                                                    } else {
                                                        if (string_equals2(ch, ")")) {
                                                            roundParenthesisCount--;
                                                        } else {
                                                            if (string_equals2(ch, "[")) {
                                                                bracketCount++;
                                                            } else {
                                                                if (string_equals2(ch, "]")) {
                                                                    bracketCount--;
                                                                } else {
                                                                    if (string_equals2(ch, "\"")) {
                                                                        quotaCount = 1 - quotaCount;
                                                                    } else {
                                                                        if (string_equals2(ch, "'")) {
                                                                            apostropheCount = 1 - apostropheCount;
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    if (string_equals2(ch, "\"") && bracketCount == 0 && specialQuotaCount == 0 && curlyBracketCount ==
                        0 &&
                        roundParenthesisCount == 0 && quotaCount == 0 && is_next_char_upper_case_or_digit(
                            upper_case_letters, line, i + 1)) {
                        array_list_add(sentences, currentSentence);
                        currentSentence = create_sentence();
                    }
                }
            }
        } else {
            if (str_contains(SENTENCE_ENDERS, ch->s)) {
                char *lowercase = lowercase_en(currentWord->s);
                if (string_equals2(ch, ".") && strcmp(lowercase, "www") == 0) {
                    webMode = true;
                }
                free_(lowercase);
                if (string_equals2(ch, ".") && !string_empty(currentWord) && (
                        webMode || emailMode || (is_digit(line, i - 1) && !is_next_char_upper_case_or_digit(
                                                     upper_case_letters, line, i + 1)))) {
                    string_append_s(currentWord, ch);
                    sentence_add_word_copy(currentSentence, currentWord->s);
                    clean_string(currentWord);
                } else {
                    if (string_equals2(ch, ".") && (
                            shortcut_list_contains(shortcuts, currentWord->s) || is_name_shortcut(
                                upper_case_letters, currentWord->s))) {
                        string_append_s(currentWord, ch);
                        sentence_add_word_copy(currentSentence, currentWord->s);
                        clean_string(currentWord);
                    } else {
                        if (string_equals2(ch, ".") && number_exists_before_and_after(line, i)) {
                            string_append_s(currentWord, ch);
                        } else {
                            if (!string_empty(currentWord)) {
                                String_ptr tmp = repeat_control(currentWord->s, webMode || emailMode);
                                sentence_add_word_copy(currentSentence, tmp->s);
                                free_string_ptr(tmp);
                            }
                            free_string_ptr(currentWord);
                            currentWord = char_at(line, i);
                            do {
                                free_string_ptr(ch);
                                i++;
                                ch = char_at(line, i);
                            } while (i < word_size(line) && str_contains(SENTENCE_ENDERS, ch->s));
                            i--;
                            free_string_ptr(ch);
                            ch = char_at(line, i);
                            sentence_add_word_copy(currentSentence, currentWord->s);
                            if (roundParenthesisCount == 0 && bracketCount == 0 && curlyBracketCount == 0 && quotaCount
                                == 0) {
                                if (i + 1 < word_size(line) && is_equal_to_char(line, i + 1, "'") && apostropheCount ==
                                    1 && is_next_char_upper_case_or_digit(upper_case_letters, line, i + 2)) {
                                    sentence_add_word_copy(currentSentence, "'");
                                    i++;
                                    free_string_ptr(ch);
                                    ch = char_at(line, i);
                                    array_list_add(sentences, currentSentence);
                                    currentSentence = create_sentence();
                                } else {
                                    if (i + 2 < word_size(line) && is_equal_to_char(line, i + 1, " ") &&
                                        is_equal_to_char(line, i + 2, "'") && apostropheCount == 1 &&
                                        is_next_char_upper_case_or_digit(upper_case_letters, line, i + 3)) {
                                        sentence_add_word_copy(currentSentence, "'");
                                        i += 2;
                                        free_string_ptr(ch);
                                        ch = char_at(line, i);
                                        array_list_add(sentences, currentSentence);
                                        currentSentence = create_sentence();
                                    } else {
                                        if (is_next_char_upper_case_or_digit(upper_case_letters, line, i + 1)) {
                                            array_list_add(sentences, currentSentence);
                                            currentSentence = create_sentence();
                                        }
                                    }
                                }
                            }
                        }
                        clean_string(currentWord);
                    }
                }
            } else {
                if (string_equals2(ch, " ")) {
                    emailMode = false;
                    webMode = false;
                    if (!string_empty(currentWord)) {
                        String_ptr tmp = repeat_control(currentWord->s, webMode || emailMode);
                        sentence_add_word_copy(currentSentence, tmp->s);
                        free_string_ptr(tmp);
                        clean_string(currentWord);
                    }
                } else {
                    if (str_contains(HYPHENS, ch->s) && !webMode && roundParenthesisCount == 0 &&
                        is_next_char_upper_case(upper_case_letters, line, i + 1) && !is_previous_word_upper_case(
                            lower_case_letters, upper_case_letters, line, i - 1)) {
                        if (!string_empty(currentWord) && !str_contains(DIGITS, currentWord->s)) {
                            String_ptr tmp = repeat_control(currentWord->s, webMode || emailMode);
                            sentence_add_word_copy(currentSentence, tmp->s);
                            free_string_ptr(tmp);
                        }
                        if (sentence_word_count(currentSentence) > 0) {
                            array_list_add(sentences, currentSentence);
                        } else {
                            free_sentence(currentSentence);
                        }
                        currentSentence = create_sentence();
                        roundParenthesisCount = 0;
                        bracketCount = 0;
                        curlyBracketCount = 0;
                        quotaCount = 0;
                        specialQuotaCount = 0;
                        Regular_expression_ptr re = create_regular_expression("\\d+");
                        if (!string_empty(currentWord) && full_matches(re, currentWord->s)) {
                            String_ptr tmp = create_string3(currentWord->s, " -");
                            sentence_add_word_copy(currentSentence, tmp->s);
                            free_string_ptr(tmp);
                        } else {
                            sentence_add_word_copy(currentSentence, "-");
                        }
                        free_regular_expression(re);
                        clean_string(currentWord);
                    } else {
                        if (str_contains(PUNCTUATION_CHARACTERS, ch->s) || str_contains(ARITHMETIC_CHARACTERS, ch->s)) {
                            if (string_equals2(ch, ":") && (string_equals2(currentWord, "http") || string_equals2(
                                                                currentWord, "https"))) {
                                webMode = true;
                            }
                            if (webMode) {
                                string_append_s(currentWord, ch);
                            } else {
                                if (string_equals2(ch, ",") && number_exists_before_and_after(line, i)) {
                                    string_append_s(currentWord, ch);
                                } else {
                                    if (string_equals2(ch, ":") && is_in_time_string(line, i)) {
                                        string_append_s(currentWord, ch);
                                    } else {
                                        if (string_equals2(ch, "-") && number_exists_before_and_after(line, i)) {
                                            string_append_s(currentWord, ch);
                                        } else {
                                            if (!string_empty(currentWord)) {
                                                String_ptr tmp = repeat_control(currentWord->s, webMode || emailMode);
                                                sentence_add_word_copy(currentSentence, tmp->s);
                                                free_string_ptr(tmp);
                                            }
                                            sentence_add_word_copy(currentSentence, ch->s);
                                            clean_string(currentWord);
                                        }
                                    }
                                }
                            }
                        } else {
                            if (string_equals2(ch, "@")) {
                                string_append_s(currentWord, ch);
                                emailMode = true;
                            } else {
                                string_append_s(currentWord, ch);
                            }
                        }
                    }
                }
            }
        }
        i++;
        free_string_ptr(ch);
    }
    if (!string_empty(currentWord)) {
        String_ptr tmp = repeat_control(currentWord->s, webMode || emailMode);
        sentence_add_word_copy(currentSentence, tmp->s);
        free_string_ptr(tmp);
    }
    free_string_ptr(currentWord);
    if (sentence_word_count(currentSentence) > 0) {
        array_list_add(sentences, currentSentence);
    } else {
        free_sentence(currentSentence);
    }
    return sentences;
}

/**
 * Checks if the character at position index is a digit or not.
 * @param line Line to be checked.
 * @param index Index of the UTF8 character.
 * @return True if the character is a digit, false otherwise.
 */
bool is_digit(const char *line, int index) {
    String_ptr ch = char_at(line, index);
    bool result = str_contains(DIGITS, ch->s);
    free_string_ptr(ch);
    return result;
}

/**
 * Checks if the character at position index is equal to a given character or not.
 * @param line Line to be checked.
 * @param index Index of the UTF8 character.
 * @param _ch Character to be checked.
 * @return True if the character at position index is equal to _ch, false otherwise.
 */
bool is_equal_to_char(const char *line, int index, char *_ch) {
    String_ptr ch = char_at(line, index);
    bool result = string_equals2(ch, _ch);
    free_string_ptr(ch);
    return result;
}
