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
__global__  void GPUMemcpy
    (
        T * Acuda, 
        T * xcuda,

        T * Y,
        T * A, 
        T * x,
        int m,
        int n
    )
{
    //TODO @Explore more options 
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


    cudaMallocManaged(&Acuda, size);
    cudaMallocManaged(&xcuda, size);
    cudaMallocManaged(&Ycuda, size);

    for(int i=0; i< m*n;i++)
    {
        *((T*)xcuda+i)=*(x+i);
        *((T*)Acuda+i)=*(A+i);
    }

    // GPUMemcpy<<<m,n>>>((T*)Acuda,(T*)xcuda,Y,A,x, m,n);
    // cudaDeviceSynchronize();
    multiplyGPU<<<m, n>>>((T*)Ycuda, (T*)Acuda,(T*)xcuda, m,n);
    cudaDeviceSynchronize();

    for(int i=0; i< m*n;i++)
    {
        *(Y+i)=*((T*)Ycuda+i);
    }

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

