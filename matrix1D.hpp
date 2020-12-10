#ifndef MATRICE_1D_H
#define MATRICE_1D_H

template <class T>
class Matrix1D
{
private:
    int size;
    T* values;
public:
    Matrix1D() {} //constructeur par defaut

    Matrix1D(int s) //constructeur
    {
        size = s;
        allocateValues();
    }

    void setSize(int s)
    {
        size = s;
    }
    int getSize()
    {
        return size;
    }
    
    void allocateValues()
    {
        /*
        if (size == 0)
        {
            return nullptr;
        }
        */
        values = (T*)malloc(size * sizeof(T));
    }
    void setValues(T* v)
    {
        values = v ;
    }
    void setValue(int i, T v)
    {
        values[i] = v;
    }
    T* getValues()
    {
        return values;
    }
    T getValue(int i)
    {
        return values[i];
    }
    void freeM()
    {
        free(values);
    }
};

#endif
