#ifndef __MATEXPR
#define __MATEXPR
#include <iostream>
#include <boost/numeric/ublas/matrix.hpp>

template <class T>
class MatrixExpression
{
    private:
        boost::numeric::ublas::matrix<T> * A;    
        boost::numeric::ublas::matrix<T> * B;
        boost::numeric::ublas::matrix<T> * x;

    public:
        void matrixA_init(size_t m,size_t n,std::vector<T> &vec); 
        void matrixB_init(size_t m,size_t n,std::vector<T> &vec); 
        void matrixX_init(size_t m,size_t n,std::vector<T> &vec); 
        void printMatrix();
};

#endif