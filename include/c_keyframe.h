#ifndef C_KEYFRAME_H
#define C_KEYFRAME_H

#include "types.h"
#include "PR/mbi.h"
#include "game.h"
#include "m_lib.h"

#ifdef __cplusplus
extern "C" {
#endif

#define cKF_JOINT_FLAG_DISP_OPA (0 << 0) // Joint rendered in OPA display list
#define cKF_JOINT_FLAG_DISP_XLU (1 << 0) // When set, joint is rendered in XLU display list

/* Flags for animation components to apply to each joint */
#define cKF_ANIMITION_BIT_NONE (0 << 0) // No translation or rotation
#define cKF_ANIMATION_BIT_TRANS_X (1 << 5)
#define cKF_ANIMATION_BIT_TRANS_Y (1 << 4)
#define cKF_ANIMATION_BIT_TRANS_Z (1 << 3)
#define cKF_ANIMATION_BIT_ROT_X (1 << 2)
#define cKF_ANIMATION_BIT_ROT_Y (1 << 1)
#define cKF_ANIMATION_BIT_ROT_Z (1 << 0)

#define cKF_ANIMATION_TRANS_XZ (1 << 0) // Translation on XZ
#define cKF_ANIMATION_TRANS_Y (1 << 1)  // Translation on Y
#define cKF_ANIMATION_ROT_Y (1 << 2)    // Rotation on the X axis

enum {
    cKF_STATE_NONE,
    cKF_STATE_STOPPED,
    cKF_STATE_CONTINUE,

    cKF_STATE_NUM
};

typedef struct joint_s {
    Gfx* model;
    u8 child;
    u8 flags;
    s_xyz translation;
} cKF_Joint_R_c;

typedef struct skeleton_s {
    u8 num_joints;
    u8 num_shown_joints;
    cKF_Joint_R_c* joint_table;
} cKF_Skeleton_R_c;

typedef struct animation_s {
    u8* flag_table;
    s16* data_table;
    s16* key_table;
    s16* fixed_table;
    s16 pad;
    s16 frames;
} cKF_Animation_R_c;

enum {
    cKF_FRAMECONTROL_STOP,
    cKF_FRAMECONTROL_REPEAT,

    cKF_FRAMECONTROL_NUM
};

typedef struct frame_control_s {
    f32 start_frame;
    f32 end_frame;
    f32 max_frames;
    f32 speed;
    f32 current_frame;
    f32 previous_frame;
    int mode;
} cKF_FrameControl_c;

typedef struct skeleton_info_s {
    cKF_FrameControl_c frame_control;
    cKF_Skeleton_R_c* skeleton;
    cKF_Animation_R_c* animation;

    f32 morph_counter;
    s_xyz* current_joint;
    s_xyz* target_joint;
    s_xyz* rotation_diff_table;

    int animation_enabled;
    xyz_t base_world_position;
    s16 base_angle_y;

    xyz_t base_model_translation;
    s_xyz base_model_rotation;
    s_xyz updated_base_model_rotation;

    f32 fixed_counter;
    xyz_t model_world_position_correction;
    s16 model_angle_correction;
} cKF_SkeletonInfo_R_c;

typedef struct combine_work_set_s {
    cKF_SkeletonInfo_R_c* keyframe;
    u8* anm_check_bit_tbl;
    s16* anm_const_val_tbl;
    s16* anm_data_src;
    s16* anm_key_num;
    int anm_key_num_idx;
    int anm_const_val_tbl_idx;
    int anm_data_src_idx;
} cKF_SkeletonInfo_R_combine_work_c;

typedef struct tex_anim_s {
    s16 frame;
    s16 timer;
} cKF_TextureAnimation_c;

typedef struct anim_info_s {
    cKF_Animation_R_c* animation;
    f32 speed;
    f32 start_frame;
    f32 end_frame;
    int mode;
    f32 counter;
} cKF_AnimInfo_c;

typedef int (*cKF_draw_callback)(GAME*, cKF_SkeletonInfo_R_c*, int, Gfx**, u8*, void*, s_xyz*, xyz_t*);

#define cKF_FRAMERATE 30.0f
#define cKF_FRAMETIME (1.0f / cKF_FRAMERATE)
#define cKF_EPSILON 0.008f

/**
 * Determines if the current frame has passed a specified frame, considering direction.
 *
 * @param fc Pointer to the frame control structure.
 * @param current The frame to check against the current frame.
 * @return Returns 1 if the current frame is past the specified frame, 0 otherwise.
 */
extern int cKF_FrameControl_passCheck_now(cKF_FrameControl_c* fc, f32 current);

/**
 * Stops animation at its end frame.
 *
 * Adjusts the current frame to the end frame if it's determined to surpass the end or start frame,
 * effectively stopping the animation.
 *
 * @param fc Pointer to the frame control structure.
 * @return cKF_STATE_STOPPED if animation stops; cKF_STATE_NONE otherwise.
 */
extern int cKF_FrameControl_stop_proc(cKF_FrameControl_c* fc);

/**
 * Computes a point on a Hermite curve for given time and tension.
 *
 * @param time Normalized time (0 to 1) along the curve.
 * @param tension Controls curve tightness around control points.
 * @param startPos Position of the start point.
 * @param endPos Position of the end point.
 * @param startTangent Tangent at the start point.
 * @param endTangent Tangent at the end point.
 * @return Position of the point on the curve.
 */
extern f32 cKF_HermitCalc(f32 time, f32 tension, f32 startPos, f32 endPos, f32 startTangent, f32 endTangent);

/**
 * Interpolates rotation values for skeletal animation blending.
 *
 * Determines the shortest rotation path and interpolates based on a given fraction (t),
 * considering both signed and unsigned differences to handle wraparound cases.
 *
 * @param t Interpolation factor between 0 and 1.
 * @param out Pointer to store interpolated rotation result.
 * @param rot1 Start rotation value.
 * @param rot2 End rotation value.
 */
extern void cKF_SkeletonInfo_subRotInterpolation(f32 t, s16* out, s16 rot1, s16 rot2);

/**
 * Initializes a skeleton info structure with skeleton and animation data.
 *
 * Sets up the skeleton info structure for use, linking it with its skeleton structure,
 * animation data, and joint work and target tables.
 *
 * @param keyframe Pointer to the skeleton info structure.
 * @param skeleton Pointer to the associated skeleton structure.
 * @param animation Pointer to the animation data to use.
 * @param work_table Pointer to the work table for current joint positions.
 * @param target_table Pointer to the target table for target joint positions.
 */
extern void cKF_SkeletonInfo_R_ct(cKF_SkeletonInfo_R_c* keyframe, cKF_Skeleton_R_c* skeleton,
                                  cKF_Animation_R_c* animation, s_xyz* work_table, s_xyz* target_table);

/**
 * Destructor for a skeleton info structure. Currently a stub with no operation.
 *
 * @param keyframe Pointer to the skeleton info structure to destruct.
 */
extern void cKF_SkeletonInfo_R_dt(cKF_SkeletonInfo_R_c* keyframe);

/**
 * Initializes a skeleton info structure for standard stop animation.
 *
 * Sets up the animation to stop at the last frame.
 *
 * @param keyframe Pointer to the skeleton info structure.
 * @param animation Pointer to the animation data.
 * @param rotation_diff_table Pointer to the rotation difference table.
 */
extern void cKF_SkeletonInfo_R_init_standard_stop(cKF_SkeletonInfo_R_c* keyframe, cKF_Animation_R_c* animation,
                                                  s_xyz* rotation_diff_table);

/**
 * Initializes a skeleton info structure for standard stop animation with morphing.
 *
 * Similar to standard stop but includes a morph counter to blend animations.
 *
 * @param keyframe Pointer to the skeleton info structure.
 * @param animation Pointer to the animation data.
 * @param rotation_diff_table Pointer to the rotation difference table.
 * @param morph Morph counter for animation blending.
 */
extern void cKF_SkeletonInfo_R_init_standard_stop_morph(cKF_SkeletonInfo_R_c* keyframe, cKF_Animation_R_c* animation,
                                                        s_xyz* rotation_diff_table, f32 morph);

/**
 * Initializes a skeleton info structure for standard repeat animation.
 *
 * Sets up the animation to repeat from start to end frame.
 *
 * @param keyframe Pointer to the skeleton info structure.
 * @param animation Pointer to the animation data.
 * @param rotation_diff_table Pointer to the rotation difference table.
 */
extern void cKF_SkeletonInfo_R_init_standard_repeat(cKF_SkeletonInfo_R_c* keyframe, cKF_Animation_R_c* animation,
                                                    s_xyz* rotation_diff_table);

/**
 * Initializes a skeleton info structure for standard repeat animation with morphing.
 *
 * Similar to standard repeat but includes a morph counter for blending animations.
 *
 * @param keyframe Pointer to the skeleton info structure.
 * @param animation Pointer to the animation data.
 * @param rotation_diff_table Pointer to the rotation difference table.
 * @param morph Morph counter for animation blending.
 */
extern void cKF_SkeletonInfo_R_init_standard_repeat_morph(cKF_SkeletonInfo_R_c* keyframe, cKF_Animation_R_c* animation,
                                                          s_xyz* rotation_diff_table, f32 morph);

/**
 * Generic initializer for a skeleton info structure with detailed animation control.
 *
 * Allows for custom start, end, current frame, and frame speed settings, including
 * the animation mode and morph counter.
 *
 * @param keyframe Pointer to the skeleton info structure.
 * @param skeleton Pointer to the skeleton structure.
 * @param animation Pointer to the animation data.
 * @param start_frame Animation start frame.
 * @param end_frame Animation end frame.
 * @param current_frame Current frame of animation.
 * @param frame_speed Speed of frame progression.
 * @param morph_counter Counter for morphing between animations.
 * @param mode Animation mode (stop or repeat).
 * @param rotation_diff_table Pointer to the rotation difference table.
 */
extern void cKF_SkeletonInfo_R_init(cKF_SkeletonInfo_R_c* keyframe, cKF_Skeleton_R_c* skeleton,
                                    cKF_Animation_R_c* animation, f32 start_frame, f32 end_frame, f32 current_frame,
                                    f32 frame_speed, f32 morph_counter, int mode, s_xyz* rotation_diff_table);

/**
 * Plays the animation for a given skeleton info structure, applying keyframe data and morphing.
 *
 * Advances the animation based on the current frame, applying keyframe data for each joint.
 * Handles morphing between the current and target joint positions if a morph counter is set.
 * Updates joint positions based on animation flags, fixed values, and calculated keyframe values.
 * Also applies rotation differences and updates the frame control state based on the animation mode.
 *
 * @param keyframe Pointer to the skeleton info structure containing animation and joint data.
 * @return The state of the animation after processing (e.g., stopped, none, continued).
 */
extern int cKF_SkeletonInfo_R_play(cKF_SkeletonInfo_R_c* keyframe);

/**
 * Recursively draws child joints of a skeleton, applying transformations and rendering callbacks.
 *
 * @param game Pointer to the game structure.
 * @param keyframe Pointer to the skeleton info structure for joint data and animation state.
 * @param joint_num Pointer to the current joint index being processed.
 * @param prerender_callback Callback function executed before rendering each joint.
 * @param postrender_callback Callback function executed after rendering each joint.
 * @param arg Additional arguments passed to the callbacks.
 * @param mtxpp Pointer to the transformation matrix for the current joint.
 */
extern void cKF_Si3_draw_SV_R_child(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int* joint_num,
                                    cKF_draw_callback prerender_callback, cKF_draw_callback postrender_callback,
                                    void* arg, Mtx** mtxpp);

/**
 * Renders a skeleton before and after applying transformations, using callbacks for custom rendering logic.
 *
 * @param game Pointer to the game structure.
 * @param keyframe Pointer to the skeleton info structure.
 * @param mtxp Pointer to the transformation matrix.
 * @param prerender_callback Function called before rendering the skeleton.
 * @param postrender_callback Function called after rendering the skeleton.
 * @param arg Additional arguments passed to the callbacks.
 */
extern void cKF_Si3_draw_R_SV(GAME* game, cKF_SkeletonInfo_R_c* keyframe, Mtx* mtxp,
                              cKF_draw_callback prerender_callback, cKF_draw_callback postrender_callback, void* arg);

/**
 * Initializes a skeleton info structure for repeating animation with specified speed and morph counter.
 *
 * @param keyframe Pointer to the skeleton info structure.
 * @param animation Pointer to the animation data.
 * @param rotation_diff_table Pointer to the rotation difference table.
 * @param frame_speed Animation playback speed.
 * @param morph_counter Counter for morphing between animations.
 */
extern void cKF_SkeletonInfo_R_init_standard_repeat_speedsetandmorph(cKF_SkeletonInfo_R_c* keyframe,
                                                                     cKF_Animation_R_c* animation,
                                                                     s_xyz* rotation_diff_table, f32 frame_speed,
                                                                     f32 morph_counter);

/**
 * Initializes a skeleton info structure for repeating animation, setting frame, speed, and morph counter.
 *
 * @param keyframe Pointer to the skeleton info structure.
 * @param animation Pointer to the animation data.
 * @param rotation_diff_table Pointer to the rotation difference table.
 * @param frame Starting frame for animation.
 * @param frame_speed Animation playback speed.
 * @param morph_counter Counter for morphing between animations.
 */
extern void cKF_SkeletonInfo_R_init_standard_repeat_setframeandspeedandmorph(cKF_SkeletonInfo_R_c* keyframe,
                                                                             cKF_Animation_R_c* animation,
                                                                             s_xyz* rotation_diff_table, f32 frame,
                                                                             f32 frame_speed, f32 morph_counter);

/**
 * Initializes a skeleton info structure with custom settings including frame, speed, morph counter, and mode.
 *
 * @param keyframe Pointer to the skeleton info structure.
 * @param animation Pointer to the animation data.
 * @param rotation_diff_table Pointer to the rotation difference table.
 * @param frame Starting frame for animation.
 * @param frame_speed Animation playback speed.
 * @param morph_counter Counter for morphing between animations.
 * @param mode Animation mode (e.g., repeat, stop).
 */
extern void cKF_SkeletonInfo_R_init_standard_setframeandspeedandmorphandmode(cKF_SkeletonInfo_R_c* keyframe,
                                                                             cKF_Animation_R_c* animation,
                                                                             s_xyz* rotation_diff_table, f32 frame,
                                                                             f32 frame_speed, f32 morph_counter,
                                                                             int mode);

/**
 * Initializes a skeleton info structure for reverse playback with specified speed, morph counter, and mode.
 *
 * @param keyframe Pointer to the skeleton info structure.
 * @param animation Pointer to the animation data.
 * @param rotation_diff_table Pointer to the rotation difference table.
 * @param frame_speed Animation playback speed in reverse.
 * @param morph_counter Counter for morphing between animations.
 * @param mode Animation mode (e.g., repeat, stop).
 */
extern void cKF_SkeletonInfo_R_init_reverse_setspeedandmorphandmode(cKF_SkeletonInfo_R_c* keyframe,
                                                                    cKF_Animation_R_c* animation,
                                                                    s_xyz* rotation_diff_table, f32 frame_speed,
                                                                    f32 morph_counter, int mode);

/**
 * Prepares combine work set structure for joint animation combination.
 *
 * @param combine Pointer to the combine work set structure.
 * @param keyframe Pointer to the skeleton info structure.
 */
extern void cKF_SkeletonInfo_R_combine_work_set(cKF_SkeletonInfo_R_combine_work_c* combine,
                                                cKF_SkeletonInfo_R_c* keyframe);

/**
 * Combines translation data for joints based on animation flags, supporting up to three animation layers.
 *
 * @param joint Pointer to the joint data.
 * @param flag Pointer to the current joint flag.
 * @param combine Pointer to the combine work set structure.
 * @param part_table Pointer to the current part table.
 */
extern void cKF_SkeletonInfo_R_combine_translation(s16** joint, int* flag, cKF_SkeletonInfo_R_combine_work_c* combine,
                                                   s8* part_table);

/**
 * Combines rotation data from multiple animation layers for a joint, modifying it based on animation flags.
 *
 * @param joint Pointer to the current joint's rotation data.
 * @param flag Pointer to the animation flag affecting the current joint.
 * @param combine Pointer to the combine work set structure containing animation layer data.
 * @param part_table Pointer to the current part table.
 */
extern void cKF_SkeletonInfo_R_combine_rotation(s16** joint, int* flag, cKF_SkeletonInfo_R_combine_work_c* combine,
                                                s8* part_table);

/**
 * Combines and plays two sets of animation data, applying translations and rotations from both.
 *
 * @param info1 First skeleton info structure to combine.
 * @param info2 Second skeleton info structure to combine.
 * @param part_table Pointer to the part table determining the combination behavior.
 * @return Status of the combination and play operation.
 */
extern int cKF_SkeletonInfo_R_combine_play(cKF_SkeletonInfo_R_c* info1, cKF_SkeletonInfo_R_c* info2, s8* part_table);

/**
 * Combines and plays three sets of animation data, applying translations and rotations, and updates playback state.
 *
 * @param state1 Result of playing first animation.
 * @param state2 Result of playing second animation.
 * @param state3 Result of playing third animation.
 * @param info1 First skeleton info structure to combine.
 * @param info2 Second skeleton info structure to combine.
 * @param info3 Third skeleton info structure to combine.
 * @param part_table Pointer to the part table determining the combination behavior.
 */
extern void cKF_SkeletonInfo_R_T_combine_play(int* state1, int* state2, int* state3, cKF_SkeletonInfo_R_c* info1,
                                              cKF_SkeletonInfo_R_c* info2, cKF_SkeletonInfo_R_c* info3, s8* part_table);

/**
 * Sets base shape translation and rotation for a skeleton info structure.
 *
 * @param transx X translation of the base model.
 * @param transy Y translation of the base model.
 * @param transz Z translation of the base model.
 * @param keyframe Skeleton info structure to modify.
 * @param anglex X angle for base model rotation.
 * @param angley Y angle for base model rotation.
 * @param anglez Z angle for base model rotation.
 */
extern void cKF_SkeletonInfo_R_Animation_Set_base_shape_trs(cKF_SkeletonInfo_R_c* keyframe, f32 transx, f32 transy,
                                                            f32 transz, s16 anglex, s16 angley, s16 anglez);

/**
 * Adjusts the base position and correction for a skeleton info structure based on animation flags.
 *
 * @param basepos Original base position of the model.
 * @param correctpos Corrected base position of the model.
 * @param ybase Base Y angle for rotation.
 * @param yidle Idle Y angle for rotation.
 * @param counter Animation counter to determine the phase of movement.
 * @param keyframe Skeleton info structure to modify.
 * @param an_flag Animation flags to determine which corrections to apply.
 */
extern void cKF_SkeletonInfo_R_AnimationMove_ct_base(xyz_t* basepos, xyz_t* correctpos, s16 ybase, s16 yidle,
                                                     f32 counter, cKF_SkeletonInfo_R_c* keyframe, int animation_flag);

/**
 * Resets animation movement and flags for a skeleton info structure.
 *
 * @param keyframe The skeleton info structure to reset.
 */
extern void cKF_SkeletonInfo_R_AnimationMove_dt(cKF_SkeletonInfo_R_c* keyframe);

/**
 * Applies base movement and adjustment based on animation counter and flags.
 *
 * @param base Base position to modify.
 * @param sbase Base rotation to modify.
 * @param scale Scaling amount to apply.
 * @param yidle Y-axis idle angle.
 * @param keyframe Skeleton info structure containing animation data.
 */
extern void cKF_SkeletonInfo_R_AnimationMove_base(xyz_t* base, s16* sbase, xyz_t* scale, s16 yidle,
                                                  cKF_SkeletonInfo_R_c* keyframe);

/**
 * Calculates and applies transformation to world coordinates based on animation data.
 *
 * @param calc_pos Calculated position result.
 * @param base_pos Base world position.
 * @param trans_x X-coordinate for translation.
 * @param trans_y Y-coordinate for translation.
 * @param trans_z Z-coordinate for translation.
 * @param angle_y Angle value for rotation.
 * @param scale Scaling factor.
 * @param keyframe Skeleton info structure containing animation data.
 * @param trans_flag Flags determining which transformations to apply.
 */
extern void cKF_SkeletonInfo_R_AnimationMove_CulcTransToWorld(xyz_t* calc_pos, const xyz_t* base_pos, f32 trans_x,
                                                              f32 trans_y, f32 trans_z, s16 angle_y, const xyz_t* scale,
                                                              cKF_SkeletonInfo_R_c* keyframe, int trans_flag);

#ifdef __cplusplus
}
#endif

#endif
