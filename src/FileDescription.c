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

File_description_ptr create_file_description2(const char *path, const char *extension, int index) {
    File_description_ptr result = malloc_(sizeof(File_description), "create_file_description2");
    result->path = str_copy(result->path, path);
    result->extension = str_copy(result->extension, extension);
    result->index = index;
    return result;
}

char *get_file_name(const File_description* fd) {
    char* name = malloc_(strlen(fd->path) + 7 + strlen(fd->extension), "get_file_name");
    sprintf(name, "%s/%04d.%s", fd->path, fd->index, fd->extension);
    return name;
}

char *get_file_name2(const File_description* fd, const char *path) {
    char* name = malloc_(strlen(path) + 7 + strlen(fd->extension), "get_file_name2");
    sprintf(name, "%s/%04d.%s", path, fd->index, fd->extension);
    return name;
}

char *get_file_name_with_extension(const File_description* fd, const char *extension) {
    char* name = malloc_(strlen(fd->path) + 7 + strlen(extension), "get_file_name_with_extension");
    sprintf(name, "%s/%04d.%s", fd->path, fd->index, extension);
    return name;
}

char *get_file_name3(const File_description* fd, const char *path, const char *extension) {
    char* name = malloc_(strlen(path) + 7 + strlen(extension), "get_file_name3");
    sprintf(name, "%s/%04d.%s", path, fd->index, extension);
    return name;
}

char *get_file_name4(const File_description* fd, const char *path, int index) {
    char* name = malloc_(strlen(path) + 7 + strlen(fd->extension), "get_file_name4");
    sprintf(name, "%s/%04d.%s", path, index, fd->extension);
    return name;
}

char *get_raw_file_name(const File_description* fd) {
    char* name = malloc_(6 + strlen(fd->extension), "get_raw_file_name");
    sprintf(name, "%04d.%s", fd->index, fd->extension);
    return name;
}

void add_to_index(File_description_ptr fd, int count) {
    fd->index += count;
}

void free_file_description(File_description_ptr fd) {
    free_(fd->extension);
    free_(fd->path);
    free_(fd);
}
