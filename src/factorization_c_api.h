#ifndef FACTORIZATION_C_API_H
#define FACTORIZATION_C_API_H

#include <cstddef>

typedef void* cmatrix;

extern "C" {
void _cholesky_decomposition(cmatrix in, cmatrix out, size_t n);
}

#endif
