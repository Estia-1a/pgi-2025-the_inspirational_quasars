#include <estia-image.h>
#include <stdio.h>
#include <stdlib.h>

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
    int  i, j, maxi=-1, somme=0, x, y, R, G, B;
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

void color_red(char *source_path){
    int width, height, channel_count;
    unsigned char *data;
    int i;
    read_image_data(source_path, &data, &width, &height, &channel_count);
    for (i=0;i<width*height*3;i++){
        if (i%3 == 1){
            data[i]=0;
        }
        if (i%3 == 2){
            data[i]=0;
        }
    }
    write_image_data("image_out.bmp", data, width, height);
    free_image_data(data);
}

void color_blue(char *source_path){
    int width, height, channel_count;
    unsigned char *data;
    int i;
    read_image_data(source_path, &data, &width, &height, &channel_count);
    for (i=0;i<width*height*3;i++){
        if (i%3 == 1){
            data[i]=0;
        }
        if (i%3 == 0){
            data[i]=0;
        }
    }
    write_image_data("image_out.bmp", data, width, height);
    free_image_data(data);
}

void color_green(char *source_path){
    int width, height, channel_count;
    unsigned char *data;
    int i;
    read_image_data(source_path, &data, &width, &height, &channel_count);
    for (i=0;i<width*height*3;i++){
        if (i%3 == 2){
            data[i]=0;
        }
        if (i%3 == 0){
            data[i]=0;
        }
    }
    write_image_data("image_out.bmp", data, width, height);
    free_image_data(data);
}

void color_gray(char *source_path){
    int width, height, channel_count;
    unsigned char *data;
    int i, j, somme = 0, couleur = 0;
    read_image_data(source_path, &data, &width, &height, &channel_count);
    for (i=0;i<width*height;i++){
        for (j=0;j<2;j++){
            somme += data[i*3+j];
        }
        couleur = somme/3;
        data[3*i] = couleur;
        data[3*i+1] = couleur;
        data[3*i+2] = couleur;
        somme = 0;
    }
    write_image_data("image_out.bmp", data, width, height);
    free_image_data(data);
}

void color_invert(char *source_path){
    int width, height, channel_count;
    unsigned char *data;
    int i;
    read_image_data(source_path, &data, &width, &height, &channel_count);
    for (i=0;i<3*width*height;i++){
        data[i] = 255 - data[i];
    }
    write_image_data("image_out.bmp", data, width, height);  
    free_image_data(data);
}

void color_gray_luminance(char *source_path){
    int width, height, channel_count;
    unsigned char *data;
    int i, j, somme=0;
    read_image_data(source_path, &data, &width, &height, &channel_count);
    for (i=0;i<width*height;i++){
        for (j=0;j<3;j++){
            if (j==0){
                somme+=0.21*data[3*i+j];
            }
            if (j==1){
                somme+=0.72*data[3*i+j];
            }
            if (j==2){
                somme+=0.07*data[3*i+j];
            }
        }
        data[3*i] = somme;
        data[3*i+1] = somme;
        data[3*i+2] = somme;
        somme = 0;
    }
    write_image_data("image_out.bmp", data, width, height);
    free_image_data(data);
}

void rotate_cw(char *source_path) {
    int width, height, channel_count;
    unsigned char* data;
    read_image_data(source_path, &data, &width, &height, &channel_count);
 
    unsigned char *newdata = (unsigned char *)malloc(width * height * channel_count * sizeof(unsigned char));
    if (!newdata) {
        free_image_data(data);
        return;
    }
    int y;
    int x;
    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            pixelRGB *pixel = get_pixel(data, width, height, channel_count, x, y);
            if (!pixel) continue;
 
            int new_x = height - 1 - y;
            int new_y = x;
            int rotated_pos = channel_count * (new_y * height + new_x);
 
            newdata[rotated_pos]     = pixel->R;
            newdata[rotated_pos + 1] = pixel->G;
            newdata[rotated_pos + 2] = pixel->B;
        }
    }
 
    write_image_data("image_out.bmp", newdata, height, width);
    free_image_data(data);
}

void rotate_acw(char *source_path) {
    int width, height, channel_count;
    unsigned char* data;
    read_image_data(source_path, &data, &width, &height, &channel_count);
 
    unsigned char *newdata = (unsigned char *)malloc(width * height * channel_count * sizeof(unsigned char));
    if (!newdata) {
        free_image_data(data);
        return;
    }
    int y;
    int x;
    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            pixelRGB *pixel = get_pixel(data, width, height, channel_count, x, y);
            if (!pixel) continue;
 
            int new_x = y;
            int new_y = width - 1 - x;
            int rotated_pos = channel_count * (new_y * height + new_x);
 
            newdata[rotated_pos]     = pixel->R;
            newdata[rotated_pos + 1] = pixel->G;
            newdata[rotated_pos + 2] = pixel->B;
        }
    }
 
    write_image_data("image_out.bmp", newdata, height, width);
    free_image_data(data);
}

void mirror_horizontal(char *source_path){
    int width, height, channel_count;
    unsigned char *data;
    read_image_data(source_path, &data, &width, &height, &channel_count);

    int i, x, y, posD, posG;
    unsigned char temp;
    for(y = 0; y < height; y++){

        for (x = 0; x < width/2; x++){
            posG = (y * width + x) * channel_count; 
            posD = (y * width + (width - 1 - x)) * channel_count;

            for (i = 0; i < channel_count; i++){
                temp = data[posG + i];
                data[posG + i] = data[posD + i];
                data[posD + i] = temp;
            }
        }
    }
    write_image_data("image_out.bmp", data, width, height);
    free_image_data(data);
}

void mirror_vertical(char *source_path){
    int width, height, channel_count;
    unsigned char *data;
    read_image_data(source_path, &data, &width, &height, &channel_count);

    int i, x, y, posH, posB;
    unsigned char temp;
    for(y = 0; y < height/2; y++){

        for (x = 0; x < width; x++){
            posH = (y * width + x) * channel_count; 
            posB = ((height - 1 - y) * width + x) * channel_count;

            for (i = 0; i < channel_count; i++){
                temp = data[posH + i];
                data[posH + i] = data[posB + i];
                data[posB + i] = temp;
            }
        }
    }
    write_image_data("image_out.bmp", data, width, height);
    free_image_data(data);
}

void scale_crop(char *source_path, int center_x, int center_y, int new_width, int new_height){
    // Initialisation
    int width, height, channel_count;
    unsigned char *data;
    read_image_data(source_path, &data, &width, &height, &channel_count);

    // Vérification des paramètres d'entrée
    if (new_width >= width || new_height >= height) {    
        printf("Erreur de plage\n");
        free_image_data(data);
        return;
    }

    // Mise en place de la mémoire pour nouvelle image
    unsigned char *newdata = (unsigned char *)malloc(new_width * new_height * channel_count * sizeof(unsigned char));
    if (!newdata) {
        free_image_data(data);
        return;
    }
    // Création du repére de la nouvelle image
    int top_left_x = center_x - new_width / 2;
    int top_left_y = center_y - new_height / 2;

    // Vérification du repére de l'image
    if (top_left_x < 0 ){top_left_x = 0;}
    if (top_left_y < 0 ){top_left_y = 0;}
    if (top_left_x + new_width > width) { top_left_x = width - new_width;}
    if (top_left_y + new_height > height) { top_left_y = height - new_height;}

    // ajout des valeurs a la mémoire de la nouvelle image
    int i, x, y, orig_x, orig_y;
    for(y = 0; y < new_height; y++){
         for (x = 0; x < new_width; x++){
            orig_x = top_left_x + x;
            orig_y = top_left_y + y;

            for (i = 0; i < channel_count; i++){
                newdata[(y * new_width + x) * channel_count + i] = data[(orig_y * width + orig_x) * channel_count + i];
            }
        }
    }

    // Création de la nouvelle image
    write_image_data("image_out.bmp", newdata, new_width, new_height);

    // Libération de la mémoire
    free_image_data(data);
    free(newdata);
}

void scale_nearest(char *source_path, int X){
    printf("scale_nearest\n");
    int width, height, channel_count;
    unsigned char* data;
    read_image_data(source_path, &data, &width, &height, &channel_count);
 
    unsigned char *newdata = (unsigned char *)malloc(width * height * channel_count * sizeof(unsigned char));
    if (!newdata) {
        free_image_data(data);
        return;
    }
}