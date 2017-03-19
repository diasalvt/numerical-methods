from numerical_methods.find_lib import _LIB

import ctypes
import numpy as np

type_matrix = np.float32
cpp_cholesky_decomposition = _LIB._cholesky_decomposition
cpp_cholesky_decomposition.argtypes = [
    np.ctypeslib.ndpointer(dtype=type_matrix, ndim=2, flags='C_CONTIGUOUS'),
    np.ctypeslib.ndpointer(dtype=type_matrix, ndim=2, flags='C_CONTIGUOUS'),
    ctypes.c_int
]
cpp_cholesky_decomposition.restype = None


def cholesky_decomposition(A, check=False):
    """
    Compute the cholesky decomposition of a square matrix if possible.
    The matrix should be symetric, positive-definite.
    Compute A = LL^{T}

    Parameters
    ----------
    A: np.array
        Input matrix
    check: Boolean
        Check if the product of L and L transposed is close to A

    Return
    ------
    np.array
        Triangular Matrix L
    """
    A_float = A.astype(type_matrix)
    (n, m) = A_float.shape
    if n != m:
        ValueError("matrix is not a square matrix, n = {n} | m = {m}".format(n=n, m=m))

    res = np.zeros(shape=(n,n),dtype=type_matrix)
    cpp_cholesky_decomposition(A_float, res, n)

    if check:
        product = np.matmul(res, res.T)
        if np.allclose(product, A_float):
            print("A ~ L*L^T")
        else:
            print("NOT A ~ L*L^T")

    return res
