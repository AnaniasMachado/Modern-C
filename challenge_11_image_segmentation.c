#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#include "Image.c"

typedef struct colors {
    uint8_t *red;
    uint8_t *green;
    uint8_t *blue;
} Colors;

// Generates "num" colors and stores them in "colors"
void color_generator(Colors *colors, uint8_t num) {
    colors->red = malloc(num);
    colors->green = malloc(num);
    colors->blue = malloc(num);

    for (uint8_t i = 0; i < num; ++i) {
        colors->red[i] = rand() % 255;
        colors->green[i] = rand() % 255;
        colors->blue[i] = rand() % 255;
    }
}

// Calculate the index of the region a certain pixel is in
uint8_t get_index(uint8_t val, uint8_t region_size) {
    for (uint8_t i = 0; i < 255; i += region_size) {
        if (val >= i && val < i + region_size)
            return i / region_size;
    }
    return -1;
}

/* The ideia is to take a gray image "img" and make a colored version of it "regions"
   which has "num" regions, each regions of a different color */
void partition_colored(Image *img, Image *regions, size_t num) {
    Colors *colors = malloc(sizeof(Colors));
    color_generator(colors, num);

    for (uint8_t i = 0; i < num; ++i) {
        printf("Red = %d, Green = %d, Blue = %d\n", colors->red[i], colors->green[i], colors->blue[i]);
    }

    uint8_t region_size = 255 / num;
    Image_create(regions, img->width, img->height, 3, 0);

    uint8_t idx;
    for (uint8_t *p = regions->data, *q = img->data; p != regions->data + regions->size; p += 3, q += 1) {
        idx = get_index(*q, region_size);
        *p = colors->red[idx];
        *(p + 1) = colors->green[idx];
        *(p + 2) = colors->blue[idx];
    }

    free(colors);
}

// Calculates how many pixels there are in each region and stores it in "p"
void pixels_per_regions(Image *img, uint8_t num, uint8_t *p) {
    uint8_t region_size = 255 / num;
    memset(p, 0, num);

    uint8_t idx;
    for (uint8_t *q = img->data; q != img->data + img->size; ++q) {
        idx = get_index(*q, region_size);
        *(p + idx) += 1;
    }
}

// Calculates the sum of the gray values of an image in each region and stores it in "p"
void sum_of_pixels_per_region(Image *img, uint8_t num, uint8_t *p) {
    uint8_t region_size = 255 / num;
    memset(p, 0, num);

    uint8_t idx;
    for (uint8_t *q = img->data; q != img->data + img->size; ++q) {
        idx = get_index(*q, region_size);
        *(p + idx) += *q;
    }
}

// Calculates the average of the gray value of an image in each region and stores it in "p"
void average_value_of_pixel_per_region(Image *img, uint8_t num, uint8_t *p) {
    uint8_t *q = malloc(num);
    uint8_t *r = malloc(num);
    pixels_per_regions(img, num, q);
    sum_of_pixels_per_region(img, num, r);

    for (uint8_t i = 0; i < num; ++i) {
        if (q[i] != 0)
            p[i] = r[i] / q[i];
        else
            p[i] = 0;
    }

    free(q);
    free(r);
}

// gcc -std=c17 -Wall img_seg1.c -o ./bin/img_seg1 -lm
int main(int argc, char* argv[argc+1]) {
    clock_t start = clock();

    // Creates the gray img
    Image img, img_gray;
    Image_load(&img, "i2.jpeg");
    Image_to_gray(&img, &img_gray);
    // Image_save_jpg(&img_gray, "i2_gray.jpeg");

    // Creates the "num" colored regions and saves them
    Image regions;
    size_t num = 25;
    partition_colored(&img_gray, &regions, num);
    Image_save_jpg(&regions, "regions.jpg");

    // Prints out how many pixels there are per region
    uint8_t *p = malloc(num);
    pixels_per_regions(&img_gray, num, p);

    for (uint8_t *i = p; i < p + num; ++i)
        printf("The number of pixels in this regions is: %d\n", *i);

    // Prints out the sum of the values of pixels per region
    uint8_t *q = malloc(num);
    sum_of_pixels_per_region(&img_gray, num, q);

    for (uint8_t *i = q; i < q + num; ++i)
        printf("The sum of the values of all the pixel in this region is: %d\n", *i);
    
    // Prints out the average value of pixels per region
    uint8_t *r = malloc(num);
    average_value_of_pixel_per_region(&img_gray, num, r);

    for (uint8_t *i = r; i < r + num; ++i)
        printf("The average values of all the pixel in this region is: %d\n", *i);

    // Free all the stored memory
    Image_free(&img);
    Image_free(&img_gray);
    Image_free(&regions);
    free(p);
    free(q);
    free(r);

    // Time taken
    printf("Time taken: %.8fs\n", (double)(clock() - start)/CLOCKS_PER_SEC);
    return EXIT_SUCCESS;
}