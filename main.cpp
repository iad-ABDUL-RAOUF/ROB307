#include "dlt.hpp"
#include "matrix2D.hpp"
#include "matrix3D.hpp"

int main()
{
    int *sizeX = new int[2];
    size[0] = 5;
    size[1] = 3;
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

    int *sizeH = new int[2];
    size[0] = size[1] = 3;
    Matrix2D<float> H = Matrix2D<float>(sizeH);
    H[0][0] = 1.37054309;
    H[0][1] = 0.326472981;
    H[0][2] = -90.9781842;
    H[1][0] = 0.00346896567;
    H[1][1] = 1.65383589

    H_true = np.array([[ 1.37054309e+00 , 3.26472981e-01 ,-9.09781842e+01],
 [ 3.46896567e-03,  1.65383589e+00, -7.78613246e+01],
 [ 1.73448284e-04,  1.14069045e-03 , 1.00000000e+00]])


    return 0;
}