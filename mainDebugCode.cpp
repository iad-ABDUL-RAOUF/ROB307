#include "dlt.hpp"
#include "ransac.hpp"
#include "matrix2D.hpp"
#include "matrix3D.hpp"
#include "aux_functions.hpp"

int main()
{
    //RANSAC parameters
    float threshold = 1 ;//marge d'erreur acceptee en pixel pour dire qu'un point est bon
    int sample_size = 4;
    int goal_inliers = 1;
    int max_iterations = 100;
    int random_seed = 1024;
    printf("#### Start main debug ####\n\n");

    
    // printf("Create M1\n");
    // int sizeM1[3] = {4,3,2};
    // printf("l12\n");
    // Matrix3D<float> M1 = Matrix3D<float>(sizeM1);
    // printf("l14\n");
    // float*** valuesM1 = M1.getValues();
    // printf("l16\n");
    // for (int i = 0; i<sizeM1[0]; i++)
    // {
    //     for (int j = 0 ; j< sizeM1[1] ; j++)
    //     {
    //         for (int k = 0 ; k<sizeM1[2] ; k++)
    //         {
    //             valuesM1[i][j][k] = -1000 + 1000*i +100*j +10*k;
    //         }
    //     }
    // }
    // printf("M1 : \n");
    // printMat3D(M1);
    
    // printf("Create M2\n");
    // Matrix3D<float> M2 = Matrix3D<float>(sizeM1);
    // float*** valuesM2 = M2.getValues();
    // for (int i = 0; i<sizeM1[0]; i++)
    // {
    //     for (int j = 0 ; j< sizeM1[1] ; j++)
    //     {
    //         for (int k = 0 ; k<sizeM1[2] ; k++)
    //         {
    //             valuesM2[i][j][k] = 0.1*i +0.01*j +0.001*k;
    //         }
    //     }
    // }
    // printf("M2 : \n");
    // printMat3D(M2);

    // printf("Compute M3 = \n");
    // Matrix3D<float> M3 = Matrix3D<float>(sizeM1);
    // M3 = sum3Dmat(M1, M2);
    // printf("M3 : \n");
    // printMat3D(M3);

    printf("Creating x\n");
    int sizeX[2] = {6,3};
    Matrix2D<float> x = Matrix2D<float>(sizeX);
    float** valuesx = x.getValues();
    for (int i = 0; i<5; i++)
    {
        valuesx[i][2] = 1;
    }
    valuesx[0][0] = 100;
    valuesx[0][1] = 440;
    valuesx[1][0] = 200;
    valuesx[1][1] = 30;
    valuesx[2][0] = 20;
    valuesx[2][1] = 80;
    valuesx[3][0] = 40;
    valuesx[3][1] = 200;
    valuesx[4][0] = 300;
    valuesx[4][1] = 140;
    valuesx[5][1] = 50;
    valuesx[5][2] = 100000;
    // printf("x : \n");
    // printMat2D(x);

    printf("Creating H\n");
    int sizeH[2] = {3,3};
    Matrix2D<float> H = Matrix2D<float>(sizeH);
    float** valuesH = H.getValues();
    valuesH[0][0] = 1.37054309;
    valuesH[0][1] = 0.326472981;
    valuesH[0][2] = -90.9781842;
    valuesH[1][0] = 0.00346896567;
    valuesH[1][1] = 1.65383589;
    valuesH[1][2] = -77.8613246;
    valuesH[2][0] = 0.000173448284;
    valuesH[2][1] = 0.00114069045;
    valuesH[2][2] = 1.0;
    // printf("H : \n");
    // printMat2D(H);


    printf("Transposing x\n");
    int sizeTX[2] = {3,5};
    Matrix2D<float> tx = Matrix2D<float>(sizeTX);
    tx = transpose2D(x);
    // printf("tx : \n");
    // printMat2D(tx);
    
    printf("Multiplying H and tx\n");
    Matrix2D<float> tHx = Matrix2D<float>(sizeTX);
    tHx = MatMult2D2D(H,tx);
    // printf("tHx : \n");
    // printMat2D(tHx);

    printf("Creating Hx\n");
    Matrix2D<float> Hx = Matrix2D<float>(sizeX);
    Hx = transpose2D(tHx);
    // printf("Hx : \n");
    // printMat2D(Hx);
    
    // printf("Estimating H with DLT algorithm\n");
    // Matrix2D<float> estimatedH = Matrix2D<float>(sizeH);
    // estimatedH = DLT(x,Hx);
    // printf("Estimated H : \n");
    // printMat2D(estimatedH);
    

    printf("Estimating outliers with ransac algorithm\n");
    Matrix2D<float> outliers = ransac(x,Hx,threshold,sample_size,goal_inliers,max_iterations,random_seed);
    printf("Nb of outliers : %d\n", outliers.getSize()[0]);
    
    printf("#### End main debug ####\n");
    return 0;
}