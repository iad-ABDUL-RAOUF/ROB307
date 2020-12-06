#include "dlt.hpp"

Matrix2D<float> DLT(Matrix2D<float> x, Matrix2D<float> Hx)
{
    float epsilon = 0.0000001;
    int N = x.getSize()[0] ;
    float** valuesHx = Hx.getValues();
    float** valuesx = x.getValues();
    bool* finite_bool = (bool*)malloc(N*sizeof(bool));
    int nb_finite_points=0 ;

    // calcul de qui sont les points finis, et combien ils sont
    for (int i =0; i<N;i++)
    {
        //abs codee dans stdlib n'est valable que sur des entiers
        float compareHx = epsilon*(abs((int)valuesHx[i][0]) + abs((int)valuesHx[i][1]));
        float comparex = epsilon*(abs((int)valuesx[i][0]) + abs((int)valuesx[i][1]));
        finite_bool[i] = (valuesHx[i][2] > compareHx) && (valuesx[i][2] >comparex);
        if (finite_bool[i])
        {
            nb_finite_points++;
        }
    }

    if(nb_finite_points <4)
    {
        printf("not enough finite point in DLTcalib2 input. A least 4 finite pairs required");
        return nullptr;
    }

    // On sauvegarde les coordonnees des points donc a la fois l'image et l'antecedent sont finis.
    // Et on renormalise en meme temps pour que la 3e coordonnees soit egale a 1

    int* size = new int[2];
    size[0] = nb_finite_points;
    size[1] = 3;
    Matrix2D<float> finite_Hx = Matrix2D<float>(size);
    Matrix2D<float> finite_x = Matrix2D<float>(size);
    float** valuesFHx= finite_Hx.getValues();
    float** valuesFx= finite_x.getValues();
    int j = 0;

    for (int i = 0; i<nb_finite_points; i++)
    {
        bool found_finite = false;
        while(!found_finite)
        {
            if (finite_bool[j])
            {
                for (int k = 0; k<3;k++)
                {
                    valuesFHx[i][k] = valuesHx[j][k] / valuesHx[j][2];
                    valuesFx[i][k] = valuesx[j][k] / valuesx[j][2];
                }
                found_finite = true;
            } 
            else
            {
                j++;
            }
        }
    }


    Matrix2D<float> zeroMat = Matrix2D<float>(size);
    float** valuesZero = zeroMat.getValues();
    float* zeros = new float[3];
    zeros[0] = zeros[1] = zeros[2] = 0;
    for (int i = 0 ; i<nb_finite_points ; i++)
    {
        valuesZero[i] = zeros;
    }



}