#pragma once

#include <cstddef>
#include <vector>
#include <stdexcept>
#include <cmath>

struct point {
    std::size_t x;
    std::size_t y;
    
    // Equality operator for point comparison
    bool operator==(const point& other) const {
        return x == other.x && y == other.y;
    }
    
    // Inequality operator (optional but useful)
    bool operator!=(const point& other) const {
        return !(*this == other);
    }
};

namespace utils {
    inline int sign(int x) {
        if(x > 0)
            return 1;
        if(x < 0)
            return -1;
        return 0;
    }
    


    namespace matrix {
        class Matrix {
            private:
                // Proxy class for row access (enables [][] operator)
                class RowProxy {
                    private:
                        std::vector<double>& row;
                    public:
                        RowProxy(std::vector<double>& r) : row(r) {}
                        // Non-const version: returns reference for assignment
                        double& operator[](int col) {
                            return row[col];
                        }
                        // Const version: returns const reference for reading
                        const double& operator[](int col) const {
                            return row[col];
                        }
                };
                
                // Const proxy class for const Matrix access
                class ConstRowProxy {
                    private:
                        const std::vector<double>& row;
                    public:
                        ConstRowProxy(const std::vector<double>& r) : row(r) {}
                        const double& operator[](int col) const {
                            return row[col];
                        }
                };
                
            public:
                int rows;
                int cols;
                std::vector<std::vector<double>> elements;
                Matrix(int rows, int cols) : rows(rows), cols(cols) {
                    elements.resize(rows);
                    for(int i = 0; i < rows; i++) {
                        elements[i].resize(cols);
                    }
                }
                Matrix(int rows, int cols, std::vector<std::vector<double>> elements) : rows(rows), cols(cols), elements(elements) {
                    if(elements.size() != static_cast<std::size_t>(rows) || 
                       elements[0].size() != static_cast<std::size_t>(cols)) {
                        throw std::invalid_argument("Invalid number of elements");
                    }
                }

                double getElement(int row, int col) const {
                    return elements[row][col];
                }
                void setElement(int row, int col, double value) {
                    elements[row][col] = value;
                }
                
                // Overload [] operator to enable matrix[row][col] syntax
                // Non-const version: allows both reading and writing
                RowProxy operator[](int row) {
                    return RowProxy(elements[row]);
                }
                
                // Const version: allows reading from const Matrix
                ConstRowProxy operator[](int row) const {
                    return ConstRowProxy(elements[row]);
                }
        };

        class Vector2d : public Matrix {
            public:
                Vector2d() : Matrix(2, 1, {{0}, {0}}) {}
                Vector2d(int x, int y) : Matrix(2, 1, {{static_cast<double>(x)}, {static_cast<double>(y)}}) {}
                Vector2d(double x, double y) : Matrix(2, 1, {{x}, {y}}) {}
                Vector2d(point p1, point p2) : Matrix(2, 1, {{static_cast<double>(p2.x - p1.x)}, {static_cast<double>(p2.y - p1.y)}}) {}
                double magnitude() const {
                    return std::sqrt(elements[0][0] * elements[0][0] + elements[1][0] * elements[1][0]);
                } 
                Vector2d normalize() const {
                    double magnitude = this->magnitude();
                    return Vector2d(elements[0][0] / magnitude, elements[1][0] / magnitude);
                }
            };

        inline Matrix matMul(const Matrix& A, const Matrix& B) {
            if(A.cols != B.rows) {
                throw std::invalid_argument("Invalid matrix dimensions");
            }
            Matrix result(A.rows, B.cols);
            for(int i = 0; i < A.rows; i++) {
                for(int j = 0; j < B.cols; j++) {
                    for(int k = 0; k < A.cols; k++) {
                        result.elements[i][j] += A.elements[i][k] * B.elements[k][j];
                    }
                }
            }
            return result;
        }
        inline Matrix matAdd(const Matrix& A, const Matrix& B) {
            if(A.rows != B.rows || A.cols != B.cols) {
                throw std::invalid_argument("Invalid matrix dimensions");
            }
            Matrix result(A.rows, A.cols);
            for(int i = 0; i < A.rows; i++) {
                for(int j = 0; j < A.cols; j++) {
                    result.elements[i][j] = A.elements[i][j] + B.elements[i][j];
                }
            }
            return result;
        }
        inline Matrix matSub(const Matrix& A, const Matrix& B) {
            if(A.rows != B.rows || A.cols != B.cols) {
                throw std::invalid_argument("Invalid matrix dimensions");
            }
            Matrix result(A.rows, A.cols);
            for(int i = 0; i < A.rows; i++) {
                for(int j = 0; j < A.cols; j++) {
                    result.elements[i][j] = A.elements[i][j] - B.elements[i][j];
                }
            }
            return result;
        }
        inline Matrix matScale(const Matrix& A, double scalar) {
            Matrix result(A.rows, A.cols);
            for(int i = 0; i < A.rows; i++) {
                for(int j = 0; j < A.cols; j++) {
                    result.elements[i][j] = A.elements[i][j] * scalar;
                }
            }
            return result;
        }
        inline Matrix matDiv(const Matrix& A, double scalar) {
            if(scalar == 0) {
                throw std::invalid_argument("Division by zero");
            }
            Matrix result(A.rows, A.cols);
            for(int i = 0; i < A.rows; i++) {
                for(int j = 0; j < A.cols; j++) {
                    result.elements[i][j] = A.elements[i][j] / scalar;
                }
            }
            return result;
        }
        inline Matrix matTranspose(const Matrix& A) {
            Matrix result(A.cols, A.rows);
            for(int i = 0; i < A.rows; i++) {
                for(int j = 0; j < A.cols; j++) {
                    result.elements[j][i] = A.elements[i][j];
                }
            }
            return result;
        }

        inline Vector2d matMul(const Matrix& A, const Vector2d& B) {
            if(A.cols != 2 || B.rows != 2 || A.rows != 2 || B.cols != 1) {
                throw std::invalid_argument("Invalid matrix dimensions");
            }
            double result_x = A.elements[0][0] * B.elements[0][0] + A.elements[0][1] * B.elements[1][0];
            double result_y = A.elements[1][0] * B.elements[0][0] + A.elements[1][1] * B.elements[1][0];
            return Vector2d(result_x, result_y);
        }


    } // namespace matrix
} // namespace utils