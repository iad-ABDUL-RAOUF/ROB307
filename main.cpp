#include "dlt.hpp"
#include "matrix2D.hpp"
#include "matrix3D.hpp"

int main()
{
    int sizeX[2] = {5,3};
    Matrix2D<float> x = Matrix2D<float>(sizeX);
    float** valuesx = x.getValues();
    for (int i = 0; i<5; i++)
    {
        valuesx[2][i] = 1;
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
    valuesH[2][2] = 1;


    return 0;
}