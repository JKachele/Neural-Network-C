/*************************************************
 *File----------main.c
 *Project-------Neural-Network-C
 *Author--------Justin Kachele
 *Created-------Monday Nov 09, 2026 10:34:53 EST
 *License-------GNU GPL-3.0
 ************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "mlp.h"

#define IMAGE_SIZE 28

struct image {
        u8 data[IMAGE_SIZE][IMAGE_SIZE];
        u8 label;
};

void printImage(struct image image) {
        printf("\033[48;5;16m\033[38;5;15m");
        for (int y = 0; y < IMAGE_SIZE; y += 2) {
                for (int x = 0; x < IMAGE_SIZE; x++) {
                        u8 B1 = image.data[y][x];
                        u8 B2 = image.data[y+1][x];
                        printf("\033[48;2;%d;%d;%dm",(int)B1,(int)B1,(int)B1);
                        printf("\033[38;2;%d;%d;%dm",(int)B2,(int)B2,(int)B2);
                        printf("\xE2\x96\x83");
                }
                printf("\033[38;2;0;0;0m");	   
                printf("\033[48;2;0;0;0m\n");
        }
        printf("\033[48;5;16m\033[38;5;15m");
}

void printOutput(struct outputLayer output, float cost) {
        for (int i = 0; i < 10; i++) {
                printf("%d: %.2f\n", i, output.vec[i]);
        }
        printf("Cost: %.2f\n", cost);
}

FILE *openFile(const char *fileName) {
        FILE *file = fopen(fileName, "rb");
        if (file == NULL) {
                fprintf(stderr, "File \"%s\" Not Found!\n", fileName);
                exit(EXIT_FAILURE);
        }
        return file;
}

int getdataLength(FILE *file) {
        fseek(file, 4, SEEK_SET);
        u32 numImages;
        fread(&numImages, 4, 1, file);
        return (int)__builtin_bswap32(numImages);
}

void getImages(struct image images[], int numImages, FILE *imageFile, FILE *labelFile) {
        fseek(imageFile, 16, SEEK_SET);
        fseek(labelFile, 8, SEEK_SET);
        for (int i = 0; i < numImages; i++) {
                struct image *image = &images[i];
                fread(&image->label, 1, 1, labelFile);
                for (int y = 0; y < IMAGE_SIZE; y++) {
                        for (int x = 0; x < IMAGE_SIZE; x++) {
                                fread(&image->data[y][x], 1, 1, imageFile);
                        }
                }
        }
}

struct inputLayer imageToInput(struct image image) {
        struct inputLayer input;
        int i = 0;
        for (int y = 0; y < IMAGE_SIZE; y++) {
                for (int x = 0; x < IMAGE_SIZE; x++) {
                        input.vec[i++] = (float)image.data[y][x] / 255;
                }
        }
        return input;
}

float outputCost(struct outputLayer output, u8 expected) {
        float cost = 0;
        for (int i = 0; i < 10; i++) {
                float diff = output.vec[i];
                if (i == expected) {
                        diff -= 1.0;
                }
                cost += (diff * diff);
        }
        return cost;
}

int main(int argc, char *argv[]) {
        const char *TrainImagesName = "assets/MNIST/train-images.idx3-ubyte";
        const char *TrainLabelsName = "assets/MNIST/train-labels.idx1-ubyte";
        // const char *TestImagesName  = "assets/MNIST/t10k-images.idx3-ubyte";
        // const char *TestLabelsName  = "assets/MNIST/t10k-labels.idx1-ubyte";

        FILE *imageFile = openFile(TrainImagesName);
        FILE *labelFile = openFile(TrainLabelsName);

        int numImages = getdataLength(imageFile);
        struct image *images = calloc(numImages, sizeof(struct image));
        getImages(images, numImages, imageFile, labelFile);
        // printImage(images[0]);

        struct mlp *mlp = createMLP();
        readMLP("assets/mlp.dat", mlp);
        // randomizeMLP(mlp);
        // writeMLP("assets/mlp.dat", mlp);

        mlp->input = imageToInput(images[0]);
        runMLP(mlp);
        float cost = outputCost(mlp->output, images[0].label);
        printOutput(mlp->output, cost);

        fclose(imageFile);
        fclose(labelFile);
        return 0;
}

