template <class T>
class Matrix1D
{
private:
    int size;
    T* values;
public:
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
        if (size == 0)
        {
            return nullptr;
        }
        T *values = (T*) malloc(size * sizeof(T));
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
};