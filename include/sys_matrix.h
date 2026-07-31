#ifndef SYS_MATRIX_H
#define SYS_MATRIX_H

#include "types.h"
#include "libultra/ultratypes.h"
#include "PR/mbi.h"
#include "m_lib.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MTX_LOAD 0 // load into new matrix
#define MTX_MULT 1 // multiply into existing matrix

extern MtxF MtxF_clear;
extern N64Mtx Mtx_clear;

extern void new_Matrix(GAME* game);
extern void Matrix_push();
extern void Matrix_pull();
extern void Matrix_get(MtxF* m);
extern void Matrix_put(MtxF* m);
extern MtxF* get_Matrix_now();
extern void Matrix_mult(MtxF* m, u8 flag);
extern void Matrix_translate(f32 x, f32 y, f32 z, u8 flag);
extern void Matrix_scale(f32 x, f32 y, f32 z, u8 flag);
extern void Matrix_RotateX(s16 x, int flag);
extern void Matrix_RotateY(s16 x, int flag);
extern void Matrix_RotateZ(s16 x, int flag);
extern void Matrix_rotateXYZ(s16 x, s16 y, s16 z, int flag);
extern void Matrix_softcv3_mult(xyz_t* pos, s_xyz* rot);
extern void Matrix_softcv3_load(s_xyz* src, f32 x, f32 y, f32 z);
extern N64Mtx* _MtxF_to_Mtx(MtxF* src, N64Mtx* dest);
extern N64Mtx* _Matrix_to_Mtx(N64Mtx* dest);
extern N64Mtx* _Matrix_to_Mtx_new(GRAPH* graph);
extern void Matrix_Position(xyz_t* input_position, xyz_t* output_position);
extern void Matrix_Position_Zero(xyz_t* screen_pos);
extern void Matrix_Position_VecX(f32 x, xyz_t* screen_pos);
extern void Matrix_Position_VecZ(f32 z, xyz_t* screen_pos);
extern void Matrix_copy_MtxF(MtxF* dest, MtxF* src);
extern void Matrix_MtxtoMtxF(N64Mtx* src, MtxF* dest);
extern void Matrix_reverse(MtxF* m);
extern void Matrix_to_rotate_new(MtxF* m, s_xyz* vec, int flag);
extern void Matrix_to_rotate2_new(MtxF* m, s_xyz* vec, int flag);
extern void Matrix_RotateVector(s16 angle, xyz_t* axis, u8 flag);
extern void suMtxMakeTS(N64Mtx* m, f32 scaleX, f32 scaleY, f32 scaleZ, f32 translateX, f32 translateY, f32 translateZ);
extern void suMtxMakeSRT(N64Mtx* m, f32 scaleX, f32 scaleY, f32 scaleZ, s16 rotX, s16 rotY, s16 rotZ, f32 translateX, f32 translateY, f32 translateZ);
extern void suMtxMakeSRT_ZXY(N64Mtx* m, f32 scaleX, f32 scaleY, f32 scaleZ, s16 rotX, s16 rotY, s16 rotZ, f32 translateX, f32 translateY, f32 translateZ);

#ifdef __cplusplus
}
#endif

#endif
