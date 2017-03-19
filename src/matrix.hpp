#ifndef MATRIX_HPP
#define MATRIX_HPP

#include<vector>

/* Templated Typedef C++11 */
template <class T>
using Matrix = std::vector<std::vector<T > >;

template <class T>
using Row = std::vector<T >;

#endif
