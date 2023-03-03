//
// Created by Brian Jackson on 3/2/23.
// Copyright (c) 2023 Robotic Exploration Lab. All rights reserved.
//

#include <chrono>
#include <functional>
#include <iostream>

#include "Eigen/Dense"
#include "fmt/chrono.h"
#include "fmt/core.h"
#include "slap/slap.h"

extern "C" {
#include "slap/new_matrix.h"
}

using Eigen::MatrixXd;
using Eigen::VectorXd;

template <class T>
using millis = std::chrono::duration<T, std::milli>;

template <class T>
using micros = std::chrono::duration<T, std::micro>;

micros<double> benchmark(std::function<void()> f, int n_runs = 10) {
  auto t_start = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < n_runs; ++i) {
    f();
  }
  auto t_end = std::chrono::high_resolution_clock::now();
  return t_end - t_start;
}

int main() {
  std::cout << "Eigen and slap performance comparison\n" << std::endl;

  fmt::print("Matrix Addition (slap/Eigen)\n");
  for (int n = 3; n < 25; ++n) {
    int m = n;
    int p = n;

    Matrix A_slap = slap_NewMatrix(m, n);
    Matrix B_slap = slap_NewMatrix(n, p);
    Matrix C_slap = slap_NewMatrix(m, p);
    slap_SetConst(A_slap, 2.5);
    slap_SetConst(B_slap, 5.2);

    MatrixXd A_eig(m, n);
    MatrixXd B_eig(n, p);
    MatrixXd C_eig(m, p);
    A_eig.setConstant(2.5);
    B_eig.setConstant(5.2);

    int n_runs = 100;
    micros<double> t_slap =
        benchmark([&]() { slap_MatrixAddition(C_slap, A_slap, B_slap, 2.2); }, n_runs);
    micros<double> t_eig = benchmark(
        [&]() {
          C_eig.noalias() = A_eig * B_eig;
          C_eig.array() *= 2.2;
        },
        n_runs);
    fmt::print("n = {:10}: {:10} / {}\n", n, t_slap / n_runs, t_eig / n_runs);
  }
  fmt::print("\n\n");

  fmt::print("Matrix Multiplication (slap/Eigen)\n");
  for (int n = 3; n < 25; ++n) {
    int m = n;
    int p = n;

    Matrix A_slap = slap_NewMatrix(m, n);
    Matrix B_slap = slap_NewMatrix(n, p);
    Matrix C_slap = slap_NewMatrix(m, p);
    slap_SetConst(A_slap, 2.5);
    slap_SetConst(B_slap, 5.2);

    MatrixXd A_eig(m, n);
    MatrixXd B_eig(n, p);
    MatrixXd C_eig(m, p);
    A_eig.setConstant(2.5);
    B_eig.setConstant(5.2);

    int n_runs = 100;
    micros<double> t_slap =
        benchmark([&]() { slap_MatMulAdd(C_slap, A_slap, B_slap, 1, 0); }, n_runs);
    micros<double> t_eig = benchmark([&]() { C_eig = A_eig * B_eig; }, n_runs);
    fmt::print("n = {:10}: {:10} / {}\n", n, t_slap / n_runs, t_eig / n_runs);
  }
  fmt::print("\n\n");

  fmt::print("Matrix Multiply-Add (slap/Eigen)\n");
  for (int n = 3; n < 25; ++n) {
    int m = n;
    int p = n;

    MatrixXd A_eig(m, n);
    MatrixXd B_eig(n, p);
    MatrixXd C0_eig(m, p);
    MatrixXd C_eig(m, p);
    A_eig.setRandom();
    B_eig.setRandom();
    C0_eig.setRandom();

    Matrix A_slap = slap_NewMatrix(m, n);
    Matrix B_slap = slap_NewMatrix(n, p);
    Matrix C0_slap = slap_NewMatrix(m, p);
    Matrix C_slap = slap_NewMatrix(m, p);
    slap_MatrixCopyFromArray(A_slap, A_eig.data());
    slap_MatrixCopyFromArray(B_slap, B_eig.data());
    slap_MatrixCopyFromArray(C0_slap, C0_eig.data());

    int n_runs = 100;
    micros<double> t_slap = benchmark(
        [&]() {
          slap_MatrixCopy(C_slap, C0_slap);
          slap_MatMulAdd(C_slap, A_slap, B_slap, 1.2, 2.4);
        },
        n_runs);
    micros<double> t_eig = benchmark(
        [&]() {
          C_eig = C0_eig;
          C_eig = 2.4 * C_eig + 1.2 * A_eig * B_eig;
        },
        n_runs);
    fmt::print("n = {:10}: {:10} / {}\n", n, t_slap / n_runs, t_eig / n_runs);
  }
  fmt::print("\n\n");

  fmt::print("Cholesky Decomposition (slap/Eigen)\n");
  fmt::print("              Decomposition       |           Solve\n");
  for (int n = 3; n < 25; ++n) {
    MatrixXd A_(n, n);
    A_.setRandom();
    MatrixXd A0_eig = A_.transpose() * A_;
    A0_eig.diagonal().array() += 0.1;
    MatrixXd A_eig = A0_eig;
    VectorXd b_eig(n);
    VectorXd x_eig(n);
    b_eig.setRandom();

    Matrix A0_slap = slap_NewMatrix(n, n);
    Matrix A_slap = slap_NewMatrix(n, n);
    Matrix b_slap = slap_NewMatrix(n, 1);
    Matrix x_slap = slap_NewMatrix(n, 1);
    slap_MatrixCopyFromArray(A0_slap, A_eig.data());
    slap_MatrixCopyFromArray(b_slap, b_eig.data());

    int n_runs = 100;
    micros<double> t_slap = benchmark(
        [&]() {
          slap_MatrixCopy(A_slap, A0_slap);
          slap_Cholesky(A_slap);
        },
        n_runs);
    micros<double> t_eig = benchmark(
        [&]() {
          A_eig = A0_eig;
          A_eig.llt();
        },
        n_runs);

    slap_MatrixCopy(A_slap, A0_slap);
    slap_Cholesky(A_slap);
    A_eig = A0_eig;
    Eigen::LLT<MatrixXd> A_chol = A_eig.llt();

    micros<double> t_slap_solve = benchmark(
        [&]() {
          slap_MatrixCopy(x_slap, b_slap);
          slap_CholeskySolve(A_slap, x_slap);
        },
        n_runs);
    micros<double> t_eig_solve = benchmark(
        [&]() {
          x_eig = b_eig;
          A_chol.solveInPlace(x_eig);
        },
        n_runs);

    fmt::print("n = {:3}: {:10} / {:10}  |  {:10} / {:10}\n", n, t_slap / n_runs,
               t_eig / n_runs, t_slap_solve / n_runs, t_eig_solve / n_runs);
  }


  fmt::print("Skinny QR (slap/Eigen)\n");
  for (int n = 2; n < 25; ++n) {
    int m = 2 * n;
    MatrixXd A0_eig(m, n);
    MatrixXd A_eig(m, n);
    A0_eig.setRandom();

    Matrix A0_slap = slap_NewMatrix(n, n);
    Matrix A_slap = slap_NewMatrix(n, n);
    Matrix betas = slap_NewMatrix(m, 1);
    Matrix temp = slap_NewMatrix(m, 1);
    slap_MatrixCopyFromArray(A0_slap, A_eig.data());

    int n_runs = 100;
    micros<double> t_slap = benchmark(
        [&]() {
          slap_MatrixCopy(A_slap, A0_slap);
          slap_QR(A_slap, betas, temp);
        },
        n_runs);
    micros<double> t_eig = benchmark(
        [&]() {
          A_eig = A0_eig;
          A_eig.householderQr();
        },
        n_runs);

    slap_MatrixCopy(A_slap, A0_slap);
    slap_Cholesky(A_slap);
    A_eig = A0_eig;
    Eigen::LLT<MatrixXd> A_chol = A_eig.llt();


    fmt::print("n = {:3}: {:10} / {:10}\n", n, t_slap / n_runs,
               t_eig / n_runs);
  }

  return 0;
}