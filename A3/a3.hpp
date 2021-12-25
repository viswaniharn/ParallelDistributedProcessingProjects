/*  Viswa Nihar
 *  Nukala
 *  viswanih
 */

#ifndef A3_HPP
#define A3_HPP
#include <math.h>
#include <cuda_runtime_api.h>
#define block_size 1024

__global__ void guassian_kernel(int n, float h, float* shared_x, float* shared_y) {
    int id = blockIdx.x * blockDim.x + threadIdx.x;

    float my_data = shared_x[id];

    __shared__ float buf[block_size];

    __syncthreads();

    float f = 0.0;

    float denom = 1 / (sqrt ( 2 * 3.14285 ) * n * h);

    // To load a block length of data from the original array into the block
    for (int iter = 0; iter<gridDim.x; iter++) {
        int ind = (iter)*blockDim.x + threadIdx.x;
        buf[threadIdx.x] = shared_x[ind];

        __syncthreads();

        // To apply kernel over the shared buffer
        for(int i=0; (i<block_size && blockDim.x * iter + i < n) ; i++) {
            float x = powf((my_data - buf[i]) / h, 2) / 2;
            f += exp(-x);
        }

        __syncthreads();
    }
    shared_y[id] = denom * f;
}

void gaussian_kde(int n, float h, const std::vector<float>& x, std::vector<float>& y) {

    int num_blocks = ((block_size + n - 1) / block_size);

    float *shared_x = NULL;
    float *shared_y = NULL;

    cudaMalloc(&shared_x, sizeof(float) * n);
    cudaMalloc(&shared_y, sizeof(float) * n);

    dim3 d_block_dim(block_size);
    dim3 d_num_block_dim(num_blocks);

    cudaMemcpy(shared_x, x.data(), sizeof(float) * n, cudaMemcpyHostToDevice);

    guassian_kernel<<<d_num_block_dim, d_block_dim>>>(n, h, shared_x, shared_y);

    cudaMemcpy(y.data(), shared_y, sizeof(float) * n, cudaMemcpyDeviceToHost);

    cudaFree(shared_x);
    cudaFree(shared_y);
} // gaussian_kde

#endif // A3_HPP
