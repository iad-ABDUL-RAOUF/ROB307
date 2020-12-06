#include "dlt.hpp"

// Note: cours 2 rob313

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
        float compareHx = epsilon*(fabs(valuesHx[i][0]) + fabs(valuesHx[i][1]));
        float comparex = epsilon*(fabs(valuesx[i][0]) + fabs(valuesx[i][1]));
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

    int size[2] = {nb_finite_points,3};
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


    int sizeM[2] = {2*nb_finite_points, 9};
    Matrix2D<float> M = Matrix2D<float>(sizeM);
    float** valuesM = M.getValues();
    for(int i = 0; i<nb_finite_points; i++)
    {
        valuesM[2*i][0] = -valuesFx[i][0];
        valuesM[2*i][1] = -valuesFx[i][1];
        valuesM[2*i][2] = -1;
        valuesM[2*i][3] = valuesM[2*i][4] = valuesM[2*i][5] = 0;
        valuesM[2*i][6] = valuesFHx[i][0]*valuesFx[i][0];
        valuesM[2*i][7] = valuesFHx[i][0]*valuesFx[i][1];
        valuesM[2*i][8] = valuesFHx[i][0];

        valuesM[2*i+1][0] = valuesM[2*i+1][1] = valuesM[2*i+1][2] = 0;
        valuesM[2*i+1][3] = -valuesFx[i][0];
        valuesM[2*i+1][4] = -valuesFx[i][1];
        valuesM[2*i+1][5] = -1;
        valuesM[2*i+1][6] = valuesFHx[i][1]*valuesFx[i][0];
        valuesM[2*i+1][7] = valuesFHx[i][1]*valuesFx[i][1];
        valuesM[2*i+1][8] = valuesFHx[i][1];
    }

    int sizeSVD[2] = {9,9};
    Matrix2D<float> U = Matrix2D<float>(sizeM);
    Matrix2D<float> S = Matrix2D<float>(sizeSVD);
    Matrix2D<float> tV = Matrix2D<float>(sizeSVD);
    float** valuesU = U.getValues();
    float** valuesS = S.getValues();
    float** valuestV = tV.getValues();

    cv::SVD::compute(valuesM, valuesU, valuesS, valuestV);
    //SVD ne fonctionne pas car les entrees doivent etre de type cv::InputArray ou cv::Output array. Bref des types propre a open cv... 
    // cf ce lien pour voir comment sont definis ces type. Il semblerait ques des array de double (et non des float) soit ok ?
    // https://docs.opencv.org/3.4/d4/d32/classcv_1_1__InputArray.html#details
    
    
    int sizeH[2] = {3,3};
    Matrix2D<float> H = Matrix2D<float>(sizeH);
    float** valuesH = U.getValues();
    for (int i = 0; i<3; i++)
    {
        for (int j = 0; j<3; j++)
        {
            valuesH[i][j] = valuestV[8][3*i+j]/valuestV[8][8]; //On impose H[2][2] = 1
        }
    }

    return H;
}