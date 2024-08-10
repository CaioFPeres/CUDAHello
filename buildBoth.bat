:: This is building a .cu file that contains both host code (CPU) and device code (GPU)
:: nvcc by default on windows only uses cl.exe (ships with microsof visual studio)
:: the -allow-unsupported-compiler is applied because it often mistakes the version that it supports from cl.exe,
:: for example when you have a more updated version of cl.exe that nvcc doesn't know.

nvcc main.cu -o main -allow-unsupported-compiler