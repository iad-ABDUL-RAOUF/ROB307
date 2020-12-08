#include <assert.h> //source code : https://code.woboq.org/userspace/glibc/assert/assert.h.html
#include <stdlib.h> //pour malloc. contenu dans le compilateur
#include <math.h> //pour sqrt
#include <stdio.h> //pour printf
#include "matrix3D.hpp"
#include "matrix2D.hpp"
#include "matrix1D.hpp"

// operation matricielle
Matrix3D<float> sum3Dmat(Matrix3D<float> M_in1, Matrix3D<float> M_in2);
Matrix2D<float> sum2Dmat(Matrix2D<float> M_in1, Matrix2D<float> M_in2);
Matrix2D<float> transpose2D(Matrix2D<float> M_in);
Matrix2D<float> MatMult2D2D(Matrix2D<float> M_in1, Matrix2D<float> M_in2);
Matrix1D<float> normByRow(Matrix2D<float> M_in);
// fonction sur coordonnees homogene
Matrix2D<float> homoStandard(Matrix2D<float> M_in, float eps);
Matrix1D<bool> homoFinite(Matrix2D<float> M_in, float eps, int* nTrue);
Matrix1D<float> normByRowHomo(Matrix2D<float> M_in);
// affichage
void printMat3D(Matrix3D<float> M_in);
void printMat2D(Matrix2D<float> M_in);
// conversion
Matrix2D<float> mat3DtoHomogene2D(Matrix3D<float> M_in);
Matrix2D<float> cartToHomogene(Matrix2D<float> M_in);
// Matrix2D<float> homogeneToCart(Matrix2D<float> M_in, float eps); // // en fait c'est relou a cause des points infinis. A coder si necessaire