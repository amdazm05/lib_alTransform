#include <iostream>
#include <altransform.hpp>
int main()
{
    AlTransform<int>::init();
    AlTransform<int> *handle = AlTransform<int>::get_instance();
    std::vector<int> y =  
       {1,2,3,
        4,5,6,
        7,8,9};
    std::vector<int> x =  
       {1,2,3,
        4,5,6,
        7,8,9};
    std::vector<int> b =  
       {1,2,3,
        4,5,6,
        7,8,9};


    handle->setVariable(3,3,y,"A");
    handle->setVariable(3,3,x,"x");
    handle->setVariable(3,3,b,"B");
    
    handle->evaluateExpression();
    // handle->call();
    return 0;
}
