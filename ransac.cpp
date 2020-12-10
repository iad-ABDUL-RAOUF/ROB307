#include "ransac.hpp"

Matrix2D<float> ransac(Matrix2D<float> X, Matrix2D<float> Hx, float threshold, int samplesize, int goal_inliers, int max_iter)
{
    if(samplesize<4)
    {
        printf("sample_size should be an int equal to 4 or higher");
        return nullptr;
    }

    //Initialisation de la sortie
    Matrix2D<float> outliers = nullptr;

    //Homogeneissation des points d'arrivee
    int* sizeX = Hx.getSize();
    float** valuesHx = Hx.getValues();
    float** valuesX = X.getValues();
    for (int i = 0; i<sizeX[0]; i++)
    {
        for (int j = 0; j<sizeX[1];j++)
        {
            valuesHx[i][j] = valuesHx[i][j]/valuesHx[i][2];
        }
    }

    //Initialisation de la seed aleatoire
    srand(random_seed);


    int n_iter = 0;
    bool good_enough = false;
    int rand_index[samplesize];
    int sizeXrand[] = {samplesize,3};
    Matrix2D<float> randX = Matrix2D<float>(sizeXrand);
    Matrix2D<float> randHx = Matrix2D<float>(sizeXrand);
    float** valuesXrand = randX.getValues();
    float** valuesHxrand = randHx.getValues();
    while(!good_enough && n_iter < max_iter )
    {
        //Creation d'une liste d'indices aleatoires
        for (int i = 0; i<samplesize ; i++) 
        {
            rand_index[i] = rand()%sizeX[0];
        } 
        for (int i = 0; i<samplesize ; i++)
        {
            int j = rand_index[i];
            valuesXrand[i] = valuesX[j];
            valuesHxrand[i] = valuesHx[j];
        }

        //Calcul de l'homographie associee
        
        Matrix2D<float> H = DLT(randX,randHx);

        //Determiner les points qui correspondent effectivement a cette homographie
        
        Matrix2D<float> tH = transpose2D(H);
        Matrix2D<float> estimatedHx = MatMult2D2D(X,tH);
        //Homogeneisation des Hx estimes
        float** valuesEstmHx = estimatedHx.getValues();
        for (int i = 0; i<sizeX[0]; i++)
        {
            for (int j = 0; j<sizeX[1];j++)
            {
                valuesEstmHx[i][j] = valuesEstmHx[i][j]/valuesEstmHx[i][2];
            }
        }
        //Selection et comptage des points qui sont suffisamment bons
        bool fitting[sizeX[0]];
        int nb_fitting = 0;
        float err = 0;
        for (int i=0;i<sizeX[0];i++)
        {
            err = sqrt(pow(valuesEstmHx[i][1]-valuesHx[i][1],2) + pow(valuesEstmHx[i][2]-valuesHx[i][2],2));
            if (err <threshold)
            {
                nb_fitting +=1;
                fitting[i] = true;
            }
            else
            {
                fitting[i] = false;
            }
        }

        //Si l'homographie trouvee est suffisamment bonne, on la garde

        if (nb_fitting >= goal_inliers)
        {
            good_enough = true;

            //Copie des points qui suivent bien l'homographie trouvee
            int sizeFit[2] = {nb_fitting,3};
            Matrix2D<float> fittingX = Matrix2D<float>(sizeFit);
            Matrix2D<float> fittingHx = Matrix2D<float>(sizeFit);
            float** valuesFX = fittingX.getValues();
            float** valuesFHx = fittingHx.getValues();
            int j=0;
            for (int i = 0; i<sizeX[0]; i++)
            {
                if (fitting[i])
                {
                    valuesFHx[j] = valuesHx[i];
                    valuesFX[j] = valuesX[i];
                    j++;
                }
            }
        
            //Recalcul plus precis de l'homographie
            H = DLT(fittingX,fittingHx);

            //Calcul des nouveaux Hx estimes
            tH = transpose2D(H);
            estimatedHx = MatMult2D2D(X,tH);
            //Homogeneisation des Hx estimes
            for (int i = 0; i<sizeX[0]; i++)
            {
                for (int j = 0; j<sizeX[1];j++)
                {
                    valuesEstmHx[i][j] = valuesEstmHx[i][j]/valuesEstmHx[i][2];
                }
            }
            //Selection et comptage des points qui sont suffisamment bons
            nb_fitting = 0;
            for (int i=0;i<sizeX[0];i++)
            {
                err = sqrt(pow(valuesEstmHx[i][1]-valuesHx[i][1],2) + pow(valuesEstmHx[i][2]-valuesHx[i][2],2));
                if (err <threshold)
                {
                    nb_fitting +=1;
                    fitting[i] = true;
                }
                else
                {
                    fitting[i] = false;
                }
            }

            //Rassemblement des outliers
            int sizeOut[2] = {sizeX[0]-nb_fitting,3};
            outliers = Matrix2D<float>(sizeOut);
            float** valuesOut = outliers.getValues();
            int j=0;
            for(int i =0; i<sizeX[0]; i++)
            {
                if(fitting[i] == false)
                {
                    valuesOut[j] = valuesX[i];
                    j++;
                }
            }
        }

    }
    randX.free()
    randHx.free()
    tH.free()
    estimatedHx.free()
    fittingX.free()
    fittingHx.free()
    return outliers;
}