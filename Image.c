// Created following the contents of this link: https://solarianprogrammer.com/2019/06/10/c-programming-reading-writing-images-stb_image-libraries/

// The porpose of this file is to have some functions for image manipulation.
// This file needs the stb_image library to work. There is a comment main
// function in this file that can be consulted to see some examples of how
// to use the functions in this file. The Image_save functions is commented
// because it is buggy. There are some alternatives, but if you want a single
// function to save any file, you will have to fix/make it yourself.

#pragma once

#include <stdio.h>
#include <stdlib.h>

// It is necessary to make this definitions for the library to work
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <tgmath.h>

// Error utility macro
#define ON_ERROR_EXIT(cond, message) \
do { \
    if ((cond)) { \
        printf("Error in function %s at line %d\n", __func__, __LINE__); \
        perror((message)); \
        exit(1); \
    } \
} while (0);

// Check if a string "str" ends with a substring "ends"
static inline bool str_ends_in(const char *str, const char *end) {
    size_t str_len = strlen(str);
    size_t ends_len = strlen(str);
    char *pos = strstr(str, end);
    return (pos != NULL) && (pos + ends_len == str + str_len);
}

// Utility enum
enum allocation_type {
    NO_ALLOCATION, SELF_ALLOCATED, STB_ALLOCATED
};

// Image struct
typedef struct {
    int width;
    int height;
    int channels;
    size_t size;
    uint8_t *data;
    enum allocation_type allocation;
} Image;

// Loads a new image in a Image struct and sets its fields
void Image_load(Image *img, const char *fname) {
    if ((img->data = stbi_load(fname, &img->width, &img->height, &img->channels, 0)) != NULL) {
        img->size = img->width * img->height * img->channels;
        img->allocation = STB_ALLOCATED;
    }
}

/* Allocates memory for a new image in a Image struct and sets its fields */
void Image_create(Image *img, int width, int height, int channels, bool zeroed) {
    size_t size = width * height * channels;
    if (zeroed) {
        /* Allocates memory and initializes with 0 */
        img->data = calloc(size, 1);
    } else {
        img->data = malloc(size);
    }

    if (img->data != NULL) {
        img->width = width;
        img->height = height;
        img->channels = channels;
        img->size = size;
        img->allocation = SELF_ALLOCATED;
    }
}

/* There is some problem with this function, it is not working and I have no idea of why */
/* Takes an Image as parameter and saves it under a specific name */
// void Image_save(const Image *img, const char *fname) {
//     // Checks if the file name ends is one of the .jpg/.JPG/.jpeg/.JPEG or .png/.PNG
//     if (str_ends_in(fname, ".jpg") || str_ends_in(fname, ".JPG") || str_ends_in(fname, ".jpeg") || str_ends_in(fname, ".JPEG")) {
//         stbi_write_jpg(fname, img->width, img->height, img->channels, img->data, 100);
//     } else if (str_ends_in(fname, ".png") || str_ends_in(fname, ".PNG")) {
//         stbi_write_png(fname, img->width, img->height, img->channels, img->data, img->width * img->channels);
//     } else {
//         // fprintf(stderr, "Invalid filename\n");
//         // abort();
//         ON_ERROR_EXIT(false, "");
//     }
// }

// Takes an Image as parameter as saves it in the jpg format
void Image_save_jpg(const Image *img, const char *fname) {
    stbi_write_jpg(fname, img->width, img->height, img->channels, img->data, 100);
}

// Takes an Image as parameter as saves it in the png format
void Image_save_png(const Image *img, const char *fname) {
    stbi_write_png(fname, img->width, img->height, img->channels, img->data, img->width * img->channels);
}

/* Free the memory allocated for the Image struct's data and sets its fields to 0 or equivalent */
void Image_free(Image *img) {
    if (img->allocation != NO_ALLOCATION && img->data != NULL) {
        if (img->allocation == STB_ALLOCATED) {
            stbi_image_free(img->data);
        } else {
            free(img->data);
        }
        img->data = NULL;
        img->width = 0;
        img->height = 0;
        img->size = 0;
        img->allocation = NO_ALLOCATION;
    }
}

/* Creates a gray version of a given image in another one */
void Image_to_gray(const Image *orig, Image *gray) {
    int channels = orig->channels == 4 ? 2 : 1;
    Image_create(gray, orig->width, orig->height, channels, false);
    // if (gray->data == NULL) {
    //     fprintf(stderr, "Error in creating the image\n");
    //     abort();
    // }
    ON_ERROR_EXIT(gray->data == NULL, "Error in creating the image");

    for (uint8_t *p = orig->data, *pg = gray->data; p != orig->data + orig->size; p += orig->channels, pg += gray->channels) {
        *pg = (uint8_t) ((*p + *(p + 1) + *(p + 2))/3.0);
        if (channels == 4)
            *(pg + 1) = *(p + 3);
    }
}

/* Creates a sepia version of a given image in another one */
void Image_to_sepia(const Image *orig, Image *sepia) {
    Image_create(sepia, orig->width, orig->height, orig->channels, false);
    // if (sepia->data == NULL) {
    //     fprintf(stderr, "Error in creating the image\n");
    //     abort();
    // }
    ON_ERROR_EXIT(sepia->data == NULL, "Error in creating the image");

    /* Sepia filter coefficients from https://stackoverflow.com/questions/1061093/how-is-a-sepia-tone-created */
    for (uint8_t *p = orig->data, *pg = sepia->data; p != orig->data + orig->size; p += orig->channels, pg += sepia->channels) {
        *pg       = (uint8_t)fmin(0.393 * *p + 0.769 * *(p + 1) + 0.189 * *(p + 2), 255.0); // red
        *(pg + 1) = (uint8_t)fmin(0.349 * *p + 0.686 * *(p + 1) + 0.168 * *(p + 2), 255.0); // green
        *(pg + 2) = (uint8_t)fmin(0.272 * *p + 0.534 * *(p + 1) + 0.131 * *(p + 2), 255.0); // blue
        if (orig->channels == 4)
            *(pg + 3) = *(p + 3); // alpha
    }
}

/* gcc -std=c17 -Wall t3.c -o ./bin/t3 -lm */
// int main(int argc, char* argv[argc+1]) {
//     clock_t start = clock();

//     Image img_sky, img_shapes, img_Yukina;

//     // Loads the images
//     Image_load(&img_sky, "sky.jpg");
//     Image_load(&img_shapes, "Shapes.png");
//     Image_load(&img_Yukina, "Yukina.png");

//     // Checks if occured some problem
//     if (img_sky.data == NULL || img_shapes.data == NULL || img_Yukina.data == NULL) {
//         fprintf(stderr, "Error in loading the images\n");
//         abort();
//     }

//     // Converts the images to gray
//     Image img_sky_gray, img_shapes_gray, img_Yukina_gray;
//     Image_to_gray(&img_sky, &img_sky_gray);
//     Image_to_gray(&img_shapes, &img_shapes_gray);
//     Image_to_gray(&img_Yukina, &img_Yukina_gray);

//     // Converts the images to sepia
//     Image img_sky_sepia, img_shapes_sepia, img_Yukina_sepia;
//     Image_to_sepia(&img_sky, &img_sky_sepia);
//     Image_to_sepia(&img_shapes, &img_shapes_sepia);
//     Image_to_sepia(&img_Yukina, &img_Yukina_sepia);

//     // Saves the images
//     Image_save_jpg(&img_sky_gray, "sky_gray.jpg");
//     Image_save_jpg(&img_sky_sepia, "sky_sepia.jpg");
//     Image_save_png(&img_shapes_gray, "Shapes_gray.png");
//     Image_save_png(&img_shapes_sepia, "Shapes_sepia.png");
//     Image_save_png(&img_Yukina_gray, "Yukina_gray.png");
//     Image_save_png(&img_Yukina_sepia, "Yukina_sepia.png");

//     // Release memory
//     Image_free(&img_sky);
//     Image_free(&img_sky_gray);
//     Image_free(&img_sky_sepia);

//     Image_free(&img_shapes);
//     Image_free(&img_shapes_gray);
//     Image_free(&img_shapes_sepia);

//     Image_free(&img_Yukina);
//     Image_free(&img_Yukina_gray);
//     Image_free(&img_Yukina_sepia);

//     // Time taken
//     printf("Time taken: %.8fs\n", (double)(clock() - start)/CLOCKS_PER_SEC);
//     return EXIT_SUCCESS;
// }