template <class T>
class Matrix2D
{
private:
    int size[2];
    T** values;
public:
    Matrix2D(int s[2]) //constructeur
    {
        size = s;
        allocateValues();
    }

    void setSize(int s[2])
    {
        size = s;
    }
    int[2] getSize()
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
    void setValue(int i, int j, T v)
    {
        values[i][j] = v;
    }
    T** getValues()
    {
        return values;
    }
};