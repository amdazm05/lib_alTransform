#include <altransform.hpp>

template <typename T>
AlTransform<T> *AlTransform<T>::_inst=NULL;

template <typename T>
AlTransform<T>::AlTransform()
{
    std::cout<< "Initialised AlTransform"<<std::endl;
}

template <typename T>
void AlTransform<T>::init(void)
{   
    _inst = new AlTransform<T>;
}

template <typename T>
AlTransform<T> * AlTransform<T>::get_instance()
{
    return _inst;

}

template <typename T>
void AlTransform<T>::setExpression(std::vector<T> &A)
{
    _expr=new MatrixExpression<T>;
    _expr->matrixA_init(3,3,A);
}

//Compile for these classes
template class AlTransform<long long>;
template class AlTransform<short>;
template class AlTransform<float>;
template class AlTransform<int>;