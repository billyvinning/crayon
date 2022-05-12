#include <stdio.h>
#include <vector.h>
#include <image.h>


int main(int argc, char *argv[]){
    int img[_TEST_IMG_COLS * _TEST_IMG_ROWS][RGB_NDIM];
    test_img(img);
    write_ppm(img, _TEST_IMG_ROWS, _TEST_IMG_COLS, "test_img.ppm");
}
