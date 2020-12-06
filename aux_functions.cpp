#include "aux_functions.hpp"

Matrix3D<float> sum_flow(Matrix3D<float> DS_pointHomoIm2, Matrix3D<float> DS_pointHomoIm1, Matrix3D<float> DS_VHomoIm1)
{
    int *size = DS_pointHomoIm2.getSize();
    float*** values = DS_pointHomoIm2.getValues();
    float*** values1 = DS_pointHomoIm1.getValues();
    float*** values2 = DS_VHomoIm1.getValues();
    
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
    return DS_pointHomoIm2 ;
}