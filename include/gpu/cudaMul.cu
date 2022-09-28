#include "cudaMul.cuh"
#include <iostream>

template<typename T>
__global__  void multiplyGPU
    (
        T * Ycuda, 
        T * Acuda, 
        T * xcuda,
        int m,
        int n,
        int width,
        T spacing
     )
{
  int r = blockIdx.y * blockDim.y + threadIdx.y;   
  int c = blockIdx.x * blockDim.x + threadIdx.x;
  // check boundry conditions
  if( r < m && c < n){
    // do the multiplication for one row and col
    T value = 0;
    for(int k = 0; k < 9; k++){
      value += (*(Acuda+r * width + k)) * (*(xcuda+(k * n) + c));
    }
    // store the result
    *(Ycuda+c * n + c) = value;
    printf("%d ", *(Ycuda+r * n + c));
  }
}


template<typename T>
__global__  void init
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
    int r = blockIdx.y * blockDim.y + threadIdx.y;   
    // int c = blockIdx.x * blockDim.x + threadIdx.x;

    for(int k = 0; k < n; k++)
        {
            // *((T*)Acuda+ (r* n+c)) = *(A+ (r* n+c));
            // *((T*)xcuda+ (r* n+c)) = *(x+ (r* n+c));

            printf("%d",((T*)Acuda)[r * n + k]);
        }
}


template<typename T>
void multiplyMatrixGpuWrapper(
        void * Ycuda, 
        void * Acuda, 
        void * xcuda,

        T * Y, 
        T * A, 
        T * x,

        int m,
        int n,
        int width,
        T spacing
        ) 
{
    // dim3 block_dim(1,1,1);
    // dim3 grid_dim(1,1,1);

    std::cout<<"In the wrapper functions \n";
    int size = m*n*sizeof(T);
    std::cout<<*(A+1)<<std::endl;
    std::cout<<size<<std::endl;

    cudaMalloc(&(Acuda),size);
    cudaMemcpy(Acuda,A ,size, cudaMemcpyHostToDevice);

    cudaMalloc(&(xcuda),size); 
    cudaMemcpy(xcuda,x , size,cudaMemcpyHostToDevice);

    cudaMalloc(&(Ycuda),size);
    cudaMemcpy(Ycuda,Y ,size, cudaMemcpyHostToDevice);

    // std::cout<<Acuda<<std::endl;

    multiplyGPU<<<3, 3>>>((T*)Ycuda, (T*)Acuda,(T*)xcuda, m,n ,width,spacing);
    cudaDeviceSynchronize();

    cudaMemcpy(Y,Ycuda ,size, cudaMemcpyHostToDevice);

    cudaFree(Ycuda);
    cudaFree(xcuda);
    cudaFree(Acuda);

}


template void multiplyMatrixGpuWrapper<int>
(
    void * Ycuda, void * Acuda, void * xcuda,
    int * Y, int * A, int * x,
    int m,int n,int width,int type
);
template void multiplyMatrixGpuWrapper<short>
(
    void * Ycuda, void * Acuda, void * xcuda,
    short * Y, short * A, short * x,
    int m,int n,int width,short type
);

template void multiplyMatrixGpuWrapper<long long>
(
    void * Ycuda, void * Acuda, void * xcuda,
    long long* Y, long long * A, long long* x,
    int m,int n,int width,long long type
);

