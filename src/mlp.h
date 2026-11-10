/*************************************************
 *File----------mlp.h
 *Project-------Neural-Network-C
 *Author--------Justin Kachele
 *Created-------Monday Nov 09, 2026 12:53:26 EST
 *License-------GNU GPL-3.0
 ************************************************/
#ifndef MLP_H
#define MLP_H

#include "util.h"

#define NUM_LAYERS 6
#define NUM_HIDDEN NUM_LAYERS - 2
#define INPUT_LAYER_SIZE 784
#define HIDDEN_LAYER_SIZE 64
#define OUTPUT_LAYER_SIZE 10

struct inputLayer {
        float vec[INPUT_LAYER_SIZE];
};
struct hiddenLayer {
        float vec[HIDDEN_LAYER_SIZE];
};
struct outputLayer {
        float vec[OUTPUT_LAYER_SIZE];
};

struct inputWeights {
        float mat[HIDDEN_LAYER_SIZE][INPUT_LAYER_SIZE];
        float bias[HIDDEN_LAYER_SIZE];
};
struct hiddenWeights {
        float mat[HIDDEN_LAYER_SIZE][HIDDEN_LAYER_SIZE];
        float bias[HIDDEN_LAYER_SIZE];
};
struct outputWeights {
        float mat[OUTPUT_LAYER_SIZE][HIDDEN_LAYER_SIZE];
        float bias[OUTPUT_LAYER_SIZE];
};

struct mlp {
        struct inputWeights inWeights;
        struct hiddenWeights hiddenWeights[NUM_HIDDEN-1];
        struct outputWeights outWeights;
        struct inputLayer input;
        struct hiddenLayer hiddenLayers[NUM_HIDDEN];
        struct outputLayer output;
};


struct mlp *createMLP(void);
void randomizeMLP(struct mlp *mlp);
void writeMLP(const char *filename, struct mlp *mlp);
void readMLP(const char *filename, struct mlp *mlp);

void runMLP(struct mlp *mlp);

#endif

