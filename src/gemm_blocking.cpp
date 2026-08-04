#include "gemm.hpp"
#include <algorithm>
using namespace std;

//cache blocked GEMM

Matrix gemmBlocking(const Matrix& A , const Matrix& B){
    const int M = A.rows;
    const int K = A.cols;
    const int N = B.cols;

    Matrix C(M,N);

    for(int ii=0; ii<M ; ii += BLOCK_SIZE){
        for (int jj=0; jj<N ; jj += BLOCK_SIZE){
            for(int kk=0; kk<K ; kk+= BLOCK_SIZE){
                
                // handles reading /writing out of bounds
                int iMax = min(ii + BLOCK_SIZE, M);
                int jMax = min(jj + BLOCK_SIZE, N);
                int kMax = min(kk + BLOCK_SIZE, K);

                // triple loop for current tile
                for ( int i =ii ; i< iMax; ++i ){
                    for(int j= jj ; j< jMax; ++j){
                        long long sum = C.at(i,j);
                        for(int k =kk; k< kMax; ++k){
                            sum += A.at(i,k) * B.at(k, j);
                        }
                        C.at(i,j) = sum;
                    }
                    //  return C;
                }
                
            }
            
        }
    }
     return C;
}