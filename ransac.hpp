#ifndef RANSAC_H
#define RANSAC_H

#include <stdio.h>
#include <stdlib.h> //rand
#include <math.h>
#include "matrix2D.hpp"
#include "dlt.hpp"
#include "aux_functions.hpp"

const int random_seed = 1024;

Matrix2D<float> ransac(Matrix2D<float> x, Matrix2D<float> Hx, float threshold, int samplesize, int goal_inliers, int max_iter, bool stop_at_goal = true);

#endif