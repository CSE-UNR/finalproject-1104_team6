/******************************/
/* Name: final.c */
/* Purpose: Group Project */
/* Author: Christina Viola and Josh Riggan */
/******************************/

#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 100

void loadImage(int pixels[MAX_SIZE][MAX_SIZE], int *size);
void displayImage(int pixels[MAX_SIZE][MAX_SIZE], int size);
void editImage(int pixels[MAX_SIZE][MAX_SIZE], int *size);
void cropImage(int pixels[MAX_SIZE][MAX_SIZE], int *size);
void dimImage(int pixels[MAX_SIZE][MAX_SIZE], int size);
void brightenImage(int pixels[MAX_SIZE][MAX_SIZE], int size);
void rotateImage(int pixels[MAX_SIZE][MAX_SIZE], int *size);
void saveImage(int pixels[MAX_SIZE][MAX_SIZE], int size);

int main() {
    int pixels[MAX_SIZE][MAX_SIZE];
    int size = 0;
    bool loaded = false;
    int choice;

    do {
        printf("\n**ERINSTAGRAM**\n");
        printf("1: Load image\n");
        printf("2: Display image\n");
        printf("3: Edit image\n");
        printf("0: Exit\n\n");
        printf("Choose from one of the options above ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                loadImage(pixels, &size);
                loaded = true;
                break;
            case 2:
                if (loaded)
                    displayImage(pixels, size);
                else
                    printf("No image loaded\n");
                break;
            case 3:
                if (loaded)
                    editImage(pixels, &size);
                else
                    printf("No image loaded\n");
                break;
            case 0:
                printf("Exiting program\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    } while (choice != 0);

    return 0;
}

void loadImage(int pixels[MAX_SIZE][MAX_SIZE], int *size) {
    char filename[100];
    printf("Enter the filename");
    scanf("%s", filename);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open the file\n");
        return;
    }

    int row = 0, col = 0;
    while (fscanf(file, "%d", &pixels[row][col]) == 1) {
        col++;
        if (col >= MAX_SIZE) {
            col = 0;
            row++;
            if (row >= MAX_SIZE) {
                printf("Image is too big\n");
                fclose(file);
                return;
            }
        }
    }

    *size = row + 1;
    printf("Image loaded successfully\n");
    fclose(file);
}

void displayImage(int pixels[MAX_SIZE][MAX_SIZE], int size) {
    printf("\nDisplaying image\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            switch (pixels[i][j]) {
                case 0:
                    printf(" ");
                    break;
                case 1:
                    printf(".");
                    break;
                case 2:
                    printf("o");
                    break;
                case 3:
                    printf("O");
                    break;
                case 4:
                    printf("0");
                    break;
                default:
                    printf(" ");
            }
        }
        printf("\n");
    }
}

void editImage(int pixels[MAX_SIZE][MAX_SIZE], int *size) {
    int editChoice;
    do {
        printf("\n**EDITING**\n");
        printf("1: Crop image\n");
        printf("2: Dim image\n");
        printf("3: Brighten image\n");
        printf("4: Rotate image\n");
        printf("0: Return to main menu\n\n");
        printf("Choose an option ");
        scanf("%d", &editChoice);

        switch (editChoice) {
            case 1:
                cropImage(pixels, size);
                break;
            case 2:
                dimImage(pixels, *size);
                break;
            case 3:
                brightenImage(pixels, *size);
                break;
            case 4:
                rotateImage(pixels, size);
                break;
            case 0:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    } while (editChoice != 0);
}

void cropImage(int pixels[MAX_SIZE][MAX_SIZE], int *size) {
    printf("The image you want to crop is %d x %d.\n", *size, *size);
    printf("The row and column values start in the upper lefthand corner.\n");

    int leftCol, rightCol, topRow, bottomRow;

    printf("Enter the new left side column ");
    scanf("%d", &leftCol);
    printf("Enter the new right side column ");
    scanf("%d", &rightCol);
    printf("Enter the new top side row ");
    scanf("%d", &topRow);
    printf("Enter the new bottom side row ");
    scanf("%d", &bottomRow);

    if (leftCol < 0 || rightCol >= *size || topRow < 0 || bottomRow >= *size || leftCol >= rightCol || topRow >= bottomRow) {
        printf("Invalid crop dimensions\n");
        return;
    }

    int newSize = rightCol - leftCol + 1;
    int croppedPixels[MAX_SIZE][MAX_SIZE];
    for (int i = topRow; i <= bottomRow; i++) {
        for (int j = leftCol; j <= rightCol; j++) {
            croppedPixels[i - topRow][j - leftCol] = pixels[i][j];
        }
    }

    *size = newSize;
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            pixels[i][j] = croppedPixels[i][j];
        }
    }
    printf("Image cropped\n");
}

void dimImage(int pixels[MAX_SIZE][MAX_SIZE], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            pixels[i][j]--;
            if (pixels[i][j] < 0) {
                pixels[i][j] = 0;
            }
        }
    }
    printf("Image dimmed\n");
}

void brightenImage(int pixels[MAX_SIZE][MAX_SIZE], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            pixels[i][j]++;
            if (pixels[i][j] > 4) {
                pixels[i][j] = 4;
            }
        }
    }
    printf("Image brightened\n");
}

void rotateImage(int pixels[MAX_SIZE][MAX_SIZE], int *size) {
    int rotatedPixels[MAX_SIZE][MAX_SIZE];
    int newSize = *size;
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            rotatedPixels[j][newSize - i - 1] = pixels[i][j];
        }
    }

    *size = newSize;
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            pixels[i][j] = rotatedPixels[i][j];
        }
    }
    printf("Image rotated\n");
}

void saveImage(int pixels[MAX_SIZE][MAX_SIZE], int size) {
    char filename[100];
    printf("Enter the filename to save the imag ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Failed to open the file\n");
        return;
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            fprintf(file, "%d ", pixels[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("Image saved\n");
}
