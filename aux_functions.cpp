#include <assert.h> //source code : https://code.woboq.org/userspace/glibc/assert/assert.h.html
#include <stdlib.h> //pour malloc. contenu dans le compilateur 

float*** sum_flow(int* size,float*** DS_pointHomoIm2, float*** DS_pointHomoIm1, float*** DS_VHomoIm1)
{
    // float ***DS_pointHomoIm2 = (float***) malloc(size[0] * sizeof(float**));
    // for (int i = 0 ; i<size[0] ; i++)
    // {
    //     DS_pointHomoIm2[i] = (float**) malloc(size[1] * sizeof(float*));
    //     for (int j = 0 ; i<size[1] ; j++)
    //     {
    //         DS_pointHomoIm2[i][j] = (float*) malloc(size[2] * sizeof(float));
    //     }
    // }
    
    
    for (int i = 0; i<size[0]; i++)
    {
        for (int j = 0 ; j< size[1] ; j++)
        {
            for (int k = 0 ; k<size[2] ; k++)
            {
                DS_pointHomoIm2[i][j][k] = DS_pointHomoIm1[i][j][k] + DS_VHomoIm1[i][j][k];
            }
        }
    }
    return DS_pointHomoIm2 ;
}