#ifndef _MATRIXMUL 
#define _MATRIXMUL
#include <boost/numeric/ublas/matrix.hpp>

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

#if(__NVCC__)
#include "gpu/cudaMul.hu"
#endif

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
                std::cout<<"val Y "<<(*Y)(i,j)<<" "<<i<<j<<std::endl;
            }
        }
    }
    

}


#endif //_MATRIXMUL