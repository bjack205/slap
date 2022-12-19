//
// Created by Brian Jackson on 12/19/22.
// Copyright (c) 2022 Robotic Exploration Lab. All rights reserved.
//

#include "gtest/gtest.h"
#include "slap/slap.h"

class LinearAlgebraTest : public ::testing::Test {
 public:
  static constexpr int chol_dim = 10;
  static constexpr int chol_rhs = 2;
  // clang-format off
  double dataA[12] = {9.0, 7.0, 7.0, 9.0, -8.0, -9.0, 1.0, 5.0, 6.0, -1.0, -10.0, -4.0};
  double dataB[20] = {6.0,  5.0, 5.0, 2.0,   -4.0, 3.0,  -6.0, -3.0, 7.0, -2.0,
                      -9.0, 1.0, 3.0, -10.0, -6.0, -3.0, -4.0, 6.0,  2.0, 2.0};
  double dataC[15] = {-6.0, 6.0, 4.0, -5.0, 9.0, 10.0, -4.0, 1.0,
                      0.0,  2.0, 9.0, -7.0, 3.0, 8.0,  9.0};
  double data_chol_ans[chol_dim * chol_dim] = {1.010016501515363, 0.11564167498725109, 0.2773552045070942, 0.5050742562799346, 0.7987988303057719, 1.1585289265846068, 1.5842645451164388, 2.0760056859012677, 2.6337523489390935, 3.257504534229917, 0.1168, 1.48045950175595, 2.2479909169891794, 4.4063294938318505, 7.280009271334733, 10.86903024949783, 15.17339242832114, 20.193095807804664, 25.928140387948396, 32.378526168752344, 0.28013333333333335, 3.3601333333333336, 2.3425460590515796, 3.8453856558433643, 6.43737791674771, 9.691636891695028, 13.608162580685326, 18.186954983718593, 23.42801410079483, 29.331339931914037, 0.5101333333333334, 6.5818, 19.053466666666665, 2.1135995076168648, 2.820320019676385, 4.316197773106017, 6.128106238307182, 8.25604541527989, 10.70001530402416, 13.460015904539958, 0.8068, 10.870133333333333, 31.666799999999995, 63.1968, 1.8518853406453901, 2.0751496247381764, 3.010309367062323, 4.1173743327734185, 5.3963445218714625, 6.8472199343565165, 1.1701333333333335, 16.225133333333336, 47.45791111111111, 94.86846666666668, 158.4568, 1.697429954607423, 1.6666319872699775, 2.335135152730006, 3.1138135213518137, 4.002667093135065, 1.6001333333333334, 22.6468, 66.4268, 132.94013333333334, 222.1868, 334.1668, 1.6009378013616629, 1.417135393373918, 1.935795036782928, 2.532282845657028, 2.0968, 30.135133333333336, 88.57346666666668, 177.4118, 296.6501333333333, 446.2884666666666, 626.3268, 1.5338505932587638, 1.2446318104290612, 1.6653092511134584, 2.660133333333333, 38.69013333333333, 113.8979111111111, 228.28346666666664, 381.8468, 574.5879111111111, 806.5068000000001, 1077.6034666666667, 1.4825126888375568, 1.1130327897522478, 3.290133333333333, 48.3118, 142.40013333333332, 285.5551333333333, 477.7768, 719.0651333333333, 1009.4201333333334, 1348.8418, 1737.330133333333, 1.440483369924483};
  double data_A1[chol_dim * chol_dim];
  double data_Achol[chol_dim * chol_dim];
  double data_b[chol_dim * chol_rhs];
  double data_x[chol_dim * chol_rhs] = {-5.1347486446158195, -4.0995094536024554, -3.15706820123972, -2.3074248875278474, -1.5505795124668624, -0.8865320760563593, -0.31528257829726086, 0.1631689808118735, 0.5488226012692519, 0.8416782830759241, -4.241377291676201, -3.439765220478922, -2.6983998081034772, -2.017281054549975, -1.39640895981845, -0.8357835239085212, -0.3354047468210348, 0.10472737144529853, 0.48461283088890095, 0.8042516315106547};
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
  double dataC_ans[15] = {102.0, 7.0,   19.0,  -12.0, -52.0, -79.0, 35.0, 10.0,
                          9.0,   -66.0, 101.0, 87.0,  18.0,  -86.0, -78.0};
  Matrix C_ans = slap_MatrixFromArray(3, 5, dataC_ans);
  err = slap_MatMulAdd(C, A, B, 1.0, 0.0);
  EXPECT_EQ(err, SLAP_NO_ERROR);
  EXPECT_LT(slap_MatrixNormedDifference(C, C_ans), 1e-10);

  slap_SetConst(C, 0);
  slap_MatMulAB(C, A, B);
  EXPECT_LT(slap_MatrixNormedDifference(C, C_ans), 1e-10);
}

TEST_F(LinearAlgebraTest, MatMul_AtB) {
  enum slap_ErrorCode err;
  double dataB_ans[20] = {16.0,   -138.0, 48.0,  -70.0,  88.0, -207.0, 100.0,
                          -125.0, -29.0,  -44.0, 1.0,    -6.0, 32.0,   9.0,
                          5.0,    -64.0,  146.0, -118.0, 97.0, -119.0};
  Matrix B_ans = slap_MatrixFromArray(4, 5, dataB_ans);
  err = slap_MatMulAdd(B, slap_Transpose(A), C, 1.0, 0);
  EXPECT_EQ(err, SLAP_NO_ERROR);
  EXPECT_LT(slap_MatrixNormedDifference(B, B_ans), 1e-10);

  slap_SetConst(B, 0);
  slap_MatMulAtB(B, A, C);
  EXPECT_LT(slap_MatrixNormedDifference(B, B_ans), 1e-10);
}

TEST_F(LinearAlgebraTest, CholeskyFactorization) {
  enum slap_ErrorCode err;
  int n = chol_dim;
  A = slap_NewMatrix(n, n);

  // Create a positive-definite matrix
  slap_MatMulAdd(A, slap_Transpose(A1), A1, 1e-4, 0.0);
  slap_AddIdentity(A, 1.0);
  slap_MatrixCopy(Achol, A);

  // Cholesky factorization
  err = slap_Cholesky(Achol);

  // Check the answer
  Matrix L_ans = slap_MatrixFromArray(n, n, data_chol_ans);
  double error = slap_MatrixNormedDifference(Achol, L_ans);
  EXPECT_LT(error, 1e-10);
  EXPECT_EQ(err, SLAP_NO_ERROR);

  // Try to factorize an indefinite matrix
  slap_MatMulAdd(A, slap_Transpose(A1), A1, 1.0, 0.0);
  slap_AddIdentity(A, -1.0);
  slap_MatrixCopy(Achol, A);
  err = slap_Cholesky(Achol);
  EXPECT_EQ(err, SLAP_CHOLESKY_FAIL);

  slap_FreeMatrix(A);
}

TEST_F(LinearAlgebraTest, TriBackSub) {
  enum slap_ErrorCode err;
  constexpr int n = 3;
  double Ldata[n * n] = {1, 2, 5, 0, 1, 6, 0, 0, 7};
  double bdata[n] = {-2, 3, 10};
  double ydata[n] = {-2.0, 7.0, -3.142857142857143};
  double xdata[n] = {-19.142857142857142, 9.693877551020408, -0.4489795918367347};

  Matrix L = slap_MatrixFromArray(n, n, Ldata);
  Matrix b = slap_MatrixFromArray(n, 1, bdata);
  Matrix y = slap_MatrixFromArray(n, 1, ydata);
  Matrix x = slap_MatrixFromArray(n, 1, xdata);

  err = slap_LowerTriBackSub(L, b);
  EXPECT_EQ(err, SLAP_NO_ERROR);
  EXPECT_LT(slap_MatrixNormedDifference(b, y), 1e-10);

  err = slap_LowerTriBackSub(slap_Transpose(L), y);
  EXPECT_EQ(err, SLAP_NO_ERROR);
  EXPECT_LT(slap_MatrixNormedDifference(x, y), 1e-10);
  (void)x;
}


TEST_F(LinearAlgebraTest, CholeskySolve) {
  // Factorize a PSD matrix
  enum slap_ErrorCode err;
  int n = chol_dim;
  A = slap_NewMatrix(n, n);
  slap_MatMulAdd(A, slap_Transpose(A1), A1, 1e-4, 0.0);
  slap_AddIdentity(A, 1.0);
  slap_MatrixCopy(Achol, A);
  err = slap_Cholesky(Achol);
  EXPECT_EQ(err, SLAP_NO_ERROR);

  // Solve the system using the factorization
  Matrix x = slap_NewMatrix(chol_dim, chol_rhs);
  slap_MatrixCopy(x, b);
  slap_CholeskySolve(Achol, x);
  slap_PrintMatrix(x);
  EXPECT_LT(slap_MatrixNormedDifference(x, x_ans), 1e-10);

  // Check the residual
  Matrix b2 = slap_NewMatrix(chol_dim, chol_rhs);
  slap_MatMulAB(b2, A, x);
  EXPECT_LT(slap_MatrixNormedDifference(b2, b), 1e-10);

  slap_FreeMatrix(A);
  slap_FreeMatrix(x);
  slap_FreeMatrix(b2);
}