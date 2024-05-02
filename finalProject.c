#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 100

void loadImage(int pixels[MAX_SIZE][MAX_SIZE], int *size) {
    char filename[100];
    printf("Enter the filename: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    fscanf(file, "%d", size);
    for (int i = 0; i < *size; i++) {
        for (int j = 0; j < *size; j++) {
            fscanf(file, "%d", &pixels[i][j]);
        }
    }

    fclose(file);
    printf("Image loaded successfully.\n");
}

void displayImage(int pixels[MAX_SIZE][MAX_SIZE], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", pixels[i][j]);
        }
        printf("\n");
    }
}

void editImage(int pixels[MAX_SIZE][MAX_SIZE], int size) {
    int editChoice;
    do {
        printf("\nEdit Menu:\n");
        printf("1. Crop\n");
        printf("2. Dim\n");
        printf("3. Brighten\n");
        printf("4. Rotate\n");
        printf("5. Save edited image\n");
        printf("6. Back to main menu\n");
        printf("Enter your choice: ");
        scanf("%d", &editChoice);

        switch (editChoice) {
            case 1:
                cropImage(pixels, &size);
                break;
            case 2:
                dimImage(pixels, size);
                break;
            case 3:
                brightenImage(pixels, size);
                break;
            case 4:
                rotateImage(pixels, &size);
                break;
            case 5:
                saveImage(pixels, size);
                break;
            case 6:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (editChoice != 6);
}

void saveImage(int pixels[MAX_SIZE][MAX_SIZE], int size) {
    char filename[100];
    printf("Enter the filename to save: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    fprintf(file, "%d\n", size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            fprintf(file, "%d ", pixels[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("Image saved successfully.\n");
}

void cropImage(int pixels[MAX_SIZE][MAX_SIZE], int *size) {
    int startX, startY, endX, endY;
    printf("Enter start X coordinate: ");
    scanf("%d", &startX);
    printf("Enter start Y coordinate: ");
    scanf("%d", &startY);
    printf("Enter end X coordinate: ");
    scanf("%d", &endX);
    printf("Enter end Y coordinate: ");
    scanf("%d", &endY);

    int newSize = endX - startX + 1;
    int croppedPixels[MAX_SIZE][MAX_SIZE];
    for (int i = startX; i <= endX; i++) {
        for (int j = startY; j <= endY; j++) {
            croppedPixels[i - startX][j - startY] = pixels[i][j];
        }
    }

    *size = newSize;
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            pixels[i][j] = croppedPixels[i][j];
        }
    }
    printf("Image cropped successfully.\n");
}

void dimImage(int pixels[MAX_SIZE][MAX_SIZE], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            pixels[i][j] -= 1;
            if (pixels[i][j] < 0) {
                pixels[i][j] = 0;
            }
        }
    }
    printf("Image dimmed successfully.\n");
}

void brightenImage(int pixels[MAX_SIZE][MAX_SIZE], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            pixels[i][j] += 1;
            if (pixels[i][j] > 255) {
                pixels[i][j] = 255;
            }
        }
    }
    printf("Image brightened successfully.\n");
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
    printf("Image rotated successfully.\n");
}

int main() {
    int pixels[MAX_SIZE][MAX_SIZE];
    int size = 0;
    bool loaded = false;

    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Load a new image\n");
        printf("2. Display the current image\n");
        printf("3. Edit the current image\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
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
                    printf("No image loaded!\n");
                break;
            case 3:
                if (loaded)
                    editImage(pixels, size);
                else
                    printf("No image loaded!\n");
                break;
            case 4:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 4);

    return 0;
}
