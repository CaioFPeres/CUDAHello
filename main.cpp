#include <cuda.h>
#include <iostream>
#include <windows.h>

using namespace std;

void MaximumCUDACapabilities(CUdevice& dev){
    int maxThreadsPerBlock, maxGridSize, maxBlockSize, maxThreadsPerSM, maxWarpsPerSM, maxSMs;
    cuDeviceGetAttribute(&maxThreadsPerBlock, CU_DEVICE_ATTRIBUTE_MAX_THREADS_PER_BLOCK, dev);
    cuDeviceGetAttribute(&maxBlockSize, CU_DEVICE_ATTRIBUTE_MAX_BLOCK_DIM_X, dev);
    cuDeviceGetAttribute(&maxGridSize, CU_DEVICE_ATTRIBUTE_MAX_GRID_DIM_X, dev);
    cuDeviceGetAttribute(&maxThreadsPerSM, CU_DEVICE_ATTRIBUTE_MAX_THREADS_PER_MULTIPROCESSOR, dev);
    cuDeviceGetAttribute(&maxSMs, CU_DEVICE_ATTRIBUTE_MULTIPROCESSOR_COUNT, dev);
    cuDeviceGetAttribute(&maxWarpsPerSM, CU_DEVICE_ATTRIBUTE_WARP_SIZE, dev);

    // max (max because SMs) = 131,072 threads (1024 threads/block *  128 blocks/grid);
    cout << "threads: " << maxThreadsPerSM << " SMs: " << maxSMs << " warpsize: " << maxWarpsPerSM << '\n';
    cout << maxThreadsPerSM * maxSMs << '\n';

    printf("Max Threads Per Block: %i\n", maxThreadsPerBlock);
    printf("Max Block Size X: %i\n", maxBlockSize);
    printf("Max Grid Size X: %i\n", maxGridSize);
    printf("Max Grid Size X: %i\n", maxSMs);
}

int main() {
    CUdevice device;
    CUcontext context;
    CUmodule module;
    CUfunction kernel;
    CUresult res;

    // Initialize the CUDA driver API
    cuInit(0);

    // Get and initialize the GPU device
    cuDeviceGet(&device, 0);
    cuCtxCreate(&context, 0, device);

    MaximumCUDACapabilities(device);

    // Load the compiled CUBIN module
    res = cuModuleLoad(&module, "main.cubin");
    cout << "moduleLoad: " << res << '\n';

    // Get a handle to the kernel function
    res = cuModuleGetFunction(&kernel, module, "helloCUDA");
    cout << "moduleLoad: " << res << '\n';

    // for you to read stdout
    Sleep(3000);

    // max for my GPU (max because Streaming Multiprocessors) = 47.104 threads (1024 threads/block *  46 blocks/grid);
    // Set up kernel parameters and launch the kernel
    const int blockSize = 1024; // Number of threads per block
    const int numBlocks = 46;   // Number of blocks per grid
    // void* args[] = { /* kernel arguments */ };

    // Launching the kernel (CUDA function)
    res = cuLaunchKernel(kernel, numBlocks, 1, 1, // Grid dimensions
                         blockSize, 1, 1,         // Block dimensions
                         0, NULL, NULL, NULL);

    cuCtxSynchronize();

    // Clean up
    cuModuleUnload(module);
    cuCtxDestroy(context);

    return 0;
}