#ifndef _MATRIXMUL 
#define _MATRIXMUL
#include <boost/numeric/ublas/matrix.hpp>


#if(__NVCC__)
#include "gpu/cudaMul.cuh"
template<class T>
class MatrixMul
{
    public:
    virtual void multiply
    (
        T *Y, 
        T *A,
        T *x ,
        int m,
        int n
    )=0;
};

template<class T>
class GPUMulMatrix : 
public MatrixMul<T>
{

    void *Ycuda; 
    void *Acuda;
    void *xcuda;

    void multiply
    (
        T *Y,
        T *A,
        T *x ,
        int m,
        int n
    );
};


template<typename T>
inline void GPUMulMatrix<T>::multiply(
        T *Y, 
        T *A,
        T *x,
        int m,
        int n
    )
{   
    multiplyMatrixGpuWrapper(Ycuda, xcuda, Acuda,Y,A,x, m, n);
}


#else 

template<class T>
class MatrixMul
{
    public:
    virtual void multiply
    (
        boost::numeric::ublas::matrix<T> *Y, 
        boost::numeric::ublas::matrix<T> *A,
        boost::numeric::ublas::matrix<T> *x 
    )=0;
};

template<class T>
class StandardMul:
public MatrixMul<T>
{
    void multiply
    (   
        boost::numeric::ublas::matrix<T> *Y, 
        boost::numeric::ublas::matrix<T> *A,
        boost::numeric::ublas::matrix<T> *x  
    );
};

template<typename T>
inline void StandardMul<T>::multiply
    (   
        boost::numeric::ublas::matrix<T> *Y, 
        boost::numeric::ublas::matrix<T> *A,
        boost::numeric::ublas::matrix<T> *x 
    )
{    
    int i,j,k;
    for(i=0; i<Y->size1(); i++)
    {
        for(j=0; j<x->size2(); j++) 
        {
            for(k=0; k<Y->size2(); k++) 
            {
                (*Y)(i,j) += (*A)(i,k) * (*x)(k,j);
            }
        }
    }
    

}
template class MatrixMul<long long>;
template class MatrixMul<short>;
template class MatrixMul<int>;

#endif




#endif //_MATRIXMUL