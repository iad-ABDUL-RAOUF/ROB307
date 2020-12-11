#include "dlt.hpp"
#include "matrix2D.hpp"
#include "matrix3D.hpp"
#include "aux_functions.hpp"
#include "ransac.hpp"

int main()
{
    printf("#### Start main ####\n");

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