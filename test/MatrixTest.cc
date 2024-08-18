#include <gtest/gtest.h>
#include "Matrix.h"

class MatrixTest : public ::testing::Test {
protected:
    // Set up common test data
    void SetUp() override {
        matrix1 = Matrix(2, 2);
        matrix2 = Matrix(2, 2);
        matrix1(0, 0) = 1.0; matrix1(0, 1) = 2.0;
        matrix1(1, 0) = 3.0; matrix1(1, 1) = 4.0;
        matrix2(0, 0) = 5.0; matrix2(0, 1) = 6.0;
        matrix2(1, 0) = 7.0; matrix2(1, 1) = 8.0;
    }

    Matrix matrix1;
    Matrix matrix2;
};

// Test default constructor
TEST_F(MatrixTest, DefaultConstructor) {
    Matrix m;
    EXPECT_EQ(m.Rows(), 0);
    EXPECT_EQ(m.Columns(), 0);
}

// Test parameterized constructor
TEST_F(MatrixTest, ParameterizedConstructor) {
    Matrix m(2, 3);
    EXPECT_EQ(m.Rows(), 2);
    EXPECT_EQ(m.Columns(), 3);
}

// Test copy constructor
TEST_F(MatrixTest, CopyConstructor) {
    Matrix m1(2, 2);
    m1(0, 0) = 1.0; m1(0, 1) = 2.0;
    m1(1, 0) = 3.0; m1(1, 1) = 4.0;

    Matrix m2 = m1;
    EXPECT_EQ(m2(0, 0), 1.0);
    EXPECT_EQ(m2(0, 1), 2.0);
    EXPECT_EQ(m2(1, 0), 3.0);
    EXPECT_EQ(m2(1, 1), 4.0);
}

// Test addition
TEST_F(MatrixTest, Addition) {
    Matrix result = matrix1 + matrix2;
    EXPECT_EQ(result(0, 0), 6.0);
    EXPECT_EQ(result(0, 1), 8.0);
    EXPECT_EQ(result(1, 0), 10.0);
    EXPECT_EQ(result(1, 1), 12.0);
}

// Test subtraction
TEST_F(MatrixTest, Subtraction) {
    Matrix result = matrix1 - matrix2;
    EXPECT_EQ(result(0, 0), -4.0);
    EXPECT_EQ(result(0, 1), -4.0);
    EXPECT_EQ(result(1, 0), -4.0);
    EXPECT_EQ(result(1, 1), -4.0);
}

// Test scalar multiplication
TEST_F(MatrixTest, ScalarMultiplication) {
    Matrix result = matrix1 * 2.0;
    EXPECT_EQ(result(0, 0), 2.0);
    EXPECT_EQ(result(0, 1), 4.0);
    EXPECT_EQ(result(1, 0), 6.0);
    EXPECT_EQ(result(1, 1), 8.0);
}

// Test transpose
TEST_F(MatrixTest, Transpose) {
    Matrix result = matrix1.Transpose();
    EXPECT_EQ(result(0, 0), 1.0);
    EXPECT_EQ(result(0, 1), 3.0);
    EXPECT_EQ(result(1, 0), 2.0);
    EXPECT_EQ(result(1, 1), 4.0);
}

// Test determinant
TEST_F(MatrixTest, Determinant) {
    EXPECT_EQ(matrix1.Determinant(), -2.0);
}

// Test equality
TEST_F(MatrixTest, Equality) {
    Matrix m(2, 2);
    m(0, 0) = 1.0; m(0, 1) = 2.0;
    m(1, 0) = 3.0; m(1, 1) = 4.0;

    EXPECT_TRUE(matrix1 == m);
    EXPECT_FALSE(matrix1 == matrix2);
}

// Test isSquare
TEST_F(MatrixTest, IsSquare) {
    EXPECT_TRUE(matrix1.isSquare());
    Matrix m(2, 3);
    EXPECT_FALSE(m.isSquare());
}

// Test Sum
TEST_F(MatrixTest, Sum) {
    EXPECT_DOUBLE_EQ(matrix1.Sum(), 10.0);
}

// Test Identity
TEST_F(MatrixTest, Identity) {
    Matrix identity = Matrix::Identity(3);
    EXPECT_EQ(identity.Rows(), 3);
    EXPECT_EQ(identity.Columns(), 3);
    EXPECT_EQ(identity(0, 0), 1.0);
    EXPECT_EQ(identity(1, 1), 1.0);
    EXPECT_EQ(identity(2, 2), 1.0);
}
