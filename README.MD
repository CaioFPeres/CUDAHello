## Overview

This is a Hello world in CUDA, using all the available processing capabilities.

## Compiling methods
There are 5 main ways for compiling CUDA:
- As .ptx (intermediary code, to be compiled at runtime (JIT));
- As .cubin (optimized for specified architecture);
- As .o (I really dont know the difference between this and .cubin, maybe its because it is for any GPU arch?)
- As executable, directly from nvcc using cl.exe.
- As .fatbin: This mode generates a fat binary that contains both PTX and CUBIN code for multiple architectures. The CUDA runtime or driver selects the appropriate code for the GPU at runtime.

Compiling both as .o and linking them with GCC:

```
nvcc -c cuda_code.cu -o cuda_code.o
g++ -c host_code.cpp -o host_code.o
g++ host_code.o cuda_code.o -o final_executable.exe -lcuda
```

`extern "C"` is often used on CUDA kernels in order to force C++ compiler to preserve function names (otherwise, it will throw an runtime error for not finding the function).