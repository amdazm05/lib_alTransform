#ifndef __ALTRANFORM
#define __ALTRANFORM
#include <matrixexpr.hpp>

template <class T>
class AlTransform
{
    private:
        static AlTransform *_inst;
        AlTransform();
        MatrixExpression<T> *_expr;

    public:
        static void init(void);
        static AlTransform<T> * get_instance();
        void setExpression(std::vector<T> &A);

};

// This library takes in A,x,B and out puts Y in the container that the user passes in 
// y=Ax+B


#endif