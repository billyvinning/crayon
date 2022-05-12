#include <image.h>
#include <stdio.h>
#include <stdlib.h>

void test_img(int out[_TEST_IMG_COLS * _TEST_IMG_ROWS][RGB_NDIM]){
    int a[_TEST_IMG_COLS * _TEST_IMG_ROWS][RGB_NDIM] = {
        {0, 0, 0},
        {255, 0, 0},
        {0, 255, 0},
        {0, 0, 255},
        {255, 255, 0},
        {255, 0, 255},
        {0, 255, 255},
        {255, 255, 255}
    };
    unsigned int i;
    for (i = 0; i < _TEST_IMG_COLS * _TEST_IMG_ROWS; i = i + 1) {
        unsigned int j;
        for (j = 0; j < RGB_NDIM; j = j + 1){
            out[i][j] = a[i][j];
        }
    }
}

void print_array(const int *array_2d, unsigned int num_rows, unsigned int num_cols)
{
    // Technique 1: use `array_2d` directly, manually indexing into this
    // contiguous block of memory holding the 2D array data.
    unsigned int row;
    for (row = 0; row < num_rows; row++)
    {
        const int *row_start = &array_2d[row*num_cols];
        unsigned int col;
        for (col = 0; col < num_cols; col++)
        {
            // NB: THIS PART IS VERY DIFFERENT FROM THE OTHERS! Notice `row_start[col]`.
            printf("array_2d[%zu][%zu]=%i ", row, col, row_start[col]);
        }
        printf("\n");
    }
}

void write_ppm(const int a[][RGB_NDIM], unsigned int rows, unsigned int cols, char* path) {
    FILE *f = fopen(path, "w");
    if (f == NULL)
    {
        printf("Error opening file.\n");
        exit(1);
    }
    fprintf(f, "P3\n%u %u\n255\n", cols, rows);
    unsigned int i;
    for (i = 0; i < (cols * rows); i = i + 1) {
    
        if ( (i % cols) == 0  ) {
            fprintf(f, "\n");
        }

        unsigned int j;
        for (j = 0; j < RGB_NDIM; j = j + 1) {
            fprintf(f, "%3d ",  a[i][j]);
            // fprintf(f, "%d ", a[i][j]); 
        }
        fprintf(f, "  ");
    }
    fclose(f);

}
