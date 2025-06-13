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
    int i, j, somme=0, couleur;
    read_image_data(source_path, &data, &width, &height, &channel_count);
    for (i=0;i<width*height;i++){
        for (j=0;j<2;j++){
            somme+=data[i*3+j];
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