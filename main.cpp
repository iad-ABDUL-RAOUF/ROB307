#include "dlt.hpp"
#include "matrix2D.hpp"
#include "matrix3D.hpp"
#include "aux_functions.hpp"

int main()
{
    printf("#### Start main ####\n");

    printf("define somme parameters \n");
    // video parameters
    int nFlotTotal = 1; // nombre de flot total dans la carte sd
    int nFlot = 0;
    imSize[2] = {36,64};
    // RANSAC parameters
    float threshold = 1; // marge d'erreur accepté en pixel pour dire qu'un point fit
    int sample_size = 5;
    int goal_inliers = (int)(imSize[0]*imSize[1]*0.6); 
    int max_iterations = 100;
    int random_seed = 123456;
    
    printf('creation de la matrice de coordonnees des pixels avant deplacement')
    sizeFrame[3] = {imSize[0],imSize[1],2}
    Matrix3D<float> frame1 = Matrix3D<float>(sizeFrame);
    Matrix3D<float> frame2 = Matrix3D<float>(sizeFrame);
    float*** values1 = M_in1.getValues();
    for (int i = 0; i<imSize[0]; i++)
    {
        for (int j = 0 ; j< imSize[1] ; j++)
        {
            values1[i][j][0] = i;
            values1[i][j][0] = j;
        }
    }
    
    // mets ces coordonnes dans le format souhaite (taille N x 3)
    sizeHomogeneListe = {imSize[0]*imSize[1],3}
    Matrix2D<float> homogeneListe1 = Matrix2D<float>(sizeHomogeneListe);
    Matrix2D<float> homogeneListe2 = Matrix2D<float>(sizeHomogeneListe);
    homogeneListe1 = mat3DtoHomogene2D(frame1)
    
    Matrix2D<float> wildAnimalPixels = nullptr;
    printf("--- DEBUT recherche des animaux sauvages dans la video ---")
    while (nFlot<nFlotTotal){
        // POUR L EQUIPE INTEGRATION : flot de la carte sd a mettre dans la matrice flot
        Matrix2D<float> flot = Matrix2D<float>(imSize); // charger le flot optique la dedans
        nFlot = nFlot+1;
        // coordonnees des pixel apres deplacement
        frame2 = sum3Dmat(frame1, flot);
        // met ces coordonnees dans le format souhaite (taille N x 3)
        homogeneListe2 = mat3DtoHomogene2D(frame1);
        wildAnimalPixels = ransac( homogeneListe1, homogeneListe2, threshold, sample_size, goal_inliers, max_iterations, random_seed)
        printf('image %d : mouvement detecte sur les pixels suivants :',nFlot)
        printMat2D(wildAnimalPixels);
    }
    printf("--- FIN recherche des animaux sauvages dans la video ---")
    printf("liberation de la memoire")
    frame1.free()
    frame2.free()
    homogeneListe1.free()
    homogeneListe2.free()
    flot.free()
    wildAnimalPixels.free()
    printf("#### End main ####\n");
    return 0;
}