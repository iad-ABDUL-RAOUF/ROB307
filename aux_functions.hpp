#include <assert.h> //source code : https://code.woboq.org/userspace/glibc/assert/assert.h.html
#include <stdlib.h> //pour malloc. contenu dans le compilateur
#include <math.h> //pour racine
#include "matrix3D.hpp"
#include "matrix2D.hpp"
#include "matrix1D.hpp"

Matrix3D<float> sum3Dmat(Matrix3D<float> M_in1, Matrix3D<float> M_in2);
Matrix2D<float> sum2Dmat(Matrix2D<float> M_in1, Matrix2D<float> M_in2);
Matrix2D<float> homoStandard(Matrix2D<float> M_in, float eps);
Matrix1D<bool> homoFinite(Matrix2D<float> M_in, float eps);
Matrix2D<float> transpose2D(Matrix2D<float> M_in);
Matrix2D<float> MatMult2D2D(Matrix2D<float> M_in1, Matrix2D<float> M_in2);