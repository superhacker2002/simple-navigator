#ifndef MATRIX_H_
#define MATRIX_H_

#include <math.h>
#include <stdlib.h>

#include <cstring>
#include <iostream>
#include <vector>

#define EPS 1e-7

namespace s21 {
template <typename T>
class Matrix {
 private:
  int rows_, columns_;
  T** matrix_;
  std::vector<int> rows_seq_;
  std::vector<int> cols_seq_;

 public:
  //  Methods for filling matrix

  static double GenerateRandomNumber(double min, double max) {
    double random = (double)rand() / RAND_MAX;
    return min + random * (max - min);
  }

  static int GenerateRandomNumber(int min, int max) {
    int random = rand() / RAND_MAX;
    return min + random * (max - min);
  }

  void OutputMatrix() {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < columns_; ++j) {
        printf("%10.6f ", matrix_[i][j]);
      }
      printf("\n");
    }
  }

  //  Constructors and destructor

  Matrix() : Matrix(3, 3) { ; }

  Matrix(int rows, int columns) : rows_(rows), columns_(columns) {
    initRowsColumns_();
    if (rows <= 0 || columns <= 0)
      throw std::out_of_range("constructor Out of range");
    this->matrix_ = new T*[rows];
    for (int i = 0; i < rows; i++) {
      this->matrix_[i] = new T[columns]();
    }
  }

  Matrix(int size) : Matrix(size, size) {}

  Matrix(const Matrix& other) : Matrix(other.rows_, other.columns_) {
    this->SetEqualValues_(other);
    this->rows_seq_ = other.rows_seq_;
    this->cols_seq_ = other.cols_seq_;
  }

  Matrix(Matrix&& other)
      : rows_(other.rows_),
        columns_(other.columns_),
        matrix_(other.matrix_),
        rows_seq_(other.rows_seq_),
        cols_seq_(other.cols_seq_) {
    other.matrix_ = nullptr;
  }

  ~Matrix() { this->RemoveMatrix_(); }

  void FillMatrix(T value) {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < columns_; j++) {
        matrix_[i][j] = value;
      }
    }
  }

  //  Operators overloads

  void operator=(const Matrix& other) {
    if (IsNull_(*this))
      this->CopyConstructor_(other);
    else
      this->SetEqualValues_(other);
  }

  void operator=(Matrix&& other) {
    this->RemoveMatrix_();
    rows_ = other.rows_;
    columns_ = other.columns_;
    matrix_ = other.matrix_;
    other.matrix_ = nullptr;
  }

  void operator-=(const Matrix& other) { this->SubMatrix(other); }

  void operator+=(const Matrix& other) { this->SumMatrix(other); }

  Matrix operator-(const Matrix& other) {
    Matrix result(*this);
    result.SubMatrix(other);
    return result;
  }

  Matrix operator+(const Matrix& other) {
    Matrix result(*this);
    result.SumMatrix(other);
    return result;
  }

  void operator*=(const Matrix& other) { this->MulMatrix(other); }

  void operator*=(double num) { this->MulNumber(num); }

  Matrix operator*(const Matrix& other) {
    Matrix result(*this);
    result.MulMatrix(other);
    return result;
  }

  Matrix operator*(double num) {
    Matrix result(*this);
    result.MulNumber(num);
    return result;
  }

  bool operator==(const Matrix& other) { return this->EqMatrix(other); }

  bool operator!=(const Matrix& other) { return !(this->EqMatrix(other)); }

  T& operator()(const int& i, const int& j) {
    if (i >= this->rows_ || j >= this->columns_ || i < 0 || j < 0) {
      throw std::out_of_range("Operator() : Out of range");
    }
    return this->matrix_[i][j];
  }

  T operator()(const int& i, const int& j) const {
    if (i >= this->rows_ || j >= this->columns_ || i < 0 || j < 0) {
      throw std::out_of_range("Operator() : Out of range");
    }
    return this->matrix_[i][j];
  }

  // Main methods

  bool isEmpty() { return columns_ == 0 && rows_ == 0; }

  const T at(const int& i, const int& j) const {
    if (i >= this->rows_ || j >= this->columns_ || i < 0 || j < 0)
      throw std::out_of_range("at Out of range");
    return this->matrix_[i][j];
  }

  void SetRows(int new_rows) {
    if (new_rows <= 0) throw std::out_of_range("set rows Out of range");
    if (new_rows != this->rows_) {
      int rows_iter = (this->rows_ < new_rows) ? this->rows_ : new_rows;
      Matrix tmp(new_rows, this->columns_);
      for (int i = 0; i < rows_iter; i++)
        for (int j = 0; j < this->columns_; j++)
          tmp.matrix_[i][j] = this->matrix_[i][j];
      this->RemoveMatrix_();
      this->matrix_ = tmp.matrix_;
      this->rows_ = new_rows;
      tmp.matrix_ = nullptr;
    }
  }

  void SetColumns(int new_cols) {
    if (new_cols <= 0) throw std::out_of_range("set columns Out of range");
    if (new_cols != this->columns_) {
      int cols_iter = (this->columns_ < new_cols) ? this->columns_ : new_cols;
      Matrix tmp(this->rows_, new_cols);
      for (int i = 0; i < this->rows_; i++)
        for (int j = 0; j < cols_iter; j++)
          tmp.matrix_[i][j] = this->matrix_[i][j];
      this->RemoveMatrix_();
      this->matrix_ = tmp.matrix_;
      this->columns_ = new_cols;
      tmp.matrix_ = nullptr;
    }
  }

  void SetSize(int new_rows, int new_cols) {
    this->SetRows(new_rows), this->SetColumns(new_cols);
  }

  int GetRows() const {
    if (IsNull_(*this)) throw std::out_of_range("Matrix is null.");
    return this->rows_;
  }

  int GetCols() const {
    if (IsNull_(*this)) throw std::out_of_range("Matrix is null.");
    return this->columns_;
  }

  int actualRow(int row) const { return rows_seq_[row]; }

  int actualCol(int col) const { return cols_seq_[col]; }

  void RemoveRowColumn(const int delete_row, const int delete_col) {
    if (delete_row < 0 || delete_col < 0) {
      throw std::out_of_range("rm Out of range");
    }
    rows_seq_.erase(rows_seq_.begin() + delete_row);
    cols_seq_.erase(cols_seq_.begin() + delete_col);
    Matrix tmp(this->rows_ - 1, this->columns_ - 1);
    for (int row = 0, row_small = 0; row < rows_; row++) {
      if (row != delete_row) {
        for (int col = 0, col_small = 0; col < columns_; col++) {
          if (col != delete_col) {
            tmp.matrix_[row_small][col_small++] = matrix_[row][col];
          }
        }
        row_small++;
      }
    }
    this->RemoveMatrix_();
    this->matrix_ = tmp.matrix_;
    this->columns_ -= 1;
    this->rows_ -= 1;
    tmp.matrix_ = nullptr;
  }

  bool EqMatrix(const Matrix& other) {
    bool eq_result = true;
    if (!IsNull_(*this, other) && IsRowsAndColsEq_(*this, other)) {
      for (int i = 0; i < this->rows_ && eq_result; i++)
        for (int j = 0; j < this->columns_ && eq_result; j++)
          if (this->matrix_[i][j] != other.matrix_[i][j]) eq_result = false;
    } else {
      eq_result = false;
    }
    return eq_result;
  }

  static std::vector<double> MatrixToVector(const Matrix& matrix) {
    std::vector<double> vector(matrix.columns_ * matrix.rows_);
    auto it = vector.begin();
    for (int i = 0; i < matrix.rows_; ++i) {
      for (int j = 0; j < matrix.columns_; ++j) {
        *it = matrix.matrix_[i][j];
        ++it;
      }
    }
    return vector;
  }

  static Matrix VectorToMatrix(const std::vector<T>& other) {
    Matrix matrix(sqrt(other.size()), sqrt(other.size()));
    auto it = other.begin();
    for (int i = 0; i < matrix.rows_; ++i)
      for (int j = 0; j < matrix.columns_; ++j) matrix.matrix_[i][j] = *(it++);
    return matrix;
  }
  void Transpose() {
    Matrix<T> res_matrix(this->columns_, this->rows_);
    if (!IsNull_(*this, res_matrix)) {
      for (int i = 0; i < this->rows_; i++)
        for (int j = 0; j < this->columns_; j++)
          res_matrix.matrix_[j][i] = this->matrix_[i][j];
    }
    *this = res_matrix;
  }

  // Internal methods
 private:
  void initRowsColumns_() {
    for (int i = 0; i < rows_; i++) {
      rows_seq_.push_back(i);
      cols_seq_.push_back(i);
    }
  }

  bool IsSquared_() { return this->rows_ == this->columns_ ? true : false; }

  void SetEqualValues_(const Matrix& other) {
    this->SetSize(other.rows_, other.columns_);
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->columns_; j++) {
        this->matrix_[i][j] = other.matrix_[i][j];
      }
    }
    rows_seq_ = other.rows_seq_;
    cols_seq_ = other.cols_seq_;
  }

  bool IsRowsAndColsEq_(const Matrix& matrix1, const Matrix& matrix2) {
    return ((matrix1.columns_ == matrix2.columns_) &&
            (matrix1.rows_ == matrix2.rows_))
               ? true
               : false;
  }

  bool IsNull_(const Matrix& matrix1, const Matrix& matrix2) {
    return matrix1.matrix_ != nullptr && matrix2.matrix_ != nullptr ? false
                                                                    : true;
  }

  bool IsNull_(const Matrix& matrix) const {
    return matrix.matrix_ != nullptr ? false : true;
  }

  void CopyConstructor_(const Matrix& other) {
    Matrix tmp(other);
    this->rows_ = tmp.rows_;
    this->columns_ = tmp.columns_;
    this->matrix_ = tmp.matrix_;
    tmp.matrix_ = nullptr;
  }

  void RemoveMatrix_() {
    if (!IsNull_(*this)) {
      for (int i = 0; i < this->rows_; i++) delete[] (this->matrix_[i]);
      delete[] (this->matrix_);
    }
  }
};  // class Matrix
}  // namespace s21

#endif  // MATRIX_H_
