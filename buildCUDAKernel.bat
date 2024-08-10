:: You can compile GPU code to be a .o file, and link with the host code .exe. I dont really know the difference, 
:: but it is said that CUBIN are the fastest option since it is
:: specifically optimized for the specified architecture.

:: These two are to be both loaded in runtime:
:: PTX: Intermediary code to be compiled at runtime (JIT).
:: CUBIN: Optimized machine code specifically to the specified GPU architecture. No meu caso, rtx 2080 eh turing, portanto sm_75

nvcc -arch=sm_75 -cubin main.cu -o main.cubin -allow-unsupported-compiler