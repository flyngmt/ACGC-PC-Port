#include "c_keyframe.h"

#include "MSL_C/w_math.h"
#include "graph.h"
#include "libultra/libultra.h"
#include "sys_math3d.h"
#include "sys_matrix.h"

/**
 * Resets and initializes a frame control structure with default parameters.
 * Sets all numerical properties to 1.0f and mode to cKF_FRAMECONTROL_STOP.
 *
 * @param frame_control Pointer to the frame control structure.
 */
static void cKF_FrameControl_zeroClera(cKF_FrameControl_c* frame_control) {
    bzero(frame_control, sizeof(cKF_FrameControl_c));
    frame_control->max_frames = 1.0f;
    frame_control->current_frame = 1.0f;
    frame_control->previous_frame = 1.0f;
    frame_control->speed = 1.0f;
    frame_control->end_frame = 1.0f;
    frame_control->start_frame = 1.0f;
    frame_control->mode = cKF_FRAMECONTROL_STOP;
}

/**
 * Initializes a frame control structure.
 * Wrapper for cKF_FrameControl_zeroClera to provide a clear constructor interface.
 *
 * @param frame_control Pointer to the frame control structure to initialize.
 */
static void cKF_FrameControl_ct(cKF_FrameControl_c* frame_control) {
    cKF_FrameControl_zeroClera(frame_control);
}

/**
 * Sets the frame control parameters for an animation sequence.
 *
 * @param frame_control Pointer to the frame control structure.
 * @param start_frame Starting frame of the animation sequence.
 * @param end_frame Ending frame of the animation sequence; if less than 1.0f, max_frames is used.
 * @param max_frames Maximum number of frames in the animation sequence.
 * @param current_frame The current frame number in the animation sequence.
 * @param speed The speed at which the animation should play.
 * @param mode The mode of the animation (e.g., stop, repeat).
 */
static void cKF_FrameControl_setFrame(cKF_FrameControl_c* frame_control, f32 start_frame, f32 end_frame, f32 max_frames,
                                      f32 current_frame, f32 speed, int mode) {
    frame_control->start_frame = start_frame;

    if (end_frame < 1.0f) {
        frame_control->end_frame = max_frames;
    } else {
        frame_control->end_frame = end_frame;
    }

    frame_control->max_frames = max_frames;
    frame_control->speed = speed;
    frame_control->current_frame = current_frame;
    frame_control->previous_frame = current_frame;
    frame_control->mode = mode;
}

/**
 * Checks if the current frame is within a certain range and calculates the overshoot.
 *
 * @param fc Pointer to the frame control structure.
 * @param current The target frame to compare against the current frame.
 * @param out Pointer to a float where the overshoot amount will be stored.
 * @return Returns 1 if within the range and adjustments were made, 0 otherwise.
 */
static int cKF_FrameControl_passCheck(cKF_FrameControl_c* fc, f32 current, f32* out) {
    f32 cur;
    f32 speed;

    *out = 0.0f;
    cur = fc->current_frame;
    if (cur == current) {
        return FALSE;
    }

    speed = (fc->start_frame < fc->end_frame) ? fc->speed : -fc->speed;

    // Check if current frame within target range considering speed
    if ((speed >= 0.0f && cur < current && cur + speed >= current) ||
        (speed < 0.0f && cur > current && cur + speed <= current)) {
        *out = cur + speed - current; // Calculate overshoot
        return TRUE;
    }
    return FALSE;
}

extern int cKF_FrameControl_passCheck_now(cKF_FrameControl_c* fc, const float current) {
    const float cur = fc->current_frame;

    if (cur == current) {
        return TRUE;
    } else {
        const float prev = fc->previous_frame;
        const float start = fc->start_frame;
        const float end = fc->end_frame;
        float speed = fc->speed;

        if (start >= end) {
            speed = -speed;
        }

        if (speed >= 0.0f) {
            if (prev <= cur) {
                // no wrap this update
                if (prev < current && cur >= current) {
                    return TRUE;
                }
            } else {
                // wrapped from end -> start
                if ((prev < end && current > prev && current <= end) ||
                    (cur >= start && current >= start && current <= cur)) {
                    return TRUE;
                }
            }
        } else { // playing backwards
            if (prev >= cur) {
                // no wrap
                if (prev > current && cur <= current) {
                    return TRUE;
                }
            } else {
                // wrapped from start -> end
                if ((prev > start && current >= start && current < prev) ||
                    (cur <= end && current >= cur && current <= end)) {
                    return TRUE;
                }
            }
        }
    }

    return FALSE;
}

extern int cKF_FrameControl_stop_proc(cKF_FrameControl_c* fc) {
    f32 out;

    if (fc->current_frame == fc->end_frame) {
        return cKF_STATE_STOPPED;
    }
    if (cKF_FrameControl_passCheck(fc, fc->end_frame, &out)) {
        fc->current_frame = fc->end_frame;
        return cKF_STATE_STOPPED;
    }
    if (cKF_FrameControl_passCheck(fc, fc->start_frame, &out)) {
        fc->current_frame = fc->end_frame;
        return cKF_STATE_STOPPED;
    }
    return cKF_STATE_NONE;
}

/**
 * Repeats animation by looping from start to end frame.
 *
 * Loops the current frame back to the start or end, based on the animation's progression,
 * allowing for continuous playback.
 *
 * @param fc Pointer to the frame control structure.
 * @return cKF_STATE_CONTINUE if animation continues; cKF_STATE_NONE otherwise.
 */
static int cKF_FrameControl_repeat_proc(cKF_FrameControl_c* fc) {
    f32 out;

    if (cKF_FrameControl_passCheck(fc, fc->end_frame, &out)) {
        fc->current_frame = fc->start_frame + out;
        return cKF_STATE_CONTINUE;
    }
    if (cKF_FrameControl_passCheck(fc, fc->start_frame, &out)) {
        fc->current_frame = fc->end_frame + out;
        return cKF_STATE_CONTINUE;
    }
    return cKF_STATE_NONE;
}

/**
 * Plays animation based on current mode.
 *
 * Updates current frame according to animation speed and mode, ensuring playback within
 * the animation's frame range.
 *
 * @param fc Pointer to the frame control structure.
 * @return Animation state after update.
 */
 static int cKF_FrameControl_play(cKF_FrameControl_c* fc) {
    int rec;
    float speed;

    // Store the previous frame BEFORE any modifications (stop_proc may clamp current_frame)
    fc->previous_frame = fc->current_frame;

    if (fc->mode == cKF_FRAMECONTROL_STOP) {
        rec = cKF_FrameControl_stop_proc(fc);
    } else {
        rec = cKF_FrameControl_repeat_proc(fc);
    }

    if (rec == cKF_STATE_NONE) {
        speed = fc->speed;
        if (fc->start_frame >= fc->end_frame) {
            speed = -speed;
        }

        speed *= gamePT->graph->dt_num_60fps_frames;
        // if (frame > 0.0f) {
        //     OSReport("cKF_FrameControl_play: dt: %f, frame: %f, fc->current_frame: %f, fc->max_frames: %f\n", GAME_DELTATIME, frame, fc->current_frame, fc->max_frames);
        // }
        fc->current_frame += speed; // TODO: we should probably pass in graph somehow
    }
    if (fc->current_frame < 1.0f) {
        fc->current_frame = (fc->current_frame - 1.0f) + fc->max_frames;
    } else if (fc->current_frame > fc->max_frames) {
        fc->current_frame = (fc->current_frame - fc->max_frames) + 1.0f;
    }
    return rec;
}

extern f32 cKF_HermitCalc(f32 time, f32 tension, f32 startPos, f32 endPos, f32 startTangent, f32 endTangent) {
    f32 position;
    f32 timeSquared;
    f32 timeCubed;
    f32 basisH10;
    f32 basisH11;

    timeSquared = time * time;
    timeCubed = timeSquared * time;
    position = -(timeCubed * 2.0f) + (3.0f * timeSquared);
    basisH10 = time + (timeCubed - (timeSquared * 2.0f));
    basisH11 = timeCubed - timeSquared;

    return (((1.0f - position) * startPos) + (position * endPos)) +
           (tension * ((basisH10 * startTangent) + (basisH11 * endTangent)));
}

typedef struct {
    s16 frame;
    s16 value;
    s16 tangent;
} cKF_AnimKey_c;

/**
 * Calculates keyframe value based on frame position within keyframe data.
 *
 * Interpolates or directly retrieves the y-component of a keyframe based on the given frame number.
 * Uses linear or Hermite interpolation depending on the proximity of frame to keyframe positions.
 *
 * @param start_idx Starting index of the keyframe data.
 * @param n_frames Number of frames in the keyframe sequence.
 * @param data_src Pointer to the keyframe data source.
 * @param frame Current frame number for which to calculate the keyframe value.
 * @return Interpolated or directly retrieved keyframe value.
 */
static s16 cKF_KeyCalc(s16 start_idx, s16 n_frames, s16* data_src, f32 frame) {
    int now;
    int next;
    cKF_AnimKey_c* key_p = (cKF_AnimKey_c*)&data_src[start_idx * 3];

    /* If the first frame is greater than the current frame then the first value is held */
    if (key_p[0].frame >= frame) {
        return key_p[0].value;
    }

    /* If the current frame is greater than the last frame then the last value is held */
    if (key_p[n_frames - 1].frame <= frame) {
        return key_p[n_frames - 1].value;
    }

    // Search through all frames
    now = 0;
    next = 1;

    while (TRUE) {
        if (key_p[next].frame > frame) {
            f32 delta_frame = key_p[next].frame - key_p[now].frame;

            if (!(F32_IS_ZERO(delta_frame))) {
                f32 t = (frame - key_p[now].frame) / delta_frame; // progress towards the next frame
                f32 tension = delta_frame * (1.0f / 30.0f);
                f32 calc = cKF_HermitCalc(t, tension, key_p[now].value, key_p[next].value, key_p[now].tangent,
                                          key_p[next].tangent);
                int key = calc + 0.5; // Always round up

                return key;
            } else {
                return key_p[now].value;
            }
        }

        now++;
        next++;
    }
}

extern void cKF_SkeletonInfo_subRotInterpolation(f32 t, s16* out, s16 rot1, s16 rot2) {
    u16 urot1 = rot1;
    s32 pad;
    u16 urot2 = rot2;
    f32 f1 = rot1;
    f32 signedDiff = rot2 - f1;
    f32 f2 = urot1;
    f32 unsignedDiff = urot2 - f2;

    if (fabsf(signedDiff) < fabsf(unsignedDiff)) {
        *out = f1 + signedDiff * t;
    } else {
        *out = f2 + unsignedDiff * t;
    }
}

/**
 * Morphs current state towards a target state with a given step size.
 *
 * Adjusts 'now' values towards 'target' values based on 'step', performing this operation
 * for three consecutive s16 values (x->y->z) starting from 'now' and 'target'.
 *
 * @param now Pointer to the current values.
 * @param target Pointer to the target values to morph towards.
 * @param step Fractional step size for morphing.
 */
static void cKF_SkeletonInfo_morphST(s16* now, s16* target, f32 step) {
    int i;

    for (i = 0; i < 3; i++) {
        if (*now != *target) {
            f32 now_f = (f32)*now;
            f32 target_f = (f32)*target;
            f32 diff = (target_f - now_f);
            *now = (diff * step) + now_f;
        }

        now++;
        target++;
    }
}

/**
 * Zeroes out and initializes a skeleton info structure.
 *
 * Clears all data within cKF_SkeletonInfo_R_c structure, effectively resetting it.
 *
 * @param keyframe Pointer to the skeleton info structure to be cleared.
 */
static void cKF_SkeletonInfo_R_zeroClear(cKF_SkeletonInfo_R_c* keyframe) {
    bzero(keyframe, sizeof(cKF_SkeletonInfo_R_c));
}

extern void cKF_SkeletonInfo_R_ct(cKF_SkeletonInfo_R_c* keyframe, cKF_Skeleton_R_c* skeleton,
                                  cKF_Animation_R_c* animation, s_xyz* work_table, s_xyz* target_table) {
    cKF_SkeletonInfo_R_zeroClear(keyframe);
    cKF_FrameControl_ct(&keyframe->frame_control);

    keyframe->skeleton = skeleton;
    keyframe->animation = animation;
    keyframe->current_joint = work_table;
    keyframe->target_joint = target_table;
}

extern void cKF_SkeletonInfo_R_dt(cKF_SkeletonInfo_R_c* keyframe) {
}

extern void cKF_SkeletonInfo_R_init_standard_stop(cKF_SkeletonInfo_R_c* keyframe, cKF_Animation_R_c* animation,
                                                  s_xyz* rotation_diff_table) {
    cKF_SkeletonInfo_R_init(keyframe, keyframe->skeleton, animation, 1.0f, animation->frames, 1.0f, 0.5f, 0.0f,
                            cKF_FRAMECONTROL_STOP, rotation_diff_table);
}

extern void cKF_SkeletonInfo_R_init_standard_stop_morph(cKF_SkeletonInfo_R_c* keyframe, cKF_Animation_R_c* animation,
                                                        s_xyz* rotation_diff_table, f32 morph) {
    cKF_SkeletonInfo_R_init(keyframe, keyframe->skeleton, animation, 1.0f, animation->frames, 1.0f, 0.5f, morph,
                            cKF_FRAMECONTROL_STOP, rotation_diff_table);
}

extern void cKF_SkeletonInfo_R_init_standard_repeat(cKF_SkeletonInfo_R_c* keyframe, cKF_Animation_R_c* animation,
                                                    s_xyz* rotation_diff_table) {
    cKF_SkeletonInfo_R_init(keyframe, keyframe->skeleton, animation, 1.0f, animation->frames, 1.0f, 0.5f, 0.0f,
                            cKF_FRAMECONTROL_REPEAT, rotation_diff_table);
}

extern void cKF_SkeletonInfo_R_init_standard_repeat_morph(cKF_SkeletonInfo_R_c* keyframe, cKF_Animation_R_c* animation,
                                                          s_xyz* rotation_diff_table, f32 morph) {
    cKF_SkeletonInfo_R_init(keyframe, keyframe->skeleton, animation, 1.0f, animation->frames, 1.0f, 0.5f, morph,
                            cKF_FRAMECONTROL_REPEAT, rotation_diff_table);
}

extern void cKF_SkeletonInfo_R_init(cKF_SkeletonInfo_R_c* keyframe, cKF_Skeleton_R_c* skeleton,
                                    cKF_Animation_R_c* animation, f32 start_frame, f32 end_frame, f32 current_frame,
                                    f32 frame_speed, f32 morph_counter, int mode, s_xyz* rotation_diff_table) {
    keyframe->morph_counter = morph_counter;
    keyframe->skeleton = skeleton;
    keyframe->animation = animation;

    cKF_FrameControl_setFrame(&keyframe->frame_control, start_frame, end_frame, keyframe->animation->frames,
                              current_frame, frame_speed, mode);
    keyframe->rotation_diff_table = rotation_diff_table;
}

/**
 * Morphs joint positions towards target positions based on the morph counter.
 *
 * Adjusts each joint's position in the skeleton towards its target position using interpolation,
 * based on a calculated step size derived from the morph counter. If the morph counter is zero,
 * no morphing occurs.
 *
 * @param keyframe Pointer to the skeleton info structure containing joint and target positions.
 */
static void cKF_SkeletonInfo_R_morphJoint(cKF_SkeletonInfo_R_c* keyframe) {
    int i;
    s_xyz* current_joint = keyframe->current_joint;
    s_xyz* target_joint = keyframe->target_joint;
    f32 step;
    s16 next_joint_x;
    s16 next_joint_y;
    s16 next_joint_z;
    s16 next_target_x;
    s16 next_target_y;
    s16 next_target_z;

    if (!(F32_IS_ZERO(keyframe->morph_counter))) {
        step = 0.5f / fabsf(keyframe->morph_counter);
    } else {
        step = 0.0f;
    }

    cKF_SkeletonInfo_morphST(&current_joint->x, &target_joint->x, step);

    current_joint++;
    target_joint++;

    for (i = 0; i < keyframe->skeleton->num_joints; i++) {
        next_joint_x = current_joint->x;
        next_target_x = target_joint->x;

        next_joint_y = current_joint->y;
        next_joint_z = current_joint->z;

        next_target_y = target_joint->y;
        next_target_z = target_joint->z;

        if (next_joint_x != next_target_x || next_joint_y != next_target_y || next_joint_z != next_target_z) {
            f32 difxyz = fabsf((f32)next_target_x - (f32)next_joint_x) + fabsf((f32)next_target_y - (f32)next_joint_y) +
                         fabsf((f32)next_target_z - (f32)next_joint_z);

            s16 temp_vec_x = 0x7FFF + next_joint_x;
            s16 temp_vec_y = 0x7FFF - next_joint_y;
            s16 temp_vec_z = 0x7FFF + next_joint_z;

            f32 dif_xyz2 = fabsf((f32)next_target_x - (f32)temp_vec_x) + fabsf((f32)next_target_y - (f32)temp_vec_y) +
                           fabsf((f32)next_target_z - (f32)temp_vec_z);

            if (difxyz < dif_xyz2) {
                cKF_SkeletonInfo_subRotInterpolation(step, &current_joint->x, next_joint_x, next_target_x);
                cKF_SkeletonInfo_subRotInterpolation(step, &current_joint->y, next_joint_y, next_target_y);
                cKF_SkeletonInfo_subRotInterpolation(step, &current_joint->z, next_joint_z, next_target_z);
            } else {
                cKF_SkeletonInfo_subRotInterpolation(step, &current_joint->x, temp_vec_x, next_target_x);
                cKF_SkeletonInfo_subRotInterpolation(step, &current_joint->y, temp_vec_y, next_target_y);
                cKF_SkeletonInfo_subRotInterpolation(step, &current_joint->z, temp_vec_z, next_target_z);
            }
        }
        target_joint++;
        current_joint++;
    }
}

// TODO: There's probably no difference between this and US.
// The inlines used to match US are fake.
#if VERSION >= VER_GAFU01_00
extern int cKF_SkeletonInfo_R_play(cKF_SkeletonInfo_R_c* keyframe) {
    int i;
    int j;
    u8* flagTable;
    int keyTableIndex = 0;
    int fixedTableIndex = 0;
    int dataIndex = 0;
    s16* jointValuePtr;
    s16* fixedTable;
    s16* dataTable;
    s16* keyTable;
    u32 jointFlag; // Check translation (xyz)

    // Choose between current and target joint based on morph counter
    if (F32_IS_ZERO(keyframe->morph_counter)) {
        jointValuePtr = &keyframe->current_joint->x;
    } else {
        jointValuePtr = &keyframe->target_joint->x;
    }

    jointFlag = cKF_ANIMATION_BIT_TRANS_X;

    // Retrieve animation tables
    fixedTable = keyframe->animation->fixed_table;
    keyTable = keyframe->animation->key_table;
    dataTable = keyframe->animation->data_table;
    flagTable = keyframe->animation->flag_table;

    

    // Process root translation x -> y -> z
    for (j = 0; j < 3; j++) {
        if (*flagTable & jointFlag) {
            // Apply joint translation
            *jointValuePtr =
                cKF_KeyCalc(dataIndex, keyTable[keyTableIndex], dataTable, keyframe->frame_control.current_frame);
            dataIndex += keyTable[keyTableIndex];
            keyTableIndex++;
        } else {
            // Use fixed value if not flagged for keyframe animation
            *jointValuePtr = fixedTable[fixedTableIndex];
            fixedTableIndex++;
        }

        jointFlag >>= 1; // Shift x -> y -> z
        jointValuePtr++; // Move to next joint
    }

    // Process remaining joint rotations
    for (i = 0; i < keyframe->skeleton->num_joints; i++) {
        jointFlag = cKF_ANIMATION_BIT_ROT_X; // Reset flag for new joint

        // Process each joint x -> y -> z
        for (j = 0; j < 3; j++) {
            f32 adjustedJointValue;
            f32 mod;

            // Similar logic to above, but for each joint in the skeleton
            if (jointFlag & flagTable[i]) {
                *jointValuePtr =
                    cKF_KeyCalc(dataIndex, keyTable[keyTableIndex], dataTable, keyframe->frame_control.current_frame);
                dataIndex += keyTable[keyTableIndex];
                keyTableIndex++;
            } else {
                *jointValuePtr = fixedTable[fixedTableIndex];
                fixedTableIndex++;
            }

            // Reduce the value by 90% and clamp to [0, 360) degrees converted back to binangle (s16)
            // This effectively limits any joint's maximum rotation to be in the range of [-36.8, 36.7] degrees
            adjustedJointValue = *jointValuePtr * 0.1f;
            mod = MOD_F(adjustedJointValue, 360.0f);
            *jointValuePtr = DEG2SHORT_ANGLE(mod);
            jointValuePtr++;


            jointFlag >>= 1; // Shift flag for next component x -> y -> z
        }

        // flagTable++;
    }

    // Apply rotation differences if available
    if (keyframe->rotation_diff_table != NULL) {
        s_xyz* currentJointPtr = (F32_IS_ZERO(keyframe->morph_counter)) ? keyframe->current_joint : keyframe->target_joint;

        currentJointPtr++; // Skip first joint, usually root, which is handled separately
        for (j = 0; j < keyframe->skeleton->num_joints; j++) {
            // Apply rotation differences to each joint
            currentJointPtr->x += keyframe->rotation_diff_table[j].x;
            currentJointPtr->y += keyframe->rotation_diff_table[j].y;
            currentJointPtr->z += keyframe->rotation_diff_table[j].z;

            currentJointPtr++; // Move to next joint
        }
    }

    // Handle morphing and play control based on morph counter
    if (F32_IS_ZERO(keyframe->morph_counter)) {
        // Play normally if no morphing is needed
        return cKF_FrameControl_play(&keyframe->frame_control);
    } else if (keyframe->morph_counter > 0.0f) {
        // Morph towards target, decreasing morph counter
        cKF_SkeletonInfo_R_morphJoint(keyframe);
        keyframe->morph_counter -= 0.5f;
        if (keyframe->morph_counter <= 0.0f) {
            keyframe->morph_counter = 0.0f; // Clamp to zero if over-decremented
        }
        return cKF_STATE_NONE;
    } else {
        // Morph from target, increasing morph counter towards zero
        cKF_SkeletonInfo_R_morphJoint(keyframe);
        keyframe->morph_counter += 0.5f;
        if (keyframe->morph_counter >= 0.0f) {
            keyframe->morph_counter = 0.0f; // Clamp to zero if over-incremented
        }
        return cKF_FrameControl_play(&keyframe->frame_control);
    }
}
#else
/**
 * Retrieves the flag table from an animation structure.
 *
 * Provides direct access to the flag table indicating the state or properties of each frame
 * or keyframe in the animation sequence.
 *
 * @param keyframe Pointer to the animation structure.
 * @return Pointer to the flag table.
 */
inline u8* cKF_Animation_R_getFlagTable(cKF_Animation_R_c* keyframe) {
    return keyframe->flag_table;
}

/**
 * Retrieves the fixed table from an animation structure.
 *
 * Provides direct access to the fixed table containing fixed values used in the animation,
 * possibly for static or non-interpolated properties.
 *
 * @param keyframe Pointer to the animation structure.
 * @return Pointer to the fixed table.
 */
inline s16* cKF_Animation_R_getFixedTable(cKF_Animation_R_c* keyframe) {
    return keyframe->fixed_table;
}

/**
 * Retrieves the key table from an animation structure.
 *
 * Provides direct access to the key table containing key points used for interpolating
 * animation values.
 *
 * @param keyframe Pointer to the animation structure.
 * @return Pointer to the key table.
 */
inline s16* cKF_Animation_R_getKeyTable(cKF_Animation_R_c* keyframe) {
    return keyframe->key_table;
}

/**
 * Retrieves the data table from an animation structure.
 *
 * Provides direct access to the data table containing all numerical data points used for
 * animating properties over time.
 *
 * @param keyframe Pointer to the animation structure.
 * @return Pointer to the data table.
 */
inline s16* cKF_Animation_R_getDataTable(cKF_Animation_R_c* keyframe) {
    return keyframe->data_table;
}

extern int cKF_SkeletonInfo_R_play(cKF_SkeletonInfo_R_c* keyframe) {
    int state;
    int jointIndex;
    s_xyz* currentJointPtr;
    s16 fixedJointValue;
    s16* currentJointValue;
    cKF_Animation_R_c* animationData;
    int component;
    f32 adjustedJointValue;

    int keyTableIndex = 0;
    int fixedTableIndex = 0;

    int dataIndex = 0;

#ifdef TARGET_PC
    /* Validate keyframe data to prevent crash from corrupted animation state.
       Note: data_table and key_table can legitimately be NULL for static poses
       (all flags zero, all values from fixed_table). Only reject truly invalid state. */
    if (keyframe == NULL || keyframe->skeleton == NULL || keyframe->animation == NULL ||
        keyframe->current_joint == NULL || keyframe->skeleton->num_joints > 200 ||
        keyframe->animation->flag_table == NULL || keyframe->animation->fixed_table == NULL) {
        return cKF_STATE_STOPPED;
    }
#endif

    // Choose between current and target joint based on morph counter
    s16* jointValuePtr =
        (F32_IS_ZERO(keyframe->morph_counter)) ? &keyframe->current_joint->x : &keyframe->target_joint->x;
    u32 jointFlag = cKF_ANIMATION_BIT_TRANS_X; // Check translation (xyz)

    // Retrieve animation tables - direct struct access (bypass inline functions)
    s16* fixedTable = keyframe->animation->fixed_table;
    s16* keyTable = keyframe->animation->key_table;
    s16* dataTable = keyframe->animation->data_table;
    u8* flagTable = keyframe->animation->flag_table;

    // Process root translation x -> y -> z
    for (component = 0; component < 3; component++) {
        if (flagTable[0] & jointFlag) {
            // Apply joint translation
            *jointValuePtr =
                cKF_KeyCalc(dataIndex, keyTable[keyTableIndex], dataTable, keyframe->frame_control.current_frame);
            dataIndex += keyTable[keyTableIndex++];
        } else {
            // Use fixed value if not flagged for keyframe animation
            *jointValuePtr = fixedTable[fixedTableIndex++];
        }

        jointFlag >>= 1; // Shift x -> y -> z
        jointValuePtr++; // Move to next joint
    }

    // Process remaining joint rotations
    for (jointIndex = 0; jointIndex < keyframe->skeleton->num_joints; jointIndex++) {
        jointFlag = cKF_ANIMATION_BIT_ROT_X; // Reset flag for new joint

        // Process each joint x -> y -> z
        for (component = 0; component < 3; component++) {
            // Similar logic to above, but for each joint in the skeleton
            if (jointFlag & flagTable[jointIndex]) {
                *jointValuePtr =
                    cKF_KeyCalc(dataIndex, keyTable[keyTableIndex], dataTable, keyframe->frame_control.current_frame);
                dataIndex += keyTable[keyTableIndex++];
            } else {
                *jointValuePtr = fixedTable[fixedTableIndex++];
            }

            // Convert joint value to fixed-point format after scaling
            jointFlag >>= 1; // Shift flag for next component x -> y -> z

            // Reduce the value by 90% and clamp to [0, 360) degrees converted back to binangle (s16)
            // This effectively limits any joint's maximum rotation to be in the range of [-36.8, 36.7] degrees
            adjustedJointValue = *jointValuePtr * 0.1f;
            *jointValuePtr++ = DEG2SHORT_ANGLE(MOD_F(adjustedJointValue, 360.0f));
        }
    }

    // Apply rotation differences if available
    if (keyframe->rotation_diff_table != NULL) {
        currentJointPtr = (F32_IS_ZERO(keyframe->morph_counter)) ? keyframe->current_joint : keyframe->target_joint;

        currentJointPtr++; // Skip first joint, usually root, which is handled separately
        for (component = 0; component < keyframe->skeleton->num_joints; component++) {
            // Apply rotation differences to each joint
            currentJointPtr->x += keyframe->rotation_diff_table[component].x;
            currentJointPtr->y += keyframe->rotation_diff_table[component].y;
            currentJointPtr->z += keyframe->rotation_diff_table[component].z;

            currentJointPtr++; // Move to next joint
        }
    }

    // Handle morphing and play control based on morph counter
    if (F32_IS_ZERO(keyframe->morph_counter)) {
        // Play normally if no morphing is needed
        state = cKF_FrameControl_play(&keyframe->frame_control);
    } else if (keyframe->morph_counter > 0.0f) {
        // Morph towards target, decreasing morph counter
        cKF_SkeletonInfo_R_morphJoint(keyframe);
        keyframe->morph_counter -= 0.5f;
        if (keyframe->morph_counter <= 0.0f) {
            keyframe->morph_counter = 0.0f; // Clamp to zero if over-decremented
        }
        state = cKF_STATE_NONE;
    } else {
        // Morph from target, increasing morph counter towards zero
        cKF_SkeletonInfo_R_morphJoint(keyframe);
        keyframe->morph_counter += 0.5f;
        if (keyframe->morph_counter >= 0.0f) {
            keyframe->morph_counter = 0.0f; // Clamp to zero if over-incremented
        }
        state = cKF_FrameControl_play(&keyframe->frame_control);
    }

    return state;
}
#endif

extern void cKF_Si3_draw_SV_R_child(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int* joint_num,
                                    cKF_draw_callback prerender_callback, cKF_draw_callback postrender_callback,
                                    void* arg, Mtx** mtxpp) {
    int i;
    int an_flag;
    Gfx* joint_m;
    Gfx* mjoint_m;
    u8 joint_f;
    xyz_t trans;
    s_xyz joint1;
    cKF_Joint_R_c* skel_c_joint;
    s_xyz* cur_joint;
    GRAPH* graph;

    skel_c_joint = keyframe->skeleton->joint_table;
    skel_c_joint += *joint_num;
    cur_joint = &keyframe->current_joint[*joint_num];

    if (*joint_num != 0) {
        // Since we have joints, take the current joint's translation
        trans.x = skel_c_joint->translation.x;
        trans.y = skel_c_joint->translation.y;
        trans.z = skel_c_joint->translation.z;
    } else {
        // No joints, take the base model translation w/ respect to flags
        an_flag = keyframe->animation_enabled;
        if (an_flag & cKF_ANIMATION_TRANS_XZ) {
            trans.x = keyframe->base_model_translation.x;
            trans.z = keyframe->base_model_translation.z;
        } else {
            trans.x = cur_joint->x;
            trans.z = cur_joint->z;
        }
        if (an_flag & cKF_ANIMATION_TRANS_Y) {
            trans.y = keyframe->base_model_translation.y;
        } else {
            trans.y = cur_joint->y;
        }
    }

    joint1 = cur_joint[1];

    if ((joint_num[0] == 0) && (keyframe->animation_enabled & cKF_ANIMATION_ROT_Y)) {
        joint1.x = keyframe->base_model_rotation.x;
        joint1.y = keyframe->updated_base_model_rotation.y;
        joint1.z = keyframe->updated_base_model_rotation.z;
    }

    graph = game->graph;
    OPEN_DISP(graph);
    Matrix_push();

    joint_m = skel_c_joint->model;
    mjoint_m = joint_m;
    joint_f = skel_c_joint->flags;

    // Render joint if prerender callback wasn't supplied or the callback does not return FALSE
    {
    if ((prerender_callback == NULL) ||
        ((prerender_callback != NULL) &&
         (prerender_callback(game, keyframe, *joint_num, &mjoint_m, &joint_f, arg, &joint1, &trans)) != FALSE)) {
        Matrix_softcv3_mult(&trans, &joint1);
        if (mjoint_m != NULL) {
            _Matrix_to_Mtx(*mtxpp);
            if (joint_f & cKF_JOINT_FLAG_DISP_XLU) {
                // Joint translated & drawn in XLU display list
                gSPMatrix(NOW_POLY_XLU_DISP++, *mtxpp, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(NOW_POLY_XLU_DISP++, mjoint_m);
            } else {
                // Joint translated & drawin OPA display list
                gSPMatrix(NOW_POLY_OPA_DISP++, *mtxpp, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(NOW_POLY_OPA_DISP++, mjoint_m);
            }
            mtxpp[0]++;
        } else if (joint_m != NULL) {
            // Joint has a rendered model but the prerender callback chose not to render it
            // so we apply the translation still
            _Matrix_to_Mtx(*mtxpp);
            gSPMatrix(NOW_POLY_OPA_DISP++, *mtxpp, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            mtxpp[0]++;
        }
    }
    }

    CLOSE_DISP(graph);

    // Call postrender callback if supplied
    if (postrender_callback != NULL) {
        postrender_callback(game, keyframe, *joint_num, &mjoint_m, &joint_f, arg, &joint1, &trans);
    }

    joint_num[0]++; // Move onto next joint

    // Render all children
    for (i = 0; i < skel_c_joint->child; i++) {
        cKF_Si3_draw_SV_R_child(game, keyframe, joint_num, prerender_callback, postrender_callback, arg, mtxpp);
    }

    // Remove the effect of this joint's translation & rotatation
    Matrix_pull();
}

extern void cKF_Si3_draw_R_SV(GAME* game, cKF_SkeletonInfo_R_c* keyframe, Mtx* mtxp,
                              cKF_draw_callback prerender_callback, cKF_draw_callback postrender_callback, void* arg) {
    int joint_num;
    Mtx* mtx_p = mtxp;

    if (mtxp != NULL) {
        GRAPH* graph = game->graph;
        OPEN_DISP(graph);

        /* TODO: these should probably be made into a custom macro somewhere */
        gSPSegment(NOW_POLY_OPA_DISP++, G_MWO_SEGMENT_D,
                   mtx_p); // Load matrix (opaque)
        gSPSegment(NOW_POLY_XLU_DISP++, G_MWO_SEGMENT_D,
                   mtx_p); // Load matrix (translucent)

        CLOSE_DISP(graph);
        joint_num = 0;

        cKF_Si3_draw_SV_R_child(game, keyframe, &joint_num, prerender_callback, postrender_callback, arg, &mtx_p);
    }
}

extern void cKF_SkeletonInfo_R_init_standard_repeat_speedsetandmorph(cKF_SkeletonInfo_R_c* keyframe,
                                                                     cKF_Animation_R_c* animation,
                                                                     s_xyz* rotation_diff_table, f32 frame_speed,
                                                                     f32 morph_counter) {
    cKF_SkeletonInfo_R_init(keyframe, keyframe->skeleton, animation, 1.0f, animation->frames, 1.0f, frame_speed,
                            morph_counter, cKF_FRAMECONTROL_REPEAT, rotation_diff_table);
}

extern void cKF_SkeletonInfo_R_init_standard_repeat_setframeandspeedandmorph(cKF_SkeletonInfo_R_c* keyframe,
                                                                             cKF_Animation_R_c* animation,
                                                                             s_xyz* rotation_diff_table, f32 frame,
                                                                             f32 frame_speed, f32 morph_counter) {
    cKF_SkeletonInfo_R_init(keyframe, keyframe->skeleton, animation, 1.0f, animation->frames, frame, frame_speed,
                            morph_counter, cKF_FRAMECONTROL_REPEAT, rotation_diff_table);
}

extern void cKF_SkeletonInfo_R_init_standard_setframeandspeedandmorphandmode(cKF_SkeletonInfo_R_c* keyframe,
                                                                             cKF_Animation_R_c* animation,
                                                                             s_xyz* rotation_diff_table, f32 frame,
                                                                             f32 frame_speed, f32 morph_counter,
                                                                             int mode) {
    cKF_SkeletonInfo_R_init(keyframe, keyframe->skeleton, animation, 1.0f, animation->frames, frame, frame_speed,
                            morph_counter, mode, rotation_diff_table);
}

extern void cKF_SkeletonInfo_R_init_reverse_setspeedandmorphandmode(cKF_SkeletonInfo_R_c* keyframe,
                                                                    cKF_Animation_R_c* animation,
                                                                    s_xyz* rotation_diff_table, f32 frame_speed,
                                                                    f32 morph_counter, int mode) {
    cKF_SkeletonInfo_R_init(keyframe, keyframe->skeleton, animation, animation->frames, 1.0f, animation->frames,
                            frame_speed, morph_counter, mode, rotation_diff_table);
}

extern void cKF_SkeletonInfo_R_combine_work_set(cKF_SkeletonInfo_R_combine_work_c* combine,
                                                cKF_SkeletonInfo_R_c* keyframe) {
    combine->keyframe = keyframe;
    combine->anm_const_val_tbl = keyframe->animation->fixed_table;
    combine->anm_key_num = keyframe->animation->key_table;
    combine->anm_data_src = keyframe->animation->data_table;
    combine->anm_check_bit_tbl = keyframe->animation->flag_table;
    combine->anm_key_num_idx = 0;
    combine->anm_const_val_tbl_idx = 0;
    combine->anm_data_src_idx = 0;
}

extern void cKF_SkeletonInfo_R_combine_translation(s16** joint, int* flag, cKF_SkeletonInfo_R_combine_work_c* combine,
                                                   s8* part_table) {
    int i;

    for (i = 0; i < 3; i++) {
        /* Determine which animation we should pull from for the joint */
        switch (*part_table) {
            case 0:
                if (*combine[0].anm_check_bit_tbl & *flag) {
                    (**joint) =
                        cKF_KeyCalc(combine[0].anm_data_src_idx, combine[0].anm_key_num[combine[0].anm_key_num_idx],
                                    combine[0].anm_data_src, combine[0].keyframe->frame_control.current_frame);
                } else {
                    (**joint) = combine[0].anm_const_val_tbl[combine[0].anm_const_val_tbl_idx];
                }

                break;
            case 1:
                if (*combine[1].anm_check_bit_tbl & *flag) {
                    (**joint) =
                        cKF_KeyCalc(combine[1].anm_data_src_idx, combine[1].anm_key_num[combine[1].anm_key_num_idx],
                                    combine[1].anm_data_src, combine[1].keyframe->frame_control.current_frame);
                } else {
                    (**joint) = combine[1].anm_const_val_tbl[combine[1].anm_const_val_tbl_idx];
                }

                break;
            case 2:
                if (*combine[2].anm_check_bit_tbl & *flag) {
                    (**joint) =
                        cKF_KeyCalc(combine[2].anm_data_src_idx, combine[2].anm_key_num[combine[2].anm_key_num_idx],
                                    combine[2].anm_data_src, combine[2].keyframe->frame_control.current_frame);
                } else {
                    (**joint) = combine[2].anm_const_val_tbl[combine[2].anm_const_val_tbl_idx];
                }

                break;
        }

        if (*combine[0].anm_check_bit_tbl & *flag) {
            combine[0].anm_data_src_idx += combine[0].anm_key_num[combine[0].anm_key_num_idx];
            combine[0].anm_key_num_idx++;
        } else {
            combine[0].anm_const_val_tbl_idx++;
        }

        if (*combine[1].anm_check_bit_tbl & *flag) {
            combine[1].anm_data_src_idx += combine[1].anm_key_num[combine[1].anm_key_num_idx];
            combine[1].anm_key_num_idx++;
        } else {
            combine[1].anm_const_val_tbl_idx++;
        }

        if (*combine[2].anm_check_bit_tbl & *flag) {
            combine[2].anm_data_src_idx += combine[2].anm_key_num[combine[2].anm_key_num_idx];
            combine[2].anm_key_num_idx++;
        } else {
            combine[2].anm_const_val_tbl_idx++;
        }

        *flag = (u32)*flag >> 1;
        *joint += 1;
    }
}

extern void cKF_SkeletonInfo_R_combine_rotation(s16** joint, int* flag, cKF_SkeletonInfo_R_combine_work_c* combine,
                                                s8* part_table) {
    int i;
    int j;
    f32 calc_joint;

    for (i = 0; i < combine->keyframe->skeleton->num_joints; i++) {
        *flag = 4;

        for (j = 0; j < 3; j++) {
            /* Determine which animation we should pull from for the joint */
            switch (part_table[i + 1]) {
                case 0:
                    if (*flag & combine[0].anm_check_bit_tbl[i]) {
                        (**joint) =
                            cKF_KeyCalc(combine[0].anm_data_src_idx, combine[0].anm_key_num[combine[0].anm_key_num_idx],
                                        combine[0].anm_data_src, combine[0].keyframe->frame_control.current_frame);
                    } else {
                        (**joint) = combine[0].anm_const_val_tbl[combine[0].anm_const_val_tbl_idx];
                    }
                    break;

                case 1:
                    if (*flag & combine[1].anm_check_bit_tbl[i]) {
                        (**joint) =
                            cKF_KeyCalc(combine[1].anm_data_src_idx, combine[1].anm_key_num[combine[1].anm_key_num_idx],
                                        combine[1].anm_data_src, combine[1].keyframe->frame_control.current_frame);
                    } else {
                        (**joint) = combine[1].anm_const_val_tbl[combine[1].anm_const_val_tbl_idx];
                    }
                    break;

                case 2:
                    if (*flag & combine[2].anm_check_bit_tbl[i]) {
                        (**joint) =
                            cKF_KeyCalc(combine[2].anm_data_src_idx, combine[2].anm_key_num[combine[2].anm_key_num_idx],
                                        combine[2].anm_data_src, combine[2].keyframe->frame_control.current_frame);
                    } else {
                        (**joint) = combine[2].anm_const_val_tbl[combine[2].anm_const_val_tbl_idx];
                    }
                    break;
            }
            if (*flag & combine[0].anm_check_bit_tbl[i]) {
                combine[0].anm_data_src_idx += combine[0].anm_key_num[combine[0].anm_key_num_idx];
                combine[0].anm_key_num_idx++;
            } else {
                combine[0].anm_const_val_tbl_idx++;
            }
            if (*flag & combine[1].anm_check_bit_tbl[i]) {
                combine[1].anm_data_src_idx += combine[1].anm_key_num[combine[1].anm_key_num_idx];
                combine[1].anm_key_num_idx++;
            } else {
                combine[1].anm_const_val_tbl_idx++;
            }
            if (*flag & combine[2].anm_check_bit_tbl[i]) {
                combine[2].anm_data_src_idx += combine[2].anm_key_num[combine[2].anm_key_num_idx];
                combine[2].anm_key_num_idx++;
            } else {
                combine[2].anm_const_val_tbl_idx++;
            }

            /*
             * At this point, rotation values in joint are encoded in [degree.x] format.
             * This gives one decimal of rotational precision. We then convert from degrees to
             * s16 binangle.
             */

            /* s16 degree -> float degree with 1 decimal place precision */
            calc_joint = 0.1f * (**joint);
            /* degree (unbound) -> [0.0f, 360.0f) -> binangle [-32768, 32767] */
            **joint = (s16)DEG2SHORT_ANGLE2(MOD_F(calc_joint, 360.0f));
            *flag = (u32)*flag >> 1;
            *joint += 1;
        }
    }
}

extern int cKF_SkeletonInfo_R_combine_play(cKF_SkeletonInfo_R_c* info1, cKF_SkeletonInfo_R_c* info2, s8* part_table) {
    int combinet;
    s16* joint;
    cKF_SkeletonInfo_R_combine_work_c combine[3];
    int i;
    s_xyz* joint2;
    s_xyz* applyjoint;

    if ((info1 == NULL) || (info2 == NULL) || (part_table == NULL)) {
        return cKF_STATE_NONE;
    }
    joint = (F32_IS_ZERO(info1->morph_counter)) ? &info1->current_joint->x : &info1->target_joint->x;

    if (info1 != NULL) {
        cKF_SkeletonInfo_R_combine_work_set(&combine[0], info1);
    }
    if (info2 != NULL) {
        cKF_SkeletonInfo_R_combine_work_set(&combine[1], info2);
        cKF_SkeletonInfo_R_combine_work_set(&combine[2], info2);
    }
    combinet = 0x20;
    cKF_SkeletonInfo_R_combine_translation(&joint, &combinet, &combine[0], part_table);
    cKF_SkeletonInfo_R_combine_rotation(&joint, &combinet, &combine[0], part_table);

    if (info1->rotation_diff_table != NULL) {
        if (F32_IS_ZERO(info1->morph_counter)) {
            applyjoint = info1->current_joint;
        } else {
            applyjoint = info1->target_joint;
        }

        applyjoint += 1;
        for (i = 0; i < info1->skeleton->num_joints; i++) {
            applyjoint->x += info1->rotation_diff_table[i].x;
            applyjoint->y += info1->rotation_diff_table[i].y;
            applyjoint->z += info1->rotation_diff_table[i].z;

            applyjoint++;
        }
    }
    if (F32_IS_ZERO(info1->morph_counter)) {
        cKF_FrameControl_play(&info2->frame_control);
        return cKF_FrameControl_play(&info1->frame_control);
    } else if (info1->morph_counter > 0.0f) {
        cKF_SkeletonInfo_R_morphJoint(info1);
        info1->morph_counter -= 0.5f;
        if (info1->morph_counter <= 0.0f) {
            info1->morph_counter = 0.0f;
        }
        return cKF_STATE_NONE;
    } else {
        cKF_SkeletonInfo_R_morphJoint(info1);
        info1->morph_counter += 0.5f;
        if (info1->morph_counter >= 0.0f) {
            info1->morph_counter = 0.0f;
        }
        cKF_FrameControl_play(&info2->frame_control);
        return cKF_FrameControl_play(&info1->frame_control);
    }
}

extern void cKF_SkeletonInfo_R_T_combine_play(int* state1, int* state2, int* state3, cKF_SkeletonInfo_R_c* info1,
                                              cKF_SkeletonInfo_R_c* info2, cKF_SkeletonInfo_R_c* info3,
                                              s8* part_table) {
    int combinet;
    s16* joint;
    cKF_SkeletonInfo_R_combine_work_c combine[3];
    int i;
    s_xyz* joint2;
    s_xyz* applyjoint;

    if ((info1 == NULL) || (info2 == NULL) || (info3 == NULL) || (part_table == NULL)) {
        return;
    }

    joint = (F32_IS_ZERO(info1->morph_counter)) ? &info1->current_joint->x : &info1->target_joint->x;

    if (info1 != NULL) {
        cKF_SkeletonInfo_R_combine_work_set(&combine[0], info1);
    }
    if (info2 != NULL) {
        cKF_SkeletonInfo_R_combine_work_set(&combine[1], info2);
    }
    if (info3 != NULL) {
        cKF_SkeletonInfo_R_combine_work_set(&combine[2], info3);
    }

    combinet = 0x20;
    cKF_SkeletonInfo_R_combine_translation(&joint, &combinet, &combine[0], part_table);
    cKF_SkeletonInfo_R_combine_rotation(&joint, &combinet, &combine[0], part_table);

    if (info1->rotation_diff_table != NULL) {
        if (F32_IS_ZERO(info1->morph_counter)) {
            applyjoint = info1->current_joint;
        } else {
            applyjoint = info1->target_joint;
        }

        applyjoint += 1;
        for (i = 0; i < info1->skeleton->num_joints; i++) {
            applyjoint->x += info1->rotation_diff_table[i].x;
            applyjoint->y += info1->rotation_diff_table[i].y;
            applyjoint->z += info1->rotation_diff_table[i].z;

            applyjoint++;
        }
    }
    if (F32_IS_ZERO(info1->morph_counter)) {
        *state1 = cKF_FrameControl_play(&info1->frame_control);
        *state2 = cKF_FrameControl_play(&info2->frame_control);
        *state3 = cKF_FrameControl_play(&info3->frame_control);
    } else if (info1->morph_counter > 0.0f) {
        cKF_SkeletonInfo_R_morphJoint(info1);
        info1->morph_counter -= 0.5f;
        if (info1->morph_counter <= 0.0f) {
            info1->morph_counter = 0.0f;
        }
        *state1 = cKF_STATE_NONE;
        *state2 = cKF_STATE_NONE;
        *state3 = cKF_STATE_NONE;
    } else {
        cKF_SkeletonInfo_R_morphJoint(info1);
        info1->morph_counter += 0.5f;
        if (info1->morph_counter >= 0.0f) {
            info1->morph_counter = 0.0f;
        }
        *state1 = cKF_FrameControl_play(&info1->frame_control);
        *state2 = cKF_FrameControl_play(&info2->frame_control);
        *state3 = cKF_FrameControl_play(&info3->frame_control);
    }
}

extern void cKF_SkeletonInfo_R_Animation_Set_base_shape_trs(cKF_SkeletonInfo_R_c* keyframe, f32 transx, f32 transy,
                                                            f32 transz, s16 anglex, s16 angley, s16 anglez) {
    keyframe->base_model_translation.x = transx;
    keyframe->base_model_translation.y = transy;
    keyframe->base_model_translation.z = transz;

    keyframe->base_model_rotation.x = anglex;
    keyframe->updated_base_model_rotation.x = anglex;

    keyframe->base_model_rotation.y = angley;
    keyframe->updated_base_model_rotation.y = angley;

    keyframe->base_model_rotation.z = anglez;
    keyframe->updated_base_model_rotation.z = anglez;
}

extern void cKF_SkeletonInfo_R_AnimationMove_ct_base(xyz_t* basepos, xyz_t* correctpos, s16 ybase, s16 yidle,
                                                     f32 counter, cKF_SkeletonInfo_R_c* keyframe, int an_flag) {
    keyframe->animation_enabled = an_flag;
    keyframe->fixed_counter = (counter >= 0.0f) ? counter : -counter;
    keyframe->base_world_position = ZeroVec;
    keyframe->model_world_position_correction = ZeroVec;

    if (basepos != NULL) {
        if (correctpos == NULL) {
            correctpos = basepos;
        }
        if (an_flag & cKF_ANIMATION_TRANS_XZ) {
            keyframe->base_world_position.x = correctpos->x;
            keyframe->base_world_position.z = correctpos->z;
            keyframe->model_world_position_correction.x = basepos->x - correctpos->x;
            keyframe->model_world_position_correction.z = basepos->z - correctpos->z;
        }
        if (an_flag & cKF_ANIMATION_TRANS_Y) {
            keyframe->base_world_position.y = correctpos->y;
            keyframe->model_world_position_correction.y = basepos->y - correctpos->y;
        }
    }
    keyframe->base_angle_y = yidle;
    keyframe->model_angle_correction = 0;

    if (an_flag & cKF_ANIMATION_ROT_Y) {
        int sub = ybase - yidle;

        if (sub > DEG2SHORT_ANGLE2(180.0f)) {
            sub = -(DEG2SHORT_ANGLE2(360.0f) - sub);
        } else if (sub < DEG2SHORT_ANGLE2(-180.0f)) {
            sub += DEG2SHORT_ANGLE2(360.0f);
        }
        keyframe->base_angle_y = yidle;
        keyframe->model_angle_correction = sub;
    }
}

extern void cKF_SkeletonInfo_R_AnimationMove_dt(cKF_SkeletonInfo_R_c* keyframe) {
    int an_flag = keyframe->animation_enabled;
    s_xyz* cur_joint = keyframe->current_joint;

    if (an_flag & cKF_ANIMATION_TRANS_XZ) {
        cur_joint->x = keyframe->base_model_translation.x;
        cur_joint->z = keyframe->base_model_translation.z;
    }
    if (an_flag & cKF_ANIMATION_TRANS_Y) {
        cur_joint->y = keyframe->base_model_translation.y;
    }
    if (an_flag & cKF_ANIMATION_ROT_Y) {
        cur_joint = keyframe->current_joint;
        cur_joint[1].x = keyframe->base_model_rotation.x;
        cur_joint[1].y = keyframe->base_model_rotation.y;
        cur_joint[1].z = keyframe->base_model_rotation.z;
    }
    keyframe->animation_enabled = 0;
}

extern void cKF_SkeletonInfo_R_AnimationMove_base(xyz_t* base, s16* sbase, xyz_t* scale, s16 yidle,
                                                  cKF_SkeletonInfo_R_c* keyframe) {
    f32 fc = keyframe->fixed_counter;
    f32 count = 1.0f + fc;
    int an_flag = keyframe->animation_enabled;
    f32 correct_y;
    f32 mangle_y;
    s16 angley;
    s16 angle_c;
    s_xyz* update_base;
    s16 base_x;
    s_xyz* cur_joint;
    s16 sub;
    f32 trans_x;
    f32 trans_z;
    f32 move_x;
    f32 move_z;
    f32 temp;
    f32 sin, cos;

    if (count > 0.5f) {
        correct_y = 0.5f / count;
    } else {
        correct_y = 0.0f;
    }

    if (an_flag & cKF_ANIMATION_ROT_Y) {
        mangle_y = keyframe->model_angle_correction;
        if (count > 0.5f) {
            keyframe->model_angle_correction -= (s16)(int)(mangle_y * correct_y);
        } else {
            keyframe->model_angle_correction = 0;
        }
    }

    if (count > 0.5f) {
        if (an_flag & cKF_ANIMATION_TRANS_XZ) {
            f32 cx, cz;

            cx = keyframe->model_world_position_correction.x;
            cx *= correct_y;

            cz = keyframe->model_world_position_correction.z;
            cz *= correct_y;

            keyframe->model_world_position_correction.x -= cx;
            keyframe->model_world_position_correction.z -= cz;
        }
        if (an_flag & cKF_ANIMATION_TRANS_Y) {
            f32 cy;

            cy = keyframe->model_world_position_correction.y;
            cy *= correct_y;

            keyframe->model_world_position_correction.y -= cy;
        }
    } else {
        keyframe->model_world_position_correction.x = 0.0f;
        keyframe->model_world_position_correction.y = 0.0f;
        keyframe->model_world_position_correction.z = 0.0f;
    }

    if ((sbase != NULL) && (an_flag & cKF_ANIMATION_ROT_Y)) {
        angley = keyframe->base_angle_y;
        angle_c = keyframe->model_angle_correction;
        base_x = keyframe->base_model_rotation.x;
        update_base = &keyframe->updated_base_model_rotation;
        Matrix_push();
        Matrix_rotateXYZ(keyframe->current_joint[1].x, keyframe->current_joint[1].y, keyframe->current_joint[1].z, MTX_LOAD);
        Matrix_to_rotate2_new(get_Matrix_now(), update_base, MTX_LOAD);
        Matrix_pull();
        *sbase = angley + angle_c + (update_base->x - base_x);
    }

    if (base != NULL) {
        cur_joint = keyframe->current_joint;
        sub = 0;
        if (sbase != NULL) {
            sub = *sbase - yidle;
        }
        if (an_flag & cKF_ANIMATION_TRANS_XZ) {
            f32 move_x, move_z;
            f32 base_x, base_z;
            f32 temp2;
            f32 temp1;

            trans_x = keyframe->base_model_translation.x;
            trans_z = keyframe->base_model_translation.z;

            sin = sin_s(sub);
            cos = cos_s(sub);

            temp1 = (trans_x * cos) + (trans_z * sin);
            move_x = scale->x * (cur_joint->x - temp1);
            temp1 = (-trans_x * sin) + (trans_z * cos);
            move_z = scale->z * (cur_joint->z - temp1);

            sin = sin_s(yidle);
            cos = cos_s(yidle);

            base_x = keyframe->model_world_position_correction.x;
            base_z = keyframe->model_world_position_correction.z;
            temp2 = (move_x * cos) + (move_z * sin);
            base->x = temp2 + (keyframe->base_world_position.x + base_x);
            temp2 = (-move_x * sin) + (move_z * cos);
            base->z = temp2 + (keyframe->base_world_position.z + base_z);
        }
        if (an_flag & cKF_ANIMATION_TRANS_Y) {
            base->y = scale->y * (cur_joint->y - keyframe->base_model_translation.y) +
                      (keyframe->base_world_position.y + keyframe->model_world_position_correction.y);
        }
    }
    count = fc - 0.5f;
    if (count < 0.0f) {
        count = 0.0f;
    }
    keyframe->fixed_counter = count;
}

extern void cKF_SkeletonInfo_R_AnimationMove_CulcTransToWorld(xyz_t* calc_pos, const xyz_t* base_pos, f32 trans_x,
                                                              f32 trans_y, f32 trans_z, s16 angle_y, const xyz_t* scale,
                                                              cKF_SkeletonInfo_R_c* keyframe, int trans_flag) {
    f32 sin, cos;
    f32 j_x, j_z;
    s_xyz* cur_joint = keyframe->current_joint;

    if (trans_flag & cKF_ANIMATION_TRANS_XZ) {
        j_x = cur_joint->x - trans_x;
        j_z = cur_joint->z - trans_z;

        sin = sin_s(angle_y);
        cos = cos_s(angle_y);

        calc_pos->x = base_pos->x + scale->x * ((j_x * cos) + (j_z * sin));
        calc_pos->z = base_pos->z + scale->z * ((-j_x * sin) + (j_z * cos));
    }

    if (trans_flag & cKF_ANIMATION_TRANS_Y) {
        calc_pos->y = base_pos->y + scale->y * (cur_joint->y - trans_y);
    }
}
