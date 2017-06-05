from numerical_methods.find_lib import _LIB

import ctypes
import numpy as np

cpp_local_clustering_l2 = _LIB._local_clustering_l2
cpp_local_clustering_l2.argtypes = [
    np.ctypeslib.ndpointer(dtype=np.float32, ndim=2, flags='C_CONTIGUOUS'),
    np.ctypeslib.ndpointer(dtype=np.int32, ndim=2, flags='C_CONTIGUOUS'),
    np.ctypeslib.ndpointer(dtype=np.float32, ndim=2, flags='C_CONTIGUOUS'),
    ctypes.c_int,
    ctypes.c_int,
    ctypes.c_int,
    ctypes.c_float,
    ctypes.c_int
]
cpp_local_clustering_l2.restype = None

cpp_local_clustering_l1 = _LIB._local_clustering_l1
cpp_local_clustering_l1.argtypes = [
    np.ctypeslib.ndpointer(dtype=np.float32, ndim=2, flags='C_CONTIGUOUS'),
    np.ctypeslib.ndpointer(dtype=np.int32, ndim=2, flags='C_CONTIGUOUS'),
    np.ctypeslib.ndpointer(dtype=np.float32, ndim=2, flags='C_CONTIGUOUS'),
    ctypes.c_int,
    ctypes.c_int,
    ctypes.c_int,
    ctypes.c_float,
    ctypes.c_int
]
cpp_local_clustering_l1.restype = None

cpp_local_clustering_l0 = _LIB._local_clustering_l0
cpp_local_clustering_l0.argtypes = [
    np.ctypeslib.ndpointer(dtype=np.float32, ndim=2, flags='C_CONTIGUOUS'),
    np.ctypeslib.ndpointer(dtype=np.int32, ndim=2, flags='C_CONTIGUOUS'),
    np.ctypeslib.ndpointer(dtype=np.float32, ndim=2, flags='C_CONTIGUOUS'),
    ctypes.c_int,
    ctypes.c_int,
    ctypes.c_int,
    ctypes.c_float,
    ctypes.c_int
]
cpp_local_clustering_l0.restype = None

def local_clustering_l2(X, k, penalty, nbiter=20):
    """
    Compute local (along y axis) clusters.
    Loss function L2

    Parameters
    ----------
    X: np.array
        Input matrix
    k: int
        number of clusters
    penalty: float
        penalize the number of jump

    Return
    ------
    np.array
        S, from which cluster
    np.array
        A, clusters
    """
    X_float = X.astype(np.float32)
    (n, m) = X_float.shape
    S = np.zeros((n, m), dtype=np.int32)
    A = X_float[np.random.choice(len(X_float), k, replace=False), :]

    cpp_local_clustering_l2(X_float, S, A, n, m, k, penalty, nbiter)
    return (S, A)

def local_clustering_l1(X, k, penalty, nbiter=20):
    """
    Compute local (along y axis) clusters.
    Loss function L1

    Parameters
    ----------
    X: np.array
        Input matrix
    k: int
        number of clusters
    penalty: float
        penalize the number of jump

    Return
    ------
    np.array
        S, from which cluster
    np.array
        A, clusters
    """
    X_float = X.astype(np.float32)
    (n, m) = X_float.shape
    S = np.zeros((n, m), dtype=np.int32)
    A = X_float[np.random.choice(len(X_float), k, replace=False), :]

    cpp_local_clustering_l1(X_float, S, A, n, m, k, penalty, nbiter)
    return (S, A)

def local_clustering_l0(X, k, penalty, nbiter=20):
    """
    Compute local (along y axis) clusters.
    Loss function L1

    Parameters
    ----------
    X: np.array
        Input matrix
    k: int
        number of clusters
    penalty: float
        penalize the number of jump

    Return
    ------
    np.array
        S, from which cluster
    np.array
        A, clusters
    """
    X_float = X.astype(np.float32)
    (n, m) = X_float.shape
    S = np.zeros((n, m), dtype=np.int32)
    A = X_float[np.random.choice(len(X_float), k, replace=False), :]

    cpp_local_clustering_l0(X_float, S, A, n, m, k, penalty, nbiter)
    return (S, A)

def build_SA(S, A):
    _, m = S.shape
    x = np.arange(m)
    # x will be broadcast to the size of S
    return A[S, x]
