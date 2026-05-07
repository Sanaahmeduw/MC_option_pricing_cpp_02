#ifndef ARRAYS_H
#define ARRAYS_H

class MJArray {
public:
    MJArray(unsigned long size = 0);
    ~MJArray();
    MJArray(const MJArray& original);
    MJArray& operator=(const MJArray& original);
    inline double& operator[](unsigned long i);
    inline double operator[](unsigned long i) const;
    inline unsigned long size() const;
    void resize(unsigned long newSize);

private:
    double* Values;
    unsigned long Size;
    unsigned long Capacity;
};

inline double& MJArray::operator[](unsigned long i) {
    return Values[i];
}

inline double MJArray::operator[](unsigned long i) const {
    return Values[i];
}

inline unsigned long MJArray::size() const {
    return Size;
}

#endif
