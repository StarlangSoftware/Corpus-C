//
// Created by Olcay Taner YILDIZ on 3.04.2023.
//

#include <stdlib.h>
#include "FileDescription.h"
#include <StringUtils.h>
#include <Dictionary/Word.h>
#include <string.h>
#include <stdio.h>
#include <Memory/Memory.h>

/**
 * Constructor for the FileDescription object. FileDescription object is used to store sentence or tree file names
 * in a format of path/index.extension such as 'trees/0123.train' or 'sentences/0002.test'. At most 10000 file names
 * can be stored for an extension.
 * @param path Path of the file
 * @param raw_file_name Raw file name of the string without path name, including the index of the file and the
 *                    extension. For example 0023.train, 3456.test, 0125.dev, 0000.train etc.
 */
File_description_ptr create_file_description(const char *path, const char *raw_file_name) {
    File_description_ptr result = malloc_(sizeof(File_description), "create_file_description");
    result->path = str_copy(result->path, path);
    long index = strrchr(raw_file_name, '.') - raw_file_name;
    String_ptr sub = substring2(raw_file_name, index + 1);
    result->extension = str_copy(result->extension, sub->s);
    free_string_ptr(sub);
    sub = substring(raw_file_name, 0, index);
    result->index = atoi(sub->s);
    free_string_ptr(sub);
    return result;
}

/**
 * Another constructor for the FileDescription object. FileDescription object is used to store sentence or tree
 * file names in a format of path/index.extension such as 'trees/0123.train' or 'sentences/0002.test'. At most 10000
 * file names can be stored for an extension.
 * @param path Path of the file
 * @param extension Extension of the file such as train, test, dev etc.
 * @param index Index of the file, should be larger than or equal to 0 and less than 10000. 123, 0, 9999, etc.
 */
File_description_ptr create_file_description2(const char *path, const char *extension, int index) {
    File_description_ptr result = malloc_(sizeof(File_description), "create_file_description2");
    result->path = str_copy(result->path, path);
    result->extension = str_copy(result->extension, extension);
    result->index = index;
    return result;
}

/**
 * Returns only the filename without path as 'index.extension'.
 * @param fd File description
 * @return File name without path as 'index.extension'.
 */
char *get_file_name(const File_description* fd) {
    char* name = malloc_(strlen(fd->path) + 7 + strlen(fd->extension), "get_file_name");
    sprintf(name, "%s/%04d.%s", fd->path, fd->index, fd->extension);
    return name;
}

/**
 * Returns the filename with path replaced with the given path
 * @param fd File description
 * @param path New path
 * @return The filename with path replaced with the given path
 */
char *get_file_name2(const File_description* fd, const char *path) {
    char* name = malloc_(strlen(path) + 7 + strlen(fd->extension), "get_file_name2");
    sprintf(name, "%s/%04d.%s", path, fd->index, fd->extension);
    return name;
}

/**
 * Returns the filename with extension replaced with the given extension.
 * @param fd File description
 * @param extension New extension
 * @return The filename with extension replaced with the given extension.
 */
char *get_file_name_with_extension(const File_description* fd, const char *extension) {
    char* name = malloc_(strlen(fd->path) + 7 + strlen(extension), "get_file_name_with_extension");
    sprintf(name, "%s/%04d.%s", fd->path, fd->index, extension);
    return name;
}

/**
 * Returns the filename with path and extensions are replaced with the given path and extension.
 * @param fd File description
 * @param path New path
 * @param extension New extension
 * @return The filename with path and extensions are replaced with the given path and extension.
 */
char *get_file_name3(const File_description* fd, const char *path, const char *extension) {
    char* name = malloc_(strlen(path) + 7 + strlen(extension), "get_file_name3");
    sprintf(name, "%s/%04d.%s", path, fd->index, extension);
    return name;
}

/**
 * Returns the filename with path and index are replaced with the given path and index.
 * @param fd File description
 * @param path New path
 * @param index New Index
 * @return The filename with path and index are replaced with the given path and index.
 */
char *get_file_name4(const File_description* fd, const char *path, int index) {
    char* name = malloc_(strlen(path) + 7 + strlen(fd->extension), "get_file_name4");
    sprintf(name, "%s/%04d.%s", path, index, fd->extension);
    return name;
}

/**
 * Returns only the filename without path as 'index.extension'.
 * @param fd File description
 * @return File name without path as 'index.extension'.
 */
char *get_raw_file_name(const File_description* fd) {
    char* name = malloc_(6 + strlen(fd->extension), "get_raw_file_name");
    sprintf(name, "%04d.%s", fd->index, fd->extension);
    return name;
}

/**
 * Increments index by count
 * @param fd File description
 * @param count Count to be incremented
 */
void add_to_index(File_description_ptr fd, int count) {
    fd->index += count;
}

/**
 * Frees memory allocated for the file description.
 * @param fd File description
 */
void free_file_description(File_description_ptr fd) {
    free_(fd->extension);
    free_(fd->path);
    free_(fd);
}
