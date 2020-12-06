#include "aux_functions.hpp"

Matrix3D<float> sum3Dmat(Matrix3D<float> M_in1, Matrix3D<float> M_in2)
{
    int size[3] = M_in1.getSize();
    Matrix3D<float> M_out = Matrix3D<float>(size);
    float*** values = M_out.getValues();
    float*** values1 = M_in1.getValues();
    float*** values2 = M_in2.getValues();
    
    for (int i = 0; i<size[0]; i++)
    {
        for (int j = 0 ; j< size[1] ; j++)
        {
            for (int k = 0 ; k<size[2] ; k++)
            {
                values[i][j][k] = values1[i][j][k] + values2[i][j][k];
            }
        }
    }
    return M_out ;
}


Matrix2D<float> sum2Dmat(Matrix2D<float> M_in1, Matrix2D<float> M_in2)
{
    int size[2] = M_in1.getSize();
    Matrix2D<float> M_out = Matrix2D<float>(size);
    float** values = M_out.getValues();
    float** values1 = M_in1.getValues();
    float** values2 = M_in2.getValues();
    
    for (int i = 0; i<size[0]; i++)
    {
        for (int j = 0 ; j< size[1] ; j++)
        {
            values[i][j] = values1[i][j] + values2[i][j];
        }
    }
    return M_out ;
}

Matrix2D<float> homoStandard(Matrix2D<float> M_in, float eps)
{
    int size[2] = M_in.getSize();
    Matrix2D<float> M_out = Matrix2D<float>(size);
    float** valuesOut = M_out.getValues();
    float** valuesIn = M_in.getValues();
    int* nTrue = 0;
    Matrix1D<bool> isFinite = homoFinite(nTrue, M_in, eps);
    float norm = 0.0;
    for (int i = 0; i<size[0]; i++)
    {
        if isFinite[i]
        {
            for (int j = 0 ; j< size[1] ; j++)
            {
                valuesOut[i][j] = valuesIn[i][j]/valuesIn[i][size[1]-1];
            }
        }
        else //on impose la dernire coordonnee a zeros et on divise les autres par la norme du vecteur
        {
            norm = 0.0;
            for (int j = 0 ; j< (size[1]-1) ; j++)
            {
                norm += valuesIn[i][j]*valuesIn[i][j];
            }
            norm = sqrt(norm)
            for (int j = 0 ; j< (size[1]-1) ; j++)
            {
                valuesOut[i][j] = valuesIn[i][j]/norm;
            }
            valuesOut[i][size[1]-1] = 0.0
        }
    }
    return M_out;
}

Matrix1D<bool> homoFinite(int* nTrue, Matrix2D<float> M_in, float eps)
{
    int size[2] = M_in.getSize();
    int sizeOut = size[0]
    Matrix1D<bool> M_out = Matrix1D<bool>(sizeOut);
    bool* valuesOut = M_out.getValues();
    float** valuesIn = M_in.getValues();
    float tmp = 0.0;
    *nTrue = 0;
    
    for (int i =0; i<size[0];i++)
    {
        for (int j =0; i<size[1]-1;i++)
        {
            tmp += fabs(M_in[i][j]);
        }
        tmp = tmp*eps;
        valuesOut[i] = (tmp < valuesIn[i][size[1]-1])
        if valuesOut[i]
        {
            nTrue += 1;
        }
    }
    return M_out;
}
Matrix2D<float> transpose2D(Matrix2D<float> M_in)
{
    int size[2] = M_in.getSize();
    int sizeTranspose[2] = {size[0], size[1]};
    Matrix2D<float> M_out = Matrix2D<float>(sizeTranspose);
    float** valuesOut = M_out.getValues();
    float** valuesIn = M_in.getValues();
    for (int i = 0; i<size[0]; i++)
    {
        for (int j = 0 ; j< size[1] ; j++)
        {
            valuesOut[i][j] = valuesIn[j][i];
        }
    }
    return M_out;
}

Matrix2D<float> MatMult2D2D(Matrix2D<float> M_in1, Matrix2D<float> M_in2)
{
    int sizeIn1[2] = M_in1.getSize();
    int sizeIn2[2] = M_in2.getSize();
    int sizeOut[2] = {sizeIn1[0], sizeIn2[1]};
    Matrix3D<float> M_out = Matrix3D<float>(size);
    float*** valuesOut = M_out.getValues();
    float*** valuesIn1 = M_in1.getValues();
    float*** valuesIn2 = M_in2.getValues();
    for (int i = 0; i<sizeOut[0]; i++)
    {
        for (int j = 0 ; j< sizeOut[1] ; j++)
        {
            valuesOut[i][j] = 0
            for (int k = 0 ; k< sizeIn1[0] ; k++)
            {
                valuesOut[i][j] += valuesIn1[i][k]*valuesIn2[k][j];
            }
        }
    }
    return M_out;
}

void printMat2D(Matrix2D<float> M_in)
{
    int size[2] = M_in.getSize();
    float** values = M_in.getValues();
    printf("matrice 2D =\n");
    for (int i = 0; i<size[0]; i++)
    {
        for (int j = 0 ; j< size[1] ; j++)
        {
            printf("%f,",values[i][j]);
        }
        printf("\n");
    }
}

