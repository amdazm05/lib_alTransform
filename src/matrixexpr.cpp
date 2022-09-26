#include <matrixexpr.hpp>

template<typename T>
void MatrixExpression<T>::matrix_init(size_t m,size_t n,std::vector<T> &vec, const std::string literal)
{
    boost::numeric::ublas::matrix<T> ** variable = 
        (literal.compare("A")==0) ? &A : 
        (literal.compare("B")==0) ? &B : 
        (literal.compare("x")==0) ? &x : &Y;
        
    (*variable) = new boost::numeric::ublas::matrix<T>(m,n);
    std::copy(vec.begin(), vec.end(), (*variable)->data().begin());
    printMatrix(literal);
}

template<typename T>
void MatrixExpression<T>::init_result_size(size_t m,size_t n)
{
    Y = new boost::numeric::ublas::matrix<T>(m,n);
    for(unsigned int i=0;i<Y->size1();++i)
    {
        for (unsigned int j=0;j<Y->size2();++j)
        {
            (*Y)(i,j)=0;
        }
    }
}

template<typename T>
void MatrixExpression<T>::printMatrix(const std::string literal)
{
    boost::numeric::ublas::matrix<T> * variable = 
        (literal.compare("A")==0) ? A : 
        (literal.compare("B")==0) ? B : 
        (literal.compare("x")==0) ? x : Y;
    std::cout<<std::endl;
    for(unsigned int i=0;i<variable->size1();++i)
    {
        std::cout<<"| ";
        for (unsigned int j=0;j<variable->size2();++j)
        {
            std::cout<<(*variable)(i,j)<<" | ";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}


template class MatrixExpression<long long>;
template class MatrixExpression<short>;
template class MatrixExpression<float>;
template class MatrixExpression<int>;