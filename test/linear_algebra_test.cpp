//
// Created by Brian Jackson on 12/19/22.
// Copyright (c) 2022 Robotic Exploration Lab. All rights reserved.
//

#include <limits>
#include <cmath>

#include "gtest/gtest.h"
#include "slap/slap.h"
#include "slap/cholesky.h"

constexpr sfloat EPS = std::numeric_limits<sfloat>::epsilon();

class LinearAlgebraTest : public ::testing::Test {
 public:
  static constexpr int chol_dim = 10;
  static constexpr int chol_rhs = 2;
  // clang-format off
  sfloat dataA[12] = {9.0, 7.0, 7.0, 9.0, -8.0, -9.0, 1.0, 5.0, 6.0, -1.0, -10.0, -4.0};
  sfloat dataB[20] = {6.0,  5.0, 5.0, 2.0,   -4.0, 3.0,  -6.0, -3.0, 7.0, -2.0,
                      -9.0, 1.0, 3.0, -10.0, -6.0, -3.0, -4.0, 6.0,  2.0, 2.0};
  sfloat dataC[15] = {-6.0, 6.0, 4.0, -5.0, 9.0, 10.0, -4.0, 1.0,
                      0.0,  2.0, 9.0, -7.0, 3.0, 8.0,  9.0};
  sfloat data_chol_ans[chol_dim * chol_dim] = {1.010016501515363, 0.11564167498725109, 0.2773552045070942, 0.5050742562799346, 0.7987988303057719, 1.1585289265846068, 1.5842645451164388, 2.0760056859012677, 2.6337523489390935, 3.257504534229917, 0.1168, 1.48045950175595, 2.2479909169891794, 4.4063294938318505, 7.280009271334733, 10.86903024949783, 15.17339242832114, 20.193095807804664, 25.928140387948396, 32.378526168752344, 0.28013333333333335, 3.3601333333333336, 2.3425460590515796, 3.8453856558433643, 6.43737791674771, 9.691636891695028, 13.608162580685326, 18.186954983718593, 23.42801410079483, 29.331339931914037, 0.5101333333333334, 6.5818, 19.053466666666665, 2.1135995076168648, 2.820320019676385, 4.316197773106017, 6.128106238307182, 8.25604541527989, 10.70001530402416, 13.460015904539958, 0.8068, 10.870133333333333, 31.666799999999995, 63.1968, 1.8518853406453901, 2.0751496247381764, 3.010309367062323, 4.1173743327734185, 5.3963445218714625, 6.8472199343565165, 1.1701333333333335, 16.225133333333336, 47.45791111111111, 94.86846666666668, 158.4568, 1.697429954607423, 1.6666319872699775, 2.335135152730006, 3.1138135213518137, 4.002667093135065, 1.6001333333333334, 22.6468, 66.4268, 132.94013333333334, 222.1868, 334.1668, 1.6009378013616629, 1.417135393373918, 1.935795036782928, 2.532282845657028, 2.0968, 30.135133333333336, 88.57346666666668, 177.4118, 296.6501333333333, 446.2884666666666, 626.3268, 1.5338505932587638, 1.2446318104290612, 1.6653092511134584, 2.660133333333333, 38.69013333333333, 113.8979111111111, 228.28346666666664, 381.8468, 574.5879111111111, 806.5068000000001, 1077.6034666666667, 1.4825126888375568, 1.1130327897522478, 3.290133333333333, 48.3118, 142.40013333333332, 285.5551333333333, 477.7768, 719.0651333333333, 1009.4201333333334, 1348.8418, 1737.330133333333, 1.440483369924483};
  sfloat data_A1[chol_dim * chol_dim];
  sfloat data_Achol[chol_dim * chol_dim];
  sfloat data_b[chol_dim * chol_rhs];
  sfloat data_x[chol_dim * chol_rhs] = {-5.1347486446158195, -4.0995094536024554, -3.15706820123972, -2.3074248875278474, -1.5505795124668624, -0.8865320760563593, -0.31528257829726086, 0.1631689808118735, 0.5488226012692519, 0.8416782830759241, -4.241377291676201, -3.439765220478922, -2.6983998081034772, -2.017281054549975, -1.39640895981845, -0.8357835239085212, -0.3354047468210348, 0.10472737144529853, 0.48461283088890095, 0.8042516315106547};
  // clang-format on
  Matrix A;
  Matrix B;
  Matrix C;

  Matrix A1;
  Matrix Achol;
  Matrix b;
  Matrix x_ans;

 protected:
  void SetUp() {
    A = slap_MatrixFromArray(3, 4, dataA);
    B = slap_MatrixFromArray(4, 5, dataB);
    C = slap_MatrixFromArray(3, 5, dataC);

    int n = chol_dim;
    int m = chol_rhs;
    A1 = slap_MatrixFromArray(n, n, data_A1);
    Achol = slap_MatrixFromArray(n, n, data_A1);
    b = slap_MatrixFromArray(n, m, data_b);
    x_ans = slap_MatrixFromArray(n, m, data_x);
    for (int i = 0; i < n * n; ++i) {
      A1.data[i] = (i - 4) * (i + 3) / 6.0;  // NOLINT
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        slap_SetElement(b, i, j, -i - (n + m) * 0.5 + j);
      }
    }
    // C = A*B
    // B = A'C
  }
};

TEST_F(LinearAlgebraTest, MatMul_AB) {
  enum slap_ErrorCode err;
  sfloat dataC_ans[15] = {102.0, 7.0,   19.0,  -12.0, -52.0, -79.0, 35.0, 10.0,
                          9.0,   -66.0, 101.0, 87.0,  18.0,  -86.0, -78.0};
  Matrix C_ans = slap_MatrixFromArray(3, 5, dataC_ans);
  err = slap_MatMulAdd(C, A, B, 1.0, 0.0);
  EXPECT_EQ(err, SLAP_NO_ERROR);
  EXPECT_LT(slap_MatrixNormedDifference(C, C_ans), std::sqrt(EPS));

  slap_SetConst(C, 0);
  slap_MatMulAB(C, A, B);
  EXPECT_LT(slap_MatrixNormedDifference(C, C_ans), std::sqrt(EPS));
}

TEST_F(LinearAlgebraTest, MatMul_AtB) {
  enum slap_ErrorCode err;
  sfloat dataB_ans[20] = {16.0,   -138.0, 48.0,  -70.0,  88.0, -207.0, 100.0,
                          -125.0, -29.0,  -44.0, 1.0,    -6.0, 32.0,   9.0,
                          5.0,    -64.0,  146.0, -118.0, 97.0, -119.0};
  Matrix B_ans = slap_MatrixFromArray(4, 5, dataB_ans);
  err = slap_MatMulAdd(B, slap_Transpose(A), C, 1.0, 0);
  EXPECT_EQ(err, SLAP_NO_ERROR);
  EXPECT_LT(slap_MatrixNormedDifference(B, B_ans), std::sqrt(EPS));

  slap_SetConst(B, 0);
  slap_MatMulAtB(B, A, C);
  EXPECT_LT(slap_MatrixNormedDifference(B, B_ans), std::sqrt(EPS));
}

TEST_F(LinearAlgebraTest, CholeskyFactorization) {
  enum slap_ErrorCode err;
  int n = chol_dim;
  A = slap_NewMatrixZeros(n, n);

  // Create a positive-definite matrix
  slap_MatMulAdd(A, slap_Transpose(A1), A1, 1e-4, 0.0);
  slap_AddIdentity(A, 1.0);
  slap_MatrixCopy(Achol, A);

  // Cholesky factorization
  err = slap_Cholesky(Achol);

  // Check the answer
  Matrix L_ans = slap_MatrixFromArray(n, n, data_chol_ans);
  sfloat error = slap_MatrixNormedDifference(Achol, L_ans);
  EXPECT_LT(error, std::sqrt(EPS));
  EXPECT_EQ(err, SLAP_NO_ERROR);

  // Try to factorize an indefinite matrix
  slap_MatMulAdd(A, slap_Transpose(A1), A1, 1.0, 0.0);
  slap_AddIdentity(A, -1.0);
  slap_MatrixCopy(Achol, A);
  err = slap_Cholesky(Achol);
  EXPECT_EQ(err, SLAP_CHOLESKY_FAIL);

  slap_FreeMatrix(&A);
}

TEST_F(LinearAlgebraTest, TriBackSub) {
  enum slap_ErrorCode err;
  constexpr int n = 3;
  sfloat Ldata[n * n] = {1, 2, 5, 0, 1, 6, 0, 0, 7};
  sfloat bdata[n] = {-2, 3, 10};
  sfloat ydata[n] = {-2.0, 7.0, -3.142857142857143};
  sfloat xdata[n] = {-19.142857142857142, 9.693877551020408, -0.4489795918367347};

  Matrix L = slap_TriLower(slap_MatrixFromArray(n, n, Ldata));
  Matrix b = slap_MatrixFromArray(n, 1, bdata);
  Matrix y = slap_MatrixFromArray(n, 1, ydata);
  Matrix x = slap_MatrixFromArray(n, 1, xdata);

  err = slap_TriSolve(L, b);
  EXPECT_EQ(err, SLAP_NO_ERROR);
  EXPECT_LT(slap_MatrixNormedDifference(b, y), std::sqrt(EPS));

  err = slap_TriSolve(slap_Transpose(L), y);
  EXPECT_EQ(err, SLAP_NO_ERROR);
  EXPECT_LT(slap_MatrixNormedDifference(x, y), std::sqrt(EPS));
  (void)x;
}


TEST_F(LinearAlgebraTest, CholeskySolve) {
  // Factorize a PSD matrix
  enum slap_ErrorCode err;
  int n = chol_dim;
  A = slap_NewMatrixZeros(n, n);
  slap_MatMulAdd(A, slap_Transpose(A1), A1, 1e-4, 0.0);
  slap_AddIdentity(A, 1.0);
  slap_MatrixCopy(Achol, A);
  err = slap_Cholesky(Achol);
  EXPECT_EQ(err, SLAP_NO_ERROR);

  // Solve the system using the factorization
  Matrix x = slap_NewMatrixZeros(chol_dim, chol_rhs);
  slap_MatrixCopy(x, b);
  slap_CholeskySolve(Achol, x);
  slap_PrintMatrix(x);
  EXPECT_LT(slap_MatrixNormedDifference(x, x_ans), std::sqrt(EPS));

  // Check the residual
  Matrix b2 = slap_NewMatrixZeros(chol_dim, chol_rhs);
  slap_MatMulAB(b2, A, x);
  EXPECT_LT(slap_MatrixNormedDifference(b2, b), 100 * std::sqrt(EPS));

  slap_FreeMatrix(&A);
  slap_FreeMatrix(&x);
  slap_FreeMatrix(&b2);
}

TEST_F(LinearAlgebraTest, CholeskySolve_Bad) {
  // Factorize a PSD matrix
  enum slap_ErrorCode err;
  int n = chol_dim;
  A = slap_NewMatrixZeros(n, n);
  slap_MatMulAdd(A, slap_Transpose(A1), A1, 1e-4, 0.0);
  slap_AddIdentity(A, -10.0);
  slap_MatrixCopy(Achol, A);
  err = slap_Cholesky(Achol);
  EXPECT_EQ(err, SLAP_CHOLESKY_FAIL);

  // Solve the system using the factorization
  Matrix x = slap_NewMatrixZeros(chol_dim + 1, chol_rhs);
  err = slap_CholeskySolve(Achol, x);
  EXPECT_EQ(err, SLAP_INCOMPATIBLE_MATRIX_DIMENSIONS);

  slap_FreeMatrix(&A);
  slap_FreeMatrix(&x);
}

class QRDecompTest : public ::testing::Test {
 public:
  static constexpr int m1 = 5;
  static constexpr int n1 = 5;

  static constexpr int m2 = 5;
  static constexpr int n2 = 3;

  // clang-format off
  sfloat dataA1[m1 * n1] = {
      1.0, 0.5, 0.3333333333333333, 0.25, 0.2,
      0.5, 0.3333333333333333, 0.25, 0.2, 0.16666666666666666,
      0.3333333333333333, 0.25, 0.2, 0.16666666666666666, 0.14285714285714285,
      0.25, 0.2, 0.16666666666666666, 0.14285714285714285, 0.125,
      0.2, 0.16666666666666666, 0.14285714285714285, 0.125, 0.1111111111111111
  };
  sfloat dataA2[m2 * n1] = {
      -0.6074563212311672, 0.6925987046273734, -0.04830701721338945,
      0.11756669437635717, 0.51871450539862, 0.599358857883042,
      0.8758814599020377, 0.4518331708655029, -0.508535666126173,
      1.6553198217895213, -0.22706518216748067, -0.15012100723414903,
      -0.4349328686059969, -0.36455753152400444, 0.16025126740928738
  };
  sfloat datab[m2] = {
      -1.5642880600352318, 0.7840050512892108, -0.9899090197378724, -1.078415320831164, 1.169221916323157
  };
  sfloat datax[m2] = {
      1.5015975917105808, 0.06697808740320454, 2.622899732853888,
  };
  // clang-format on

  sfloat dataR1[m1 * n1];
  sfloat dataR2[m2 * n2];
  sfloat data_beta1[m1];
  sfloat data_beta2[m2];

  sfloat data_temp1[m1];
  sfloat data_temp2[m2];
  Matrix A1;
  Matrix A2;
  Matrix b;
  Matrix x_ans;

  Matrix R1;
  Matrix R2;

  Matrix beta1;
  Matrix beta2;

  Matrix temp1;
  Matrix temp2;

 protected:
  void SetUp() override {
    A1 = slap_MatrixFromArray(m1, n1, dataA1);
    A2 = slap_MatrixFromArray(m2, n2, dataA2);
    b = slap_MatrixFromArray(m2, 1, datab);
    x_ans = slap_MatrixFromArray(n2, 1, datax);

    R1 = slap_MatrixFromArray(m1, n1, dataR1);
    R2 = slap_MatrixFromArray(m2, n2, dataR2);

    beta1 = slap_MatrixFromArray(m1, 1, data_beta1);
    beta2 = slap_MatrixFromArray(m2, 1, data_beta2);

    temp1 = slap_MatrixFromArray(m1, 1, data_temp1);
    temp2 = slap_MatrixFromArray(m2, 1, data_temp2);
  }
};

TEST_F(QRDecompTest, QRDecomp_Square) {
  slap_MatrixCopy(R1, A1);
  slap_QR(R1, beta1, temp1);
  Matrix Q = slap_NewMatrix(m1, m1);
  Matrix Q_work = slap_NewMatrix(m1, m1);
  Matrix I_m = slap_NewMatrix(m1, m1);
  Matrix QR = slap_NewMatrix(m1, n1);
  slap_SetIdentity(I_m, 1.0);

  slap_ComputeQ(Q, R1, beta1, Q_work);

  // Check Q orthogonality (Q'Q = I)
  slap_MatMulAtB(Q_work, Q, Q);
  sfloat diff = slap_MatrixNormedDifference(Q_work, I_m);
  EXPECT_LT(diff, std::sqrt(EPS));

  // Check decomposition (Q * R = A)
  for (int j = 0; j < n1; j++) {
    for (int i = j + 1; i < m1; ++i) {
      slap_SetElement(R1, i, j, 0);
    }
  }
  slap_MatMulAB(QR, Q, R1);
  diff = slap_MatrixNormedDifference(QR, A1);
  EXPECT_LT(diff, std::sqrt(EPS));

  // Clean up temporaries
  slap_FreeMatrix(&Q);
  slap_FreeMatrix(&Q_work);
  slap_FreeMatrix(&I_m);
  slap_FreeMatrix(&QR);
}

TEST_F(QRDecompTest, QRDecomp_Skinny) {
  slap_MatrixCopy(R2, A2);
  slap_QR(R2, beta2, temp2);
  Matrix Q = slap_NewMatrix(m2, m2);
  Matrix Q_work = slap_NewMatrix(m2, m2);
  Matrix I_m = slap_NewMatrix(m2, m2);
  Matrix QR = slap_NewMatrix(m2, n2);
  slap_SetIdentity(I_m, 1.0);

  slap_ComputeQ(Q, R2, beta2, Q_work);

  // Check Q orthogonality (Q'Q = I)
  slap_MatMulAtB(Q_work, Q, Q);
  sfloat diff = slap_MatrixNormedDifference(Q_work, I_m);
  EXPECT_LT(diff, std::sqrt(EPS));

  // Check decomposition (Q * R = A)
  for (int j = 0; j < n2; j++) {
    for (int i = j + 1; i < m2; ++i) {
      slap_SetElement(R2, i, j, 0);
    }
  }
  slap_MatMulAB(QR, Q, R2);
  diff = slap_MatrixNormedDifference(QR, A2);
  EXPECT_LT(diff, std::sqrt(EPS));

  // Clean up temporaries
  slap_FreeMatrix(&Q);
  slap_FreeMatrix(&Q_work);
  slap_FreeMatrix(&I_m);
  slap_FreeMatrix(&QR);
}

TEST_F(QRDecompTest, QRDecomp_LeastSquares) {
  // Compute QR decomp
  slap_MatrixCopy(R2, A2);
  R2 = slap_TriUpper(R2);
  slap_QR(R2, beta2, temp2);

  // Get Q'b
  Matrix Qtb = slap_NewMatrix(m2, 1);
  slap_MatrixCopy(Qtb, b);
  slap_Qtb(R2, beta2, Qtb);

  // Triangular solve
  Matrix R_ = slap_CreateSubMatrix(R2, 0, 0, n2, n2);
  Matrix x = slap_CreateSubMatrix(Qtb, 0, 0, n2, 1);
  slap_TriSolve(R_, x);
  sfloat err = slap_MatrixNormedDifference(x, x_ans);
  EXPECT_LT(err, std::sqrt(EPS));

  slap_FreeMatrix(&Qtb);
}

TEST_F(QRDecompTest, QRDecomp_LeastSquaresFunction) {
  slap_LeastSquares(A2, b, beta2, temp2);
  Matrix x = slap_CreateSubMatrix(b, 0, 0, n2, 1);
  sfloat err = slap_MatrixNormedDifference(x, x_ans);
  EXPECT_LT(err, std::sqrt(EPS));
}
