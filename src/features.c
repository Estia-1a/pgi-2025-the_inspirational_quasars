#include <estia-image.h>
#include <stdio.h>

#include "features.h"
#include "utils.h"

/**
 * @brief Here, you have to code features of the project.
 * Do not forget to commit regurlarly your changes.
 * Your commit messages must contain "#n" with: n = number of the corresponding feature issue.
 * When the feature is totally implemented, your commit message must contain "close #n".
 */

void helloWorld() {
    printf("Hello World !");
}

void dimension(const char* source_path){
    int width, height, channel_count; 
    unsigned char* data;
    read_image_data(source_path, &data, &width, &height, &channel_count);
    printf("dimension: %d,%d",width,height);
    free_image_data(data);
}

void first_pixel(char* source_path){
    int width, height, channel_count; 
    unsigned char* data;
    read_image_data(source_path, &data, &width, &height, &channel_count);
    printf("fisrt_pixel: %d, %d, %d", data[0],data[1], data[2]);
    free_image_data(data);
}

void tenth_pixel (char *source_path){
    int width, height, channel_count; 
    unsigned char* data;
    read_image_data(source_path, &data, &width, &height, &channel_count);
    printf("fisrt_pixel: %d, %d, %d", data[0],data[1], data[2]);
    free_image_data(data);
}

void second_line(char* source_path){
    int width, height, channel_count; 
    unsigned char* data;
    read_image_data(source_path, &data, &width, &height, &channel_count);
    printf("second_line: %d, %d, %d", data[width*3],data[width*3 + 1], data[width*3 + 2]);
    free_image_data(data);
}
