//
// Created by Olcay Taner YILDIZ on 3.04.2023.
//

#ifndef CORPUS_FILEDESCRIPTION_H
#define CORPUS_FILEDESCRIPTION_H

struct file_description{
    char* path;
    char* extension;
    int index;
};

typedef struct file_description File_description;
typedef File_description* File_description_ptr;

File_description_ptr create_file_description(const char* path, const char* raw_file_name);
File_description_ptr create_file_description2(const char* path, const char* extension, int index);
void free_file_description(File_description_ptr fd);
char* get_file_name(const File_description* fd);
char* get_file_name2(const File_description* fd, const char* path);
char* get_file_name3(const File_description* fd, const char* path, const char* extension);
char* get_file_name4(const File_description* fd, const char* path, int index);
char* get_file_name_with_extension(const File_description* fd, const char* extension);
char* get_raw_file_name(const File_description* fd);
void add_to_index(File_description_ptr fd, int count);

#endif //CORPUS_FILEDESCRIPTION_H
