#include <stdio.h>

using namespace std;

extern "C" __global__ void helloCUDA()
{
    printf("HELLO FROM CUDA\n");
}

/*
int main()
{
    helloCUDA<<<1, 1>>>();
    cudaDeviceSynchronize();
    return 0;
}
*/
