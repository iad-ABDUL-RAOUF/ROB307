#ifndef MATRICE_2D_H
#define MATRICE_2D_H

template <class T>
class Matrix2D
{
private:
    int size[2];
    T** values;
public:
    Matrix2D(int s[2]) //constructeur
    {
        size[0] = s[0];
        size[1] = s[1];
        allocateValues();
    }

    void setSize(int s[2])
    {
        size[0] = s[0];
        size[1] = s[1];
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
            return nullptr;
        }
        retounre une erreur car fonction de type void. A remplacer par un assert
        */
        values = (T**) malloc(size[0] * sizeof(T*));
        for (int i = 0 ; i<size[0] ; i++)
        {
            values[i] = (T*) malloc(size[1] * sizeof(T));
        }
    }
    void setValues(T** v)
    {
        values = v ;
    }
    void setValue(int i, int j, T v)
    {
        values[i][j] = v;
    }
    T** getValues()
    {
        return values;
    }
    T getValue(int i, int j)
    {
        return values[i][j];
    }
};

#endif
