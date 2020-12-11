#include "dlt.hpp"
#include "matrix2D.hpp"
#include "matrix3D.hpp"
#include "aux_functions.hpp"
#include "ransac.hpp"

int main()
{
    printf("#### Start main ####\n");

    
    printf("Creating x\n");
    int sizeX[2] = {6,3};
    Matrix2D<float> homogeneListe1 = Matrix2D<float>(sizeX);
    float** valuesx = homogeneListe1.getValues();
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
    valuesx[5][1] = 55;
    valuesx[5][2] = 240;

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
    int sizeTX[2] = {sizeX[1],sizeX[0]};
    Matrix2D<float> tx = Matrix2D<float>(sizeTX);
    tx = transpose2D(homogeneListe1);
    // printf("tx : \n");
    // printMat2D(tx);
    
    printf("Multiplying H and tx\n");
    Matrix2D<float> tHx = Matrix2D<float>(sizeTX);
    tHx = MatMult2D2D(H,tx);
    // printf("tHx : \n");
    // printMat2D(tHx);

    printf("Creating Hx\n");
    Matrix2D<float> homogeneListe2 = Matrix2D<float>(sizeX);
    homogeneListe2 = transpose2D(tHx);
    float** valuesHx = homogeneListe2.getValues();
    valuesHx[5][1] = valuesHx[5][1] +6;
    valuesHx[5][2] = valuesHx[5][1] -6;






    printf("define somme parameters \n");
    // video parameters
    int nFlotTotal = 1; // nombre de flot total dans la carte sd
    int nFlot = 0;
    int imSize[2] = {36,64};
    // RANSAC parameters
    float threshold = 1; // marge d'erreur accepté en pixel pour dire qu'un point fit
    int sample_size = 5;
    int goal_inliers = 5 ;//(int)(imSize[0]*imSize[1]*0.6); // TODO
    int max_iterations = 100;
    int random_seed = 123456;
    
    printf("creation de la matrice de coordonnees des pixels avant deplacement\n");
    int sizeFrame[3] = {imSize[0],imSize[1],2};
    Matrix3D<float> frame1 = Matrix3D<float>(sizeFrame);
    Matrix3D<float> frame2 = Matrix3D<float>(sizeFrame);
    float*** values1 = frame1.getValues();
    for (int i = 0; i<imSize[0]; i++)
    {
        for (int j = 0 ; j< imSize[1] ; j++)
        {
            //printf("i = %d, j = %d\n", i, j);
            values1[i][j][0] = i;
            values1[i][j][1] = j;
        }
        //printf("--------\n");
    }
    
    // mets ces coordonnes dans le format souhaite (taille N x 3)
    int sizeHomogeneListe[2] = {imSize[0]*imSize[1],3};
    //Matrix2D<float> homogeneListe1 = Matrix2D<float>(sizeHomogeneListe); //TODO
    //Matrix2D<float> homogeneListe2 = Matrix2D<float>(sizeHomogeneListe); //TODO
    //homogeneListe1 = mat3DtoHomogene2D(frame1); //TODO
    
    Matrix3D<float> flot = Matrix3D<float>(sizeFrame);
    Matrix2D<float> wildAnimalPixels;
    printf("--- DEBUT recherche des animaux sauvages dans la video ---\n");
    while (nFlot<nFlotTotal){
        // POUR L EQUIPE INTEGRATION : flot de la carte SD a mettre dans la matrice flot
        // flot = charger le flot ici
        nFlot = nFlot+1;
        // coordonnees des pixel apres deplacement
        frame2 = sum3Dmat(frame1, flot);
        // met ces coordonnees dans le format souhaite (taille N x 3)
        // homogeneListe2 = mat3DtoHomogene2D(frame2); //TODO
        // printMat2D(homogeneListe1); //TODO
        // printMat2D(homogeneListe2); //TODO
        wildAnimalPixels = ransac( homogeneListe1, homogeneListe2, threshold, sample_size, goal_inliers, max_iterations, random_seed);
        printf("image %d : mouvement detecte sur les pixels suivants :\n",nFlot);
        printMat2D(wildAnimalPixels);
    }
    printf("--- FIN recherche des animaux sauvages dans la video ---\n");
    printf("liberation de la memoire\n");
    frame1.freeM();
    frame2.freeM();
    homogeneListe1.freeM();
    homogeneListe2.freeM();
    flot.freeM();
    wildAnimalPixels.freeM();
    printf("#### End main ####\n");
    return 0;
}