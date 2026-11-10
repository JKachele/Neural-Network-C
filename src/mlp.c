/*************************************************
 *File----------mlp.c
 *Project-------Neural-Network-C
 *Author--------Justin Kachele
 *Created-------Monday Nov 09, 2026 12:53:23 EST
 *License-------GNU GPL-3.0
 ************************************************/

#include "mlp.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

static float frand(float min, float max) {
        float r = (float)rand()/(float)(RAND_MAX/(max-min));
        return r + min;
}

struct mlp *createMLP(void) {
        struct mlp *mlp = malloc(sizeof(struct mlp));
        return mlp;
}

void initMLP(struct mlp *mlp) {
        // Input Weights
        for (int i = 0; i < HIDDEN_LAYER_SIZE; i++) {
                for (int j = 0; j < INPUT_LAYER_SIZE; j++) {
                        mlp->inWeights.mat[i][j] = 0.0;
                }
        }

        // Hidden Weights
        for (int l = 0; l < NUM_HIDDEN - 1; l++) {
                for (int i = 0; i < HIDDEN_LAYER_SIZE; i++) {
                        for (int j = 0; j < HIDDEN_LAYER_SIZE; j++) {
                                mlp->hiddenWeights[l].mat[i][j] = 0.0;
                        }
                }
        }

        // Output Weights
        for (int i = 0; i < OUTPUT_LAYER_SIZE; i++) {
                for (int j = 0; j < HIDDEN_LAYER_SIZE; j++) {
                        mlp->outWeights.mat[i][j] = 0.0;
                }
        }

        // Hidden Layer Biases
        for (int i = 0; i < HIDDEN_LAYER_SIZE; i++) {
                mlp->inWeights.bias[i] = 0.0;
        }
        for (int l = 0; l < NUM_HIDDEN-1; l++) {
                for (int i = 0; i < HIDDEN_LAYER_SIZE; i++) {
                        mlp->hiddenWeights[l].bias[i] = 0.0;
                }
        }

        // Output Layer Biases
        for (int i = 0; i < OUTPUT_LAYER_SIZE; i++) {
                        mlp->outWeights.bias[i] = 0.0;
        }
}

void randomizeMLP(struct mlp *mlp) {
        srand((unsigned)time(0));
        const float minVal = -0.5f;
        const float maxVal =  0.5f;

        // Input Weights
        for (int i = 0; i < HIDDEN_LAYER_SIZE; i++) {
                for (int j = 0; j < INPUT_LAYER_SIZE; j++) {
                        mlp->inWeights.mat[i][j] = frand(minVal, maxVal);
                }
        }

        // Hidden Weights
        for (int l = 0; l < NUM_HIDDEN - 1; l++) {
                for (int i = 0; i < HIDDEN_LAYER_SIZE; i++) {
                        for (int j = 0; j < HIDDEN_LAYER_SIZE; j++) {
                                mlp->hiddenWeights[l].mat[i][j] = frand(minVal, maxVal);
                        }
                }
        }

        // Output Weights
        for (int i = 0; i < OUTPUT_LAYER_SIZE; i++) {
                for (int j = 0; j < HIDDEN_LAYER_SIZE; j++) {
                        mlp->outWeights.mat[i][j] = frand(minVal, maxVal);
                }
        }

        // Hidden Layer Biases
        for (int i = 0; i < HIDDEN_LAYER_SIZE; i++) {
                mlp->inWeights.bias[i] = frand(minVal, maxVal);
        }
        for (int l = 0; l < NUM_HIDDEN-1; l++) {
                for (int i = 0; i < HIDDEN_LAYER_SIZE; i++) {
                        mlp->hiddenWeights[l].bias[i] = frand(minVal, maxVal);
                }
        }

        // Output Layer Biases
        for (int i = 0; i < OUTPUT_LAYER_SIZE; i++) {
                        mlp->outWeights.bias[i] = frand(minVal, maxVal);
        }
}

// Write to file in order: InputWeights, HiddenWeights, OutputWeights, HiddenBiases, OutputBiases
void writeMLP(const char *filename, struct mlp *mlp) {
        FILE *file = fopen(filename, "wb");
        if (file == NULL) {
                fprintf(stderr, "Error occured while creating file!\n");
                exit(EXIT_FAILURE);
        }

        // Input Weights
        for (int i = 0; i < HIDDEN_LAYER_SIZE; i++) {
                for (int j = 0; j < INPUT_LAYER_SIZE; j++) {
                        fwrite(&mlp->inWeights.mat[i][j], sizeof(float), 1, file);
                }
        }

        // Hidden Weights
        for (int l = 0; l < NUM_HIDDEN - 1; l++) {
                for (int i = 0; i < HIDDEN_LAYER_SIZE; i++) {
                        for (int j = 0; j < HIDDEN_LAYER_SIZE; j++) {
                                fwrite(&mlp->hiddenWeights[l].mat[i][j], sizeof(float), 1, file);
                        }
                }
        }

        // Output Weights
        for (int i = 0; i < OUTPUT_LAYER_SIZE; i++) {
                for (int j = 0; j < HIDDEN_LAYER_SIZE; j++) {
                        fwrite(&mlp->outWeights.mat[i][j], sizeof(float), 1, file);
                }
        }

        // Hidden Layer Biases
        for (int i = 0; i < HIDDEN_LAYER_SIZE; i++) {
                fwrite(&mlp->inWeights.bias[i], sizeof(float), 1, file);
        }
        for (int l = 0; l < NUM_HIDDEN-1; l++) {
                for (int i = 0; i < HIDDEN_LAYER_SIZE; i++) {
                        fwrite(&mlp->hiddenWeights[l].bias[i], sizeof(float), 1, file);
                }
        }

        // Output Layer Biases
        for (int i = 0; i < OUTPUT_LAYER_SIZE; i++) {
                fwrite(&mlp->outWeights.bias[i], sizeof(float), 1, file);
        }

        fclose(file);
}

void readMLP(const char *filename, struct mlp *mlp) {
        FILE *file = fopen(filename, "rb");
        if (file == NULL) {
                fprintf(stderr, "File \"%s\" Not Found!\n", filename);
                exit(EXIT_FAILURE);
        }

        // Input Weights
        for (int i = 0; i < HIDDEN_LAYER_SIZE; i++) {
                for (int j = 0; j < INPUT_LAYER_SIZE; j++) {
                        fread(&mlp->inWeights.mat[i][j], sizeof(float), 1, file);
                }
        }

        // Hidden Weights
        for (int l = 0; l < NUM_HIDDEN-1; l++) {
                for (int i = 0; i < HIDDEN_LAYER_SIZE; i++) {
                        for (int j = 0; j < HIDDEN_LAYER_SIZE; j++) {
                                fread(&mlp->hiddenWeights[l].mat[i][j], sizeof(float), 1, file);
                        }
                }
        }

        // Output Weights
        for (int i = 0; i < OUTPUT_LAYER_SIZE; i++) {
                for (int j = 0; j < HIDDEN_LAYER_SIZE; j++) {
                        fread(&mlp->outWeights.mat[i][j], sizeof(float), 1, file);
                }
        }

        // Hidden Layer Biases
        for (int i = 0; i < HIDDEN_LAYER_SIZE; i++) {
                fread(&mlp->inWeights.bias[i], sizeof(float), 1, file);
        }
        for (int l = 0; l < NUM_HIDDEN-1; l++) {
                for (int i = 0; i < HIDDEN_LAYER_SIZE; i++) {
                        fread(&mlp->hiddenWeights[l].bias[i], sizeof(float), 1, file);
                }
        }

        // Output Layer Biases
        for (int i = 0; i < OUTPUT_LAYER_SIZE; i++) {
                fread(&mlp->outWeights.bias[i], sizeof(float), 1, file);
        }

        fclose(file);
}

float sigmoid(float f) {
        return (1 / (1 + (float)exp(-f)));
}

float relu(float f) {
        return (f > 0) ? f : 0.0;
}

void softmax(struct outputLayer *output) {
        float max = output->vec[0];
        for (int i = 1; i < OUTPUT_LAYER_SIZE; i++) {
                if (output->vec[i] > max) {
                        max = output->vec[i];
                }
        }

        double sum = 0.0;
        double temp[OUTPUT_LAYER_SIZE];
        for (int i = 0; i < OUTPUT_LAYER_SIZE; i++) {
                temp[i] = exp((double)(output->vec[i] - max));
                sum += temp[i];
        }

        double recipSum = 1.0 / sum;
        for (int i = 0; i < OUTPUT_LAYER_SIZE; i++) {
                output->vec[i] = (float)(temp[i] * recipSum);
        }
}

// out(1 x sizeX) = mat(sizeX x sizeY) x vec(1 x sizeY)
static void matVecMul(int sizeX, int sizeY, float mat[][sizeX], float vec[], float out[]) {
        for (int y = 0; y < sizeY; y++) {
                out[y] = 0;
                for (int x = 0; x < sizeX; x++) {
                        out[y] += mat[y][x] * vec[x];
                }
        }
}

// out(sizeX x sizeY) = vec1(1 x sizeY) * vec2(sizeX x 1)
static void vecVecMul(int sizeX, int sizeY, float vec1[], float vec2[], float out[][sizeX]) {
        for (int y = 0; y < sizeY; y++) {
                for (int x = 0; x < sizeX; x++) {
                        out[y][x] = vec1[y] * vec2[x];
                }
        }
}

static void matAdd(int sizeX, int sizeY, float mat1[][sizeY], float mat2[][sizeX],
                float out[][sizeX]) {
        for (int y = 0; y < sizeY; y++) {
                for (int x = 0; x < sizeX; x++) {
                        out[y][x] = mat1[y][x] + mat2[y][x];
                }
        }
}

// out = vec1 + vec2
static void vecAdd(int size, float vec1[], float vec2[], float out[]) {
        for (int i = 0; i < size; i++) {
                out[i] = vec1[i] + vec2[i];
        }
}

// vec1 = vec1 - vec2
static void vecSub(int size, float vec1[], float vec2[], float out[]) {
        for (int i = 0; i < size; i++) {
                out[i] = vec1[i] - vec2[i];
        }
}

// out = func(vec)
static void vecFunc(int size, float vec[], float out[], float (*func)(float)) {
        for (int i = 0; i < size; i++) {
                out[i] = func(vec[i]);
        }
}

static void addMLP(struct mlp *mlp1, struct mlp *mlp2) {
        matAdd(INPUT_LAYER_SIZE, HIDDEN_LAYER_SIZE,
                        mlp1->inWeights.mat, mlp2->inWeights.mat, mlp1->inWeights.mat);
        vecAdd(HIDDEN_LAYER_SIZE, mlp1->inWeights.bias, mlp2->inWeights.bias, mlp1->inWeights.bias);
}

// Multiply input vector with input weight martix then add hidden layer biases. Then apply sigmoid
static void inputToHidden(struct inputLayer *input, struct inputWeights weights,
                struct hiddenLayer *hidden) {
        matVecMul(INPUT_LAYER_SIZE, HIDDEN_LAYER_SIZE, weights.mat, input->vec, hidden->vec);
        vecAdd(HIDDEN_LAYER_SIZE, hidden->vec, weights.bias, hidden->vec);
        vecFunc(HIDDEN_LAYER_SIZE, hidden->vec, hidden->vec, relu);
}

static void hiddenToHidden(struct hiddenLayer *hidden1, struct hiddenWeights weights,
                struct hiddenLayer *hidden2) {
        matVecMul(HIDDEN_LAYER_SIZE, HIDDEN_LAYER_SIZE, weights.mat, hidden1->vec, hidden2->vec);
        vecAdd(HIDDEN_LAYER_SIZE, hidden2->vec, weights.bias, hidden2->vec);
        vecFunc(HIDDEN_LAYER_SIZE, hidden2->vec, hidden2->vec, relu);
}

static void hiddenToOutput(struct hiddenLayer *hidden, struct outputWeights weights,
                struct outputLayer *output) {
        matVecMul(HIDDEN_LAYER_SIZE, OUTPUT_LAYER_SIZE, weights.mat, hidden->vec, output->vec);
        vecAdd(OUTPUT_LAYER_SIZE, output->vec, weights.bias, output->vec);
}

void runMLP(struct mlp *mlp) {
        inputToHidden(&mlp->input, mlp->inWeights, &mlp->hiddenLayers[0]);
        for (int i = 0; i < NUM_HIDDEN - 1; i++) {
                hiddenToHidden(&mlp->hiddenLayers[i], mlp->hiddenWeights[i],
                                &mlp->hiddenLayers[i+1]);
        }
        hiddenToOutput(&mlp->hiddenLayers[NUM_HIDDEN-1], mlp->outWeights, &mlp->output);
        softmax(&mlp->output);
}

void backProp(struct mlp *adjs, struct mlp *mlp, struct outputLayer expected) {
        struct mlp *temp = malloc(sizeof(struct mlp));
        vecSub(OUTPUT_LAYER_SIZE, mlp->output.vec, expected.vec, adjs->outWeights.bias);

        vecVecMul(HIDDEN_LAYER_SIZE, OUTPUT_LAYER_SIZE, adjs->outWeights.bias,
                        mlp->hiddenLayers[NUM_HIDDEN-1].vec, adjs->outWeights.mat);

        addMLP(adjs, temp);
        free(temp);
}

