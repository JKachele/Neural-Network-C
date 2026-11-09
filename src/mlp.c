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
#include <time.h>

static float frand(float min, float max) {
        float r = (float)rand()/(float)(RAND_MAX/(max-min));
        return r + min;
}

struct mlp *createMLP(void) {
        struct mlp *mlp = malloc(sizeof(struct mlp));
        return mlp;
}

void randomizeMLP(struct mlp *mlp) {
        srand((unsigned)time(0));

        // Input Weights
        for (int i = 0; i < HIDDER_LAYER_SIZE; i++) {
                for (int j = 0; j < INPUT_LAYER_SIZE; j++) {
                        mlp->inWeights.mat[i][j] = frand(-1, 1);
                }
        }

        // Hidden Weights
        for (int l = 0; l < NUM_LAYERS - 3; l++) {
                for (int i = 0; i < HIDDER_LAYER_SIZE; i++) {
                        for (int j = 0; j < INPUT_LAYER_SIZE; j++) {
                                mlp->hiddenWeights[l].mat[i][j] = frand(-1, 1);
                        }
                }
        }

        // Output Weights
        for (int i = 0; i < OUTPUT_LAYER_SIZE; i++) {
                for (int j = 0; j < HIDDER_LAYER_SIZE; j++) {
                        mlp->outWeights.mat[i][j] = frand(-1, 1);
                }
        }

        // Hidden Layer Biases
        for (int l = 0; l < NUM_LAYERS - 2; l++) {
                for (int i = 0; i < HIDDER_LAYER_SIZE; i++) {
                        mlp->hidden[l].bias[i] = frand(-1, 1);
                }
        }

        // Output Layer Biases
        for (int i = 0; i < OUTPUT_LAYER_SIZE; i++) {
                        mlp->outputBias.vec[i] = frand(-1, 1);
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
        for (int i = 0; i < HIDDER_LAYER_SIZE; i++) {
                for (int j = 0; j < INPUT_LAYER_SIZE; j++) {
                        fwrite(&mlp->inWeights.mat[i][j], sizeof(float), 1, file);
                }
        }

        // Hidden Weights
        for (int l = 0; l < NUM_LAYERS - 3; l++) {
                for (int i = 0; i < HIDDER_LAYER_SIZE; i++) {
                        for (int j = 0; j < INPUT_LAYER_SIZE; j++) {
                                fwrite(&mlp->hiddenWeights[l].mat[i][j], sizeof(float), 1, file);
                        }
                }
        }

        // Output Weights
        for (int i = 0; i < OUTPUT_LAYER_SIZE; i++) {
                for (int j = 0; j < HIDDER_LAYER_SIZE; j++) {
                        fwrite(&mlp->outWeights.mat[i][j], sizeof(float), 1, file);
                }
        }

        // Hidden Layer Biases
        for (int l = 0; l < NUM_LAYERS - 2; l++) {
                for (int i = 0; i < HIDDER_LAYER_SIZE; i++) {
                        fwrite(&mlp->hidden[l].bias[i], sizeof(float), 1, file);
                }
        }

        // Output Layer Biases
        for (int i = 0; i < OUTPUT_LAYER_SIZE; i++) {
                fwrite(&mlp->outputBias.vec[i], sizeof(float), 1, file);
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
        for (int i = 0; i < HIDDER_LAYER_SIZE; i++) {
                for (int j = 0; j < INPUT_LAYER_SIZE; j++) {
                        fread(&mlp->inWeights.mat[i][j], sizeof(float), 1, file);
                }
        }

        // Hidden Weights
        for (int l = 0; l < NUM_LAYERS - 3; l++) {
                for (int i = 0; i < HIDDER_LAYER_SIZE; i++) {
                        for (int j = 0; j < INPUT_LAYER_SIZE; j++) {
                                fread(&mlp->hiddenWeights[l].mat[i][j], sizeof(float), 1, file);
                        }
                }
        }

        // Output Weights
        for (int i = 0; i < OUTPUT_LAYER_SIZE; i++) {
                for (int j = 0; j < HIDDER_LAYER_SIZE; j++) {
                        fread(&mlp->outWeights.mat[i][j], sizeof(float), 1, file);
                }
        }

        // Hidden Layer Biases
        for (int l = 0; l < NUM_LAYERS - 2; l++) {
                for (int i = 0; i < HIDDER_LAYER_SIZE; i++) {
                        fread(&mlp->hidden[l].bias[i], sizeof(float), 1, file);
                }
        }

        // Output Layer Biases
        for (int i = 0; i < OUTPUT_LAYER_SIZE; i++) {
                fread(&mlp->outputBias.vec[i], sizeof(float), 1, file);
        }

        fclose(file);
}

void runMLP(struct mlp mlp, struct inputLayer input, struct outputLayer output) {
}

