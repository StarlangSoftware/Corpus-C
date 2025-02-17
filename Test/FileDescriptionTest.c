//
// Created by Olcay Taner YILDIZ on 6.04.2023.
//

#include <stdio.h>
#include <string.h>
#include <Memory/Memory.h>
#include "../src/FileDescription.h"

void testGetIndex(){
    File_description_ptr file_description = create_file_description("mypath", "1234.train");
    if (file_description->index != 1234){
        printf("Error in get index 1");
    }
    free_file_description(file_description);
    file_description = create_file_description("mypath", "0000.test");
    if (file_description->index != 0){
        printf("Error in get index 2");
    }
    free_file_description(file_description);
    file_description = create_file_description("mypath", "0003.dev");
    if (file_description->index != 3){
        printf("Error in get index 3");
    }
    free_file_description(file_description);
    file_description = create_file_description("mypath", "0020.train");
    if (file_description->index != 20){
        printf("Error in get index 4");
    }
    free_file_description(file_description);
    file_description = create_file_description("mypath", "0304.dev");
    if (file_description->index != 304){
        printf("Error in get index 5");
    }
    free_file_description(file_description);
}

void testGetExtension() {
    File_description_ptr file_description = create_file_description("mypath", "1234.train");
    if (strcmp(file_description->extension, "train") != 0) {
        printf("Error in get extension 1");
    }
    free_file_description(file_description);
    file_description = create_file_description("mypath", "0000.test");
    if (strcmp(file_description->extension, "test") != 0) {
        printf("Error in get extension 2");
    }
    free_file_description(file_description);
    file_description = create_file_description("mypath", "0003.dev");
    if (strcmp(file_description->extension, "dev") != 0) {
        printf("Error in get extension 3");
    }
    free_file_description(file_description);
}

void testGetFileName(){
    File_description_ptr file_description = create_file_description("mypath", "0003.train");
    char* file_name = get_file_name(file_description);
    if (strcmp(file_name, "mypath/0003.train") != 0) {
        printf("Error in get filename 1");
    }
    free_(file_name);
    file_name = get_file_name2(file_description, "newpath");
    if (strcmp(file_name, "newpath/0003.train") != 0) {
        printf("Error in get filename 2");
    }
    free_(file_name);
    file_name = get_file_name3(file_description, "newpath", "dev");
    if (strcmp(file_name, "newpath/0003.dev") != 0) {
        printf("Error in get filename 3");
    }
    free_(file_name);
    file_name = get_file_name4(file_description, "newpath", 0);
    if (strcmp(file_name, "newpath/0000.train") != 0) {
        printf("Error in get filename 4");
    }
    free_(file_name);
    file_name = get_raw_file_name(file_description);
    if (strcmp(file_name, "0003.train") != 0) {
        printf("Error in get filename 5");
    }
    free_(file_name);
    file_name = get_file_name_with_extension(file_description, "dev");
    if (strcmp(file_name, "mypath/0003.dev") != 0) {
        printf("Error in get filename 6");
    }
    free_(file_name);
    free_file_description(file_description);
}

int main(){
    testGetIndex();
    testGetExtension();
    testGetFileName();
}