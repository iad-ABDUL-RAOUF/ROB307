#include <assert.h> //source code : https://code.woboq.org/userspace/glibc/assert/assert.h.html
#include <stdlib.h> //pour malloc. contenu dans le compilateur 
#include "matrix3D.hpp"
#include "matrix2D.hpp"

void sum3Dmat(Matrix3D<float> M_out, Matrix3D<float> M_in1, Matrix3D<float> M_in2);
void sum2Dmat(Matrix2D<float> M_out, Matrix2D<float> M_in1, Matrix2D<float> M_in2);
void homoStandard(Matrix2D<float> M_out, Matrix2D<float> M_in);
void homoFinite(Matrix2D<bool> VectBool, Matrix2D<float> M_in);


