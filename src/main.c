#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <estia-image.h>
#include <getopt.h>

#include "features.h"
#include "utils.h"
#include "argsparse.h"

int main(int argc, char **argv) {
  Config configuration ;
  parse_arguments( argc, argv, &configuration ) ;
  check_debug_mode(configuration);
  check_file();
  
  if ( strncmp( configuration.command, "helloworld", 10 ) == 0 ) {
    helloWorld();
  }
  else if ( strncmp( configuration.command, "dimension", 9 ) == 0 ) {
    dimension( configuration.filenames[0] );
  }
  else if ( strncmp( configuration.command, "first_pixel", 11 ) == 0 ) {
    first_pixel(configuration.filenames[0]);
  }
  else if ( strncmp( configuration.command, "tenth_pixel", 11 ) == 0 ) {
    tenth_pixel(configuration.filenames[0]);
  }
  else if ( strncmp( configuration.command, "second_line", 11 ) == 0 ) {
    second_line(configuration.filenames[0]);
  }
  else if ( strncmp( configuration.command, "print_pixel", 11 ) == 0 ) {
    int x = atoi(configuration.arguments[0]);
    int y = atoi(configuration.arguments[1]);
    print_pixel(configuration.filenames[0], x, y);
  }
  else if ( strncmp( configuration.command, "max_pixel", 9 ) == 0 ) {
    max_pixel(configuration.filenames[0]);
  }
  else if ( strncmp( configuration.command, "min_pixel", 9 ) == 0 ) {
    min_pixel(configuration.filenames[0]);
  }
  else if ( strncmp( configuration.command, "max_component", 13 ) == 0 ) {
    char composante = configuration.arguments[0][0];
    max_component(configuration.filenames[0], composante);
  }
  else if ( strncmp( configuration.command, "min_component", 13 ) == 0 ) {
    char composante = configuration.arguments[0][0];
    min_component(configuration.filenames[0], composante);
  }
  else if ( strncmp( configuration.command, "stat_report", 11 ) == 0 ) {
    stat_report(configuration.filenames[0]);
  }
  else if ( strncmp( configuration.command, "color_red", 9 ) == 0 ) {
    color_red(configuration.filenames[0]);
  }
  else if ( strncmp( configuration.command, "color_blue", 10 ) == 0 ) {
    color_blue(configuration.filenames[0]);
  }
  else if ( strncmp( configuration.command, "color_green", 11 ) == 0 ) {
    color_green(configuration.filenames[0]);
  }
  else if ( strncmp( configuration.command, "color_gray", 10 ) == 0 ) {
    color_gray(configuration.filenames[0]);
  }
  else if ( strncmp( configuration.command, "color_invert", 12 ) == 0 ) {
    color_invert(configuration.filenames[0]);
  }
  else if ( strncmp( configuration.command, "color_gray_luminance", 20 ) == 0 ) {
    color_gray_luminance(configuration.filenames[0]);
  }
  else if ( strncmp( configuration.command, "rotate_cw", 20 ) == 0 ) {
    rotate_cw(configuration.filenames[0]);
  }
  else if ( strncmp( configuration.command, "rotate_acw", 20 ) == 0 ) {
    rotate_acw(configuration.filenames[0]);
  }
  else if ( strncmp( configuration.command, "mirror_horizontal", 17 ) == 0 ) {
    mirror_horizontal(configuration.filenames[0]);
  }
  else if ( strncmp( configuration.command, "mirror_vertical", 15 ) == 0 ) {
    mirror_vertical(configuration.filenames[0]);
  }
  else if ( strncmp( configuration.command, "mirror_total", 12 ) == 0 ) {
    mirror_horizontal(configuration.filenames[0]);
    mirror_vertical("image_out.bmp");
  }
  else if ( strncmp( configuration.command, "scale_crop", 9 ) == 0 ) {
    int center_x = atoi(configuration.arguments[0]);
    int center_y = atoi(configuration.arguments[1]);
    int new_width = atoi(configuration.arguments[2]);
    int new_height = atoi(configuration.arguments[3]);
    scale_crop(configuration.filenames[0], center_x, center_y, new_width,new_height);
  }
  return 0;
}
