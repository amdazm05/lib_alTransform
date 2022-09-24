#include <iostream>
#include <altransform.hpp>
int main()
{
    AlTransform<float>::init();
    AlTransform<float> *handle = AlTransform<float>::get_instance();
    std::vector<float> y = {1,2,3,4,5,6,7,8,9};
    handle->setExpression(y);
    // handle->call();
    return 0;
}
