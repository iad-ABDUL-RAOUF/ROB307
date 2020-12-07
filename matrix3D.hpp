#ifndef MATRICE_3D_H
#define MATRICE_3D_H
#include <assert.h>

template <class T>
class Matrix3D
{
private:
    int size[3];
    T*** values;
public:
    Matrix3D(int s[3]) //constructeur
    {
        size[0] = s[0];
        size[1] = s[1];
        size[2] = s[2];
        allocateValues();
    }

    void setSize(int s[3])
    {
        size[0] = s[0];
        size[1] = s[1];
        size[2] = s[2];
    }
    int* getSize()
    {
        return size;
    }
    
    void allocateValues()
    {
        /*
        if (size == nullptr)
        {
            return nullptr; // on ne peut rein retourner la fonction est de type void
        }
        commente ca car retourne une erreur. put etre a Remplacer par un assert
        */
        assert(size !=nullptr);
        values = (T***) malloc(size[0] * sizeof(T**));
        assert(values);
        for (int i = 0 ; i<size[0] ; i++)
        {
            values[i] = (T**) malloc(size[1] * sizeof(T*));
            assert(values[i]);
            for (int j = 0 ; j<size[1] ; j++)
            {
                values[i][j] = (T*) malloc(size[2] * sizeof(T));
                assert(values[i][j]);
            }
        }
        printf("end allocateValues mat3D\n");              
    }
    void setValues(T*** v)
    {
        values = v ;
    }
    void setValue(int i, int j, int k, T v)
    {
        values[i][j][k] = v;
    }
    T*** getValues()
    {
        return values;
    }
    T getValue(int i, int j, int k)
    {
        return values[i][j][k];
    }
};

#endif


