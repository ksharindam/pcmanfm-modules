#include <stdio.h>

int isJpeg(FILE *file);

int isPng(FILE *file);

int jpegsize(FILE * infile, int *image_width, int *image_height);

int pngsize(FILE * infile, int *image_width, int *image_height);

int imgsize(FILE * infile, int *image_width, int *image_height);

