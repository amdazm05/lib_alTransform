# lib_alTransform
A boost based Affine transformation library written in C++ / Supports CUDA for acceleration
**You will be needing boost as a dependancy**

### Building process 
``` 
    mkdir -p build
    cmake ..
    make
```
### Enabling GPU CUDA for acceleration
```
  cmake .. -DGPU_ACCELERATION=ON
```

### Work in progress !
TODO : OpenCL support 
