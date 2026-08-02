#include "gemm.hpp"

Matrix gemmSimple(const Matrix& A, const Matrix& B){
    const int M=A.rows;
    const int K= A.cols;
    const int N= B.cols;

    Matrix C(M,N);

    for (int i =0; i <M; ++i){
        for(int j=0; j<N; ++j){
            long long sum=0;
            for(int k =0; k<K; ++k){
                sum += A.at(i,k)*B.at(k, j);
            }
            c.at(i,j) = sum;
        }
    }
    return c;
}