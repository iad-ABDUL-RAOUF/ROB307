#include <assert.h> //source code : https://code.woboq.org/userspace/glibc/assert/assert.h.html
#include <stdlib.h> //pour malloc. contenu dans le compilateur 
#include "matrix3D.hpp"

Matrix3D<float> sum_flow(Matrix3D<float> DS_pointHomoIm2, Matrix3D<float> DS_pointHomoIm1, Matrix3D<float> DS_VHomoIm1);