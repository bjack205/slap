//
// Created by Brian Edward Jackson on 1/31/23.
//

#pragma once

#include "slap/slap.h"

/**
 * @brief Solve a Linear Time-Invariant LQR problem using Riccati recursion, calculating
 * the feedback gains and cost-to-go
 *
 * @param[in] N Number of segments (horizon length - 1)
 * @param[in] A State transition Matrix (n,n)
 * @param[in] B Input Matrix (n,m)
 * @param[in] f Affine dynamics (n,1)
 * @param[in] Q State penalty Matrix (n,n). Must be PSD.
 * @param[in] R Input penalty Matrix (m,m). Must be PD.
 * @param[in] q Affine state penalty (n,1)
 * @param[in] r Affine input penalty (m,1)
 * @param[out] K Feedback gains (N-1) x (m,n)
 * @param[out] d Feedforward gains  (N-1) x (m,1)
 * @param[out] P Cost-to-go Hessians N x (n,n)
 * @param[out] p Cost-to-go gradients N x (n,1)
 * @param S_temp Storage for temparary values (n+m, n+m+1)
 * @return
 */
enum slap_ErrorCode slap_Riccati_LTI(int N, const Matrix A, const Matrix B, const Matrix f,
                                     const Matrix Q, const Matrix R, const Matrix q,
                                     const Matrix r, Matrix* K, Matrix* d, Matrix* P,
                                     Matrix* p, Matrix S_temp);

/**
 * @brief Calculate the optimal state, input, and co-state (i.e. dual variables)
 * trajectories for a discrete Linear-Time-Invariant LQR problem.
 *
 * @param[in] N Number of segments (horizon length - 1)
 * @param[in] A State transition Matrix (n,n)
 * @param[in] B Input Matrix (n,m)
 * @param[in] f Affine dynamics (n,1)
 * @param[in] x0 Initial state (n,1)
 * @param[in] K Feedback gains (N-1) x (m,n)
 * @param[in] d Feedforward gains  (N-1) x (m,1)
 * @param[in] P Cost-to-go Hessians N x (n,n)
 * @param[in] p Cost-to-go gradients N x (n,1)
 * @param[out] x State trajectory N x (n,1)
 * @param[out] u Input trajectory (N-1) x (m,1)
 * @param[out] y Co-state trajectory N x (n,1)
 * @return
 */
enum slap_ErrorCode slap_RiccatiForwardPass_LTI(int N, const Matrix A, const Matrix B,
                                                const Matrix f, const Matrix x0,
                                                const Matrix* K, const Matrix* d,
                                                const Matrix* P, const Matrix* p, Matrix* x,
                                                Matrix* u, Matrix* y);

int slap_RiccatiDataSize_LTI(int N, int num_states, int num_inputs);


double slap_Stationarity_LTI(int N, const Matrix A, const Matrix B, const Matrix f);
