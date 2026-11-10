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
#define INPUT_LAYER_SIZE 784
#define HIDDER_LAYER_SIZE 256
#define OUTPUT_LAYER_SIZE 10
#define EULER_NUMBER 2.71828182846

struct inputLayer {
        float vec[INPUT_LAYER_SIZE];
};
struct hiddenLayer {
        float vec[HIDDER_LAYER_SIZE];
        float bias[HIDDER_LAYER_SIZE];
};
struct outputLayer {
        float vec[OUTPUT_LAYER_SIZE];
};

struct inputWeights {
        float mat[HIDDER_LAYER_SIZE][INPUT_LAYER_SIZE];
};
struct hiddenWeights {
        float mat[HIDDER_LAYER_SIZE][HIDDER_LAYER_SIZE];
};
struct outputWeights {
        float mat[OUTPUT_LAYER_SIZE][HIDDER_LAYER_SIZE];
};

struct mlp {
        struct hiddenLayer hidden[NUM_LAYERS - 2];
        struct outputLayer outputBias;
        struct inputWeights inWeights;
        struct hiddenWeights hiddenWeights[NUM_LAYERS - 3];
        struct outputWeights outWeights;
};


struct mlp *createMLP(void);
void randomizeMLP(struct mlp *mlp);
void writeMLP(const char *filename, struct mlp *mlp);
void readMLP(const char *filename, struct mlp *mlp);

void runMLP(struct mlp mlp, struct inputLayer input, struct outputLayer output);

#endif

