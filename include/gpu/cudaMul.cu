#include "cudaMul.cuh"
#include <iostream>

#define gpuErrchk(ans) { gpuAssert((ans), __FILE__, __LINE__); }
inline void gpuAssert(cudaError_t code, const char *file, int line, bool abort=true)
{
   if (code != cudaSuccess) 
   {
      fprintf(stderr,"GPUassert: %s %s %d\n", cudaGetErrorString(code), file, line);
      if (abort) exit(code);
   }
}

template<typename T>
__global__  void multiplyGPU
    (
        T * Ycuda, 
        T * Acuda, 
        T * xcuda,
        int m,
        int n
    )
{
    int blkindex = blockIdx.x*blockDim.x;
    int blkindex_lookahead = blockIdx.x*blockDim.x+blockDim.x;
    int j=0;
  
    int i = blkindex;
    for( ; i < blkindex_lookahead ; i++)
    {
        Ycuda[threadIdx.x+blkindex] = Ycuda[threadIdx.x+blkindex] + (Acuda[i])*xcuda[(j+threadIdx.x+(blockDim.x-1)*j)];
        // printf("iterator value = i = %d threadIdx = %d ,value = %d , block = %d , A %d, x %d \n",i,threadIdx.x,value, blockIdx.x,*(Acuda+i),(j+threadIdx.x+(blockDim.x-1)*j));
        j++;
    }

}


template<typename T>
__global__  void init
    (
        T * Ycuda, 
        T * Acuda, 
        T * xcuda,

        int m,
        int n
     )
{

}


template<typename T>
void multiplyMatrixGpuWrapper
        (
            void * Ycuda, 
            void * Acuda,
            void * xcuda,

            T * Y, 
            T * A, 
            T * x,

            int m,
            int n
        ) 
{
    int size = m*n*sizeof(T);


    gpuErrchk(cudaMalloc(&(Acuda),size));
    gpuErrchk(cudaMemcpy(Acuda,A ,size, cudaMemcpyHostToDevice));

    gpuErrchk(cudaMalloc(&(xcuda),size)); 
    gpuErrchk(cudaMemcpy(xcuda,x , size,cudaMemcpyHostToDevice));

    gpuErrchk(cudaMalloc(&(Ycuda),size));
    gpuErrchk(cudaMemcpy(Ycuda,Y , size,cudaMemcpyHostToDevice));

    // std::cout<<Acuda<<std::endl;

    multiplyGPU<<<m, n>>>((T*)Ycuda, (T*)Acuda,(T*)xcuda, m,n);
    gpuErrchk(cudaDeviceSynchronize());

    gpuErrchk(cudaMemcpy(Y,Ycuda ,size, cudaMemcpyDeviceToHost));

    cudaFree(Ycuda);
    cudaFree(xcuda);
    cudaFree(Acuda);

}


template void multiplyMatrixGpuWrapper<int>
(
    void * Ycuda, void * Acuda, void * xcuda,
    int * Y, int * A, int * x,
    int m,int n
);
template void multiplyMatrixGpuWrapper<short>
(
    void * Ycuda, void * Acuda, void * xcuda,
    short * Y, short * A, short * x,
    int m,int n
);

template void multiplyMatrixGpuWrapper<long long>
(
    void * Ycuda, void * Acuda, void * xcuda,
    long long* Y, long long * A, long long* x,
    int m,int n
);

