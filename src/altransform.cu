#include "altransform.hpp"


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
    
    #if(__NVCC__)
        std::cout<<"Using CUDA for operations"<<std::endl;
        _inst->_mulops = new GPUMulMatrix<T>;
    #else
        std::cout<<"Using CPU Standard Multiplications for operations"<<std::endl;
        _inst->_mulops = new StandardMul<T>;
    #endif
    

    _inst->_expr= new MatrixExpression<T>;
}

template <typename T>
AlTransform<T> * AlTransform<T>::get_instance()
{
    return _inst;

}

template <typename T>
void AlTransform<T>::setVariable(short m,short n,std::vector<T> &vec ,const std::string literal)
{
    _expr->matrix_init(m,n,vec,literal);
    
}

template <typename T>
void AlTransform<T>::setExpression(
            std::vector<T> &A,
            std::vector<T> &x,
            std::vector<T> &B,
            const std::string literal)
{
    _expr=new MatrixExpression<T>;
    //Assume them to be square matrices of equal sizes 
    _expr->matrix_init((int)std::sqrt(A.size()),(int)std::sqrt(A.size()),A,"A");
    _expr->matrix_init((int)std::sqrt(B.size()),(int)std::sqrt(B.size()),B,"B");
    _expr->matrix_init((int)std::sqrt(x.size()),(int)std::sqrt(x.size()),x,"x");
}

template <typename T>
std::vector<T> * AlTransform<T>::evaluateExpression()
{
    // Evaluate this 
    // _expr->Y=_expr->A*_expr->x+_expr->B;
    _expr->init_result_size(_expr->A->size1(),_expr->x->size2());
    
    // mxn  * nxk  == n*k 
    //Multilpication is possible 
    _expr->y = (void *)&((_expr->Y->data())[0]);
    _expr->a = (void *)&((_expr->A->data())[0]);
    _expr->X = (void *)&((_expr->x->data())[0]);


    if(_expr->A->size2() == _expr->B->size1())
    {
         _mulops->multiply((T*)(_expr->y),(T *)(_expr->a),(T*)(_expr->X),_expr->x->size1(),_expr->x->size2());
    }


    // _expr->printMatrix("Y");

    return (std::vector<T> *)_expr->Y; //the very fact that this is legal is exciting 
}

//Compile for these classes
template class AlTransform<long long>;
template class AlTransform<short>;
template class AlTransform<int>;