#ifndef __MATEXPR
#define __MATEXPR
#include <iostream>
#include <boost/numeric/ublas/matrix.hpp>

template <class T>
class MatrixExpression
{
    public:
        boost::numeric::ublas::matrix<T> * A;    
        boost::numeric::ublas::matrix<T> * B;
        boost::numeric::ublas::matrix<T> * x;

        void *a=NULL;  //oh you'll know why I did this :)
        void *b=NULL;
        void *X=NULL;
        void *y=NULL;
        //TODO Later
        boost::numeric::ublas::matrix<T> * Y;

    public:
        void matrix_init(size_t m,size_t n,std::vector<T> &vec,const std::string literal);  
        void printMatrix(std::string literal);
        void init_result_size(size_t m,size_t n);
};

#endif