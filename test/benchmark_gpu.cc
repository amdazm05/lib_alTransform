#include <altransform.hpp>
#include <benchmark/benchmark.h>

static void GPU_MATRIX_BENCHMARK(benchmark::State& state) 
{
    AlTransform<int>::init();
    AlTransform<int> *handle = AlTransform<int>::get_instance();
    std::vector<int> y =  
       {1  ,23, 4,
        5  ,1,  5,
        12 ,4,  2};
    std::vector<int> x =  
       {1,1,67,
        1,1,0,
        89,0,1};
    std::vector<int> b =  
       {1,2,3,
        4,5,6,
        7,8,9};

    handle->setVariable(3,3,y,"A");
    handle->setVariable(3,3,x,"x");
    handle->setVariable(3,3,b,"B");


  for (auto _ : state)
  {
    handle->evaluateExpression();
  }
}
BENCHMARK(GPU_MATRIX_BENCHMARK)->Iterations(20000);

BENCHMARK_MAIN();