#ifndef MATRIX_ARRAY_MATRIX_ARRAY_H
#define MATRIX_ARRAY_MATRIX_ARRAY_H
#define MATRIX_ARRAY_SQUARE_MATRIX_IMPLEMENTED

#include <util/constants.h>
#include <iostream>
#include "rational.h"

class MatrixArrayIsDegenerateError : public std::runtime_error {
public:
    MatrixArrayIsDegenerateError() : std::runtime_error("MatrixArrayIsDegenerateError") {
    }
};

class MatrixArrayOutOfRange : public std::out_of_range {
public:
    MatrixArrayOutOfRange() : std::out_of_range("MatrixArrayOutOfRange") {
    }
};

template <class T, size_t M, size_t N>
class MatrixArray {
public:
    T matrix[M][N];
    size_t RowsNumber() const {
        return M;
    }
    size_t ColumnsNumber() const {
        return N;
    }
    const T& operator()(size_t, size_t) const;
    T& operator()(size_t, size_t);
    const T& At(size_t, size_t) const;
    T& At(size_t, size_t);
    MatrixArray<T, N, M> GetTransposed() const;
    MatrixArray<T, M, N> operator+(const MatrixArray<T, M, N>&) const;
    MatrixArray<T, M, N> operator-(const MatrixArray<T, M, N>&) const;
    MatrixArray<T, M, N>& operator*=(const MatrixArray<T, N, N>&);
    MatrixArray<T, M, N>& operator+=(const MatrixArray<T, M, N>&);
    MatrixArray<T, M, N>& operator-=(const MatrixArray<T, M, N>&);
    MatrixArray<T, M, N> operator*(int number) const;
    MatrixArray<T, M, N>& operator*=(int number);
    MatrixArray<T, M, N> operator/(int number) const;
    MatrixArray<T, M, N>& operator/=(int number);
    bool operator==(const MatrixArray<T, M, N>&) const;
    bool operator!=(const MatrixArray<T, M, N>&) const;
    MatrixArray<T, M, N> GetInversed() const;
    MatrixArray<T, M, N>& Inverse();
    Rational Determinant() const;
    T Trace() const;
    MatrixArray<T, M, N>& Transpose();
};

template <class T, size_t M, size_t N>
T& MatrixArray<T, M, N>::operator()(size_t i, size_t j) {
    return matrix[i][j];
}

template <class T, size_t M, size_t N>
const T& MatrixArray<T, M, N>::operator()(size_t i, size_t j) const {
    return matrix[i][j];
}

template <class T, size_t M, size_t N>
T& MatrixArray<T, M, N>::At(size_t i, size_t j) {
    if ((i >= M) || (j >= N)) {
        throw MatrixArrayOutOfRange{};
    }
    return matrix[i][j];
}

template <class T, size_t M, size_t N>
const T& MatrixArray<T, M, N>::At(size_t i, size_t j) const {
    if ((i >= M) || (j >= N)) {
        throw MatrixArrayOutOfRange{};
    }
    return matrix[i][j];
}

template <class T, size_t M, size_t N>
MatrixArray<T, N, M> MatrixArray<T, M, N>::GetTransposed() const {
    MatrixArray<T, N, M> transposed_matrix;
    for (size_t i = 0; i < M; ++i) {
        for (size_t j = 0; j < N; ++j) {
            transposed_matrix(j, i) = matrix[i][j];
        }
    }
    return transposed_matrix;
}

template <class T, size_t M, size_t N>
MatrixArray<T, M, N> MatrixArray<T, M, N>::operator+(const MatrixArray<T, M, N>& right_matrix) const {
    MatrixArray<T, M, N> result_matrix;
    for (size_t i = 0; i < M; ++i) {
        for (size_t j = 0; j < N; ++j) {
            result_matrix(i, j) = matrix[i][j] + right_matrix(i, j);
        }
    }
    return result_matrix;
}

template <class T, size_t M, size_t N>
MatrixArray<T, M, N> MatrixArray<T, M, N>::operator-(const MatrixArray<T, M, N>& right_matrix) const {
    MatrixArray<T, M, N> result_matrix;
    for (size_t i = 0; i < M; ++i) {
        for (size_t j = 0; j < N; ++j) {
            result_matrix(i, j) = matrix[i][j] - right_matrix(i, j);
        }
    }
    return result_matrix;
}

template <class T, size_t M, size_t N, size_t K>
MatrixArray<T, M, K> operator*(const MatrixArray<T, M, N>& left_matrix, const MatrixArray<T, N, K>& right_matrix) {
    MatrixArray<T, M, K> result_matrix;
    for (size_t i = 0; i < M; ++i) {
        for (size_t j = 0; j < K; ++j) {
            result_matrix(i, j) = 0;
            for (size_t k = 0; k < N; ++k) {
                result_matrix(i, j) += left_matrix(i, k) * right_matrix(k, j);
            }
        }
    }
    return result_matrix;
}

template <class T, size_t M, size_t N>
MatrixArray<T, M, N>& MatrixArray<T, M, N>::operator+=(const MatrixArray<T, M, N>& right_matrix) {
    for (size_t i = 0; i < M; ++i) {
        for (size_t j = 0; j < N; ++j) {
            matrix[i][j] += right_matrix(i, j);
        }
    }
    return *this;
}

template <class T, size_t M, size_t N>
MatrixArray<T, M, N>& MatrixArray<T, M, N>::operator-=(const MatrixArray<T, M, N>& right_matrix) {
    MatrixArray<T, M, N> result_matrix;
    for (size_t i = 0; i < M; ++i) {
        for (size_t j = 0; j < N; ++j) {
            matrix[i][j] -= right_matrix(i, j);
        }
    }
    return *this;
}

template <class T, size_t M, size_t N>
MatrixArray<T, M, N>& MatrixArray<T, M, N>::operator*=(const MatrixArray<T, N, N>& right_matrix) {
    MatrixArray<T, M, N> result_matrix = *this * right_matrix;
    *this = result_matrix;
    return *this;
}

template <class T, size_t M, size_t N>
MatrixArray<T, M, N> MatrixArray<T, M, N>::operator*(int number) const {
    MatrixArray<T, M, N> result_matrix;
    for (size_t i = 0; i < M; ++i) {
        for (size_t j = 0; j < N; ++j) {
            result_matrix(i, j) = matrix[i][j] * number;
        }
    }
    return result_matrix;
}

template <class T, size_t M, size_t N>
MatrixArray<T, M, N> operator*(int number, const MatrixArray<T, M, N>& matrix_array) {
    MatrixArray<T, M, N> result_matrix;
    for (size_t i = 0; i < M; ++i) {
        for (size_t j = 0; j < N; ++j) {
            result_matrix(i, j) = matrix_array(i, j) * number;
        }
    }
    return result_matrix;
}

template <class T, size_t M, size_t N>
MatrixArray<T, M, N>& MatrixArray<T, M, N>::operator*=(int number) {
    MatrixArray<T, M, N> result_matrix;
    for (size_t i = 0; i < M; ++i) {
        for (size_t j = 0; j < N; ++j) {
            result_matrix(i, j) = matrix[i][j] * number;
        }
    }
    *this = result_matrix;
    return *this;
}

template <class T, size_t M, size_t N>
MatrixArray<T, M, N> MatrixArray<T, M, N>::operator/(int number) const {
    MatrixArray<T, M, N> result_matrix;
    for (size_t i = 0; i < M; ++i) {
        for (size_t j = 0; j < N; ++j) {
            result_matrix(i, j) = matrix[i][j] / number;
        }
    }
    return result_matrix;
}

template <class T, size_t M, size_t N>
MatrixArray<T, M, N>& MatrixArray<T, M, N>::operator/=(int number) {
    MatrixArray<T, M, N> result_matrix;
    for (size_t i = 0; i < M; ++i) {
        for (size_t j = 0; j < N; ++j) {
            result_matrix(i, j) = matrix[i][j] / number;
        }
    }
    *this = result_matrix;
    return *this;
}

template <class T, size_t M, size_t N>
bool MatrixArray<T, M, N>::operator==(const MatrixArray<T, M, N>& right_matrix) const {
    for (size_t i = 0; i < M; ++i) {
        for (size_t j = 0; j < N; ++j) {
            if (matrix[i][j] != right_matrix(i, j)) {
                return false;
            }
        }
    }
    return true;
}

template <class T, size_t M, size_t N>
bool MatrixArray<T, M, N>::operator!=(const MatrixArray<T, M, N>& right_matrix) const {
    return !(*this == right_matrix);
}

template <class T, size_t M, size_t N>
std::istream& operator>>(std::istream& in, MatrixArray<T, M, N>& matrix_array) {
    for (size_t i = 0; i < M; ++i) {
        for (size_t j = 0; j < N; ++j) {
            in >> matrix_array.matrix[i][j];
        }
    }
    return in;
}

template <class T, size_t M, size_t N>
std::ostream& operator<<(std::ostream& out, const MatrixArray<T, M, N>& matrix_array) {
    for (size_t i = 0; i < M; ++i) {
        for (size_t j = 0; j < N; ++j) {
            out << matrix_array.matrix[i][j];
            if (j < N - 1) {
                out << ' ';
            }
        }
        out << "\n";
    }
    return out;
}

template <class T, size_t M, size_t N>
MatrixArray<T, M, N>& MatrixArray<T, M, N>::Transpose() {
    static_assert(M == N, "Not a square matrix");
    *this = GetTransposed();
    return *this;
}

template <class T, size_t M, size_t N>
T MatrixArray<T, M, N>::Trace() const {
    static_assert(M == N, "Not a square matrix");
    T trace = 0;
    for (size_t i = 0; i < M; ++i) {
        trace += matrix[i][i];
    }
    return trace;
}

template <class T, size_t M, size_t N>
Rational MatrixArray<T, M, N>::Determinant() const {
    static_assert(M == N, "Not a square matrix");
    MatrixArray<Rational, M, N> matrix_copy;
    Rational factor = 1;
    for (size_t i = 0; i < M; ++i) {
        for (size_t j = 0; j < N; ++j) {
            matrix_copy.matrix[i][j] = Rational(matrix[i][j]);
        }
    }
    for (size_t j = 0; j < N; ++j) {
        size_t i = j;
        while ((i < M) && (matrix_copy.matrix[i][j] == 0)) {
            i++;
        }
        if (i == M) {
            continue;
        }
        if (i != j) {
            for (size_t k = 0; k < N; ++k) {
                std::swap(matrix_copy.matrix[i][k], matrix_copy.matrix[j][k]);
            }
            factor *= -1;
        }
        factor *= matrix_copy.matrix[j][j];
        Rational inverse = Rational(1) / matrix_copy.matrix[j][j];
        for (size_t k = 0; k < N; ++k) {
            matrix_copy.matrix[j][k] *= inverse;
        }
        for (size_t k = j + 1; k < M; ++k) {
            Rational leader = matrix_copy.matrix[k][j];
            for (size_t l = 0; l < N; ++l) {
                matrix_copy.matrix[k][l] -= leader * matrix_copy.matrix[j][l];
            }
        }
    }
    Rational det = factor;
    for (size_t i = 0; i < M; ++i) {
        det *= matrix_copy.matrix[i][i];
    }
    return det;
}

template <class T, size_t M, size_t N>
MatrixArray<T, M, N> MatrixArray<T, M, N>::GetInversed() const {
    static_assert(M == N, "Not a square matrix");
    if (Determinant() == 0) {
        throw MatrixArrayIsDegenerateError{};
    }
    MatrixArray<Rational, M, N> matrix_copy;
    MatrixArray<Rational, M, N> ident_matrix;
    for (size_t i = 0; i < M; ++i) {
        for (size_t j = 0; j < N; ++j) {
            matrix_copy.matrix[i][j] = Rational(matrix[i][j]);
            ident_matrix.matrix[i][j] = (i == j) ? 1 : 0;
        }
    }
    for (size_t j = 0; j < N; ++j) {
        size_t i = j;
        while ((i < M) && (matrix_copy.matrix[i][j] == 0)) {
            i++;
        }
        if (i == M) {
            continue;
        }
        if (i != j) {
            for (size_t k = 0; k < N; ++k) {
                std::swap(matrix_copy.matrix[i][k], matrix_copy.matrix[j][k]);
                std::swap(ident_matrix.matrix[i][k], ident_matrix.matrix[j][k]);
            }
        }
        Rational inverse = Rational(1) / matrix_copy.matrix[j][j];
        for (size_t k = 0; k < N; ++k) {
            matrix_copy.matrix[j][k] *= inverse;
            ident_matrix.matrix[j][k] *= inverse;
        }
        for (size_t k = 0; k < M; ++k) {
            if (k == j) {
                continue;
            }
            Rational leader = matrix_copy.matrix[k][j];
            for (size_t l = 0; l < N; ++l) {
                matrix_copy.matrix[k][l] -= leader * matrix_copy.matrix[j][l];
                ident_matrix.matrix[k][l] -= leader * ident_matrix.matrix[j][l];
            }
        }
    }
    return ident_matrix;
}

template <class T, size_t M, size_t N>
MatrixArray<T, M, N>& MatrixArray<T, M, N>::Inverse() {
    static_assert(M == N, "Not a square matrix");
    if (Determinant() == 0) {
        throw MatrixArrayIsDegenerateError{};
    }
    *this = GetInversed();
    return *this;
}

template <class T, size_t M, size_t N>
MatrixArray<T, M, 1> SolveLinearSystem(MatrixArray<T, M, N> a, MatrixArray<T, M, 1> b) {
    static_assert(M == N, "Not a square matrix");
    if (a.Determinant() == 0) {
        throw MatrixArrayIsDegenerateError{};
    }
    return a.GetInversed() * b;
}

#endif
