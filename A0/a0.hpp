/*  Viswa Nihar
 *  Nukala
 *  viswanih
 */

#ifndef A0_HPP
#define A0_HPP

#include <vector>
#include <omp.h>

// returns the index of the vector from the indices of the matrix
inline long long int return_index(int row, int column, int size) { 
    return (long long int) row * (long long int) size + (long long int) column;
}

void filter_2d(int n, int m, const std::vector<float>& K, std::vector<float>& A) {
    std::vector<float> B = A;
    // initialising the parallel construct
    #pragma omp parallel
    {
        // making sure that only one thread is run as tasks needs to be allocated by the thread
        #pragma omp single nowait
        {
	     // pragma to initate task with A, K and B as shared because all the threads need to either read or write from there variables.
            #pragma omp task shared(A, K, B)
            for (int i=0; i<n-1; i++) {
                // pragma to initate task loop with i as firstprivate
               #pragma omp task firstprivate(i)
                for (int j=0; j<m-1; j++) {
                    if(i!=0 && i!=n-1 && j!=0 && j!=m-1) {
                        int row_prev = i-1;
                        int row_next = i+1;
                        int col_prev = j-1;
                        int col_next = j+1;
                        long long int sum = 0;
                        
                        sum = sum + B[return_index(row_prev, col_prev, m)] * K[return_index(0, 0, 3)] + B[return_index(row_prev, j, m)] * K[return_index(1, 0, 3)] + B[return_index(row_prev, col_next, m)] * K[return_index(2, 0, 3)];
                        
                        sum = sum + B[return_index(row_prev, col_prev, m)] * K[return_index(0, 1, 3)] + B[return_index(row_prev, j, m)] * K[return_index(1, 1, 3)] + B[return_index(row_prev, col_next, m)] * K[return_index(2, 1, 3)];
                        
                        sum = sum + B[return_index(row_prev, col_prev, m)] * K[return_index(0, 2, 3)] + B[return_index(row_prev, j, m)] * K[return_index(1, 2, 3)] + B[return_index(row_prev, col_next, m)] * K[return_index(2, 2, 3)];
                        
                        sum = sum + B[return_index(i, col_prev, m)] * K[return_index(0, 0, 3)] + B[return_index(i, j, m)] * K[return_index(1, 0, 3)] + B[return_index(i, col_next, m)] * K[return_index(2, 0, 3)];
                        
                        sum = sum + B[return_index(i, col_prev, m)] * K[return_index(0, 1, 3)] + B[return_index(i, j, m)] * K[return_index(1, 1, 3)] + B[return_index(i, col_next, m)] * K[return_index(2, 1, 3)];
                        
                        sum = sum + B[return_index(i, col_prev, m)] * K[return_index(0, 2, 3)] + B[return_index(i, j, m)] * K[return_index(1, 2, 3)] + B[return_index(i, col_next, m)] * K[return_index(2, 2, 3)];
                        
                        sum = sum + B[return_index(row_next, col_prev, m)] * K[return_index(0, 1, 3)] + B[return_index(row_next, j, m)] * K[return_index(1, 0, 3)] + B[return_index(row_next, col_next, m)] * K[return_index(2, 0, 3)];
                        
                        sum = sum + B[return_index(row_next, col_prev, m)] * K[return_index(0, 1, 3)] + B[return_index(row_next, j, m)] * K[return_index(1, 1, 3)] + B[return_index(row_next, col_next, m)] * K[return_index(2, 1, 3)];
                        
                        sum = sum + B[return_index(row_next, col_prev, m)] * K[return_index(0, 2, 3)] + B[return_index(row_next, j, m)] * K[return_index(1, 2, 3)] + B[return_index(row_next, col_next, m)] * K[return_index(2, 2, 3)];
                        
                        A[(long long int)(i)*(long long int)(m)+(long long int)(j)] = sum;
                    }
                }
            }
        }
    }

} // filter_2d

#endif // A0_HPP
