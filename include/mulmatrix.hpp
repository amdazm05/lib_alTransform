#ifndef _MATRIXMUL 
#define _MATRIXMUL
#include <boost/numeric/ublas/matrix.hpp>

template<class T>
class MatrixMul
{
    public:
    virtual void multiply
    (
        T *Y, 
        T *A,
        T *x 
    )=0;
};

#if(__NVCC__)
#include "gpu/cudaMul.cuh"
#endif

template<class T>
class StandardMul:
public MatrixMul<T>
{
    void multiply
    (   
        T *Y, 
        T *A,
        T *x  
    );
};

template<typename T>
inline void StandardMul<T>::multiply
    (   
        T *Y, 
        T *A,
        T *x 
    )
{    
    int i,j,k;
    for(i=0; i<Y->size1(); i++)
    {
        for(j=0; j<x->size2(); j++) 
        {
            for(k=0; k<Y->size2(); k++) 
            {
                // (*Y)(i,j) += (*A)(i,k) * (*x)(k,j);
            }
        }
    }
    

}

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
        T *x 
    );
};


template<typename T>
inline void GPUMulMatrix<T>::multiply
    (
        T *Y, 
        T *A,
        T *x 
    )
{   
    multiplyMatrixGpuWrapper(Ycuda, xcuda, Acuda,Y,A,x, 3, 3, 3 );
}



#endif //_MATRIXMUL