#include <matrixexpr.hpp>

template<typename T>
void MatrixExpression<T>::matrixA_init(size_t m,size_t n,std::vector<T> &vec)
{
    //this is like dynamic memory
    // boost::numeric::ublas::unbounded_array<T> temp(m*n);
    A= new boost::numeric::ublas::matrix<T>(m,n);
    std::copy(vec.begin(), vec.end(), A->data().begin());
    printMatrix();
}

template<typename T>
void MatrixExpression<T>::printMatrix()
{
    for(unsigned int i=0;i<A->size1();++i)
    {
        std::cout<<"| ";
        for (unsigned int j=0;j<A->size2();++j)
        {
            std::cout<<(*A)(i,j)<<" | ";
        }
        std::cout<<std::endl;
    }
}


template<typename T>
void MatrixExpression<T>::matrixB_init(size_t m,size_t n,std::vector<T> &vec)
{
    // this->B.resize(m,n);

} 

template<typename T>
void MatrixExpression<T>::matrixX_init(size_t m,size_t n,std::vector<T> &vec)
{
    // this->x.resize(m,n);
}

template class MatrixExpression<long long>;
template class MatrixExpression<short>;
template class MatrixExpression<float>;
template class MatrixExpression<int>;