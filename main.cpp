#include "dlt.hpp"
#include "matrix2D.hpp"
#include "matrix3D.hpp"
#include "aux_functions.hpp"

int main()
{
    printf("#### Start main ####\n");
    
    int nImagesTotal = 2; // nombre d'image total dans la video.
    int nImage = 0;
    printf("load data\n");
    // charger les deux images stocké dans la carte sd.
    // La premiere image à mettre dans frame 1 et la deuxième dans frame 2
    imSize[2] = {36,64};
    Matrix2D<float> frame1 = Matrix2D<float>(imSize);
    Matrix2D<float> frame2 = Matrix2D<float>(imSize);
    nImage = nImage+1;
    
    
    
    
    
    
    printf("Create M1\n");
    int sizeM1[3] = {4,3,2};
    printf("l12\n");
    Matrix3D<float> M1 = Matrix3D<float>(sizeM1);
    printf("l14\n");
    float*** valuesM1 = M1.getValues();
    printf("l16\n");
    for (int i = 0; i<sizeM1[0]; i++)
    {
        for (int j = 0 ; j< sizeM1[1] ; j++)
        {
            for (int k = 0 ; k<sizeM1[2] ; k++)
            {
                valuesM1[i][j][k] = -1000 + 1000*i +100*j +10*k;
            }
        }
    }
    printf("M1 : \n");
    printMat3D(M1);
    
    printf("Create M2\n");
    Matrix3D<float> M2 = Matrix3D<float>(sizeM1);
    float*** valuesM2 = M2.getValues();
    for (int i = 0; i<sizeM1[0]; i++)
    {
        for (int j = 0 ; j< sizeM1[1] ; j++)
        {
            for (int k = 0 ; k<sizeM1[2] ; k++)
            {
                valuesM2[i][j][k] = 0.1*i +0.01*j +0.001*k;
            }
        }
    }
    printf("M2 : \n");
    printMat3D(M2);

    printf("Compute M3 = \n");
    Matrix3D<float> M3 = Matrix3D<float>(sizeM1);
    M3 = sum3Dmat(M1, M2);
    printf("M3 : \n");
    printMat3D(M3);

    printf("Creating x\n");
    int sizeX[2] = {5,3};
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
    printf("x : \n");
    printMat2D(x);

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
    printf("H : \n");
    printMat2D(H);


    printf("Transposing x\n");
    int sizeTX[2] = {3,5};
    Matrix2D<float> tx = Matrix2D<float>(sizeTX);
    tx = transpose2D(x);
    printf("tx : \n");
    printMat2D(tx);
    
    printf("Multiplying H and tx\n");
    Matrix2D<float>tHx = Matrix2D<float>(sizeTX);
    tHx = MatMult2D2D(H,tx);
    printf("tHx : \n");
    printMat2D(tHx);

    printf("Creating Hx\n");
    Matrix2D<float> Hx = Matrix2D<float>(sizeX);
    Hx = transpose2D(tHx);
    printf("Hx : \n");
    printMat2D(Hx);
    
    printf("Estimating H with DLT algorithm\n");
    Matrix2D<float> estimatedH = Matrix2D<float>(sizeH);
    estimatedH = DLT(x,Hx);
    printf("Estimated H : \n");
    printMat2D(estimatedH);
    
    
    printf("#### End main ####\n");
    return 0;
}