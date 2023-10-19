// FCAI - CS213 Programming II – 2023 / 2024 - Object Oriented Programming
// Assignment 1
// Teaching Assistant : Dr. Mohammad El-Ramly
// Author1 Name & ID : Mohamed Eِlfateh Esmat - 20220970 - Group A - s10
// Author2 Name & ID : Mohamed Rabea Mohamed - 20220424 - Group B - s8
// Author3 Name & ID : Reem Mohamed Mahmoud  - 20221230 - Group B - s18
// Last Modification Date : 9 / 10 /2023
// program Name : main.cpp
// Program Purpose : RGB Colored Image processing using 15 filter

//_________________________________________

#include <iostream>
#include <cstring>
#include <string>
#include "bmplib.h"
#include "bmplib.cpp"
using namespace std ;
unsigned char image [SIZE][SIZE][RGB];
unsigned char image2 [SIZE][SIZE][RGB];
unsigned char image3[SIZE][SIZE];
unsigned char image4[SIZE][SIZE];


void loadImage() ;
void doSomethingForImage ();
void saveImage ();



int main() {

    loadImage() ;
    doSomethingForImage ();
    saveImage ();

    return 0;
}

//_________________________________________

void loadImage()
{
    char imageFileName[100];
    // Get gray scale image file name
    cout  <<"Ahlan ya user ya habibi :)\n" ;
    cout << "Please enter file name of the image to process: \n";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readRGBBMP(imageFileName,image);
}

//_________________________________________

void saveImage()
{
    char imageFileName[100];
    // Get gray scale image target file name
    cout << "Enter the target image file output name:\n";

    cin.ignore();
    cin.getline(imageFileName,99);

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeRGBBMP(imageFileName,image);

}

//_________________________________________

void doSomethingForImage () {

    //          applying the below filters on a colored image

    char filter;

    cout << "Please select a filter to apply or 0 to exit:\n"
         << "     1- Black & White Filter                 \n"
         << "     2- Invert Filter                        \n"
         << "     3- Merge Filter                         \n"
         << "     4- Flip Image                           \n"
         << "     5- darken and lighten image             \n"
         << "     6- Rotate Image                         \n"
         << "     7- Detect Image Edges                   \n"
         << "     8- Enlarge Image                        \n"
         << "     9- Shrink Image                         \n"
         << "     a- Mirror 1/2 Image                     \n"
         << "     b- Shuffle Image                        \n"
         << "     c- Blur Image                           \n"
         << "     d- Crop Image                           \n"
         << "     e- Skew Image Right                     \n"
         << "     f- Skew Image Up                        \n"
         << "     0- Exit                                 \n"
         << "     Note : Image is saved automatically     \n"
         << "     >> ";

    cin >> filter;

    switch (filter) {
        case '0': {
            //          zero case : Exit

            break;
        };
            break;


        case '5': {
            //          filter 5 : Dareken or Ligthen image filter


            char light;

            cout << "please type d for darken or l for lighten?" << '\n';
            cin >> light;

            switch (light) {
                case 'l':
                case 'L':
//          in lighten case increase each pixel < 205 by 50 and if the pixel > 205 let pixel eqaul 255 to avoid overload
                    for (int k = 0; k < RGB; k++) {
                        for (int i = 0; i < SIZE; i++) {
                            for (int j = 0; j < SIZE; j++) {
                                if (image[i][j][k] <= 205) { image[i][j][k] += 50; }
                                else { image[i][j][k] = 255; }
                            }
                        }
                    }
                    break;

                case 'd':
                case 'D':
//          in darken case divide each pixel over 2 to get the half light
                    for (int k = 0; k < RGB; k++) {
                        for (int i = 0; i < SIZE; i++) {
                            for (int j = 0; j < SIZE; j++)
                                image[i][j][k] /= 2;
                        }
                    }
                    break;

                default:
                    cout << "invalid input";

                    break;
            }
        };
            break;


        case '6': {
            //          filter 6 : Rotate Image filter with 3 different degrees

            int angle;

            cout << " Rotate (90), (180) or (270) degrees :" << '\n';
            cin >> angle;

            if (angle == 90) {
                for (int k = 0; k < RGB; k++) {
                    for (int i = 0; i < SIZE / 2; i++) {
                        for (int j = i; j < SIZE - i - 1; j++) {
                            //              Store current pixel in helper variable
                            char helper = image[i][j][k];

                            //              Swap elements of each cycle
                            //              in clockwise direction by 90 degree

                            //              Move values from right to top
                            image[i][j][k] = image[SIZE - 1 - j][i][k];
                            //              Move values from bottom to right
                            image[SIZE - 1 - j][i][k] = image[SIZE - 1 - i][SIZE - 1 - j][k];
                            //              Move values from left to bottom
                            image[SIZE - 1 - i][SIZE - 1 - j][k] = image[j][SIZE - 1 - i][k];
                            //              Assign helper to left
                            image[j][SIZE - 1 - i][k] = helper;
                        }
                    }
                }
            } else if (angle == 180) {
//      in 180 degree we used the main algorithm of 90 degree two times to get 90+90 swap that equal 180 degree
                for (int i = 0; i < 2; i++) {
                    for (int k = 0; k < RGB; k++) {
                        for (int i = 0; i < SIZE / 2; i++) {
                            for (int j = i; j < SIZE - i - 1; j++) {
                                char helper = image[i][j][k];
                                image[i][j][k] = image[SIZE - 1 - j][i][k];
                                image[SIZE - 1 - j][i][k] = image[SIZE - 1 - i][SIZE - 1 - j][k];
                                image[SIZE - 1 - i][SIZE - 1 - j][k] = image[j][SIZE - 1 - i][k];
                                image[j][SIZE - 1 - i][k] = helper;
                            }
                        }
                    }
                }
            } else if (angle == 270) {
//      in 270 degree we used the main algorithm of 90 degree three times to get 90+90+90 swap that equal 270 degree
                for (int i = 0; i < 3; i++) {
                    for (int k = 0; k < RGB; k++) {
                        for (int i = 0; i < SIZE / 2; i++) {
                            for (int j = i; j < SIZE - i - 1; j++) {
                                char helper = image[i][j][k];
                                image[i][j][k] = image[SIZE - 1 - j][i][k];
                                image[SIZE - 1 - j][i][k] = image[SIZE - 1 - i][SIZE - 1 - j][k];
                                image[SIZE - 1 - i][SIZE - 1 - j][k] = image[j][SIZE - 1 - i][k];
                                image[j][SIZE - 1 - i][k] = helper;
                            }
                        }
                    }
                }
            }

        };
            break;


        case '7': {
            //          filter 7 : Detect image edges filter

//  convert image to black & white
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    //      if pixel color above 127 (white dgrees) let it = 255 (solid white)
                    if (image[i][j][0] > 127)
                        image3[i][j] = 255;
                        //          else if pixel color under 127 (black dgrees) let it = 0 (solid black)
                    else
                        image3[i][j] = 0;
                }
            }

            int x = 0, y = 0, down, up, right, center, left;

            while (true) {
//      assign top & mid & right & left and bot pixels in each 3*3 matrix in photo
                center = image3[y + 1][x + 1];
                right = image3[y + 1][x + 2];
                left = image3[y + 1][x];
                down = image3[y + 2][x + 1];
                up = image3[y][x + 1];

//      edge detection equation
                image4[y + 1][x + 1] = (right + left + down + up) - (center * 4);



//      condition to break the loop & increamnt
                if (y == 253 && x == 253) { break; }
                else { y++; }

                if (y == 254) {
                    y = 0;
                    x++;
                }

            }

//  invert image colors
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
//          subtract 255 from each pixel to get the invert pixel color
                    image4[i][j] = 255 - image4[i][j];
                }
            }
        };
            break;


        case '8': {
            //          filter 8 : Enlarge one out of 4 quarter in the image

            unsigned int size, xx, yy;

            //User is required to enter number of the quarter to be enlarged
            cout << "which quarter of the picture do you wish to enlarge?" << '\n';
            cin >> size;

            //Set StartX and StartY positions to specify the desired quarter to be enlarged
            switch (size) {
                case 1:
                    xx = yy = 0;
                    break;

                case 2:
                    xx = 0;
                    yy = SIZE / 2;
                    break;

                case 3:
                    xx = SIZE / 2;
                    yy = 0;
                    break;

                case 4:
                    xx = SIZE / 2;
                    yy = SIZE / 2;
                    break;

                default :
                    cout << "invalid input please try again";

                    break;

            }
            //Duplicate each column of the selected quarter to increase its width for each RGB value
            int zz = 0;
            for (int k = xx; k < SIZE; k++) {
                int color = 0;
                for (int i = yy; i < SIZE; i++) {

                    if (color > 256) break;

                    image2[zz][++color][0] = image[k][i][0];
                    image2[zz][color][1] = image[k][i][1];
                    image2[zz][color][2] = image[k][i][2];

                    if (color > 256) break;

                    image2[zz][++color][0] = image[k][i][0];
                    image2[zz][color][1] = image[k][i][1];
                    image2[zz][color][2] = image[k][i][2];
                }

                //Duplicate each row of the selected quarter to increase its length for each RGB value
                for (int j = 0; j < SIZE; j++) {

                    image2[zz + 1][j][0] = image2[zz][j][0];
                    image2[zz + 1][j][1] = image2[zz][j][1];
                    image2[zz + 1][j][2] = image2[zz][j][2];
                }
                zz += 2;

                if (zz > 256) break;
            }
        };
            break;


        case '9': {
            //          filter 9 : Shrink image with 3 different sizes

            //User is required to enter ratio by which the dimensions will be shrunk
            int min;
            cout << "Enter 1 or 2 or 3 to Shrink to (1/2) or (1/3) or (1/4) respectively : ";
            cin >> min;


            min = min + 1;
            int row = 0;
            for (int i = 0; i < SIZE; i++) {
                int col = 0;
                for (int j = 0; j < SIZE; j++) {
                    //If the current pixel is out of range(dependent on the ratio) set its value to 255(white)
                    if (i > SIZE / min || j > SIZE / min) {


                        image[i][j][0] = 255;
                        image[i][j][1] = 255;
                        image[i][j][2] = 255;


                    } else {
                        //exclude pixels depending on specified ratio

                        image[i][j][0] = image[row][col][0];
                        image[i][j][1] = image[row][col][1];
                        image[i][j][2] = image[row][col][2];

                    }

                    col += min;

                }
                row += min;

            }
        };
            break;
    }
}