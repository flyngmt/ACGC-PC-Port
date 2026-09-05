#include "m_common_data.h"

#include "libultra/libultra.h"

common_data_t common_data;

extern void common_data_reinit(){

    u8 state;

    state = Common_Get(pad_connected);

    bzero(&common_data, sizeof(common_data));
    Common_Set(transition.wipe_type, -1);
    Common_Set(game_started,1);
    Common_Set(last_scene_no, -1);
    Common_Set(demo_profiles[0], mAc_PROFILE_NUM); /* cleared state */
    Common_Set(demo_profiles[1], mAc_PROFILE_NUM); /* cleared state */
    Common_Set(pad_connected, state);

    mFRm_ClearSaveCheckData(Save_GetPointer(save_check));
}

extern void common_data_init(){
    common_data_reinit();
}

extern void common_data_clear(){
    clip_clear();
}
