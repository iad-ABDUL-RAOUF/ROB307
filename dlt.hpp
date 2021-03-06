#ifndef DLT_H
#define DLT_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
//#include <opencv2/core.hpp> // a enlever pour Vivado
//#include <vector> //a enlever pour Vivado
#include "matrix3D.hpp"
#include "matrix2D.hpp"
#include "aux_functions.hpp"

// using namespace cv // a enlever pour Vivado
// using namespace std

Matrix2D<float> DLT(Matrix2D<float> x, Matrix2D<float> Hx);

#endif