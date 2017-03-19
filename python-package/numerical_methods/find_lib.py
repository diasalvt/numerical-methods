import ctypes as C
import os

def _get_lib():
    dirpath = os.path.dirname(os.path.abspath(os.path.expanduser(__file__)))
    libpath_possible = [os.path.join(dirpath, '../libcpp/', 'libnumericalmethods.so')]
    libpath = [path for path in libpath_possible if os.path.exists(path) and os.path.isfile(path)]

    if not libpath:
        raise Exception("Library not found in :\n" + '\n'.join(libpath_possible))

    selected_lib = libpath[0]
    lib = C.cdll.LoadLibrary(selected_lib)

    return lib

_LIB = _get_lib()
