template <class T>
class Matrix2D
{
private:
    int* size;
    T** values;
public:
    Matrix2D(int* s) //constructeur
    {
        size = s;
        allocateValues();
    }

    void setSize(int* s)
    {
        size = s;
    }
    int* getSize()
    {
        return size;
    }
    
    void allocateValues()
    {
        if (size == nullptr)
        {
            return nullptr;
        }
        T **values = (T**) malloc(size[0] * sizeof(T*));
        for (int i = 0 ; i<size[0] ; i++)
        {
            values[i] = (T*) malloc(size[1] * sizeof(T));
        }
    }
    void setValues(T** v)
    {
        values = v ;
    }
    void setValue(int i, int j, int k, T v)
    {
        values[i][j][k] = v;
    }
    T** getValues()
    {
        return values;
    }
};