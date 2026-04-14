#ifndef M_LIB_H
#define M_LIB_H

#include "types.h"
#include "m_play_h.h"
#include "m_actor_type.h"
#include "sys_math.h"
#include "libu64/u64types.h"
#include "game.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SHT_MINV (1.0f / SHT_MAX)
#define ABS(x) (((x) >= 0) ? (x) : -(x))
#define SQ(x) ((x) * (x))
#define CLAMP_MIN(x, min) ((x) < (min) ? (min) : (x))
#define CLAMP_MAX(x, max) ((max) < (x) ? (max) : (x))
#define CLAMP(x, min, max) ((x) < (min) ? (min) : (((x) > (max) ? (max) : (x))))
#define CLAMP2(x, min, max) ((min) < (x) ? (((x) < (max) ? (x) : (max))) : (min))

// clamp macro specifically for Animal Crossing
#ifndef M_CLAMP
#define M_CLAMP(v, l, h) MAX(MIN((v), (l)), (h))
#endif

// Easing macros
#define CALC_EASE(x) (1.0f - sqrtf(1.0f - (x)))
#define CALC_EASE2(x) CALC_EASE(CALC_EASE(x))

/* Float modulo operator */
#define MOD_F(a, m) (a - (int)((a) * (1.0f / (m))) * (m))

/* radians -> short angle */
#define RAD2SHORT_ANGLE(rad) ((s16)(int)((rad) * (65536.0f / (2.0f * F_PI))))
#define RAD2SHORTANGLE(rad) ((s16)((32768.0f / F_PI) * ((f32)(rad))))
#define RAD2SHORT_ANGLE2(rad) ((s16)((rad) * (65536.0f / (2.0f * F_PI))))

/* short angle -> radians */
#define SHORT2RAD_ANGLE(s) ((((f32)(s)) / (65536.0f / (2.0f * F_PI))))
#define SHORT2RAD_ANGLE2(s) ((f32)(s) * ((2.0f * F_PI) / 65536.0f))
#define SHORTANGLE2RAD(sangle) ((F_PI / 32768.0f) * ((f32)(sangle)))

/* degrees -> short angle */
#define DEG2SHORT_ANGLE(deg) ((s16)((deg) * (65536.0f / 360.0f)))
#define DEG2SHORT_ANGLE2(deg) ((int)((deg) * (65536.0f / 360.0f)))
#define DEG2SHORT_ANGLE3(deg) ((deg) * (65536.0f / 360.0f))

/* short angle -> degrees */
#define SHORT2DEG_ANGLE(s) ((((f32)(s)) / (65536.0f / 360.0f)))

/* radians -> degrees */
#define RAD2DEG(rad) ((180.0f / F_PI) * (rad))

/* degrees -> radians */
#define DEG2RAD(deg) ((F_PI / 180.0f) * (deg))

// short angle difference
#define DIFF_SHORT_ANGLE(x, y) ((s16)((x) - (y)))
#define DIFF_USHORT_ANGLE(x, y) ((u16)((x) - (y)))

// fixed timestep -> delta time conversions
#define DTCONV(v, dt) powf(v, GRAPH_BASE_FRAME_RATE * (dt)) // raw dt in seconds
#define DTCONV_GRAPH(v, graph) powf(v, (graph)->dt_num_60fps_frames) // used with GRAPH*
#define DTCONV_GAME(v, game) DTCONV_GRAPH(v, (game)->graph) // used with GAME*

#define DTCONV_CALC_LAMBDA(v) (GRAPH_BASE_FRAME_RATE * logf(v)) // calculate dt exponential lambda, cache result
#define DTCONV_EXP(lambda, dt) expf((lambda) * (dt)) // optimized route for precalculated dt lambdas
#define DTCONV_EXP_GRAPH(lambda, graph) DTCONV_EXP(lambda, (graph)->dt) // optimized route for GRAPH*
#define DTCONV_EXP_GAME(lambda, game) DTCONV_EXP_GRAPH(lambda, (game)->graph) // optimized route for GAME*

typedef struct rgba_t { // can be put in other place
    u8 r, g, b, a;
} rgba_t;

typedef struct rgb_t {
    uint r, g, b;
} rgb_t;

typedef struct rgb8_t {
    u8 r, g, b;
} rgb8_t;

typedef struct {
    xyz_t position;
    s_xyz angle;
} PositionAngle;

extern void mem_copy(u8* dst, u8* src, size_t size);
extern void mem_clear(u8* dst, size_t size, u8 val);
extern int mem_cmp(u8* p1, u8* p2, size_t size);

extern f32 cos_s(s16 angle);
extern f32 sin_s(s16 angle);
#define tan_s(angle) (sin_s(angle) / cos_s(angle))

extern int chase_angle(s16* const pValue, const s16 target, s16 step);
extern int chase_s(s16* const pValue, const s16 target, s16 step);
extern int chase_f(f32* const pValue, const f32 target, f32 step);
extern f32 chase_xyz_t(xyz_t* const pValue, const xyz_t* const target, const f32 fraction);
extern int chase_angle2(s16* const pValue, const s16 limit, const s16 step);

extern void inter_float(f32* const pValue, const f32 arg1, const int step);
extern s16 get_random_timer(const s16 base, const s16 range);

extern void xyz_t_move(xyz_t* const dest, const xyz_t* const src);
extern void xyz_t_move_s_xyz(xyz_t* const dest, const s_xyz* const src);
extern void xyz_t_add(const xyz_t* const augend, const xyz_t* const addend, xyz_t* const total);
extern void xyz_t_sub(const xyz_t* const minuend, const xyz_t* const subtrahend, xyz_t* const diff);
extern void xyz_t_mult_v(xyz_t* const multiplicand, const f32 multiplier);

extern f32 search_position_distance(const xyz_t* const pos, const xyz_t* const target);
extern f32 search_position_distanceXZ(const xyz_t* const pos, const xyz_t* const target);
extern s16 search_position_angleY(const xyz_t* const pos, const xyz_t* const target);
extern s16 search_position_angleX(const xyz_t* const pos, const xyz_t* const target);

extern f32 add_calc(f32* pValue, f32 target, f32 fraction, f32 maxStep, f32 minStep);
extern void add_calc2(f32* pValue, f32 target, f32 fraction, f32 maxStep);
extern void add_calc0(f32* pValue, f32 fraction, f32 maxStep);

extern s16 add_calc_short_angle2(s16* pValue, s16 target, f32 fraction, s16 maxStep, s16 minStep);
extern s16 add_calc_short_angle3(s16* pValue, s16 target, f32 fraction, s16 maxStep, s16 minStep);

extern void rgba_t_move(rgba_t* dest, const rgba_t* const src);

extern int none_proc1();
extern void none_proc2(ACTOR* actor, GAME* game);

extern int _Game_play_isPause(GAME_PLAY* play);
extern f32 check_percent_abs(f32 x, f32 min, f32 max, f32 scale, int shift_by_min);
extern f32 get_percent_forAccelBrake(f32 now, f32 start, f32 end, f32 accelerateDist, f32 brakeDist);
extern void Game_play_Projection_Trans(GAME_PLAY* const play, xyz_t* world_pos, xyz_t* screen_pos);

extern f32 get_percent(const int max, const int min, const int x);

#ifdef __cplusplus
}
#endif

#endif
