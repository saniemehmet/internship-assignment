#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <malloc.h>
#include<errno.h>
#include <string.h>

bool hasNeighbours(char c, char** array, int32_t matrixHeight, int32_t matrixWidth, int32_t rowIndex, int32_t colIndex) {
    char neighbour;
    //check if a top neighbour exists
    if (rowIndex - 1 >= 0) { 
        neighbour = array[rowIndex - 1][colIndex];
        if (neighbour == c) { // if yes, check if the top neighbour is equal to our character
            return true;
        }
    }
    //check if a bottom neighbour exists
    if (rowIndex + 1 < matrixHeight) { 
        neighbour = array[rowIndex + 1][colIndex];
        if (neighbour == c) {
            return true;
        }
    }
    //check if a right neighbour exists
    if (colIndex - 1 >= 0) { 
        neighbour = array[rowIndex][colIndex - 1];
        if (neighbour == c) {
            return true;
        }
    }
    //check if a left neighbour exists
    if (colIndex + 1 < matrixWidth) {
        neighbour = array[rowIndex][colIndex + 1];
        if (neighbour == c) {
            return true;
        }
    }
    return false;
}

int32_t findNeighboursCount(char c, char** array, int32_t matrixHeight, int32_t matrixWidth) {
    int sum = 0;
    for (int32_t row = 0; row < matrixHeight; row++) {
        for (int32_t col = 0; col < matrixWidth; col++) {
            if (array[row][col] == c) {
                if (hasNeighbours(c, array, matrixHeight, matrixWidth, row, col) == true) {
                    sum += 1;
                }
            }
        }
    }
    return sum;
}

int32_t findMax(char** arr, int32_t matrixHeight, int32_t matrixWidth) {
    int result_R = findNeighboursCount('R', arr, matrixHeight, matrixWidth);
    int result_B = findNeighboursCount('B', arr, matrixHeight, matrixWidth);
    int result_G = findNeighboursCount('G', arr, matrixHeight, matrixWidth);
    int max = result_R;
    if (max < result_B) {
        max = result_B;
    }
    if (max < result_G) {
        max = result_G;
    }
    return max;
}

int32_t findLongestSequence(char* filePath) {
    FILE* file;
    errno_t err;
    if ((err = fopen_s(&file, filePath, "r")) != 0)
    {
        printf("File was not opened.\n");
    }
    else {
        int32_t matrixHeight, matrixWidth;//n-rows, m-cols
        fscanf(file, "%d %d", &matrixHeight, &matrixWidth);

        char** arr = malloc(matrixHeight * matrixWidth * sizeof(char*));
        for (int rows = 0; rows < matrixHeight; rows++)
        {
            arr[rows] = malloc(matrixHeight * matrixWidth * sizeof(char));
        }
        for (int row = 0; row < matrixHeight; row++) {
            for (int col = 0; col < matrixWidth; col++) {
                fscanf(file, "%s", &arr[row][col]);
            }
        }

        int32_t result = findMax(arr, matrixHeight, matrixWidth);

        for (int row = 0; row < matrixHeight; row++) {
            free(arr[row]);
        }
        free(arr);
        fclose(file);
        return result;
    }

}
int main(int argc, char* argv[]) {
    char* test_1 = ".//tests//test_1.txt";
    char* test_2 = ".//tests//test_2.txt";
    char* test_3 = ".//tests//test_3.txt";
    char* test_4 = ".//tests//test_4.txt";

    for (int i = 0; i < argc; i++)
    {
        if (strcmp("test_1", argv[i]) == 0) {
            printf("%d ",findLongestSequence(test_1));
        }
        else if (strcmp("test_2", argv[i]) == 0) {
            printf("%d ", findLongestSequence(test_2));
        }
        else if (strcmp("test_3", argv[i]) == 0) {
            printf("%d ", findLongestSequence(test_3));
        }
        else if (strcmp("test_4", argv[i]) == 0) {
            printf("%d ", findLongestSequence(test_4));
        }
    }
    return 0;
}