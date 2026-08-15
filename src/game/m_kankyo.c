#include "m_kankyo.h"

#include "m_camera2.h"
#include "m_room_type.h"
#include "m_scene_table.h"
#include "m_common_data.h"
#include "m_debug.h"
#include "m_npc_schedule.h"
#include "m_player_lib.h"
#include "libultra/libultra.h"

#define mEnv_TIME_TO_SECS(hour, min, sec) ((hour) * mTM_SECONDS_IN_HOUR + (min) * mTM_SECONDS_IN_MINUTE + (sec))

static int klight_chg_tim[mEnv_TERM_NUM + 1] = {
    mEnv_TIME_TO_SECS(0, 0, 0),  mEnv_TIME_TO_SECS(4, 0, 0),  mEnv_TIME_TO_SECS(6, 0, 0),
    mEnv_TIME_TO_SECS(8, 0, 0),  mEnv_TIME_TO_SECS(12, 0, 0), mEnv_TIME_TO_SECS(16, 0, 0),
    mEnv_TIME_TO_SECS(18, 0, 0), mEnv_TIME_TO_SECS(20, 0, 0), mEnv_TIME_TO_SECS(24, 0, 0),
};

static BaseLight l_mEnv_kcolor_fine_data[mEnv_TERM_NUM] = {
    /* 00:00 -> 03:59 */
    {
        { 20, 10, 120 }, // ambient color

        { 73, 73, 73 }, // sun direction
        { 0, 0, 0 },    // sun color

        { 73, 73, 73 },   // moon direction
        { 120, 180, 80 }, // moon color

        { 20, 20, 80 }, // fog color
        1799,           // fog near
        1000,           // fog far

        { 0, 0, 50 },      // shadow color
        { 120, 160, 150 }, // room color
        { 120, 160, 150 }, // window sun color
        { 230, 230, 120 }, // window moon color
        { 28, 32, 92 }     // background color
    },

    {
        { 0, 10, 120 }, // ambient color

        { 73, 73, 73 }, // sun direction
        { 0, 20, 40 },  // sun color

        { 73, 73, 73 },    // moon direction
        { 150, 200, 100 }, // moon color

        { 80, 100, 120 }, // fog color
        1774,             // fog near
        1000,             // fog far

        { 0, 0, 60 },      // shadow color
        { 140, 190, 190 }, // room color
        { 150, 170, 170 }, // window sun color
        { 230, 230, 120 }, // window moon color
        { 44, 52, 112 }    // background color
    },

    {
        { 60, 60, 120 }, // ambient color

        { 73, 73, 73 },    // sun direction
        { 255, 255, 200 }, // sun color

        { 73, 73, 73 }, // moon direction
        { 10, 40, 60 }, // moon color

        { 120, 150, 150 }, // fog color
        1749,              // fog near
        950,               // fog far

        { 0, 10, 70 },     // shadow color
        { 180, 210, 210 }, // room color
        { 160, 180, 180 }, // window sun color
        { 230, 230, 120 }, // window moon color
        { 60, 76, 120 }    // background color
    },

    {
        { 80, 80, 150 }, // ambient color

        { 73, 73, 73 },    // sun direction
        { 180, 220, 220 }, // sun color

        { 73, 73, 73 }, // moon direction
        { 0, 10, 20 },  // moon color

        { 80, 120, 150 }, // fog color
        1749,             // fog near
        1000,             // fog far

        { 0, 20, 70 },     // shadow color
        { 210, 240, 240 }, // room color
        { 190, 220, 220 }, // window sun color
        { 230, 230, 120 }, // window moon color
        { 56, 72, 140 }    // background color
    },

    {
        { 80, 80, 150 }, // ambient color

        { 73, 73, 73 },    // sun direction
        { 200, 240, 240 }, // sun color

        { 73, 73, 73 }, // moon direction
        { 0, 0, 0 },    // moon color

        { 80, 120, 150 }, // fog color
        1749,             // fog near
        1000,             // fog far

        { 0, 30, 70 },     // shadow color
        { 220, 250, 250 }, // room color
        { 210, 240, 240 }, // window sun color
        { 230, 230, 120 }, // window moon color
        { 52, 78, 144 }    // background color
    },

    {
        { 80, 80, 150 }, // ambient color

        { 73, 73, 73 },    // sun direction
        { 200, 240, 240 }, // sun color

        { 73, 73, 73 }, // moon direction
        { 10, 0, 30 },  // moon color

        { 80, 120, 150 }, // fog color
        1749,             // fog near
        1000,             // fog far

        { 0, 30, 90 },     // shadow color
        { 220, 250, 250 }, // room color
        { 220, 240, 240 }, // window sun color
        { 230, 230, 120 }, // window moon color
        { 48, 72, 140 }    // background color
    },

    {
        { 60, 60, 150 }, // ambient color

        { 73, 73, 73 },  // sun direction
        { 200, 120, 0 }, // sun color

        { 73, 73, 73 }, // moon direction
        { 20, 0, 80 },  // moon color

        { 20, 20, 80 }, // fog color
        1774,           // fog near
        1000,           // fog far

        { 0, 10, 70 },     // shadow color
        { 190, 120, 120 }, // room color
        { 180, 120, 120 }, // window sun color
        { 230, 230, 120 }, // window moon color
        { 32, 32, 92 }     // background color
    },

    {
        { 30, 30, 120 }, // ambient color

        { 73, 73, 73 }, // sun direction
        { 60, 60, 0 },  // sun color

        { 73, 73, 73 },   // moon direction
        { 120, 180, 80 }, // moon color

        { 20, 20, 80 }, // fog color
        1774,           // fog near
        1000,           // fog far

        { 0, 0, 60 },      // shadow color
        { 130, 160, 160 }, // room color
        { 180, 120, 120 }, // window sun color
        { 230, 230, 120 }, // window moon color
        { 28, 28, 92 }     // background color
    }
};

static BaseLight l_mEnv_kcolor_insect_fine_data[mEnv_TERM_NUM] = { {
                                                                       { 12, 6, 72 }, // ambient color

                                                                       { 73, 73, 73 }, // sun direction
                                                                       { 0, 0, 0 },    // sun color

                                                                       { 73, 73, 73 },  // moon direction
                                                                       { 72, 108, 48 }, // moon color

                                                                       { 20, 20, 80 }, // fog color
                                                                       1799,           // fog near
                                                                       1000,           // fog far

                                                                       { 0, 0, 50 },      // shadow color
                                                                       { 72, 96, 90 },    // room color
                                                                       { 120, 160, 150 }, // window sun color
                                                                       { 230, 230, 120 }, // window moon color
                                                                       { 28, 32, 92 }     // background color
                                                                   },

                                                                   {
                                                                       { 0, 6, 72 }, // ambient color

                                                                       { 73, 73, 73 }, // sun direction
                                                                       { 0, 12, 24 },  // sun color

                                                                       { 73, 73, 73 },  // moon direction
                                                                       { 90, 120, 60 }, // moon color

                                                                       { 80, 100, 120 }, // fog color
                                                                       1774,             // fog near
                                                                       1000,             // fog far

                                                                       { 0, 0, 60 },      // shadow color
                                                                       { 84, 114, 114 },  // room color
                                                                       { 150, 170, 170 }, // window sun color
                                                                       { 230, 230, 120 }, // window moon color
                                                                       { 44, 52, 112 }    // background color
                                                                   },

                                                                   {
                                                                       { 36, 36, 72 }, // ambient color

                                                                       { 73, 73, 73 },    // sun direction
                                                                       { 153, 153, 120 }, // sun color

                                                                       { 73, 73, 73 }, // moon direction
                                                                       { 6, 24, 36 },  // moon color

                                                                       { 120, 150, 150 }, // fog color
                                                                       1749,              // fog near
                                                                       950,               // fog far

                                                                       { 0, 10, 70 },     // shadow color
                                                                       { 108, 126, 126 }, // room color
                                                                       { 160, 180, 180 }, // window sun color
                                                                       { 230, 230, 120 }, // window moon color
                                                                       { 60, 76, 120 }    // background color
                                                                   },

                                                                   {
                                                                       { 80, 80, 150 }, // ambient color

                                                                       { 73, 73, 73 },    // sun direction
                                                                       { 180, 220, 220 }, // sun color

                                                                       { 73, 73, 73 }, // moon direction
                                                                       { 0, 10, 20 },  // moon color

                                                                       { 80, 120, 150 }, // fog color
                                                                       1749,             // fog near
                                                                       1000,             // fog far

                                                                       { 0, 20, 70 },     // shadow color
                                                                       { 210, 240, 240 }, // room color
                                                                       { 190, 220, 220 }, // window sun color
                                                                       { 230, 230, 120 }, // window moon color
                                                                       { 56, 72, 140 }    // background color
                                                                   },

                                                                   {
                                                                       { 80, 80, 150 }, // ambient color

                                                                       { 73, 73, 73 },    // sun direction
                                                                       { 200, 240, 240 }, // sun color

                                                                       { 73, 73, 73 }, // moon direction
                                                                       { 0, 0, 0 },    // moon color

                                                                       { 80, 120, 150 }, // fog color
                                                                       1749,             // fog near
                                                                       1000,             // fog far

                                                                       { 0, 30, 70 },     // shadow color
                                                                       { 220, 250, 250 }, // room color
                                                                       { 210, 240, 240 }, // window sun color
                                                                       { 230, 230, 120 }, // window moon color
                                                                       { 52, 78, 144 }    // background color
                                                                   },

                                                                   {
                                                                       { 80, 80, 150 }, // ambient color

                                                                       { 73, 73, 73 },    // sun direction
                                                                       { 200, 240, 240 }, // sun color

                                                                       { 73, 73, 73 }, // moon direction
                                                                       { 10, 0, 30 },  // moon color

                                                                       { 80, 120, 150 }, // fog color
                                                                       1749,             // fog near
                                                                       1000,             // fog far

                                                                       { 0, 30, 90 },     // shadow color
                                                                       { 220, 250, 250 }, // room color
                                                                       { 220, 240, 240 }, // window sun color
                                                                       { 230, 230, 120 }, // window moon color
                                                                       { 48, 72, 140 }    // background color
                                                                   },

                                                                   {
                                                                       { 36, 36, 90 }, // ambient color

                                                                       { 73, 73, 73 }, // sun direction
                                                                       { 120, 72, 0 }, // sun color

                                                                       { 73, 73, 73 }, // moon direction
                                                                       { 12, 0, 48 },  // moon color

                                                                       { 20, 20, 80 }, // fog color
                                                                       1774,           // fog near
                                                                       1000,           // fog far

                                                                       { 0, 10, 70 },     // shadow color
                                                                       { 114, 72, 72 },   // room color
                                                                       { 180, 120, 120 }, // window sun color
                                                                       { 230, 230, 120 }, // window moon color
                                                                       { 32, 32, 92 }     // background color
                                                                   },

                                                                   {
                                                                       { 18, 18, 72 }, // ambient color

                                                                       { 73, 73, 73 }, // sun direction
                                                                       { 36, 36, 0 },  // sun color

                                                                       { 73, 73, 73 },  // moon direction
                                                                       { 72, 108, 48 }, // moon color

                                                                       { 20, 20, 80 }, // fog color
                                                                       1774,           // fog near
                                                                       1000,           // fog far

                                                                       { 0, 0, 60 },      // shadow color
                                                                       { 78, 96, 96 },    // room color
                                                                       { 180, 120, 120 }, // window sun color
                                                                       { 230, 230, 120 }, // window moon color
                                                                       { 28, 28, 92 }     // background color
                                                                   } };

static BaseLight l_mEnv_kcolor_rain_data[mEnv_TERM_NUM] = { {
                                                                { 18, 9, 108 }, // ambient color

                                                                { 73, 73, 73 }, // sun direction
                                                                { 0, 0, 0 },    // sun color

                                                                { 73, 73, 73 },   // moon direction
                                                                { 108, 162, 72 }, // moon color

                                                                { 20, 20, 80 }, // fog color
                                                                1799,           // fog near
                                                                1000,           // fog far

                                                                { 0, 0, 50 },      // shadow color
                                                                { 108, 144, 135 }, // room color
                                                                { 120, 160, 150 }, // window sun color
                                                                { 230, 230, 120 }, // window moon color
                                                                { 28, 32, 92 }     // background color
                                                            },

                                                            {
                                                                { 0, 9, 108 }, // ambient color

                                                                { 73, 73, 73 }, // sun direction
                                                                { 0, 18, 36 },  // sun color

                                                                { 73, 73, 73 },   // moon direction
                                                                { 135, 180, 90 }, // moon color

                                                                { 80, 100, 120 }, // fog color
                                                                1774,             // fog near
                                                                1000,             // fog far

                                                                { 0, 0, 60 },      // shadow color
                                                                { 126, 171, 171 }, // room color
                                                                { 150, 170, 170 }, // window sun color
                                                                { 230, 230, 120 }, // window moon color
                                                                { 44, 52, 112 }    // background color
                                                            },

                                                            {
                                                                { 54, 54, 108 }, // ambient color

                                                                { 73, 73, 73 },    // sun direction
                                                                { 229, 229, 180 }, // sun color

                                                                { 73, 73, 73 }, // moon direction
                                                                { 9, 36, 54 },  // moon color

                                                                { 120, 150, 150 }, // fog color
                                                                1749,              // fog near
                                                                950,               // fog far

                                                                { 0, 10, 70 },     // shadow color
                                                                { 162, 189, 189 }, // room color
                                                                { 160, 180, 180 }, // window sun color
                                                                { 230, 230, 120 }, // window moon color
                                                                { 60, 76, 120 }    // background color
                                                            },

                                                            {
                                                                { 72, 72, 135 }, // ambient color

                                                                { 73, 73, 73 },    // sun direction
                                                                { 162, 198, 198 }, // sun color

                                                                { 73, 73, 73 }, // moon direction
                                                                { 0, 9, 18 },   // moon color

                                                                { 80, 120, 150 }, // fog color
                                                                1749,             // fog near
                                                                1000,             // fog far

                                                                { 0, 20, 70 },     // shadow color
                                                                { 189, 216, 216 }, // room color
                                                                { 190, 220, 220 }, // window sun color
                                                                { 230, 230, 120 }, // window moon color
                                                                { 56, 72, 140 }    // background color
                                                            },

                                                            {
                                                                { 72, 72, 135 }, // ambient color

                                                                { 73, 73, 73 },    // sun direction
                                                                { 180, 216, 216 }, // sun color

                                                                { 73, 73, 73 }, // moon direction
                                                                { 0, 0, 0 },    // moon color

                                                                { 80, 120, 150 }, // fog color
                                                                1749,             // fog near
                                                                1000,             // fog far

                                                                { 0, 30, 70 },     // shadow color
                                                                { 198, 225, 225 }, // room color
                                                                { 210, 240, 240 }, // window sun color
                                                                { 230, 230, 120 }, // window moon color
                                                                { 52, 78, 144 }    // background color
                                                            },

                                                            {
                                                                { 72, 72, 135 }, // ambient color

                                                                { 73, 73, 73 },    // sun direction
                                                                { 180, 216, 216 }, // sun color

                                                                { 73, 73, 73 }, // moon direction
                                                                { 9, 0, 27 },   // moon color

                                                                { 80, 120, 150 }, // fog color
                                                                1749,             // fog near
                                                                1000,             // fog far

                                                                { 0, 30, 90 },     // shadow color
                                                                { 198, 225, 225 }, // room color
                                                                { 220, 240, 240 }, // window sun color
                                                                { 230, 230, 120 }, // window moon color
                                                                { 48, 72, 140 }    // background color
                                                            },

                                                            {
                                                                { 54, 54, 135 }, // ambient color

                                                                { 73, 73, 73 },  // sun direction
                                                                { 180, 108, 0 }, // sun color

                                                                { 73, 73, 73 }, // moon direction
                                                                { 18, 0, 72 },  // moon color

                                                                { 20, 20, 80 }, // fog color
                                                                1774,           // fog near
                                                                1000,           // fog far

                                                                { 0, 10, 70 },     // shadow color
                                                                { 171, 108, 108 }, // room color
                                                                { 180, 120, 120 }, // window sun color
                                                                { 230, 230, 120 }, // window moon color
                                                                { 32, 32, 92 }     // background color
                                                            },

                                                            {
                                                                { 27, 27, 108 }, // ambient color

                                                                { 73, 73, 73 }, // sun direction
                                                                { 54, 54, 0 },  // sun color

                                                                { 73, 73, 73 },   // moon direction
                                                                { 108, 162, 72 }, // moon color

                                                                { 20, 20, 80 }, // fog color
                                                                1774,           // fog near
                                                                1000,           // fog far

                                                                { 0, 0, 60 },      // shadow color
                                                                { 117, 144, 144 }, // room color
                                                                { 180, 120, 120 }, // window sun color
                                                                { 230, 230, 120 }, // window moon color
                                                                { 28, 28, 92 }     // background color
                                                            } };

static BaseLight l_mEnv_kcolor_insect_rain_data[mEnv_TERM_NUM] = { {
                                                                       { 10, 5, 64 }, // ambient color

                                                                       { 73, 73, 73 }, // sun direction
                                                                       { 0, 0, 0 },    // sun color

                                                                       { 73, 73, 73 }, // moon direction
                                                                       { 64, 97, 43 }, // moon color

                                                                       { 20, 20, 80 }, // fog color
                                                                       1799,           // fog near
                                                                       1000,           // fog far

                                                                       { 0, 0, 50 },      // shadow color
                                                                       { 64, 86, 81 },    // room color
                                                                       { 120, 160, 150 }, // window sun color
                                                                       { 230, 230, 120 }, // window moon color
                                                                       { 28, 32, 92 }     // background color
                                                                   },

                                                                   {
                                                                       { 0, 5, 64 }, // ambient color

                                                                       { 73, 73, 73 }, // sun direction
                                                                       { 0, 10, 21 },  // sun color

                                                                       { 73, 73, 73 },  // moon direction
                                                                       { 81, 108, 54 }, // moon color

                                                                       { 80, 100, 120 }, // fog color
                                                                       1774,             // fog near
                                                                       1000,             // fog far

                                                                       { 0, 0, 60 },      // shadow color
                                                                       { 75, 102, 102 },  // room color
                                                                       { 150, 170, 170 }, // window sun color
                                                                       { 230, 230, 120 }, // window moon color
                                                                       { 44, 52, 112 }    // background color
                                                                   },

                                                                   {
                                                                       { 32, 32, 64 }, // ambient color

                                                                       { 73, 73, 73 },    // sun direction
                                                                       { 137, 137, 108 }, // sun color

                                                                       { 73, 73, 73 }, // moon direction
                                                                       { 5, 21, 32 },  // moon color

                                                                       { 120, 150, 150 }, // fog color
                                                                       1749,              // fog near
                                                                       950,               // fog far

                                                                       { 0, 10, 70 },     // shadow color
                                                                       { 97, 113, 113 },  // room color
                                                                       { 160, 180, 180 }, // window sun color
                                                                       { 230, 230, 120 }, // window moon color
                                                                       { 60, 76, 120 }    // background color
                                                                   },

                                                                   {
                                                                       { 72, 72, 135 }, // ambient color

                                                                       { 73, 73, 73 },    // sun direction
                                                                       { 162, 198, 198 }, // sun color

                                                                       { 73, 73, 73 }, // moon direction
                                                                       { 0, 9, 18 },   // moon color

                                                                       { 80, 120, 150 }, // fog color
                                                                       1749,             // fog near
                                                                       1000,             // fog far

                                                                       { 0, 20, 70 },     // shadow color
                                                                       { 189, 216, 216 }, // room color
                                                                       { 190, 220, 220 }, // window sun color
                                                                       { 230, 230, 120 }, // window moon color
                                                                       { 56, 72, 140 }    // background color
                                                                   },

                                                                   {
                                                                       { 72, 72, 135 }, // ambient color

                                                                       { 73, 73, 73 },    // sun direction
                                                                       { 180, 216, 216 }, // sun color

                                                                       { 73, 73, 73 }, // moon direction
                                                                       { 0, 0, 0 },    // moon color

                                                                       { 80, 120, 150 }, // fog color
                                                                       1749,             // fog near
                                                                       1000,             // fog far

                                                                       { 0, 30, 70 },     // shadow color
                                                                       { 198, 225, 225 }, // room color
                                                                       { 210, 240, 240 }, // window sun color
                                                                       { 230, 230, 120 }, // window moon color
                                                                       { 52, 78, 144 }    // background color
                                                                   },

                                                                   {
                                                                       { 72, 72, 135 }, // ambient color

                                                                       { 73, 73, 73 },    // sun direction
                                                                       { 180, 216, 216 }, // sun color

                                                                       { 73, 73, 73 }, // moon direction
                                                                       { 9, 0, 27 },   // moon color

                                                                       { 80, 120, 150 }, // fog color
                                                                       1749,             // fog near
                                                                       1000,             // fog far

                                                                       { 0, 30, 90 },     // shadow color
                                                                       { 198, 225, 225 }, // room color
                                                                       { 220, 240, 240 }, // window sun color
                                                                       { 230, 230, 120 }, // window moon color
                                                                       { 48, 72, 140 }    // background color
                                                                   },

                                                                   {
                                                                       { 32, 32, 81 }, // ambient color

                                                                       { 73, 73, 73 }, // sun direction
                                                                       { 108, 64, 0 }, // sun color

                                                                       { 73, 73, 73 }, // moon direction
                                                                       { 10, 0, 43 },  // moon color

                                                                       { 20, 20, 80 }, // fog color
                                                                       1774,           // fog near
                                                                       1000,           // fog far

                                                                       { 0, 10, 70 },     // shadow color
                                                                       { 102, 64, 64 },   // room color
                                                                       { 180, 120, 120 }, // window sun color
                                                                       { 230, 230, 120 }, // window moon color
                                                                       { 32, 32, 92 }     // background color
                                                                   },

                                                                   {
                                                                       { 16, 16, 64 }, // ambient color

                                                                       { 73, 73, 73 }, // sun direction
                                                                       { 32, 32, 0 },  // sun color

                                                                       { 73, 73, 73 }, // moon direction
                                                                       { 64, 97, 43 }, // moon color

                                                                       { 20, 20, 80 }, // fog color
                                                                       1774,           // fog near
                                                                       1000,           // fog far

                                                                       { 0, 0, 60 },      // shadow color
                                                                       { 70, 86, 86 },    // room color
                                                                       { 180, 120, 120 }, // window sun color
                                                                       { 230, 230, 120 }, // window moon color
                                                                       { 28, 28, 92 }     // background color
                                                                   } };

static BaseLight l_mEnv_kcolor_data_p_sel = {
    { 30, 30, 80 }, // ambient color

    { 0, 89, 79 },     // sun direction
    { 255, 255, 200 }, // sun color

    { 0, 185, 160 }, // moon direction
    { 0, 0, 0 },     // moon color

    { 100, 100, 120 }, // fog color
    2000,              // fog near
    1280,              // fog far

    { 0, 30, 70 },     // shadow color
    { 255, 255, 255 }, // room color
    { 0, 0, 0 },       // window sun color
    { 0, 0, 0 },       // window moon color
    { 22, 27, 94 }     // background color
};

static BaseLight l_mEnv_kcolor_shop = {
    { 20, 10, 100 }, // ambient color

    { 0, 69, 97 },     // sun direction
    { 150, 160, 130 }, // sun color

    { 0, 223, 115 }, // moon direction
    { 50, 40, 20 },  // moon color

    { 100, 100, 120 }, // fog color
    2000,              // fog near
    1280,              // fog far

    { 0, 30, 70 },     // shadow color
    { 255, 255, 255 }, // room color
    { 0, 0, 0 },       // window sun color
    { 0, 0, 0 },       // window moon color
    { 22, 27, 94 }     // background color
};

static BaseLight l_mEnv_kcolor_buggy = {
    { 30, 30, 30 }, // ambient color

    { 0, 69, 97 }, // sun direction
    { 0, 0, 0 },   // sun color

    { 0, 223, 115 }, // moon direction
    { 0, 60, 90 },   // moon color

    { 100, 100, 120 }, // fog color
    2000,              // fog near
    1280,              // fog far

    { 0, 20, 30 },     // shadow color
    { 175, 175, 155 }, // room color
    { 0, 0, 0 },       // window sun color
    { 0, 0, 0 },       // window moon color
    { 22, 27, 94 }     // background color
};

static BaseLight l_mEnv_kcolor_broker = {
    { 20, 30, 40 }, // ambient color

    { 0, 69, 97 },   // sun direction
    { 100, 80, 80 }, // sun color

    { 0, 223, 115 }, // moon direction
    { 20, 10, 0 },   // moon color

    { 100, 100, 120 }, // fog color
    2000,              // fog near
    1280,              // fog far

    { 0, 0, 20 },      // shadow color
    { 140, 120, 120 }, // room color
    { 0, 0, 0 },       // window sun color
    { 0, 0, 0 },       // window moon color
    { 22, 27, 94 }     // background color
};

static BaseLight l_mEnv_kcolor_kamakura = {
    { 50, 25, 20 }, // ambient color

    { 0, 69, 97 }, // sun direction
    { 50, 40, 5 }, // sun color

    { 0, 223, 115 }, // moon direction
    { 50, 80, 85 },  // moon color

    { 100, 100, 120 }, // fog color
    2000,              // fog near
    1280,              // fog far

    { 40, 50, 80 },    // shadow color
    { 250, 240, 160 }, // room color
    { 0, 0, 0 },       // window sun color
    { 0, 0, 0 },       // window moon color
    { 22, 27, 94 }     // background color
};

static BaseLight l_mEnv_kcolor_museum_fossil = {
    { 50, 50, 60 }, // ambient color

    { 0, 69, 97 },  // sun direction
    { 60, 60, 80 }, // sun color

    { 0, 223, 115 }, // moon direction
    { 20, 10, 0 },   // moon color

    { 0, 0, 0 }, // fog color
    2000,        // fog near
    1280,        // fog far

    { 0, 10, 60 },     // shadow color
    { 255, 255, 255 }, // room color
    { 0, 0, 0 },       // window sun color
    { 0, 0, 0 },       // window moon color
    { 22, 27, 94 }     // background color
};

static BaseLight l_mEnv_kcolor_museum_fish = {
    { 40, 50, 60 }, // ambient color

    { 0, 69, 97 },  // sun direction
    { 20, 30, 40 }, // sun color

    { 0, 223, 115 }, // moon direction
    { 0, 10, 20 },   // moon color

    { 0, 0, 0 }, // fog color
    2000,        // fog near
    1280,        // fog far

    { 0, 20, 30 },    // shadow color
    { 120, 90, 100 }, // room color
    { 0, 0, 0 },      // window sun color
    { 0, 0, 0 },      // window moon color
    { 22, 27, 94 }    // background color
};

static BaseLight l_mEnv_kcolor_museum_picture = {
    { 30, 30, 60 }, // ambient color

    { 0, 69, 97 },    // sun direction
    { 120, 100, 80 }, // sun color

    { 0, 223, 115 }, // moon direction
    { 0, 10, 20 },   // moon color

    { 0, 0, 0 }, // fog color
    2000,        // fog near
    1280,        // fog far

    { 0, 10, 50 },     // shadow color
    { 255, 255, 255 }, // room color
    { 0, 0, 0 },       // window sun color
    { 0, 0, 0 },       // window moon color
    { 22, 27, 94 }     // background color
};

static BaseLight l_mEnv_kcolor_basement = {
    { 35, 30, 25 }, // ambient color

    { 0, 69, 97 }, // sun direction
    { 0, 0, 0 },   // sun color

    { 0, 223, 115 }, // moon direction
    { 0, 0, 0 },     // moon color

    { 0, 0, 0 }, // fog color
    2000,        // fog near
    1280,        // fog far

    { 0, 5, 10 },   // shadow color
    { 53, 53, 33 }, // room color
    { 0, 0, 0 },    // window sun color
    { 0, 0, 0 },    // window moon color
    { 22, 27, 94 }  // background color
};

static BaseLight l_mEnv_kcolor_lighthouse = {
    { 35, 30, 25 }, // ambient color

    { 0, 69, 97 }, // sun direction
    { 0, 0, 0 },   // sun color

    { 0, 223, 115 }, // moon direction
    { 0, 0, 0 },     // moon color

    { 0, 0, 0 }, // fog color
    2000,        // fog near
    1280,        // fog far

    { 0, 20, 30 },     // shadow color
    { 135, 125, 105 }, // room color
    { 0, 0, 0 },       // window sun color
    { 0, 0, 0 },       // window moon color
    { 0, 0, 0 }        // background color
};

static BaseLight* l_mEnv_normal_kcolor_data[4] = {
    l_mEnv_kcolor_fine_data, /* clear */
    l_mEnv_kcolor_rain_data, /* rain */
    l_mEnv_kcolor_rain_data, /* snow */
    l_mEnv_kcolor_fine_data  /* cherry blossoms */
};

static BaseLight* l_mEnv_normal_kcolor_insect_data[4] = {
    l_mEnv_kcolor_insect_fine_data, /* clear */
    l_mEnv_kcolor_insect_rain_data, /* rain */
    l_mEnv_kcolor_insect_rain_data, /* snow */
    l_mEnv_kcolor_insect_fine_data  /* cherry blossoms */
};

typedef struct electric_light_s {
    f32 point_light_percent;
    u8 point_light_color[3];
    s16 _08;
    s16 now_weather;
    s16 next_weather;
    f32 change_weather_env_rate;
    s16 light_animating_on;
    s16 light_anime_frame;
    f32 light_anime_accum;
    int point_light_on_type;
    int point_light_off_type;
    f32 point_light_off_step;
    s16 point_light_is_flame; /* flickering effect when non-zero */
    f32 staffroll_fade_rate;
    f32 sun_percent;
    f32 shadow_adjust;
    f32 windowlight_alpha;
    Light_list* current_point_light;
    s16 add_moon_color[3];
    Light_list* point_light_list_buf[mEnv_POINT_LIGHT_NUM];
    Lights point_lights[mEnv_POINT_LIGHT_NUM];
    int switch_status;
    f32 point_light_min;
    f32 diffuse_light_effect_rate;
    s16 _98;
    s16 shadow_alpha;
    f32 diffuse_adjust;
    u8 shadow_alpha_adjust;
} mEnv_electric_light_c;

static mEnv_electric_light_c l_mEnv_electric_light;

static int mEnv_CheckNpcRoomPointLightNiceStatus();
static void mEnv_set_time(Kankyo* kankyo);
static void mEnv_MakeWindowLightAlpha(int enabled);
static void mEnv_InitWind();
static int mEnv_Pointlight_on_check();

static f32 mEnv_DiffuseLightEffectRate() {
    if (mRmTp_GetNowSceneLightSwitchIndex() != -1) {
        if (!mSc_IS_SCENE_BASEMENT(Save_Get(scene_no)) && Save_Get(scene_no) != SCENE_LIGHTHOUSE &&
            Save_Get(scene_no) != SCENE_TENT) {
            return 0.7f;
        }
    }
    return l_mEnv_electric_light.diffuse_light_effect_rate;
}

#include "../src/game/m_kankyo_weather.c_inc"

extern void mEnv_regist_nature(Kankyo* kankyo, NATURE_PROC nature_proc, void* arg) {
    kankyo->nature.proc = nature_proc;
    kankyo->nature.arg = arg;
}

extern int mEnv_unregist_nature(Kankyo* kankyo, NATURE_PROC nature_proc) {
    int res = FALSE;

    if (nature_proc == kankyo->nature.proc) {
        mEnv_regist_nature(kankyo, (NATURE_PROC)&none_proc1, NULL);
        res = TRUE;
    }

    return res;
}

static int mEnv_GetNowRoomPointLightInfo(GAME_PLAY* play, s_xyz* pos, u8* color, s16* power, s16* is_flame) {
    int res = TRUE;

    switch (Common_Get(field_draw_type)) {
        case FIELD_DRAW_TYPE_INDOORS: {
            color[0] = 160; // r
            color[1] = 160; // g
            color[2] = 160; // b
            power[0] = 1000;

            switch (Save_Get(scene_no)) {
                case SCENE_MY_ROOM_S: {
                    color[0] = 220; // r
                    color[1] = 220; // g
                    color[2] = 200; // b

                    pos->x = 120;
                    pos->y = 180;
                    pos->z = 180;

                    break;
                }

                case SCENE_MY_ROOM_M:
                case SCENE_MY_ROOM_LL2: {
                    color[0] = 220; // r
                    color[1] = 220; // g
                    color[2] = 200; // b

                    pos->x = 160;
                    pos->y = 180;
                    pos->z = 240;

                    break;
                }

                case SCENE_SHOP0:
                case SCENE_POST_OFFICE: {
                    color[0] = 220; // r
                    color[1] = 220; // g
                    color[2] = 200; // b

                    pos->x = 160;
                    pos->y = 180;
                    pos->z = 240;

                    break;
                }

                case SCENE_NPC_HOUSE:
                case SCENE_COTTAGE_NPC: {
                    pos->x = 160;
                    pos->y = 180;
                    pos->z = 240;

                    color[0] = 220; // r
                    color[1] = 220; // g
                    color[2] = 200; // b

                    break;
                }

                case SCENE_BUGGY: {
                    pos->x = 160;
                    pos->y = 80;
                    pos->z = 200;

                    color[0] = 205; // r
                    color[1] = 165; // g
                    color[2] = 110; // b

                    power[0] = 155;
                    is_flame[0] = TRUE;

                    break;
                }

                case SCENE_MY_ROOM_BASEMENT_S:
                case SCENE_MY_ROOM_BASEMENT_M:
                case SCENE_MY_ROOM_BASEMENT_L:
                case SCENE_MY_ROOM_BASEMENT_LL1: {
                    color[0] = 220; // r
                    color[1] = 190; // g
                    color[2] = 190; // b

                    pos->x = 200;
                    pos->y = 220;
                    pos->z = 300;

                    break;
                }

                case SCENE_MY_ROOM_L:
                case SCENE_MY_ROOM_LL1:
                case SCENE_COTTAGE_MY: {
                    color[0] = 220; // r
                    color[1] = 220; // g
                    color[2] = 200; // b

                    pos->x = 200;
                    pos->y = 220;
                    pos->z = 300;

                    break;
                }

                case SCENE_POLICE_BOX: {
                    color[0] = 220; // r
                    color[1] = 220; // g
                    color[2] = 200; // b

                    pos->x = 200;
                    pos->y = 220;
                    pos->z = 300;

                    break;
                }

                case SCENE_KAMAKURA: {
                    pos->x = 160;
                    pos->y = 80;
                    pos->z = 38;

                    color[0] = 250; // r
                    color[1] = 240; // g
                    color[2] = 120; // b

                    power[0] = 300;
                    is_flame[0] = TRUE;

                    break;
                }

                case SCENE_MUSEUM_ENTRANCE: {
                    color[0] = 220; // r
                    color[1] = 220; // g
                    color[2] = 200; // b

                    pos->x = 240;
                    pos->y = 220;
                    pos->z = 280;

                    break;
                }

                case SCENE_MUSEUM_ROOM_PAINTING: {
                    color[0] = 180; // r
                    color[1] = 180; // g
                    color[2] = 150; // b

                    pos->x = 320;
                    pos->y = 220;
                    pos->z = 280;

                    power[0] = 800;

                    break;
                }

                case SCENE_MUSEUM_ROOM_FOSSIL: {
                    color[0] = 200; // r
                    color[1] = 200; // g
                    color[2] = 180; // b

                    pos->x = 320;
                    pos->y = 220;
                    pos->z = 280;

                    power[0] = 800;

                    break;
                }

                case SCENE_MUSEUM_ROOM_INSECT: {
                    color[0] = 50; // r
                    color[1] = 50; // g
                    color[2] = 50; // b

                    pos->x = 280;
                    pos->y = 220;
                    pos->z = 320;

                    break;
                }

                case SCENE_MUSEUM_ROOM_FISH: {
                    pos->x = 320;
                    pos->y = 220;
                    pos->z = 320;

                    color[0] = 100; // r
                    color[1] = 120; // g
                    color[2] = 130; // b

                    break;
                }

                case SCENE_NEEDLEWORK: {
                    color[0] = 220; // r
                    color[1] = 220; // g
                    color[2] = 200; // b

                    pos->x = 200;
                    pos->y = 160;
                    pos->z = 280;

                    break;
                }

                case SCENE_LIGHTHOUSE: {
                    pos->x = 120;
                    pos->y = 80;
                    pos->z = 160;

                    color[0] = 235; // r
                    color[1] = 190; // g
                    color[2] = 185; // b

                    power[0] = 6000;

                    break;
                }

                case SCENE_TENT: {
                    pos->x = 120;
                    pos->y = 80;
                    pos->z = 120;

                    color[0] = 235; // r
                    color[1] = 190; // g
                    color[2] = 185; // b

                    power[0] = 6000;

                    break;
                }

                case SCENE_BROKER_SHOP: {
                    color[0] = 170; // r
                    color[1] = 170; // g
                    color[2] = 160; // b

                    pos->x = 250;
                    pos->y = 1000;
                    pos->z = 378;

                    power[0] = 8000;

                    break;
                }

                default: {
                    pos->x = 250;
                    pos->y = 1000;
                    pos->z = 378;

                    power[0] = 8000;

                    break;
                }
            }

            break;
        }

        case FIELD_DRAW_TYPE_TRAIN: {
            switch (Save_Get(scene_no)) {
                case SCENE_START_DEMO:
                case SCENE_START_DEMO3: {
                    Common_Set(sunlight_flag, FALSE);

                    break;
                }
            }

            l_mEnv_electric_light.sun_percent = 0.0f;

            pos->x = 80;
            pos->y = 120;
            pos->z = 510;

            color[0] = 255;
            color[1] = 255;
            color[2] = 160;

            power[0] = 1200;

            break;
        }

        default:
            res = FALSE;
            break;
    }

    return res;
}

static void mEnv_RoomTypePointLightSet(GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    s_xyz pos;
    u8 color[3];
    s16 power;
    int light_switch;

    if (Save_Get(scene_no) == SCENE_TITLE_DEMO) {
        mRmTp_SetDefaultLightSwitchData(FALSE);
        mRmTp_IndexLightSwitchOFF(mRmTp_LIGHT_SWITCH_9);
    } else if (Save_Get(scene_no) == SCENE_NPC_HOUSE || Save_Get(scene_no) == SCENE_COTTAGE_NPC) {
        if (mEnv_CheckNpcRoomPointLightNiceStatus() == FALSE) {
            mRmTp_IndexLightSwitchOFF(mRmTp_LIGHT_SWITCH_NPC);
        } else {
            mRmTp_IndexLightSwitchON(mRmTp_LIGHT_SWITCH_NPC);
        }
    }

    l_mEnv_electric_light.point_light_is_flame = FALSE;
    l_mEnv_electric_light.point_light_percent = 0.0f;

    if (mEnv_GetNowRoomPointLightInfo(play, &pos, color, &power, &l_mEnv_electric_light.point_light_is_flame) == TRUE) {
        Light_point_ct(&play->kankyo.point_light, pos.x, pos.y, pos.z, color[0], color[1], color[2], power);
        l_mEnv_electric_light.point_light_color[0] = color[0];
        l_mEnv_electric_light.point_light_color[1] = color[1];
        l_mEnv_electric_light.point_light_color[2] = color[2];
        l_mEnv_electric_light.current_point_light =
            Global_light_list_new(game, &play->global_light, &play->kankyo.point_light);

        light_switch = mRmTp_GetNowSceneLightSwitchIndex();

        if (light_switch != -1) {
            int switch_status = mRmTp_Index2LightSwitchStatus(light_switch);

            l_mEnv_electric_light.point_light_percent =
                switch_status != 0 ? 1.0f : l_mEnv_electric_light.point_light_min;
        } else {
            l_mEnv_electric_light.point_light_percent = 1.0f;
        }
    }
}

static void mEnv_RoomTypediffuseLightSet(GAME* game, Kankyo* kankyo) {
    GAME_PLAY* play = (GAME_PLAY*)game;

    Light_diffuse_ct(&kankyo->sun_light, 1, 0, 0, 0, 0, 0);
    Global_light_list_new(game, &play->global_light, &kankyo->sun_light);

    Light_diffuse_ct(&kankyo->moon_light, 1, 0, 0, 0, 0, 0);
    Global_light_list_new(game, &play->global_light, &kankyo->moon_light);
}

static void mEnv_RoomTypeLightSet(GAME* game, Kankyo* kankyo) {
    mEnv_RoomTypePointLightSet(game);
    mEnv_RoomTypediffuseLightSet(game, kankyo);
}

static void mEnv_rainbow_check_set() {
    if (mFI_CheckFieldData() != FALSE && mFI_GET_TYPE(mFI_GetFieldId()) == mFI_FIELD_FG && mEv_IsNotTitleDemo()) {
        if (Save_Get(rainbow_reserved)) {
            if (Common_Get(time).rtc_time.month == Save_Get(rainbow_month) &&
                Common_Get(time).rtc_time.day == Save_Get(rainbow_day)) {
                int now_sec = Common_Get(time).now_sec;
                if (now_sec >= mEnv_RAINBOW_TIME_START && now_sec < mEnv_RAINBOW_TIME_END) {
                    Save_Set(rainbow_reserved, FALSE);

                    if (Common_Get(time).season == mTM_SEASON_SUMMER) {
                        Common_Set(rainbow_opacity, 1.0f);
                    }
                }
            } else {
                Save_Set(rainbow_reserved, FALSE);
            }
        } else if (Common_Get(rainbow_opacity) > 0.0f) {
            if (Common_Get(time).rtc_time.month != Save_Get(rainbow_month) ||
                Common_Get(time).rtc_time.day != Save_Get(rainbow_day) ||
                Common_Get(time).now_sec <
                    mEnv_RAINBOW_TIME_START || // might need to break out time.now_sec into its own variable
                Common_Get(time).now_sec >= mEnv_RAINBOW_TIME_BYE ||
                Common_Get(time).season != mTM_SEASON_SUMMER) {
                Common_Set(rainbow_opacity, 0.0f);
            }
        }
    }
}

extern void Global_kankyo_ct(GAME* game, Kankyo* kankyo) {
    GAME_PLAY* play = (GAME_PLAY*)game;

    bzero(&l_mEnv_electric_light, sizeof(l_mEnv_electric_light));
    mRmTp_IndexLightSwitchOFF(mRmTp_LIGHT_SWITCH_NPC);

    l_mEnv_electric_light.staffroll_fade_rate = 1.0f;
    l_mEnv_electric_light.shadow_adjust = 1.0f;
    l_mEnv_electric_light.sun_percent = 1.0f;
    l_mEnv_electric_light.current_point_light = NULL;

    if (Save_Get(scene_no) == SCENE_MUSEUM_ROOM_INSECT) {
        l_mEnv_electric_light.diffuse_adjust = 0.5f;
    } else {
        l_mEnv_electric_light.diffuse_adjust = 0.4f;
    }

    if (Save_Get(scene_no) == SCENE_MUSEUM_ROOM_INSECT) {
        l_mEnv_electric_light.shadow_alpha_adjust = 100;
    } else {
        l_mEnv_electric_light.shadow_alpha_adjust = 150;
    }

    l_mEnv_electric_light.change_weather_env_rate = 0.0f;

    switch (Save_Get(scene_no)) {
        case SCENE_LIGHTHOUSE:
        case SCENE_TENT: {
            l_mEnv_electric_light.point_light_min = 0.14f;
            break;
        }

        default: {
            l_mEnv_electric_light.point_light_min = 0.14f;
            break;
        }
    }

    l_mEnv_electric_light.diffuse_light_effect_rate = 1.0f;

    bzero(kankyo, sizeof(Kankyo));
    SETREG(MYKREG, 28, 100);
    Common_Set(transition._00, 0);
    mEnv_set_time(kankyo);
    kankyo->countdown_timer = 0xFF;
    mEnv_RoomTypeLightSet(game, kankyo);
    mEnv_regist_nature(kankyo, (NATURE_PROC)none_proc1, NULL);
    mEnv_MakeWindowLightAlpha(FALSE);
    mEnv_InitWind();
    l_mEnv_electric_light.switch_status =
        (u8)mEnv_Pointlight_on_check() ? mEnv_SWITCH_STATUS_TURNING_OFF : mEnv_SWITCH_STATUS_TURNING_ON;
    mEnv_rainbow_check_set();
}

static void mEnv_MakeShadowInfo(Kankyo* kankyo) {
    f32 time_adjust;
    f32 weather_base_adjust;
    f32 weather_change_adjust;
    f32 shadow_pos;
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    int now_sec;
    u8 transition_zero = FALSE;
    int switch_index;
    int min_sec = (rtc_time->min) * mTM_SECONDS_IN_MINUTE;
    int hour_sec = (rtc_time->hour) * mTM_SECONDS_IN_HOUR;

    now_sec = hour_sec + min_sec + rtc_time->sec;
    switch_index = mRmTp_GetNowSceneLightSwitchIndex(); // unused

    /*
     * Time period overview for shadows
     *   [0] 00:00:00 - 03:59:29 | 0.4 (rate normal)
     *   [1] 03:59:30 - 04:00:02 | 0.4 (rate reduced)
     *   [2] 04:00:03 - 06:00:00 | 0.4 -> 1.0 (rate normal)
     *   [3] 06:00:01 - 17:59:59 | 1.0  (rate normal)
     *   [4] 18:00:00 - 19:59:30 | 1.0 -> 0.4 (rate normal)
     *   [5] 19:59:31 - 20:00:03 | 0.4 (rate reduced)
     *   [6] 20:00:04 - 23:59:59 | 0.4 (rate normal)
     */

    if (now_sec > mEnv_TIME_TO_SECS(6, 0, 0) && now_sec < mEnv_TIME_TO_SECS(18, 0, 0)) {
        time_adjust = 1.0f;
    } else if (now_sec < mEnv_TIME_TO_SECS(3, 59, 30) || now_sec > mEnv_TIME_TO_SECS(20, 0, 3)) {
        time_adjust = 0.4f;
    } else if (now_sec >= mEnv_TIME_TO_SECS(4, 0, 3) && now_sec <= mEnv_TIME_TO_SECS(6, 0, 0)) {
        time_adjust = 0.4f + ((f32)(now_sec - mEnv_TIME_TO_SECS(4, 0, 3)) /
                              (f32)(mEnv_TIME_TO_SECS(6, 0, 0) - mEnv_TIME_TO_SECS(4, 0, 3))) *
                                 0.6f;
    } else if (now_sec >= mEnv_TIME_TO_SECS(18, 0, 0) && now_sec <= mEnv_TIME_TO_SECS(19, 59, 30)) {
        time_adjust = 0.4f + ((1.0f - (f32)(now_sec - mEnv_TIME_TO_SECS(18, 0, 0)) /
                                          (f32)(mEnv_TIME_TO_SECS(19, 59, 30) - mEnv_TIME_TO_SECS(18, 0, 0)))) *
                                 0.6f;
    } else {
        transition_zero = TRUE;
        time_adjust = 0.4f;
    }

    if (transition_zero == TRUE) {
        if ((now_sec > mEnv_TIME_TO_SECS(3, 59, 55) && now_sec < mEnv_TIME_TO_SECS(4, 0, 3)) ||
            (now_sec > mEnv_TIME_TO_SECS(19, 59, 55) && now_sec < mEnv_TIME_TO_SECS(20, 0, 3))) {
            add_calc(&l_mEnv_electric_light.shadow_adjust, 0.0f, 1.0f - sqrtf(0.5), 0.005f, 0.005f);
        } else {
            add_calc(&l_mEnv_electric_light.shadow_adjust, 0.0f, 1.0f - sqrtf(0.9), 0.0006f, 0.0004f);
        }
    } else {
        add_calc(&l_mEnv_electric_light.shadow_adjust, 1.0f, 1.0f - sqrtf(0.9), 0.0005f, 0.00005f);
    }

    weather_base_adjust = (l_mEnv_electric_light.now_weather == mEnv_WEATHER_RAIN ||
                           l_mEnv_electric_light.now_weather == mEnv_WEATHER_SNOW)
                              ? 0.75f
                              : 1.0f;
    weather_change_adjust = (l_mEnv_electric_light.next_weather == mEnv_WEATHER_RAIN ||
                             l_mEnv_electric_light.next_weather == mEnv_WEATHER_SNOW)
                                ? 0.75f
                                : 1.0f;

    time_adjust *= (weather_base_adjust +
                    l_mEnv_electric_light.change_weather_env_rate * (weather_change_adjust - weather_base_adjust));
    kankyo->shadow_alpha = (time_adjust * 255.0f * l_mEnv_electric_light.shadow_adjust * 0.75f) *
                           l_mEnv_electric_light.staffroll_fade_rate;

    if (l_mEnv_electric_light.shadow_alpha != 0) {
        kankyo->shadow_alpha = l_mEnv_electric_light.shadow_alpha;
    } else if (Save_Get(scene_no) != SCENE_FG && Save_Get(scene_no) != SCENE_MUSEUM_ROOM_INSECT) {
        kankyo->shadow_alpha = (f32)kankyo->shadow_alpha +
                               l_mEnv_electric_light.point_light_percent *
                                   ((f32)l_mEnv_electric_light.shadow_alpha_adjust - (f32)kankyo->shadow_alpha);
    }

    if (now_sec >= mEnv_TIME_TO_SECS(4, 0, 0) && now_sec <= mEnv_TIME_TO_SECS(20, 0, 0)) {
        f32 diff = now_sec - mEnv_TIME_TO_SECS(4, 0, 0);
        shadow_pos = diff / (f32)(mEnv_TIME_TO_SECS(20, 0, 0) - mEnv_TIME_TO_SECS(4, 0, 0));
    } else {
        if (now_sec < mEnv_TIME_TO_SECS(20, 0, 0)) {
            now_sec += mTM_SECONDS_IN_DAY;
        }

        shadow_pos = (f32)(now_sec - mEnv_TIME_TO_SECS(20, 0, 0)) /
                     (f32)((mEnv_TIME_TO_SECS(4, 0, 0) + mTM_SECONDS_IN_DAY) - mEnv_TIME_TO_SECS(20, 0, 0));
    }

    kankyo->shadow_pos = shadow_pos * 200.0f - 100.0f;
}

static void mEnv_set_time(Kankyo* kankyo) {
    rgba_t light_color;
    int shadows_affected;

    /* Convert day seconds from [0, 86400) -> [-0.5, 0.5) -> [-32768, 32768) (seconds -> bin-angle) */
    s16 time_angle = ((Common_Get(time).now_sec - mTM_SECONDS_IN_HALFDAY) / (f32)mTM_SECONDS_IN_DAY) * 65536.0f;
    f32 sin = sin_s(time_angle); // unused
    f32 cos = cos_s(time_angle); // unused
    mEnv_MakeShadowInfo(kankyo);

    if (Common_Get(clip).effect_clip != NULL &&
        Common_Get(clip).effect_clip->effect_light_status(&light_color, &shadows_affected) !=
            eEC_LIGHT_COLOR_DISABLED &&
        shadows_affected == TRUE) {
        f32 color_add = light_color.r + light_color.g + light_color.b;
        f32 adjusted_shadow_alpha = kankyo->shadow_alpha;

        color_add = color_add > 200.0f ? 200.0f : color_add;

        adjusted_shadow_alpha += (color_add / 200.0f) * 110.0f;
        adjusted_shadow_alpha = adjusted_shadow_alpha > 255.0f ? 255.0f : adjusted_shadow_alpha;
        adjusted_shadow_alpha = adjusted_shadow_alpha < 0.0f ? 0.0f : adjusted_shadow_alpha;

        kankyo->shadow_alpha = adjusted_shadow_alpha;
    }

    mNPS_schedule_manager(); // This is a very odd place to put this. It would be better suited in game_play_Move().
}

static void mEnv_ChangeRGBLight(u8* dst, u8* src_nxt_w0, u8* src_nxt_w1, u8* src_now_w0, u8* src_now_w1, f32 f0,
                                f32 f1) {
    f32 weather_change_bias = l_mEnv_electric_light.change_weather_env_rate;
    f32 inverse_weather_change_bias = 1.0f - weather_change_bias;
    int i;

    for (i = 0; i < 3; i++) {
        *dst =
            weather_change_bias * (f1 * (*src_nxt_w0 + f0 * ((f32)*src_nxt_w1 - (f32)*src_nxt_w0))) +
            inverse_weather_change_bias * (f1 * (*src_now_w0 + f0 * ((f32)*src_now_w1 - (f32)*src_now_w0)));

        dst++;
        src_nxt_w0++;
        src_nxt_w1++;
        src_now_w0++;
        src_now_w1++;
    }
}

static void mEnv_ChangeDiffuseVctlSet(BaseLight* base_light) {
    switch (Save_Get(scene_no)) {
        case SCENE_BROKER_SHOP:
        case SCENE_BUGGY:
        case SCENE_CONVENI:
        case SCENE_SUPER:
        case SCENE_DEPART:
        case SCENE_DEPART_2:
        case SCENE_KAMAKURA:
        case SCENE_MUSEUM_ROOM_PAINTING:
        case SCENE_MUSEUM_ROOM_FOSSIL:
        case SCENE_MUSEUM_ROOM_FISH:
        case SCENE_MY_ROOM_BASEMENT_S:
        case SCENE_MY_ROOM_BASEMENT_M:
        case SCENE_MY_ROOM_BASEMENT_L:
        case SCENE_MY_ROOM_BASEMENT_LL1:
        case SCENE_LIGHTHOUSE: {
            base_light->sun_dir[0] = 0;  // x
            base_light->sun_dir[1] = 69; // y
            base_light->sun_dir[2] = 97; // z

            base_light->moon_dir[0] = 0;   // x
            base_light->moon_dir[1] = -33; // y
            base_light->moon_dir[2] = 115; // z

            break;
        }

        default: {
            f32 dir_x;
            f32 dir_y;
            f32 dir_z;

            switch (Common_Get(field_draw_type)) {
                case FIELD_DRAW_TYPE_TRAIN:
                case FIELD_DRAW_TYPE_PLAYER_SELECT: {
                    dir_x = 0.0f;
                    dir_y = 60.0f;
                    dir_z = 60.0f;

                    break;
                }

                default: {
                    /* second in the day -> [-32768, 32767] */
                    s16 bin_sec_radial =
                        ((f32)(Common_Get(time).now_sec - mTM_SECONDS_IN_HALFDAY) / (f32)mTM_SECONDS_IN_HALFDAY) *
                        (SHT_MAX + 1.0f);

                    dir_x = sin_s(bin_sec_radial) * 60.0f;
                    dir_y = cos_s(bin_sec_radial) * 60.0f;
                    dir_z = cos_s(bin_sec_radial) * 60.0f;

                    break;
                }
            }

            base_light->sun_dir[0] = -dir_x;        // x
            base_light->sun_dir[1] = dir_y + 30.0f; // y
            base_light->sun_dir[2] = dir_z + 20.0f; // z

            base_light->moon_dir[0] = dir_x;         // x
            base_light->moon_dir[1] = 30.0f - dir_y; // y
            base_light->moon_dir[2] = 20.0f - dir_z; // z

            break;
        }
    }
}

static void mEnv_ChangeDiffuseLight(BaseLight* dst, BaseLight* src_nxt_w0, BaseLight* src_nxt_w1, BaseLight* src_now_w0,
                                    BaseLight* src_now_w1, f32 f0) {
    f32 diffuse_light_effect_rate = mEnv_DiffuseLightEffectRate();
    f32 f1;

    mEnv_ChangeDiffuseVctlSet(dst);
    if (Common_Get(sunlight_flag) == TRUE) {
        add_calc(&l_mEnv_electric_light.sun_percent, 1.0f, 1.0f - sqrtf(0.5), 0.1f, 0.005f);
    } else {
        add_calc(&l_mEnv_electric_light.sun_percent, 0.0f, 1.0f - sqrtf(0.5), 0.1f, 0.005f);
    }

    mEnv_ChangeRGBLight(
        dst->sun_color, src_nxt_w0->sun_color, src_nxt_w1->sun_color, src_now_w0->sun_color, src_now_w1->sun_color, f0,
        l_mEnv_electric_light.sun_percent * diffuse_light_effect_rate * l_mEnv_electric_light.staffroll_fade_rate);
    mEnv_ChangeRGBLight(
        dst->moon_color, src_nxt_w0->moon_color, src_nxt_w1->moon_color, src_now_w0->moon_color, src_now_w1->moon_color,
        f0, l_mEnv_electric_light.sun_percent * diffuse_light_effect_rate * l_mEnv_electric_light.staffroll_fade_rate);

    if (mRmTp_GetNowSceneLightSwitchIndex() != -1) {
        /* If the room has a light switch point light, combine its power with the celestial body colors */
        f32 celestial_adjust =
            (l_mEnv_electric_light.diffuse_adjust - 1.0f) * l_mEnv_electric_light.point_light_percent + 1.0f;

        dst->sun_color[0] *= celestial_adjust;
        dst->sun_color[1] *= celestial_adjust;
        dst->sun_color[2] *= celestial_adjust;

        dst->moon_color[0] *= celestial_adjust;
        dst->moon_color[1] *= celestial_adjust;
        dst->moon_color[2] *= celestial_adjust;
    }
}

static void mEnv_ChangeFogLight(BaseLight* dst, BaseLight* src_nxt_w0, BaseLight* src_nxt_w1, BaseLight* src_now_w0,
                                BaseLight* src_now_w1, f32 f0) {
    f32 weather_change_bias = l_mEnv_electric_light.change_weather_env_rate;
    f32 inverse_weather_change_bias = 1.0f - weather_change_bias;
    f32 f1 = l_mEnv_electric_light.sun_percent * l_mEnv_electric_light.staffroll_fade_rate;
    f32 fog_near;
    f32 fog_far;

    mEnv_ChangeRGBLight(dst->fog_color, src_nxt_w0->fog_color, src_nxt_w1->fog_color, src_now_w0->fog_color,
                        src_now_w1->fog_color, f0, f1);

    fog_near =
        weather_change_bias * ((f32)(src_nxt_w0->fog_near & 0x3FF) +
                               f0 * ((f32)(src_nxt_w1->fog_near & 0x3FF) - (f32)(src_nxt_w0->fog_near & 0x3FF))) +
        inverse_weather_change_bias *
            ((f32)(src_now_w0->fog_near & 0x3FF) +
             f0 * ((f32)(src_now_w1->fog_near & 0x3FF) - (f32)(src_now_w0->fog_near & 0x3FF)));

    dst->fog_near = fog_near;
    fog_far =
        weather_change_bias * ((f32)src_nxt_w0->fog_far + f0 * ((f32)src_nxt_w1->fog_far - (f32)src_nxt_w0->fog_far)) +
        inverse_weather_change_bias *
            ((f32)src_now_w0->fog_far + f0 * ((f32)src_now_w1->fog_far - (f32)src_now_w0->fog_far));

    dst->fog_far = fog_far;
}

static void mEnv_CalcSetLight_train(BaseLight* light) {
    if (Save_Get(scene_no) == SCENE_START_DEMO || Save_Get(scene_no) == SCENE_START_DEMO3) {
        if (l_mEnv_electric_light.sun_percent < 1.0f) {
            f32 inv = 1.0f - l_mEnv_electric_light.sun_percent;
            int add_r = inv * 35.0f;
            int add_g = inv * 30.0f;
            int add_b = inv * 40.0f;

            light->ambient_color[0] += (u8)add_r;
            light->ambient_color[1] += (u8)add_g;
            light->ambient_color[2] += (u8)add_b;
        }
    }
}

static void mEnv_CalcSetLight(BaseLight* dst, BaseLight* src_nxt_w0, BaseLight* src_nxt_w1, BaseLight* src_now_w0,
                              BaseLight* src_now_w1, Kankyo* kankyo, f32 f0) {
    mEnv_ChangeRGBLight(dst->ambient_color, src_nxt_w0->ambient_color, src_nxt_w1->ambient_color,
                        src_now_w0->ambient_color, src_now_w1->ambient_color, f0,
                        l_mEnv_electric_light.sun_percent * l_mEnv_electric_light.staffroll_fade_rate);
    mEnv_CalcSetLight_train(dst);
    mEnv_ChangeDiffuseLight(dst, src_nxt_w0, src_nxt_w1, src_now_w0, src_now_w1, f0);
    mEnv_ChangeFogLight(dst, src_nxt_w0, src_nxt_w1, src_now_w0, src_now_w1, f0);

/* @BUG - devs accidently used the wrong light parameter, should've been src_nxt_w1 but wrote src_now_w1 */
#ifndef BUGFIXES
    mEnv_ChangeRGBLight(dst->shadow_color, src_nxt_w0->shadow_color, src_now_w1->shadow_color, src_now_w0->shadow_color,
                        src_now_w1->shadow_color, f0,
                        l_mEnv_electric_light.sun_percent * l_mEnv_electric_light.staffroll_fade_rate);
#else
    mEnv_ChangeRGBLight(dst->shadow_color, src_nxt_w0->shadow_color, src_nxt_w1->shadow_color, src_now_w0->shadow_color,
                        src_now_w1->shadow_color, f0,
                        l_mEnv_electric_light.sun_percent * l_mEnv_electric_light.staffroll_fade_rate);
#endif
    mEnv_ChangeRGBLight(dst->room_color, src_nxt_w0->room_color, src_nxt_w1->room_color, src_now_w0->room_color,
                        src_now_w1->room_color, f0,
                        l_mEnv_electric_light.sun_percent * l_mEnv_electric_light.staffroll_fade_rate);
    mEnv_ChangeRGBLight(dst->sun_color_window, src_nxt_w0->sun_color_window, src_nxt_w1->sun_color_window,
                        src_now_w0->sun_color_window, src_now_w1->sun_color_window, f0,
                        l_mEnv_electric_light.sun_percent * l_mEnv_electric_light.staffroll_fade_rate);
    mEnv_ChangeRGBLight(dst->moon_color_window, src_nxt_w0->moon_color_window, src_nxt_w1->moon_color_window,
                        src_now_w0->moon_color_window, src_now_w1->moon_color_window, f0,
                        l_mEnv_electric_light.sun_percent * l_mEnv_electric_light.staffroll_fade_rate);
    mEnv_ChangeRGBLight(dst->background_color, src_nxt_w0->background_color, src_nxt_w1->background_color,
                        src_now_w0->background_color, src_now_w1->background_color, f0,
                        l_mEnv_electric_light.sun_percent * l_mEnv_electric_light.staffroll_fade_rate);
}

static int mEnv_GetNowTerm() {
    int now_sec = Common_Get(time).now_sec;
    int i;

    for (i = 0; i < mEnv_TERM_NUM; i++) {
        if (klight_chg_tim[i + 1] >= now_sec) {
            return i;
        }
    }

    return 0;
}

static void mEnv_SetBaseLight(Kankyo* kankyo) {
    int now_sec = Common_Get(time).now_sec;
    int term = mEnv_GetNowTerm();
    int weather = l_mEnv_electric_light.now_weather;
    int fog_disabled = TRUE;
    int next_term = term + 1;
    f32 percent_towards_next_term = get_percent(klight_chg_tim[next_term], klight_chg_tim[term], now_sec);

    switch (Common_Get(field_draw_type)) {
        case FIELD_DRAW_TYPE_TRAIN: {
            int next_term = (term + 1) % mEnv_TERM_NUM;
            BaseLight* src_w1 = l_mEnv_normal_kcolor_data[weather] + next_term;
            BaseLight* src_w0 = l_mEnv_normal_kcolor_data[weather] + term;

            mEnv_CalcSetLight(&kankyo->base_light, src_w0, src_w1, src_w0, src_w1, kankyo, percent_towards_next_term);
            break;
        }

        case FIELD_DRAW_TYPE_PLAYER_SELECT: {
            mEnv_CalcSetLight(&kankyo->base_light, &l_mEnv_kcolor_data_p_sel, &l_mEnv_kcolor_data_p_sel,
                              &l_mEnv_kcolor_data_p_sel, &l_mEnv_kcolor_data_p_sel, kankyo, 0.5f);
            l_mEnv_electric_light.shadow_alpha = 200;

            break;
        }

        default: {
            if (Save_Get(scene_no) == SCENE_CONVENI || Save_Get(scene_no) == SCENE_SUPER ||
                Save_Get(scene_no) == SCENE_DEPART || Save_Get(scene_no) == SCENE_DEPART_2) {
                mEnv_CalcSetLight(&kankyo->base_light, &l_mEnv_kcolor_shop, &l_mEnv_kcolor_shop, &l_mEnv_kcolor_shop,
                                  &l_mEnv_kcolor_shop, kankyo, 0.5f);
                l_mEnv_electric_light.shadow_alpha = 150;
            } else if (Save_Get(scene_no) == SCENE_BUGGY) {
                mEnv_CalcSetLight(&kankyo->base_light, &l_mEnv_kcolor_buggy, &l_mEnv_kcolor_buggy, &l_mEnv_kcolor_buggy,
                                  &l_mEnv_kcolor_buggy, kankyo, 0.5f);
                l_mEnv_electric_light.shadow_alpha = 150;
            } else if (Save_Get(scene_no) == SCENE_KAMAKURA) {
                mEnv_CalcSetLight(&kankyo->base_light, &l_mEnv_kcolor_kamakura, &l_mEnv_kcolor_kamakura,
                                  &l_mEnv_kcolor_kamakura, &l_mEnv_kcolor_kamakura, kankyo, 0.5f);
                l_mEnv_electric_light.shadow_alpha = 150;
            } else if (Save_Get(scene_no) == SCENE_BROKER_SHOP) {
                mEnv_CalcSetLight(&kankyo->base_light, &l_mEnv_kcolor_broker, &l_mEnv_kcolor_broker,
                                  &l_mEnv_kcolor_broker, &l_mEnv_kcolor_broker, kankyo, 0.5f);
                l_mEnv_electric_light.shadow_alpha = 150;
            } else if (Save_Get(scene_no) == SCENE_MUSEUM_ROOM_FISH) {
                mEnv_CalcSetLight(&kankyo->base_light, &l_mEnv_kcolor_museum_fish, &l_mEnv_kcolor_museum_fish,
                                  &l_mEnv_kcolor_museum_fish, &l_mEnv_kcolor_museum_fish, kankyo, 0.5f);
                l_mEnv_electric_light.shadow_alpha = 150;
            } else if (Save_Get(scene_no) == SCENE_MUSEUM_ROOM_FOSSIL) {
                mEnv_CalcSetLight(&kankyo->base_light, &l_mEnv_kcolor_museum_fossil, &l_mEnv_kcolor_museum_fossil,
                                  &l_mEnv_kcolor_museum_fossil, &l_mEnv_kcolor_museum_fossil, kankyo, 0.5f);
                l_mEnv_electric_light.shadow_alpha = 150;
            } else if (Save_Get(scene_no) == SCENE_MUSEUM_ROOM_PAINTING) {
                mEnv_CalcSetLight(&kankyo->base_light, &l_mEnv_kcolor_museum_picture, &l_mEnv_kcolor_museum_picture,
                                  &l_mEnv_kcolor_museum_picture, &l_mEnv_kcolor_museum_picture, kankyo, 0.5f);
                l_mEnv_electric_light.shadow_alpha = 150;
            } else if (Save_Get(scene_no) == SCENE_MY_ROOM_BASEMENT_S ||
                       Save_Get(scene_no) == SCENE_MY_ROOM_BASEMENT_M ||
                       Save_Get(scene_no) == SCENE_MY_ROOM_BASEMENT_L ||
                       Save_Get(scene_no) == SCENE_MY_ROOM_BASEMENT_LL1) {
                mEnv_CalcSetLight(&kankyo->base_light, &l_mEnv_kcolor_basement, &l_mEnv_kcolor_basement,
                                  &l_mEnv_kcolor_basement, &l_mEnv_kcolor_basement, kankyo, 0.5f);
                l_mEnv_electric_light.shadow_alpha = 150;
            } else if (Save_Get(scene_no) == SCENE_LIGHTHOUSE) {
                mEnv_CalcSetLight(&kankyo->base_light, &l_mEnv_kcolor_lighthouse, &l_mEnv_kcolor_lighthouse,
                                  &l_mEnv_kcolor_lighthouse, &l_mEnv_kcolor_lighthouse, kankyo, 0.5f);
                l_mEnv_electric_light.shadow_alpha = 115;
            } else if (Save_Get(scene_no) == SCENE_MUSEUM_ROOM_INSECT) {
                BaseLight* now = l_mEnv_normal_kcolor_insect_data[l_mEnv_electric_light.now_weather];
                BaseLight* nxt = l_mEnv_normal_kcolor_insect_data[l_mEnv_electric_light.next_weather];
                int next_term = (term + 1) % mEnv_TERM_NUM;
                BaseLight* nxt_w0 = nxt + term;
                BaseLight* nxt_w1 = nxt + next_term;
                BaseLight* now_w0 = now + term;
                BaseLight* now_w1 = now + next_term;

                mEnv_CalcSetLight(&kankyo->base_light, nxt_w0, nxt_w1, now_w0, now_w1, kankyo,
                                  percent_towards_next_term);
            } else {
                BaseLight* now = l_mEnv_normal_kcolor_data[l_mEnv_electric_light.now_weather];
                BaseLight* nxt = l_mEnv_normal_kcolor_data[l_mEnv_electric_light.next_weather];
                int next_term = (term + 1) % mEnv_TERM_NUM;
                BaseLight* nxt_w0 = nxt + term;
                BaseLight* nxt_w1 = nxt + next_term;
                BaseLight* now_w0 = now + term;
                BaseLight* now_w1 = now + next_term;

                mEnv_CalcSetLight(&kankyo->base_light, nxt_w0, nxt_w1, now_w0, now_w1, kankyo,
                                  percent_towards_next_term);
            }

            if (Common_Get(field_type) == mFI_FIELDTYPE2_FG) {
                fog_disabled = FALSE;
            }

            break;
        }
    }

    if (fog_disabled == TRUE) {
        kankyo->base_light.fog_color[2] = 0;
        kankyo->base_light.fog_color[1] = 0;
        kankyo->base_light.fog_color[0] = 0;
        kankyo->base_light.fog_near = 2020;
        kankyo->base_light.fog_far = 1000;
    }
}

static u8 mEnv_LimitChkRGBColor(int c) {
    if (c > 255) {
        c = 255;
    } else if (c < 0) {
        c = 0;
    }

    return c;
}

static void mEnv_AddAndSetRGBColor(u8* dst, u8* src0, s16* src1) {
    int i;

    for (i = 0; i < 3; i++) {
        dst[0] = mEnv_LimitChkRGBColor(src0[0] + src1[0]);

        dst++;
        src0++;
        src1++;
    }
}

static void mEnv_SetDiffuseLight(Kankyo* kankyo) {
    mEnv_AddAndSetRGBColor(kankyo->sun_light.lights.diffuse.color, kankyo->base_light.sun_color,
                           kankyo->add_light_info.diffuse_color);
    mEnv_AddAndSetRGBColor(kankyo->moon_light.lights.diffuse.color, kankyo->base_light.moon_color,
                           l_mEnv_electric_light.add_moon_color);

    kankyo->sun_light.lights.diffuse.x = kankyo->base_light.sun_dir[0];
    kankyo->sun_light.lights.diffuse.y = kankyo->base_light.sun_dir[1];
    kankyo->sun_light.lights.diffuse.z = kankyo->base_light.sun_dir[2];

    kankyo->moon_light.lights.diffuse.x = kankyo->base_light.moon_dir[0];
    kankyo->moon_light.lights.diffuse.y = kankyo->base_light.moon_dir[1];
    kankyo->moon_light.lights.diffuse.z = kankyo->base_light.moon_dir[2];
}

static void mEnv_SetFog(GAME_PLAY* play, Kankyo* kankyo, Global_light* global_light) {
    int field_id = mFI_GetFieldId();
    int fog_near;
    int fog_far;

    mEnv_AddAndSetRGBColor(global_light->fogColor, kankyo->base_light.fog_color, kankyo->add_light_info.fog_color);

    fog_near = kankyo->base_light.fog_near + kankyo->add_light_info.fog_near;
    if (fog_near <= mEnv_FOG_NEAR_MAX) {
        global_light->fogNear = fog_near;
    } else {
        global_light->fogNear = mEnv_FOG_NEAR_MAX;
    }

    fog_far = kankyo->base_light.fog_far + kankyo->add_light_info.fog_far;
    if (fog_far <= mEnv_FOG_FAR_MAX) {
        global_light->fogFar = fog_far;
    } else {
        global_light->fogFar = mEnv_FOG_FAR_MAX;
    }

    if (mFI_GET_TYPE(field_id) != mFI_FIELD_FG) {
        global_light->fogFar = 1000;
        global_light->fogNear = 1000;
    }
#ifdef PC_ENHANCEMENTS
    /* reset fog if rotated camera with C-stick outside*/
    else if  (play->camera.focus_distance != 620.0){
        if  (play->camera.now_main_index == CAMERA2_PROCESS_NORMAL || play->camera.now_main_index == CAMERA2_PROCESS_WADE){
            global_light->fogFar = 1000;
            global_light->fogNear = 1000;
        } 
    }  
#endif
}

static void mEnv_PermitCheckDiffuseLight(Kankyo* kankyo) {
    if (kankyo->sun_light.lights.diffuse.x == 0 && kankyo->sun_light.lights.diffuse.y == 0 &&
        kankyo->sun_light.lights.diffuse.z == 0) {
        kankyo->sun_light.lights.diffuse.x = 1;
    }

    if (kankyo->moon_light.lights.diffuse.x == 0 && kankyo->moon_light.lights.diffuse.y == 0 &&
        kankyo->moon_light.lights.diffuse.z == 0) {
        kankyo->moon_light.lights.diffuse.x = 1;
    }
}

extern void mEnv_GetRoomPrimColor(u8* r, u8* g, u8* b, GAME_PLAY* play) {
    u8 color[3];

    f32 point_light_percent = l_mEnv_electric_light.point_light_percent;
    f32 diffuse_light_effect_rate = mEnv_DiffuseLightEffectRate();
    int c;
    f32 f0 = 1.0f + point_light_percent * -0.3f;
    f32 f1 = point_light_percent * 0.6f;
    s16 flame = l_mEnv_electric_light.point_light_is_flame;
    u8* point_light_color = l_mEnv_electric_light.point_light_color;
    u8* room_color = play->kankyo.base_light.room_color;
    int i;

    for (i = 0; i < 3; i++) {

        if (flame) {
            c = (point_light_color[0] >> 1) + (room_color[0] >> 1); // take the average
        } else {
            c = room_color[0] * f0 * diffuse_light_effect_rate + point_light_color[0] * f1;
        }

        if (c < 0) {
            c = 0;
        } else if (c >= 256) {
            c = 255;
        }

        color[i] = c;

        point_light_color++;
        room_color++;
    }

    r[0] = color[0];
    g[0] = color[1];
    b[0] = color[2];
}

extern void Global_kankyo_set_room_prim(GAME* game) {
    u8 r;
    u8 g;
    u8 b;
    GRAPH* graph;

    mEnv_GetRoomPrimColor(&r, &g, &b, (GAME_PLAY*)game);

    {
        graph = game->graph;
        OPEN_DISP(graph);

        gDPPipeSync(NOW_POLY_OPA_DISP++);
        gDPSetPrimColor(NOW_POLY_OPA_DISP++, 0, 128, r, g, b, 255);
        gDPPipeSync(NOW_POLY_XLU_DISP++);
        gDPSetPrimColor(NOW_POLY_XLU_DISP++, 0, 128, r, g, b, 255);
        gDPPipeSync(NOW_BG_OPA_DISP++);
        gDPSetPrimColor(NOW_BG_OPA_DISP++, 0, 128, r, g, b, 255);

        CLOSE_DISP(graph);
    }
}

static void mEnv_check_countdown_start(GAME_PLAY* play) {
    if (mEv_check_status(mEv_EVENT_NEW_YEARS_EVE_COUNTDOWN, mEv_STATUS_PLAYSOUND) == FALSE) {
        int bx;
        int bz;

        mFI_BlockKind2BkNum(&bx, &bz, mRF_BLOCKKIND_POOL);

        if (bx != play->block_table.block_x || bz != play->block_table.block_z) {
            if (Common_Get(time).now_sec >= mEnv_TIME_TO_SECS(23, 59, 0)) {
                mEv_set_status(mEv_EVENT_NEW_YEARS_EVE_COUNTDOWN, mEv_STATUS_PLAYSOUND);
            }
        }
    }
}

static void mEnv_countdown_proc(GAME_PLAY* play) {
    if (Common_Get(field_draw_type) == FIELD_DRAW_TYPE_TRAIN ||
        Common_Get(field_draw_type) == FIELD_DRAW_TYPE_PLAYER_SELECT) {
        return;
    }

    if (mEv_check_status(mEv_EVENT_NEW_YEARS_EVE_COUNTDOWN, mEv_STATUS_ACTIVE) == TRUE) {
        mEnv_check_countdown_start(play);

        if (mEv_check_status(mEv_EVENT_NEW_YEARS_EVE_COUNTDOWN, mEv_STATUS_PLAYSOUND) == TRUE) {
            u8 countdown_timer;
            u8 now_countdown = play->kankyo.countdown_timer;

            if (Common_Get(time.rtc_time).month != lbRTC_DECEMBER) {
                countdown_timer = 0;
            } else {
                countdown_timer = mTM_SECONDS_IN_DAY - Common_Get(time).now_sec;
            }

            if (countdown_timer != now_countdown) {
                u16 sfx;

                if (countdown_timer == 0) {
                    sfx = 0x151;
                } else if (countdown_timer <= 10) {
                    sfx = 0x150;
                } else {
                    sfx = 0x431;
                }

                sAdo_SysTrgStart(sfx);
                play->kankyo.countdown_timer = countdown_timer;
            }
        }
    }
}

extern int mEnv_RequestChangeLightON(GAME_PLAY* play, int light_on_type, int play_sfx) {
    if (mRmTp_NowSceneLightSwitchON()) {
        l_mEnv_electric_light.point_light_on_type = light_on_type;

        if (light_on_type == mEnv_LIGHT_TYPE_PLAYER) {
            PLAYER_ACTOR* player = get_player_actor_withoutCheck(play); // unused

            l_mEnv_electric_light.light_animating_on = TRUE;
            l_mEnv_electric_light.light_anime_frame = 0;
            l_mEnv_electric_light.light_anime_accum = 0.0f;

            if (play_sfx == TRUE) {
                sAdo_SysTrgStart(NA_SE_LIGHT_ON);
            }
        }

        return TRUE;
    }
    return FALSE;
}

extern int mEnv_RequestChangeLightOFF(GAME_PLAY* play, int light_off_type, f32 step) {
    if (mRmTp_NowSceneLightSwitchOFF()) {
        l_mEnv_electric_light.point_light_off_type = light_off_type;
        l_mEnv_electric_light.point_light_off_step = ABS(step);

        if (light_off_type == mEnv_LIGHT_TYPE_PLAYER) {
            PLAYER_ACTOR* player = get_player_actor_withoutCheck(play); // unused

            sAdo_SysTrgStart(NA_SE_LIGHT_OFF);
        }
        return TRUE;
    }

    return FALSE;
}

static void mEnv_LightAnimeToSwitchON(GAME* game) {
    static f32 switch_on_anime_percent_table[mEnv_LIGHT_ANIME_FRAMES] = { 0.00f, 0.05f, 0.10f, 0.15f, 0.20f,
                                                                          0.25f, 0.30f, 0.25f, 0.20f, 0.15f,
                                                                          0.10f, 0.30f, 0.35f, 0.40f, 0.45f,
                                                                          0.50f, 0.45f, 0.40f, 0.35f, 0.30f };
    int ticks = graph_dt_60hz_ticks(game, &l_mEnv_electric_light.light_anime_accum);

    while (ticks-- > 0) {
        int frame = l_mEnv_electric_light.light_anime_frame;

        if (frame >= mEnv_LIGHT_ANIME_FRAMES) {
            l_mEnv_electric_light.light_animating_on = FALSE;
            return;
        }

        l_mEnv_electric_light.point_light_percent =
            l_mEnv_electric_light.point_light_min +
            (1.0f - l_mEnv_electric_light.point_light_min) * switch_on_anime_percent_table[frame];
        l_mEnv_electric_light.light_anime_frame++;
    }
}

extern void mEnv_ManagePointLight(GAME_PLAY* play, Kankyo* kankyo, Global_light* global_light) {
    PLAYER_ACTOR* player = get_player_actor_withoutCheck(play); // unused

    int lightswitch_on = mRmTp_Index2LightSwitchStatus(mRmTp_GetNowSceneLightSwitchIndex());

    if (lightswitch_on) {
        if (l_mEnv_electric_light.light_animating_on == TRUE) {
            mEnv_LightAnimeToSwitchON((GAME*)play);
        } else {
            if (l_mEnv_electric_light.point_light_on_type == mEnv_LIGHT_TYPE_LIGHTHOUSE) {
                add_calc(&l_mEnv_electric_light.point_light_percent, 1.0f, 0.02f, 0.02f, 0.00007f);
            } else {
                add_calc(&l_mEnv_electric_light.point_light_percent, 1.0f, 0.01f, 0.01f, 0.01f);
            }

            if (chkTrigger(BUTTON_Z) && mRmTp_PleaseDrawLightSwitch()) {
                mEnv_RequestChangeLightOFF(play, mEnv_LIGHT_TYPE_PLAYER, 0.0f);
            }
        }
    } else {
        mActor_name_t field_id = mFI_GetFieldId();

        if (l_mEnv_electric_light.point_light_off_type == mEnv_LIGHT_TYPE_PLAYER) {
            add_calc(&l_mEnv_electric_light.point_light_percent, l_mEnv_electric_light.point_light_min, 0.2f, 0.2f,
                     0.02f);
        } else {
            l_mEnv_electric_light.point_light_percent -= l_mEnv_electric_light.point_light_off_step;

            if (l_mEnv_electric_light.point_light_percent < l_mEnv_electric_light.point_light_min) {
                l_mEnv_electric_light.point_light_percent = l_mEnv_electric_light.point_light_min;
            } else if (l_mEnv_electric_light.point_light_percent > 1.0f) {
                l_mEnv_electric_light.point_light_percent = 1.0f;
            }
        }

        if (chkTrigger(BUTTON_Z) && mRmTp_PleaseDrawLightSwitch()) {
            mEnv_RequestChangeLightON(play, mEnv_LIGHT_TYPE_PLAYER, TRUE);
        } else if (mFI_GET_TYPE(field_id) == mFI_FIELD_NPCROOM0 && Common_Get(last_scene_no) == SCENE_FG) {
            mEnv_CheckNpcRoomPointLightNiceStatus();
        }
    }

    if (mRmTp_GetNowSceneLightSwitchIndex() != -1) {
        u8* color = play->kankyo.point_light.lights.point.color;
        int i;

        for (i = 0; i < 3; i++) {
            color[i] = l_mEnv_electric_light.point_light_color[i] * l_mEnv_electric_light.point_light_percent;
        }
    }
}

static void mEnv_ManageChangeWeatherEnvRate() {
    if (l_mEnv_electric_light.now_weather != l_mEnv_electric_light.next_weather) {
        l_mEnv_electric_light.change_weather_env_rate += mEnv_CHANGE_WEATHER_ENV_RATE;

        if (l_mEnv_electric_light.change_weather_env_rate >= 1.0f) {
            l_mEnv_electric_light.change_weather_env_rate = 1.0f;

            if (aWeather_ChangingWeather() == FALSE) {
                l_mEnv_electric_light.now_weather = l_mEnv_electric_light.next_weather;
                l_mEnv_electric_light.change_weather_env_rate = 0.0f;
            }
        }
    } else {
        l_mEnv_electric_light.change_weather_env_rate = 0.0f;

        if (aWeather_ChangingWeather() == FALSE) {
            l_mEnv_electric_light.now_weather = Common_Get(weather);
            l_mEnv_electric_light.next_weather = Common_Get(weather);
        }
    }
}

static void mEnv_JudgeSwitchStatus() {
    switch (l_mEnv_electric_light.switch_status) {
        case mEnv_SWITCH_STATUS_ON:
            l_mEnv_electric_light.switch_status = mEnv_SWITCH_STATUS_TURNING_OFF;
            break;

        case mEnv_SWITCH_STATUS_OFF:
            l_mEnv_electric_light.switch_status = mEnv_SWITCH_STATUS_TURNING_ON;
            break;

        case mEnv_SWITCH_STATUS_TURNING_OFF:
            if (mRmTp_Index2LightSwitchStatus(mRmTp_GetNowSceneLightSwitchIndex()) == FALSE) {
                l_mEnv_electric_light.switch_status = mEnv_SWITCH_STATUS_OFF;
            }
            break;

        case mEnv_SWITCH_STATUS_TURNING_ON:
            if (mRmTp_Index2LightSwitchStatus(mRmTp_GetNowSceneLightSwitchIndex()) != FALSE) {
                l_mEnv_electric_light.switch_status = mEnv_SWITCH_STATUS_ON;
            }
            break;
    }
}

static void mEnv_rainbow_power_calc() {
    f32 dt = gamePT->graph->dt_num_60fps_frames;

    if (Save_Get(rainbow_reserved) && mFI_CheckFieldData() && mFI_GET_TYPE(mFI_GetFieldId()) == mFI_FIELD_FG &&
        mEv_IsNotTitleDemo() && Common_Get(time.rtc_time).month == Save_Get(rainbow_month) &&
        Common_Get(time.rtc_time).day == Save_Get(rainbow_day) && Common_Get(time).now_sec >= mEnv_RAINBOW_TIME_START &&
        Common_Get(time).now_sec < mEnv_RAINBOW_TIME_END && Common_Get(time).season == mTM_SEASON_SUMMER) {
        if (chase_f(Common_GetPointer(rainbow_opacity), 1.0f, (1.0f / 1800.0f) * dt) != FALSE) {
            Save_Set(rainbow_reserved, FALSE); // rainbow has been shown
        }
    } else {
        chase_f(Common_GetPointer(rainbow_opacity), 0.0f, (1.0f / 108000.0f) * dt); // slowly fade out rainbow
    }
}

static void mEnv_TaimatuPointLightWaveMoveProc(GAME_PLAY* play);
static void mEnv_CheckNpcLight_ToSwitchON(GAME_PLAY* play);

extern void Global_kankyo_set(GAME_PLAY* play, Kankyo* kankyo, Global_light* global_light) {
    mEnv_JudgeSwitchStatus();
    mEnv_ManageChangeWeatherEnvRate();
    mEnv_set_time(kankyo);
    mEnv_SetBaseLight(kankyo);
    mEnv_AddAndSetRGBColor(global_light->ambientColor, kankyo->base_light.ambient_color,
                           kankyo->add_light_info.ambient_color);
    mEnv_SetDiffuseLight(kankyo);
    mEnv_SetFog(play, kankyo, global_light);
    mEnv_PermitCheckDiffuseLight(kankyo);
    mEnv_TaimatuPointLightWaveMoveProc(play);
    mEnv_CheckNpcLight_ToSwitchON(play);
    mEnv_countdown_proc(play);
    mEnv_MakeWindowLightAlpha(TRUE);
    mEnv_rainbow_power_calc();

    if (l_mEnv_electric_light._98 < 10) {
        l_mEnv_electric_light._98++;
    }
}

static int mEnv_CheckNpcRoomPointLightNiceStatus() {
    mNPS_schedule_c* schedule;
    Animal_c* animal;

    if (Save_Get(scene_no) == SCENE_COTTAGE_NPC) {
        animal = Save_GetPointer(island.animal);
        schedule = Common_GetPointer(npc_schedule[ANIMAL_NUM_MAX]);

        if (schedule != NULL) {
            if (
#if VERSION < VER_GAFU01_00
            schedule->current_type == mNPS_SCHED_IN_HOUSE &&
#endif
            animal->is_home == TRUE &&
                (Common_Get(time).now_sec < mEnv_NPC_LIGHTS_OFF_TIME ||
                 Common_Get(time).now_sec >= mEnv_NPC_LIGHTS_ON_TIME)) {
                return TRUE;
            }
        }
    } else {
        animal = mNpc_GetAnimalInfoP(Common_Get(house_owner_name));

        if (animal != NULL) {
            schedule = mNPS_get_schedule_area(&animal->id);

            if (schedule != NULL) {
                if (
#if VERSION < VER_GAFU01_00
                    schedule->current_type == mNPS_SCHED_IN_HOUSE &&
#endif
                    animal->is_home == TRUE &&
                    (Common_Get(time).now_sec < mEnv_NPC_LIGHTS_OFF_TIME ||
                     Common_Get(time).now_sec >= mEnv_NPC_LIGHTS_ON_TIME)) {
                    return TRUE;
                }
            }
        }
    }

    return FALSE;
}

static void mEnv_TaimatuPointLightWaveMoveProc(GAME_PLAY* play) {
    static s16 point_light_wave_counter;
    static f32 point_light_wave_accum;
    u8* point_light_color;
    int ticks = graph_dt_60hz_ticks((GAME*)play, &point_light_wave_accum);

    point_light_wave_counter += (s16)(400 * ticks);
    point_light_color = l_mEnv_electric_light.point_light_color;

    if (l_mEnv_electric_light.point_light_is_flame) {
        f32 wave = sin_s(point_light_wave_counter);
        u8 c;

        if (wave >= 0.0f) {
            wave = sin_s(point_light_wave_counter);
        } else {
            wave = -sin_s(point_light_wave_counter);
        }

        c = (wave * 40.0f) + 40.0f;
        point_light_color[0] = 255 - c; // r
        point_light_color[1] = 240 - c; // g
    }
}

static void mEnv_CheckNpcLight_ToSwitchON(GAME_PLAY* play) {
    // stubbed
}

static void mEnv_PointLightSet(GAME_PLAY* play, f32 fade_rate) {
    PLAYER_ACTOR* player = get_player_actor_withoutCheck(play);
    s16* kk_event_data = (s16*)mEv_get_save_area(mEv_EVENT_KK_SLIDER, 10);

    Light_point_ct(&play->kankyo.point_light, player->actor_class.world.position.x,
                   player->actor_class.world.position.y, player->actor_class.world.position.z - 25.0f, 255, 255, 220,
                   (f32)kk_event_data[0] * (1.0f - fade_rate));

    l_mEnv_electric_light.point_light_color[0] = 255;
    l_mEnv_electric_light.point_light_color[1] = 255;
    l_mEnv_electric_light.point_light_color[2] = 220;
}

static Light_list* S_get_light_list;

extern void staffroll_light_init(GAME_PLAY* play) {
    l_mEnv_electric_light.staffroll_fade_rate = 1.0f;
    mEnv_PointLightSet(play, 1.0f);
    S_get_light_list = Global_light_list_new((GAME*)play, &play->global_light, &play->kankyo.point_light);
}

static void mEnv_DecideStaffrollFadeOutRate() {
    l_mEnv_electric_light.staffroll_fade_rate -= 1.0f / (((f32)GETREG(CRV, 91) * 0.01f + 2.8f) * 60.0f);

    if (l_mEnv_electric_light.staffroll_fade_rate <= 0.0f) {
        l_mEnv_electric_light.staffroll_fade_rate = 0.0f;
    }
}

static void mEnv_DecideStaffrollFadeInRate() {
    l_mEnv_electric_light.staffroll_fade_rate += 1.0f / (((f32)GETREG(CRV, 91) * 0.01f + 2.8f) * 60.0f);

    if (l_mEnv_electric_light.staffroll_fade_rate > 1.0f) {
        l_mEnv_electric_light.staffroll_fade_rate = 1.0f;
    }
}

extern void staffroll_light_proc_start(GAME_PLAY* play) {
    mEnv_DecideStaffrollFadeOutRate();
    mEnv_PointLightSet(play, l_mEnv_electric_light.staffroll_fade_rate);
}

extern int staffroll_light_proc_end(GAME_PLAY* play) {
    mEnv_DecideStaffrollFadeInRate();
    mEnv_PointLightSet(play, l_mEnv_electric_light.staffroll_fade_rate);

    return l_mEnv_electric_light.staffroll_fade_rate == 1.0f;
}

extern void staffroll_light_dt(GAME_PLAY* play) {
    Global_light_list_delete(&play->global_light, S_get_light_list);
}

extern void mEnv_GetShadowPrimColor_Light(u8* r, u8* g, u8* b, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;

    r[0] = play->kankyo.base_light.shadow_color[0];
    g[0] = play->kankyo.base_light.shadow_color[1];
    b[0] = play->kankyo.base_light.shadow_color[2];
}

static int mEnv_Pointlight_on_check() {
    return (l_mEnv_electric_light.point_light_percent <= l_mEnv_electric_light.point_light_min) ? FALSE : TRUE;
}

extern int mEnv_PointLightMin() {
    return l_mEnv_electric_light.point_light_percent <= l_mEnv_electric_light.point_light_min;
}

/* @unused @fabricated - likely incorrect, real size is 0x68 (DnM+), this is 0x44 */
extern MATCH_FORCESTRIP int mEnv_HereIsPlayerSelect() {
    static int place_chk[4] = { SCENE_PLAYERSELECT, SCENE_PLAYERSELECT_2, SCENE_PLAYERSELECT_3,
                                SCENE_PLAYERSELECT_SAVE };

    int i;

    for (i = 0; i < 4; i++) {
        if (place_chk[i] == Save_Get(scene_no)) {
            return TRUE;
        }
    }

    return FALSE;
}

static void mEnv_MakeWindowLightAlpha(int enabled) {
    f32 step = 1.0f / 100.0f;
    f32 target = 0.0f;

    if (Common_Get(field_draw_type) == FIELD_DRAW_TYPE_INDOORS) {
        int switch_idx = mRmTp_GetNowSceneLightSwitchIndex();

        if (enabled == FALSE) {
            l_mEnv_electric_light.windowlight_alpha = 0.0f;
            step = 1.0f;
        }

        if (ABS((s16)Common_Get(time).now_sec) < 120 ||
            ABS((s16)(Common_Get(time).now_sec - mTM_SECONDS_IN_DAY)) < 120 ||
            ABS((s16)(Common_Get(time).now_sec - mTM_SECONDS_IN_HALFDAY)) < 120) {
            target = 0.0f;
        } else if (switch_idx != -1) {
            target = (1.0f - l_mEnv_electric_light.point_light_percent) * 0.78f + 0.22f;
        } else if (Common_Get(time).now_sec >= mEnv_NPC_LIGHTS_OFF_TIME &&
                   Common_Get(time).now_sec < mEnv_NPC_LIGHTS_ON_TIME) {
            target = 1.0f;
        }

        add_calc(&l_mEnv_electric_light.windowlight_alpha, target, 1.0f - sqrtf(0.8), 0.5f * step, 0.5f * step);
    }
}

extern f32 mKK_windowlight_alpha_get() {
    return l_mEnv_electric_light.windowlight_alpha;
}

extern int mEnv_ReqeustChangeWeatherEnviroment(s16 now_weather, s16 next_weather) {
    if (l_mEnv_electric_light.now_weather == l_mEnv_electric_light.next_weather) {
        if (l_mEnv_normal_kcolor_data[now_weather & 3] != l_mEnv_normal_kcolor_data[next_weather & 3]) {
            l_mEnv_electric_light.change_weather_env_rate = 0.0f;
            l_mEnv_electric_light.now_weather = now_weather & 3;
            l_mEnv_electric_light.next_weather = next_weather & 3;
        }

        return TRUE;
    }

    return FALSE;
}

extern int mEnv_ReservePointLight(GAME_PLAY* play, xyz_t* pos, u8 r, u8 g, u8 b, s16 power) {
    Light_list* list;
    Lights* point_light;
    int i;

    for (i = 0; i < mEnv_POINT_LIGHT_NUM; i++) {
        if (l_mEnv_electric_light.point_light_list_buf[i] == NULL) {
            point_light = &l_mEnv_electric_light.point_lights[i];

            Light_point_ct(&l_mEnv_electric_light.point_lights[i], pos->x, pos->y, pos->z, r, g, b, power);
            list = Global_light_list_new((GAME*)play, &play->global_light, &l_mEnv_electric_light.point_lights[i]);

            if (list != NULL) {
                l_mEnv_electric_light.point_light_list_buf[i] = list;
                return i;
            }
        }
    }

    return -1;
}

extern void mEnv_OperateReservedPointLight_Position(int point_light_idx, xyz_t* pos) {
    if (point_light_idx >= 0 && point_light_idx < mEnv_POINT_LIGHT_NUM) {
        Lights* l = &l_mEnv_electric_light.point_lights[point_light_idx];

        l->lights.point.x = pos->x;
        l->lights.point.y = pos->y;
        l->lights.point.z = pos->z;
    }
}

extern void mEnv_OperateReservedPointLight_Color(int point_light_idx, u8 r, u8 g, u8 b) {
    if (point_light_idx >= 0 && point_light_idx < mEnv_POINT_LIGHT_NUM) {
        Lights* l = &l_mEnv_electric_light.point_lights[point_light_idx];

        l->lights.point.color[0] = r;
        l->lights.point.color[1] = g;
        l->lights.point.color[2] = b;
    }
}

extern void mEnv_OperateReservedPointLight_Power(int point_light_idx, s16 power) {
    if (point_light_idx >= 0 && point_light_idx < mEnv_POINT_LIGHT_NUM) {
        Lights* l = &l_mEnv_electric_light.point_lights[point_light_idx];

        l->lights.point.radius = power;
    }
}

extern void mEnv_OperateReservedPointLight(int point_light_idx, xyz_t* pos, u8 r, u8 g, u8 b, s16 power) {
    mEnv_OperateReservedPointLight_Position(point_light_idx, pos);
    mEnv_OperateReservedPointLight_Color(point_light_idx, r, g, b);
    mEnv_OperateReservedPointLight_Power(point_light_idx, power);
}

extern int mEnv_CancelReservedPointLight(int point_light_idx, GAME_PLAY* play) {
    if (point_light_idx >= 0 && point_light_idx < mEnv_POINT_LIGHT_NUM) {
        Light_list** list = l_mEnv_electric_light.point_light_list_buf;

        Global_light_list_delete(&play->global_light, list[point_light_idx]);
        list[point_light_idx] = NULL;
        point_light_idx = -1;
    }

    return point_light_idx;
}
