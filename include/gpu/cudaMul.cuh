#pragma once 

template<typename T>
__global__  void multiplyGPU
    (
        void * Ycuda, 
        void * Acuda, 
        void * xcuda,
        int m,
        int n,
        int width,
        T spacing
     );

template<typename T>
__global__  void init
    (
        T * Ycuda, 
        T * Acuda, 
        T * xcuda,

        T * Y, 
        T * A, 
        T * x,

        int m,
        int n
     );

template<typename T>
void multiplyMatrixGpuWrapper(void * Ycuda, 
        void * Acuda, 
        void * xcuda,

        T * Y, 
        T * A, 
        T * x,

        int m,
        int n,
        int width,
        T spacing
        );