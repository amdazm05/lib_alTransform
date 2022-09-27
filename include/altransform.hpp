#ifndef __ALTRANFORM
#define __ALTRANFORM
#include "matrixexpr.hpp"
#include "mulmatrix.hpp"

template <class T>
class AlTransform 
{
    private:
        static AlTransform *_inst;
        AlTransform();
        MatrixExpression<T> *_expr;
        MatrixMul<T> * _mulops;

    public:
        static void init(void);
        static AlTransform<T> * get_instance();
        void setVariable(
            short m,short n,
            std::vector<T> &A,
            const std::string literal);

        void setExpression(
            std::vector<T> &A,
            std::vector<T> &x, 
            std::vector<T> &B ,
            const std::string literal);

        std::vector<T> *evaluateExpression();
};


// This library takes in A,x,B and out puts Y in the container that the user passes in 
// y=Ax+B


#endif  //__ALTRANFORM