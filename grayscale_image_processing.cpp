// FCAI - CS213 Programming II – 2023 / 2024 - Object Oriented Programming
// Assignment 1
// Teaching Assistant : Dr. Mohammad El-Ramly
// Author1 Name & ID : Mohamed Eِlfateh Esmat - 20220970 - Group A - s10
// Author2 Name & ID : Mohamed Rabea Mohamed - 20220424 - Group B - s8
// Author3 Name & ID : Reem Mohamed Mahmoud  - 20221230 - Group B - s18
// Last Modification Date : 17 / 10 /2023
// program Name : main.cpp
// Program Purpose : Black and White Image processing using 15 different filter
//


#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include "bmplib.h"
#include "bmplib.cpp"
using namespace std ;
unsigned char TestImage1 [SIZE][SIZE];
unsigned char TestImage2 [SIZE][SIZE];


void ReadImage() ;
void Filtering ();
void NewImage ();


int main() {

    ReadImage() ;
    Filtering ();
    NewImage ();

    return 0;
}

//_________________________________________

void ReadImage()  {
    char ImageName[100];
    cout  <<"Ahlan ya user ya habibi :)\n" ;
    cout << "Please enter file name of the image to process: \n";
    cin >> ImageName ;

    // Add to it .bmp extension and load image
    strcat (ImageName, ".bmp");
    readGSBMP(ImageName, TestImage1);
}

//_________________________________________

void NewImage ()  {
    char ImageNewName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> ImageNewName;

    // Add to it .bmp extension and load image
    strcat (ImageNewName, ".bmp");
    writeGSBMP(ImageNewName, TestImage1);
}

//_________________________________________

void Filtering()  {
    //          applying the below filters on a black and white image
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

    cin >>  filter ;

    switch (filter) {
        case '0': {
            //          zero case : Exit
           cout << "Program Exit " <<'\n' ;
        };
            break;

        case '5': {
            //          filter 5 : Dareken or Ligthen image filter

            string s;
            cout << "Do you want to darken or lighten ?"<<'\n';
            cout << "please enter the word darken or lighten :";
            cin >> s;

            //          in darken case divide each pixel over 2 to get the half light
            if (s == "darken") {
                for (int i = 0; i < SIZE; i++) {
                    for (int j = 0; j < SIZE; j++) {
                        TestImage1[i][j] = TestImage1[i][j] / 2;
                    }
                }
//                in lighten case increase each pixel < 205 by 50 and if the pixel >
//                205 let pixel eqaul 255 to avoid overload

            } else if (s == "lighten") {
                for (int i = 0; i < SIZE; i++) {
                    for (int j = 0; j < SIZE; j++) {
                        TestImage1[i][j] = (TestImage1[i][j]) + ((255 - TestImage1[i][j]) / 2);
                    }
                }
            } else {
                cout << "Error, Wrong Choice! " << '\n';
                cout << "   Please restart and  try again " ;
            }
        };
            break;


        case '6': {
            //          filter 6 : Rotate Image filter with 3 different degrees

            string s;
            cout << "Rotate (90) , (180) or (270) ?";
            cin >> s;

            if (s == "90") {
                for (int i = 0; i < SIZE / 2; i++) {
                    for (int j = i; j < SIZE - i - 1; j++) {
                        //              Store current pixel in helper variable

                        //              Swap elements of each cycle
                        //              in clockwise direction by 90 degree
                        int temp = TestImage1[i][j];
                        //              Move values from right to top
                        TestImage1[i][j] = TestImage1[SIZE - 1 - j][i];
                        //              Move values from bottom to right
                        TestImage1[SIZE - 1 - j][i] = TestImage1[SIZE - 1 - i][SIZE - 1 - j];
                        //              Move values from left to bottom
                        TestImage1[SIZE - 1 - i][SIZE - 1 - j] = TestImage1[j][SIZE - 1 - i];
                        //              Assign helper to left
                        TestImage1[j][SIZE - 1 - i] = temp;
                    }
                }
            } else if (s == "180") {
//      in 180 degree we used the main algorithm of 90 degree two times to get 90+90 swap that equal 180 degree
                for (int i = 0; i < SIZE; i++) {
                    for (int j = i; j < SIZE; j++) {
                        swap(TestImage1[i][j], TestImage1[j][i]);
                    }
                }


                for (int i = 0; i < SIZE; i++) {
                    for (int j = 0, k = SIZE - 1; j < k; j++, k--) {
                        swap(TestImage1[j][i], TestImage1[k][i]);
                    }
                }


                for (int i = 0; i < SIZE; i++) {
                    for (int j = i; j < SIZE; j++) {
                        swap(TestImage1[i][j], TestImage1[j][i]);
                    }
                }


                for (int i = 0; i < SIZE; i++) {
                    for (int j = 0, k = SIZE - 1; j < k; j++, k--) {
                        swap(TestImage1[j][i], TestImage1[k][i]);
                    }
                }
            } else {
//      in 270 degree we used the main algorithm of 90 degree three times to get 90+90+90 swap that equal 270 degree

                for (int i = 0; i < SIZE / 2; i++) {
                    for (int j = i; j < SIZE - i - 1; j++) {
                        int temp = TestImage1[i][j];
                        TestImage1[i][j] = TestImage1[j][SIZE - i - 1];
                        TestImage1[j][SIZE - i - 1] = TestImage1[SIZE - i - 1][SIZE - j - 1];
                        TestImage1[SIZE - i - 1][SIZE - j - 1] = TestImage1[SIZE - j - 1][i];
                        TestImage1[SIZE - j - 1][i] = temp;
                    }
                }
            }

        };
            break;


        case '7': {
            //          filter 7 : Detect image edges filter

            //  convert image to black & white
            unsigned char arr[SIZE][SIZE];
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    //      if pixel color above 127 (white dgrees) let it = 255 (solid white)
                    arr[i][j] = TestImage1[i][j];
                }
            }

            for (int i = 1; i < SIZE - 1; i++) {
                for (int j = 1; j < SIZE - 1; j++) {
                    //      edge detection equation
                    int x = 2 * arr[i][j - 1] - 2 * arr[i][j + 1] + arr[i - 1][j - 1] - arr[i - 1][j + 1] +
                            arr[i + 1][j - 1] - arr[i + 1][j + 1];
                    //      assign top & mid & right & left and bot pixels in each 3*3 matrix in photo
                    int y = 2 * arr[i + 1][j] - 2 * arr[i - 1][j] + arr[i + 1][j - 1] - arr[i - 1][j - 1] +
                            arr[i + 1][j + 1] - arr[i - 1][j + 1];

                    if (abs(x) > 100 || abs(y) > 100) {
                        TestImage1[i][j] = 0;
                    } else {
                        //          else if pixel color under 127 (black dgrees) let it = 0 (solid black)
                        TestImage1[i][j] = 255;
                    }
                }
            }
        };
            break;


        case '8': {
            //          filter 8 : Enlarge one out of 4 quarter in the image

            unsigned char temp[SIZE / 2][SIZE / 2];
            //User is required to enter number of the quarter to be enlarged
            int startRow, startCol, endRow, endCol;
            int quarter = 0;
            while (quarter > 4 || quarter < 1) {
                cout << "Which quarter to enlarge 1, 2, 3 or 4?" << "\n";
                cin >> quarter;
            }
            //Set Start row and Start colum positions to specify the desired quarter to be enlarged
            startRow = quarter == 1 || quarter == 2 ? 0 : SIZE / 2;
            endRow = quarter == 1 || quarter == 2 ? SIZE / 2 : SIZE;
            startCol = quarter == 1 || quarter == 3 ? 0 : SIZE / 2;
            endCol = quarter == 1 || quarter == 3 ? SIZE / 2 : SIZE;
//Duplicate each column of the selected quarter to increase its width for each RGB value
            for (int i = startRow, row = 0; i < endRow; i++) {
                for (int j = startCol, col = 0; j < endCol; j++) {
                    temp[row][col] = TestImage1[i][j];
                    col++;
                }
                row++;
            }

            for (int i = 0, row = 0; i < SIZE / 2; i++) {
                for (int j = 0, col = 0; j < SIZE / 2; j++) {
                    //Duplicate each row of the selected quarter to increase its length for each RGB value
                    TestImage1[row][col] = temp[i][j];
                    TestImage1[row + 1][col] = temp[i][j];
                    TestImage1[row][col + 1] = temp[i][j];
                    TestImage1[row + 1][col + 1] = temp[i][j];
                    col += 2;
                }
                row += 2;
            }

        };
            break;


        case '9': {
            //          filter 9 : Shrink image with 3 different sizes

            int num;
            cout << "Enter 1 or 2 or 3 to Shrink to (1/2) or (1/3) or (1/4) respectively : " ;
            cin >> num;
            //User is required to enter ratio by which the dimensions will be shrunk
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    if (i != 0) {
                        //If the current pixel is out of range(dependent on the ratio) set its value to 255(white)
                        for (int x = i; x <= SIZE - i; x++) {
                            if (x == SIZE - i) {
                                TestImage1[x][j] = 255;
                            } else {
                                //exclude pixels depending on specified ratio
                                TestImage1[x][j] = TestImage1[x + num][j];
                            }
                        }
                    }

                }
            }
            for (int i = 0; i < SIZE / 2; i++){
                for (int j = 0; j < SIZE; j++){
                    if (j != 0) {
                        for (int x = j; x <= SIZE - j; x++) {
                            if (x == SIZE - j) {
                                TestImage1[i][x] = 255;
                            } else {
                                TestImage1[i][x] = TestImage1[i][x + num];
                            }
                        }
                    }
                }

            }
        };
            break;

