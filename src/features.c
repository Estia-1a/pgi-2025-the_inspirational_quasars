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

void helloWorld()
{
    printf("Hello World !");
}

void dimension(const char *source_path)
{
    int width, height, channel_count;
    unsigned char *data;
    read_image_data(source_path, &data, &width, &height, &channel_count);
    printf("dimension: %d,%d", width, height);
    free_image_data(data);
}

void first_pixel(char *source_path)
{
    int width, height, channel_count;
    unsigned char *data;
    read_image_data(source_path, &data, &width, &height, &channel_count);
    printf("first_pixel: %d, %d, %d", data[0], data[1], data[2]);
    free_image_data(data);
}

void tenth_pixel(char *source_path)
{
    int width, height, channel_count;
    unsigned char *data;
    read_image_data(source_path, &data, &width, &height, &channel_count);
    printf("tenth_pixel: %d, %d, %d", data[27], data[28], data[29]);
    free_image_data(data);
}

void second_line(char *source_path)
{
    int width, height, channel_count;
    unsigned char *data;
    read_image_data(source_path, &data, &width, &height, &channel_count);
    printf("second_line: %d, %d, %d", data[width * 3], data[width * 3 + 1], data[width * 3 + 2]);
    free_image_data(data);
}

void print_pixel(char *source_path, int x, int y)
{
    int width, height, channel_count;
    unsigned char *data;
    read_image_data(source_path, &data, &width, &height, &channel_count);
    pixelRGB* pixel;
    pixel = get_pixel(data, width, height, channel_count, x, y);
    printf("print_pixel (%d,%d): %d, %d, %d", x, y, pixel->R, pixel->G, pixel->B);
    free_image_data(data);
}

void max_pixel(char *source_path){
    int width, height, channel_count;
    unsigned char *data;
    int  i, j, maxi=0, somme=0, x, y, R, G, B;
    read_image_data(source_path, &data, &width, &height, &channel_count);
    for (i=0;i<=width*height-1;i++){
        for (j=0;j<=2;j++){
            somme+=data[i*3+j];
        }
        if (somme>maxi){
            maxi = somme;
            x = i%width;
            y = i/width;
            R = data[3*i];
            G = data[3*i+1];
            B = data[3*i+2];
        }
        somme = 0;
    }
    printf("max_pixel (%d,%d): %d, %d, %d", x, y, R, G, B);
    free_image_data(data);
}

void min_pixel(char *source_path){
    int width, height, channel_count;
    unsigned char *data;
    int  i, j, mini=1000, somme=0, x, y, R, G, B;
    read_image_data(source_path, &data, &width, &height, &channel_count);
    for (i=0;i<=width*height-1;i++){
        for (j=0;j<=2;j++){
            somme+=data[i*3+j];
        }
        if (somme<mini){
            mini = somme;
            x = i%width;
            y = i/width;
            R = data[3*i];
            G = data[3*i+1];
            B = data[3*i+2];
        }
        somme = 0;
    }
    printf("min_pixel (%d,%d): %d, %d, %d", x, y, R, G, B);
    free_image_data(data);
}

void max_component(char *source_path, char composante)
{
    int width, height, channel_count; 
    int decalage, x, y, max = -1;
    enum couleur{
        rouge,
        vert,
        bleu,
    };
    unsigned char *data;
    read_image_data(source_path, &data, &width, &height, &channel_count);

    if (composante == 'R'){
        decalage = rouge;//0
    }
    else if (composante == 'G'){
        decalage = vert;//1
    }
    else if (composante == 'B'){
        decalage = bleu;//2
    }
    else{
        printf("Invalid color component");
        free_image_data(data);
        return;
    }
    
    int i;
    for(i = 0; i<width*height; i++){
        if (data[3 * i + decalage] > max){
            max = data[3 * i + decalage];
            x = i % width;
            y = i / width;
        }
    }
    printf ("max_component %c (%d,%d): %d", composante, x, y, max); // [R or G or B] (x,y): value
    free_image_data(data);
}

void min_component(char *source_path, char composante)
{
    int width, height, channel_count; 
    int decalage, x, y, min = 256;
    enum couleur{
        rouge,
        vert,
        bleu,
    };
    unsigned char *data;
    read_image_data(source_path, &data, &width, &height, &channel_count);

    if (composante == 'R'){
        decalage = rouge;//0
    }
    else if (composante == 'G'){
        decalage = vert;//1
    }
    else if (composante == 'B'){
        decalage = bleu;//2
    }
    else{
        printf("Invalid color component");
        free_image_data(data);
        return;
    }
    
    int i;
    for(i = 0; i<width*height; i++){
        if (data[3 * i + decalage] < min){
            min = data[3 * i + decalage];
            x = i % width;
            y = i / width;
        }
    }
    printf ("min_component %c (%d,%d): %d", composante, x, y, min); // [R or G or B] (x,y): value
    free_image_data(data);
}

void stat_report(char *source_path){
    int width, height, channel_count;
    unsigned char *data;
    read_image_data(source_path, &data, &width, &height, &channel_count);
    FILE *stat_report;
    stat_report = freopen("report.txt", "w",stdout);
    max_pixel(source_path);
    printf("\n");
    printf("\n");

    min_pixel(source_path);
    printf("\n");
    printf("\n");

    max_component(source_path,'R');
    printf("\n");
    printf("\n");

    max_component(source_path,'G');
    printf("\n");
    printf("\n");

    max_component(source_path,'B');
    printf("\n");
    printf("\n");

    min_component(source_path,'R');
    printf("\n");
    printf("\n");

    min_component(source_path,'G');
    printf("\n");
    printf("\n");

    min_component(source_path,'B');
    printf("\n");
    printf("\n");

    fclose(stat_report);

    free_image_data(data);
}

void color_red(char *south_path){
    
}