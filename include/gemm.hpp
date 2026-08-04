#ifndef GEMM_HPP
#define GEMM_HPP

#include "matrix_io.hpp"

constexpr int BLOCK_SIZE =32;

 //simple triple loop implemntation
Matrix gemmSimple(const Matrix& A, const Matrix &B);
// tiled implementation
Matrix gemmBlocking( const Matrix& A, const Matrix& B);

#endif