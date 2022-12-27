#ifndef GEMM_H
#define GEMM_H

#include "../../core/types.h"

void ai_gemm_bin(i32 M, i32 N, i32 K, f32 ALPHA, char *A, i32 lda, f32 *B, i32 ldb, f32 *C, i32 ldc);

void
ai_gemm(i32 TA, i32 TB, i32 M, i32 N, i32 K, f32 ALPHA, f32 *A, i32 lda, f32 *B, i32 ldb, f32 BETA, f32 *C, i32 ldc);

void ai_gemm_cpu(i32 TA, i32 TB, i32 M, i32 N, i32 K, f32 ALPHA, f32 *A, i32 lda, f32 *B, i32 ldb, f32 BETA, f32 *C,
                 i32 ldc);

#ifdef GPU
void gemm_gpu(i32 TA, i32 TB, i32 M, i32 N, i32 K, f32 ALPHA, 
        f32 *A_gpu, i32 lda, 
        f32 *B_gpu, i32 ldb,
        f32 BETA,
        f32 *C_gpu, i32 ldc);

void gemm_gpu(i32 TA, i32 TB, i32 M, i32 N, i32 K, f32 ALPHA, 
        f32 *A, i32 lda, 
        f32 *B, i32 ldb,
        f32 BETA,
        f32 *C, i32 ldc);
#endif
#endif
