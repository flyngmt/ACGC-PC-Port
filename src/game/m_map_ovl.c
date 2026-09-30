#include "m_map_ovl.h"

#include "audio.h"
#include "m_random_field.h"
#include "m_field_info.h"
#include "m_event.h"
#include "m_font.h"
#include "m_player.h"
#include "m_player_lib.h"
#include "game.h"
#include "sys_matrix.h"
#include "m_malloc.h"
#include "m_common_data.h"
#ifdef MOUSE_INPUT
#include "pc_mouse_input.h"
#endif

#define mMP_MAP_OFFSET_X 11.7f
#define mMP_MAP_OFFSET_Y 45.7f

extern u8 kan_tizu_f_TA_tex_txt[];
extern u8 kan_tizu_tst1_TA_tex_txt[];
extern u8 kan_tizu_t_TA_tex_txt[];
extern u8 kan_tizu_tr1_TA_tex_txt[];
extern u8 kan_tizu_fmh_TA_tex_txt[];
extern u8 kan_tizu_c1_TA_tex_txt[];
extern u8 kan_tizu_c2_TA_tex_txt[];
extern u8 kan_tizu_c3_TA_tex_txt[];
extern u8 kan_tizu_c4_TA_tex_txt[];
extern u8 kan_tizu_c5_TA_tex_txt[];
extern u8 kan_tizu_c6_TA_tex_txt[];
extern u8 kan_tizu_c7_TA_tex_txt[];
extern u8 kan_tizu_c1r1_TA_tex_txt[];
extern u8 kan_tizu_c2r1_TA_tex_txt[];
extern u8 kan_tizu_c3r1_TA_tex_txt[];
extern u8 kan_tizu_c4r1_TA_tex_txt[];
extern u8 kan_tizu_c5r1_TA_tex_txt[];
extern u8 kan_tizu_c6r1_TA_tex_txt[];
extern u8 kan_tizu_c7r1_TA_tex_txt[];
extern u8 kan_tizu_c1r2_TA_tex_txt[];
extern u8 kan_tizu_c2r2_TA_tex_txt[];
extern u8 kan_tizu_c3r2_TA_tex_txt[];
extern u8 kan_tizu_c4r2_TA_tex_txt[];
extern u8 kan_tizu_c5r2_TA_tex_txt[];
extern u8 kan_tizu_c1r2_TA_tex_txt[];
extern u8 kan_tizu_c4r2_TA_tex_txt[];
extern u8 kan_tizu_c5r2_TA_tex_txt[];
extern u8 kan_tizu_c6r3_TA_tex_txt[];
extern u8 kan_tizu_c7r3_TA_tex_txt[];
extern u8 kan_tizu_r1_TA_tex_txt[];
extern u8 kan_tizu_r2_TA_tex_txt[];
extern u8 kan_tizu_r2_TA_tex_txt[];
extern u8 kan_tizu_r4_TA_tex_txt[];
extern u8 kan_tizu_r5_TA_tex_txt[];
extern u8 kan_tizu_r6_TA_tex_txt[];
extern u8 kan_tizu_r7_TA_tex_txt[];
extern u8 kan_tizu_r1b_TA_tex_txt[];
extern u8 kan_tizu_r2b_TA_tex_txt[];
extern u8 kan_tizu_r2b_TA_tex_txt[];
extern u8 kan_tizu_r4b_TA_tex_txt[];
extern u8 kan_tizu_r5b_TA_tex_txt[];
extern u8 kan_tizu_r6b_TA_tex_txt[];
extern u8 kan_tizu_r7b_TA_tex_txt[];
extern u8 kan_tizu_c1s_TA_tex_txt[];
extern u8 kan_tizu_c2s_TA_tex_txt[];
extern u8 kan_tizu_c3s_TA_tex_txt[];
extern u8 kan_tizu_c4s_TA_tex_txt[];
extern u8 kan_tizu_c5s_TA_tex_txt[];
extern u8 kan_tizu_c6s_TA_tex_txt[];
extern u8 kan_tizu_c7s_TA_tex_txt[];
extern u8 kan_tizu_m_TA_tex_txt[];
extern u8 kan_tizu_mr1_TA_tex_txt[];
extern u8 kan_tizu_fsh_TA_tex_txt[];
extern u8 kan_tizu_fpk_TA_tex_txt[];
extern u8 kan_tizu_fpo_TA_tex_txt[];
extern u8 kan_tizu_fko_TA_tex_txt[];
extern u8 kan_tizu_pr1_TA_tex_txt[];
extern u8 kan_tizu_pr2_TA_tex_txt[];
extern u8 kan_tizu_pr2_TA_tex_txt[];
extern u8 kan_tizu_pr4_TA_tex_txt[];
extern u8 kan_tizu_pr5_TA_tex_txt[];
extern u8 kan_tizu_pr6_TA_tex_txt[];
extern u8 kan_tizu_pr7_TA_tex_txt[];
extern u8 kan_tizu_mr1b_TA_tex_txt[];
extern u8 kan_tizu_fmu_TA_tex_txt[];
extern u8 kan_tizu_fta_TA_tex_txt[];
extern u8 kan_tizu_tr1b_TA_tex_txt[];
extern u8 kan_tizu_c1r2b_TA_tex_txt[];
extern u8 kan_tizu_c3r1b_TA_tex_txt[];
extern u8 kan_tizu_c4r1b_TA_tex_txt[];
extern u8 kan_tizu_c4r2b_TA_tex_txt[];
extern u8 kan_tizu_c5r2b_TA_tex_txt[];
extern u8 kan_tizu_c6r1b_TA_tex_txt[];
extern u8 kan_tizu_c7r1b_TA_tex_txt[];
extern u8 kan_tizu_mwf_TA_tex_txt[];

static u8* l_map_texture[mFM_BLOCK_TYPE_NUM] = {
    kan_tizu_f_TA_tex_txt, // mFM_BLOCK_TYPE_BORDER_CLIFF_TOP
    kan_tizu_f_TA_tex_txt, // mFM_BLOCK_TYPE_BORDER_CLIFF_RIVER
    kan_tizu_f_TA_tex_txt, // mFM_BLOCK_TYPE_BORDER_CLIFF_LEFT
    kan_tizu_f_TA_tex_txt, // mFM_BLOCK_TYPE_3
    kan_tizu_f_TA_tex_txt, // mFM_BLOCK_TYPE_BORDER_CLIFF_RIGHT
    kan_tizu_f_TA_tex_txt, // mFM_BLOCK_TYPE_BORDER_CLIFF_CORNER_TOP_LEFT
    kan_tizu_f_TA_tex_txt, // mFM_BLOCK_TYPE_6
    kan_tizu_f_TA_tex_txt, // mFM_BLOCK_TYPE_TRACKS
    kan_tizu_f_TA_tex_txt, // mFM_BLOCK_TYPE_BORDER_CLIFF_CORNER_TOP_RIGHT
    kan_tizu_f_TA_tex_txt, // mFM_BLOCK_TYPE_BORDER_CLIFF_LEFT_TUNNEL
    kan_tizu_f_TA_tex_txt, // mFM_BLOCK_TYPE_BORDER_CLIFF_RIGHT_TUNNEL
    kan_tizu_tst1_TA_tex_txt, // mFM_BLOCK_TYPE_TRACKS_STATION
    kan_tizu_t_TA_tex_txt, // mFM_BLOCK_TYPE_TRACKS_DUMP
    kan_tizu_tr1_TA_tex_txt, // mFM_BLOCK_TYPE_TRACKS_RIVER
    kan_tizu_fmh_TA_tex_txt, // mFM_BLOCK_TYPE_PLAYER_HOUSE
    kan_tizu_c1_TA_tex_txt, // mFM_BLOCK_TYPE_CLIFF_HORIZONTAL
    kan_tizu_c2_TA_tex_txt, // mFM_BLOCK_TYPE_CLIFF_BOTTOM_RIGHT_CORNER
    kan_tizu_c3_TA_tex_txt, // mFM_BLOCK_TYPE_CLIFF_VERTICAL_RIGHT
    kan_tizu_c4_TA_tex_txt, // mFM_BLOCK_TYPE_CLIFF_TOP_RIGHT_CORNER
    kan_tizu_c5_TA_tex_txt, // mFM_BLOCK_TYPE_CLIFF_TOP_LEFT_CORNER
    kan_tizu_c6_TA_tex_txt, // mFM_BLOCK_TYPE_CLIFF_VERTICAL_LEFT
    kan_tizu_c7_TA_tex_txt, // mFM_BLOCK_TYPE_CLIFF_BOTTOM_LEFT_CORNER
    kan_tizu_c1r1_TA_tex_txt, // mFM_BLOCK_TYPE_WATERFALL_STRAIGHT_CLIFF_HORIZONTAL
    kan_tizu_c2r1_TA_tex_txt, // mFM_BLOCK_TYPE_WATERFALL_STRAIGHT_CLIFF_BOTTOM_RIGHT_CORNER
    kan_tizu_c3r1_TA_tex_txt, // mFM_BLOCK_TYPE_RIVER_STRAIGHT_CLIFF_VERTICAL_RIGHT
    kan_tizu_c4r1_TA_tex_txt, // mFM_BLOCK_TYPE_RIVER_STRAIGHT_CLIFF_TOP_RIGHT_CORNER
    kan_tizu_c5r1_TA_tex_txt, // mFM_BLOCK_TYPE_WATERFALL_STRAIGHT_CLIFF_TOP_LEFT_CORNER
    kan_tizu_c6r1_TA_tex_txt, // mFM_BLOCK_TYPE_RIVER_STRAIGHT_CLIFF_VERTICAL_LEFT
    kan_tizu_c7r1_TA_tex_txt, // mFM_BLOCK_TYPE_RIVER_STRAIGHT_CLIFF_BOTTOM_LEFT_CORNER
    kan_tizu_c1r2_TA_tex_txt, // mFM_BLOCK_TYPE_RIVER_STRAIGHT_CLIFF_HORIZONTAL
    kan_tizu_c2r2_TA_tex_txt, // mFM_BLOCK_TYPE_WATERFALL_EAST_CLIFF_BOTTOM_RIGHT_CORNER
    kan_tizu_c3r2_TA_tex_txt, // mFM_BLOCK_TYPE_WATERFALL_EAST_CLIFF_VERTICAL_RIGHT
    kan_tizu_c4r2_TA_tex_txt, // mFM_BLOCK_TYPE_RIVER_EAST_CLIFF_TOP_RIGHT_CORNER
    kan_tizu_c5r2_TA_tex_txt, // mFM_BLOCK_TYPE_RIVER_EAST_CLIFF_TOP_LEFT_CORNER
    kan_tizu_c1r2_TA_tex_txt, // mFM_BLOCK_TYPE_RIVER_WEST_CLIFF_HORIZONTAL
    kan_tizu_c4r2_TA_tex_txt, // mFM_BLOCK_TYPE_RIVER_WEST_CLIFF_TOP_RIGHT_CORNER
    kan_tizu_c5r2_TA_tex_txt, // mFM_BLOCK_TYPE_RIVER_WEST_CLIFF_TOP_LEFT_CORNER
    kan_tizu_c6r3_TA_tex_txt, // mFM_BLOCK_TYPE_WATERFALL_WEST_CLIFF_VERTICAL_LEFT
    kan_tizu_c7r3_TA_tex_txt, // mFM_BLOCK_TYPE_WATERFALL_WEST_CLIFF_BOTTOM_LEFT_CORNER
    kan_tizu_f_TA_tex_txt, // mFM_BLOCK_TYPE_FLAT
    kan_tizu_r1_TA_tex_txt, // mFM_BLOCK_TYPE_RIVER_SOUTH
    kan_tizu_r2_TA_tex_txt, // mFM_BLOCK_TYPE_RIVER_EAST
    kan_tizu_r2_TA_tex_txt, // mFM_BLOCK_TYPE_RIVER_WEST
    kan_tizu_r4_TA_tex_txt, // mFM_BLOCK_TYPE_RIVER_SOUTH_EAST
    kan_tizu_r5_TA_tex_txt, // mFM_BLOCK_TYPE_RIVER_EAST_SOUTH
    kan_tizu_r6_TA_tex_txt, // mFM_BLOCK_TYPE_RIVER_SOUTH_WEST
    kan_tizu_r7_TA_tex_txt, // mFM_BLOCK_TYPE_RIVER_WEST_SOUTH
    kan_tizu_r1b_TA_tex_txt, // mFM_BLOCK_TYPE_RIVER_SOUTH_BRIDGE
    kan_tizu_r2b_TA_tex_txt, // mFM_BLOCK_TYPE_RIVER_EAST_BRIDGE
    kan_tizu_r2b_TA_tex_txt, // mFM_BLOCK_TYPE_RIVER_WEST_BRIDGE
    kan_tizu_r4b_TA_tex_txt, // mFM_BLOCK_TYPE_RIVER_SOUTH_EAST_BRIDGE
    kan_tizu_r5b_TA_tex_txt, // mFM_BLOCK_TYPE_RIVER_EAST_SOUTH_BRIDGE
    kan_tizu_r6b_TA_tex_txt, // mFM_BLOCK_TYPE_RIVER_SOUTH_WEST_BRIDGE
    kan_tizu_r7b_TA_tex_txt, // mFM_BLOCK_TYPE_RIVER_WEST_SOUTH_BRIDGE
    kan_tizu_c1s_TA_tex_txt, // mFM_BLOCK_TYPE_SLOPE_HORIZONTAL
    kan_tizu_c2s_TA_tex_txt, // mFM_BLOCK_TYPE_SLOPE_BOTTOM_RIGHT_CORNER
    kan_tizu_c3s_TA_tex_txt, // mFM_BLOCK_TYPE_SLOPE_VERTICAL_RIGHT
    kan_tizu_c4s_TA_tex_txt, // mFM_BLOCK_TYPE_SLOPE_TOP_RIGHT_CORNER
    kan_tizu_c5s_TA_tex_txt, // mFM_BLOCK_TYPE_SLOPE_TOP_LEFT_CORNER
    kan_tizu_c6s_TA_tex_txt, // mFM_BLOCK_TYPE_SLOPE_VERTICAL_LEFT
    kan_tizu_c7s_TA_tex_txt, // mFM_BLOCK_TYPE_SLOPE_BOTTOM_LEFT_CORNER
    kan_tizu_f_TA_tex_txt, // mFM_BLOCK_TYPE_BORDER_CLIFF_LEFT_TRANSITION
    kan_tizu_f_TA_tex_txt, // mFM_BLOCK_TYPE_BORDER_CLIFF_RIGHT_TRANSITION
    kan_tizu_m_TA_tex_txt, // mFM_BLOCK_TYPE_BEACH
    kan_tizu_mr1_TA_tex_txt, // mFM_BLOCK_TYPE_BEACH_RIVER
    kan_tizu_fsh_TA_tex_txt, // mFM_BLOCK_TYPE_TRACKS_SHOP
    kan_tizu_fpk_TA_tex_txt, // mFM_BLOCK_TYPE_SHRINE
    kan_tizu_fpo_TA_tex_txt, // mFM_BLOCK_TYPE_TRACKS_POST_OFFICE
    kan_tizu_fko_TA_tex_txt, // mFM_BLOCK_TYPE_POLICE_BOX
    kan_tizu_pr1_TA_tex_txt, // mFM_BLOCK_TYPE_POOL_SOUTH
    kan_tizu_pr2_TA_tex_txt, // mFM_BLOCK_TYPE_POOL_EAST
    kan_tizu_pr2_TA_tex_txt, // mFM_BLOCK_TYPE_POOL_WEST
    kan_tizu_pr4_TA_tex_txt, // mFM_BLOCK_TYPE_POOL_SOUTH_EAST
    kan_tizu_pr5_TA_tex_txt, // mFM_BLOCK_TYPE_POOL_EAST_SOUTH
    kan_tizu_pr6_TA_tex_txt, // mFM_BLOCK_TYPE_POOL_SOUTH_WEST
    kan_tizu_pr7_TA_tex_txt, // mFM_BLOCK_TYPE_POOL_WEST_SOUTH
    kan_tizu_f_TA_tex_txt, // mFM_BLOCK_TYPE_TRACKS6
    kan_tizu_r1_TA_tex_txt, // mFM_BLOCK_TYPE_TRACKS7
    kan_tizu_c1_TA_tex_txt, // mFM_BLOCK_TYPE_TRACKS8
    kan_tizu_c1_TA_tex_txt, // mFM_BLOCK_TYPE_TRACKS9
    kan_tizu_c1_TA_tex_txt, // mFM_BLOCK_TYPE_BORDER_CLIFF_OCEAN_LEFT
    kan_tizu_c1_TA_tex_txt, // mFM_BLOCK_TYPE_BORDER_CLIFF_OCEAN_RIGHT
    kan_tizu_mr1b_TA_tex_txt, // mFM_BLOCK_TYPE_BEACH_RIVER_BRIDGE
    kan_tizu_mr1_TA_tex_txt, // mFM_BLOCK_TYPE_OCEAN
    kan_tizu_fmu_TA_tex_txt, // mFM_BLOCK_TYPE_MUSEUM
    kan_tizu_fta_TA_tex_txt, // mFM_BLOCK_TYPE_NEEDLEWORK
    kan_tizu_tr1b_TA_tex_txt, // mFM_BLOCK_TYPE_TRACKS_RIVER_BRIDGE
    kan_tizu_c1r2b_TA_tex_txt, // mFM_BLOCK_TYPE_RIVER_STRAIGHT_CLIFF_HORIZONTAL_BRIDGE
    kan_tizu_c3r1b_TA_tex_txt, // mFM_BLOCK_TYPE_RIVER_STRAIGHT_CLIFF_VERTICAL_RIGHT_BRIDGE
    kan_tizu_c4r1b_TA_tex_txt, // mFM_BLOCK_TYPE_RIVER_STRAIGHT_CLIFF_TOP_RIGHT_CORNER_BRIDGE
    kan_tizu_c4r2b_TA_tex_txt, // mFM_BLOCK_TYPE_RIVER_EAST_CLIFF_TOP_RIGHT_CORNER_BRIDGE
    kan_tizu_c5r2b_TA_tex_txt, // mFM_BLOCK_TYPE_RIVER_EAST_CLIFF_TOP_LEFT_CORNER_BRIDGE
    kan_tizu_c6r1b_TA_tex_txt, // mFM_BLOCK_TYPE_RIVER_STRAIGHT_CLIFF_VERTICAL_LEFT_BRIDGE
    kan_tizu_c7r1b_TA_tex_txt, // mFM_BLOCK_TYPE_RIVER_STRAIGHT_CLIFF_BOTTOM_LEFT_CORNER_BRIDGE
    kan_tizu_c7r1b_TA_tex_txt, // mFM_BLOCK_TYPE_OCEAN_2
    kan_tizu_c7r1b_TA_tex_txt, // mFM_BLOCK_TYPE_OCEAN_3
    kan_tizu_c7r1b_TA_tex_txt, // mFM_BLOCK_TYPE_OCEAN_4
    kan_tizu_c7r1b_TA_tex_txt, // mFM_BLOCK_TYPE_OCEAN_5
    kan_tizu_c7r1b_TA_tex_txt, // mFM_BLOCK_TYPE_ISLAND_LEFT
    kan_tizu_c7r1b_TA_tex_txt, // mFM_BLOCK_TYPE_ISLAND_RIGHT
    kan_tizu_mwf_TA_tex_txt, // mFM_BLOCK_TYPE_PORT
    kan_tizu_mwf_TA_tex_txt, // mFM_BLOCK_TYPE_SEA_EXCEPTIONAL
    kan_tizu_mwf_TA_tex_txt, // mFM_BLOCK_TYPE_OCEAN_6
    kan_tizu_mwf_TA_tex_txt, // mFM_BLOCK_TYPE_OCEAN_7
    kan_tizu_mwf_TA_tex_txt, // mFM_BLOCK_TYPE_OCEAN_8
    kan_tizu_c1r2b_TA_tex_txt, // mFM_BLOCK_TYPE_RIVER_WEST_CLIFF_HORIZONTAL_BRIDGE
    kan_tizu_c4r2b_TA_tex_txt, // mFM_BLOCK_TYPE_RIVER_WEST_CLIFF_TOP_RIGHT_CORNER_BRIDGE
    kan_tizu_c5r2b_TA_tex_txt, // mFM_BLOCK_TYPE_RIVER_WEST_CLIFF_TOP_LEFT_CORNER_BRIDGE
};

static u8 l_map_pal[mFM_BLOCK_TYPE_NUM] = {
    0, // mFM_BLOCK_TYPE_BORDER_CLIFF_TOP
    0, // mFM_BLOCK_TYPE_BORDER_CLIFF_RIVER
    0, // mFM_BLOCK_TYPE_BORDER_CLIFF_LEFT
    0, // mFM_BLOCK_TYPE_3
    0, // mFM_BLOCK_TYPE_BORDER_CLIFF_RIGHT
    0, // mFM_BLOCK_TYPE_BORDER_CLIFF_CORNER_TOP_LEFT
    0, // mFM_BLOCK_TYPE_6
    0, // mFM_BLOCK_TYPE_TRACKS
    0, // mFM_BLOCK_TYPE_BORDER_CLIFF_CORNER_TOP_RIGHT
    0, // mFM_BLOCK_TYPE_BORDER_CLIFF_LEFT_TUNNEL
    0, // mFM_BLOCK_TYPE_BORDER_CLIFF_RIGHT_TUNNEL
    1, // mFM_BLOCK_TYPE_TRACKS_STATION
    1, // mFM_BLOCK_TYPE_TRACKS_DUMP
    1, // mFM_BLOCK_TYPE_TRACKS_RIVER
    1, // mFM_BLOCK_TYPE_PLAYER_HOUSE
    0, // mFM_BLOCK_TYPE_CLIFF_HORIZONTAL
    0, // mFM_BLOCK_TYPE_CLIFF_BOTTOM_RIGHT_CORNER
    0, // mFM_BLOCK_TYPE_CLIFF_VERTICAL_RIGHT
    0, // mFM_BLOCK_TYPE_CLIFF_TOP_RIGHT_CORNER
    0, // mFM_BLOCK_TYPE_CLIFF_TOP_LEFT_CORNER
    0, // mFM_BLOCK_TYPE_CLIFF_VERTICAL_LEFT
    0, // mFM_BLOCK_TYPE_CLIFF_BOTTOM_LEFT_CORNER
    0, // mFM_BLOCK_TYPE_WATERFALL_STRAIGHT_CLIFF_HORIZONTAL
    0, // mFM_BLOCK_TYPE_WATERFALL_STRAIGHT_CLIFF_BOTTOM_RIGHT_CORNER
    0, // mFM_BLOCK_TYPE_RIVER_STRAIGHT_CLIFF_VERTICAL_RIGHT
    0, // mFM_BLOCK_TYPE_RIVER_STRAIGHT_CLIFF_TOP_RIGHT_CORNER
    0, // mFM_BLOCK_TYPE_WATERFALL_STRAIGHT_CLIFF_TOP_LEFT_CORNER
    0, // mFM_BLOCK_TYPE_RIVER_STRAIGHT_CLIFF_VERTICAL_LEFT
    0, // mFM_BLOCK_TYPE_RIVER_STRAIGHT_CLIFF_BOTTOM_LEFT_CORNER
    0, // mFM_BLOCK_TYPE_RIVER_STRAIGHT_CLIFF_HORIZONTAL
    0, // mFM_BLOCK_TYPE_WATERFALL_EAST_CLIFF_BOTTOM_RIGHT_CORNER
    0, // mFM_BLOCK_TYPE_WATERFALL_EAST_CLIFF_VERTICAL_RIGHT
    0, // mFM_BLOCK_TYPE_RIVER_EAST_CLIFF_TOP_RIGHT_CORNER
    0, // mFM_BLOCK_TYPE_RIVER_EAST_CLIFF_TOP_LEFT_CORNER
    0, // mFM_BLOCK_TYPE_RIVER_WEST_CLIFF_HORIZONTAL
    0, // mFM_BLOCK_TYPE_RIVER_WEST_CLIFF_TOP_RIGHT_CORNER
    0, // mFM_BLOCK_TYPE_RIVER_WEST_CLIFF_TOP_LEFT_CORNER
    0, // mFM_BLOCK_TYPE_WATERFALL_WEST_CLIFF_VERTICAL_LEFT
    0, // mFM_BLOCK_TYPE_WATERFALL_WEST_CLIFF_BOTTOM_LEFT_CORNER
    0, // mFM_BLOCK_TYPE_FLAT
    0, // mFM_BLOCK_TYPE_RIVER_SOUTH
    0, // mFM_BLOCK_TYPE_RIVER_EAST
    0, // mFM_BLOCK_TYPE_RIVER_WEST
    0, // mFM_BLOCK_TYPE_RIVER_SOUTH_EAST
    0, // mFM_BLOCK_TYPE_RIVER_EAST_SOUTH
    0, // mFM_BLOCK_TYPE_RIVER_SOUTH_WEST
    0, // mFM_BLOCK_TYPE_RIVER_WEST_SOUTH
    0, // mFM_BLOCK_TYPE_RIVER_SOUTH_BRIDGE
    0, // mFM_BLOCK_TYPE_RIVER_EAST_BRIDGE
    0, // mFM_BLOCK_TYPE_RIVER_WEST_BRIDGE
    0, // mFM_BLOCK_TYPE_RIVER_SOUTH_EAST_BRIDGE
    0, // mFM_BLOCK_TYPE_RIVER_EAST_SOUTH_BRIDGE
    0, // mFM_BLOCK_TYPE_RIVER_SOUTH_WEST_BRIDGE
    0, // mFM_BLOCK_TYPE_RIVER_WEST_SOUTH_BRIDGE
    0, // mFM_BLOCK_TYPE_SLOPE_HORIZONTAL
    0, // mFM_BLOCK_TYPE_SLOPE_BOTTOM_RIGHT_CORNER
    0, // mFM_BLOCK_TYPE_SLOPE_VERTICAL_RIGHT
    0, // mFM_BLOCK_TYPE_SLOPE_TOP_RIGHT_CORNER
    0, // mFM_BLOCK_TYPE_SLOPE_TOP_LEFT_CORNER
    0, // mFM_BLOCK_TYPE_SLOPE_VERTICAL_LEFT
    0, // mFM_BLOCK_TYPE_SLOPE_BOTTOM_LEFT_CORNER
    0, // mFM_BLOCK_TYPE_BORDER_CLIFF_LEFT_TRANSITION
    0, // mFM_BLOCK_TYPE_BORDER_CLIFF_RIGHT_TRANSITION
    1, // mFM_BLOCK_TYPE_BEACH
    1, // mFM_BLOCK_TYPE_BEACH_RIVER
    1, // mFM_BLOCK_TYPE_TRACKS_SHOP
    1, // mFM_BLOCK_TYPE_SHRINE
    1, // mFM_BLOCK_TYPE_TRACKS_POST_OFFICE
    1, // mFM_BLOCK_TYPE_POLICE_BOX
    0, // mFM_BLOCK_TYPE_POOL_SOUTH
    0, // mFM_BLOCK_TYPE_POOL_EAST
    0, // mFM_BLOCK_TYPE_POOL_WEST
    0, // mFM_BLOCK_TYPE_POOL_SOUTH_EAST
    0, // mFM_BLOCK_TYPE_POOL_EAST_SOUTH
    0, // mFM_BLOCK_TYPE_POOL_SOUTH_WEST
    0, // mFM_BLOCK_TYPE_POOL_WEST_SOUTH
    0, // mFM_BLOCK_TYPE_TRACKS6
    0, // mFM_BLOCK_TYPE_TRACKS7
    0, // mFM_BLOCK_TYPE_TRACKS8
    0, // mFM_BLOCK_TYPE_TRACKS9
    0, // mFM_BLOCK_TYPE_BORDER_CLIFF_OCEAN_LEFT
    0, // mFM_BLOCK_TYPE_BORDER_CLIFF_OCEAN_RIGHT
    1, // mFM_BLOCK_TYPE_BEACH_RIVER_BRIDGE
    1, // mFM_BLOCK_TYPE_OCEAN
    1, // mFM_BLOCK_TYPE_MUSEUM
    1, // mFM_BLOCK_TYPE_NEEDLEWORK
    1, // mFM_BLOCK_TYPE_TRACKS_RIVER_BRIDGE
    0, // mFM_BLOCK_TYPE_RIVER_STRAIGHT_CLIFF_HORIZONTAL_BRIDGE
    0, // mFM_BLOCK_TYPE_RIVER_STRAIGHT_CLIFF_VERTICAL_RIGHT_BRIDGE
    0, // mFM_BLOCK_TYPE_RIVER_STRAIGHT_CLIFF_TOP_RIGHT_CORNER_BRIDGE
    0, // mFM_BLOCK_TYPE_RIVER_EAST_CLIFF_TOP_RIGHT_CORNER_BRIDGE
    0, // mFM_BLOCK_TYPE_RIVER_EAST_CLIFF_TOP_LEFT_CORNER_BRIDGE
    0, // mFM_BLOCK_TYPE_RIVER_STRAIGHT_CLIFF_VERTICAL_LEFT_BRIDGE
    0, // mFM_BLOCK_TYPE_RIVER_STRAIGHT_CLIFF_BOTTOM_LEFT_CORNER_BRIDGE
    0, // mFM_BLOCK_TYPE_OCEAN_2
    0, // mFM_BLOCK_TYPE_OCEAN_3
    0, // mFM_BLOCK_TYPE_OCEAN_4
    0, // mFM_BLOCK_TYPE_OCEAN_5
    0, // mFM_BLOCK_TYPE_ISLAND_LEFT
    0, // mFM_BLOCK_TYPE_ISLAND_RIGHT
    1, // mFM_BLOCK_TYPE_PORT
    1, // mFM_BLOCK_TYPE_SEA_EXCEPTIONAL
    1, // mFM_BLOCK_TYPE_OCEAN_6
    1, // mFM_BLOCK_TYPE_OCEAN_7
    1, // mFM_BLOCK_TYPE_OCEAN_8
    0, // mFM_BLOCK_TYPE_RIVER_WEST_CLIFF_HORIZONTAL_BRIDGE
    0, // mFM_BLOCK_TYPE_RIVER_WEST_CLIFF_TOP_RIGHT_CORNER_BRIDGE
    0, // mFM_BLOCK_TYPE_RIVER_WEST_CLIFF_TOP_LEFT_CORNER_BRIDGE
};

static u8 pluss_bridge[mFM_BLOCK_TYPE_NUM] = {
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_BORDER_CLIFF_TOP
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_BORDER_CLIFF_RIVER
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_BORDER_CLIFF_LEFT
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_3
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_BORDER_CLIFF_RIGHT
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_BORDER_CLIFF_CORNER_TOP_LEFT
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_6
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_TRACKS
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_BORDER_CLIFF_CORNER_TOP_RIGHT
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_BORDER_CLIFF_LEFT_TUNNEL
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_BORDER_CLIFF_RIGHT_TUNNEL
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_TRACKS_STATION
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_TRACKS_DUMP
    mFM_BLOCK_TYPE_TRACKS_RIVER_BRIDGE, // mFM_BLOCK_TYPE_TRACKS_RIVER
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_PLAYER_HOUSE
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_CLIFF_HORIZONTAL
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_CLIFF_BOTTOM_RIGHT_CORNER
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_CLIFF_VERTICAL_RIGHT
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_CLIFF_TOP_RIGHT_CORNER
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_CLIFF_TOP_LEFT_CORNER
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_CLIFF_VERTICAL_LEFT
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_CLIFF_BOTTOM_LEFT_CORNER
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_WATERFALL_STRAIGHT_CLIFF_HORIZONTAL
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_WATERFALL_STRAIGHT_CLIFF_BOTTOM_RIGHT_CORNER
    mFM_BLOCK_TYPE_RIVER_STRAIGHT_CLIFF_VERTICAL_RIGHT_BRIDGE, // mFM_BLOCK_TYPE_RIVER_STRAIGHT_CLIFF_VERTICAL_RIGHT
    mFM_BLOCK_TYPE_RIVER_STRAIGHT_CLIFF_TOP_RIGHT_CORNER_BRIDGE, // mFM_BLOCK_TYPE_RIVER_STRAIGHT_CLIFF_TOP_RIGHT_CORNER
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_WATERFALL_STRAIGHT_CLIFF_TOP_LEFT_CORNER
    mFM_BLOCK_TYPE_RIVER_STRAIGHT_CLIFF_VERTICAL_LEFT_BRIDGE, // mFM_BLOCK_TYPE_RIVER_STRAIGHT_CLIFF_VERTICAL_LEFT
    mFM_BLOCK_TYPE_RIVER_STRAIGHT_CLIFF_BOTTOM_LEFT_CORNER_BRIDGE, // mFM_BLOCK_TYPE_RIVER_STRAIGHT_CLIFF_BOTTOM_LEFT_CORNER
    mFM_BLOCK_TYPE_RIVER_STRAIGHT_CLIFF_HORIZONTAL_BRIDGE, // mFM_BLOCK_TYPE_RIVER_STRAIGHT_CLIFF_HORIZONTAL
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_WATERFALL_EAST_CLIFF_BOTTOM_RIGHT_CORNER
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_WATERFALL_EAST_CLIFF_VERTICAL_RIGHT
    mFM_BLOCK_TYPE_RIVER_EAST_CLIFF_TOP_RIGHT_CORNER_BRIDGE, // mFM_BLOCK_TYPE_RIVER_EAST_CLIFF_TOP_RIGHT_CORNER
    mFM_BLOCK_TYPE_RIVER_EAST_CLIFF_TOP_LEFT_CORNER_BRIDGE, // mFM_BLOCK_TYPE_RIVER_EAST_CLIFF_TOP_LEFT_CORNER
    mFM_BLOCK_TYPE_RIVER_WEST_CLIFF_HORIZONTAL_BRIDGE, // mFM_BLOCK_TYPE_RIVER_WEST_CLIFF_HORIZONTAL
    mFM_BLOCK_TYPE_RIVER_WEST_CLIFF_TOP_RIGHT_CORNER_BRIDGE, // mFM_BLOCK_TYPE_RIVER_WEST_CLIFF_TOP_RIGHT_CORNER
    mFM_BLOCK_TYPE_RIVER_WEST_CLIFF_TOP_LEFT_CORNER_BRIDGE, // mFM_BLOCK_TYPE_RIVER_WEST_CLIFF_TOP_LEFT_CORNER
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_WATERFALL_WEST_CLIFF_VERTICAL_LEFT
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_WATERFALL_WEST_CLIFF_BOTTOM_LEFT_CORNER
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_FLAT
    mFM_BLOCK_TYPE_RIVER_SOUTH_BRIDGE, // mFM_BLOCK_TYPE_RIVER_SOUTH
    mFM_BLOCK_TYPE_RIVER_EAST_BRIDGE, // mFM_BLOCK_TYPE_RIVER_EAST
    mFM_BLOCK_TYPE_RIVER_WEST_BRIDGE, // mFM_BLOCK_TYPE_RIVER_WEST
    mFM_BLOCK_TYPE_RIVER_SOUTH_EAST_BRIDGE, // mFM_BLOCK_TYPE_RIVER_SOUTH_EAST
    mFM_BLOCK_TYPE_RIVER_EAST_SOUTH_BRIDGE, // mFM_BLOCK_TYPE_RIVER_EAST_SOUTH
    mFM_BLOCK_TYPE_RIVER_SOUTH_WEST_BRIDGE, // mFM_BLOCK_TYPE_RIVER_SOUTH_WEST
    mFM_BLOCK_TYPE_RIVER_WEST_SOUTH_BRIDGE, // mFM_BLOCK_TYPE_RIVER_WEST_SOUTH
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_RIVER_SOUTH_BRIDGE
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_RIVER_EAST_BRIDGE
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_RIVER_WEST_BRIDGE
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_RIVER_SOUTH_EAST_BRIDGE
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_RIVER_EAST_SOUTH_BRIDGE
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_RIVER_SOUTH_WEST_BRIDGE
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_RIVER_WEST_SOUTH_BRIDGE
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_SLOPE_HORIZONTAL
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_SLOPE_BOTTOM_RIGHT_CORNER
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_SLOPE_VERTICAL_RIGHT
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_SLOPE_TOP_RIGHT_CORNER
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_SLOPE_TOP_LEFT_CORNER
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_SLOPE_VERTICAL_LEFT
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_SLOPE_BOTTOM_LEFT_CORNER
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_BORDER_CLIFF_LEFT_TRANSITION
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_BORDER_CLIFF_RIGHT_TRANSITION
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_BEACH
    mFM_BLOCK_TYPE_BEACH_RIVER_BRIDGE, // mFM_BLOCK_TYPE_BEACH_RIVER
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_TRACKS_SHOP
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_SHRINE
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_TRACKS_POST_OFFICE
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_POLICE_BOX
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_POOL_SOUTH
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_POOL_EAST
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_POOL_WEST
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_POOL_SOUTH_EAST
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_POOL_EAST_SOUTH
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_POOL_SOUTH_WEST
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_POOL_WEST_SOUTH
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_TRACKS6
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_TRACKS7
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_TRACKS8
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_TRACKS9
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_BORDER_CLIFF_OCEAN_LEFT
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_BORDER_CLIFF_OCEAN_RIGHT
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_BEACH_RIVER_BRIDGE
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_OCEAN
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_MUSEUM
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_NEEDLEWORK
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_TRACKS_RIVER_BRIDGE
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_RIVER_STRAIGHT_CLIFF_HORIZONTAL_BRIDGE
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_RIVER_STRAIGHT_CLIFF_VERTICAL_RIGHT_BRIDGE
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_RIVER_STRAIGHT_CLIFF_TOP_RIGHT_CORNER_BRIDGE
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_RIVER_EAST_CLIFF_TOP_RIGHT_CORNER_BRIDGE
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_RIVER_EAST_CLIFF_TOP_LEFT_CORNER_BRIDGE
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_RIVER_STRAIGHT_CLIFF_VERTICAL_LEFT_BRIDGE
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_RIVER_STRAIGHT_CLIFF_BOTTOM_LEFT_CORNER_BRIDGE
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_OCEAN_2
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_OCEAN_3
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_OCEAN_4
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_OCEAN_5
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_ISLAND_LEFT
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_ISLAND_RIGHT
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_PORT
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_SEA_EXCEPTIONAL
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_OCEAN_6
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_OCEAN_7
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_OCEAN_8
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_RIVER_WEST_CLIFF_HORIZONTAL_BRIDGE
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_RIVER_WEST_CLIFF_TOP_RIGHT_CORNER_BRIDGE
    mFM_BLOCK_TYPE_NONE, // mFM_BLOCK_TYPE_RIVER_WEST_CLIFF_TOP_LEFT_CORNER_BRIDGE
};

extern Gfx kan_win_model[];
extern Gfx kan_win_model2[];

static Gfx* kan_win_wakuT_model_p;
static Gfx* kan_win_waku1T_model_p;
static Gfx* kan_win_waku2T_model_p;
static Gfx* kan_win_waku3T_model_p;
static Gfx* kan_win_waku4T_model_p;
static Gfx* kan_win_color0_mode_p;
static Gfx* kan_win_color1_mode_p;

extern Gfx kan_win_wakuT_model[];
extern Gfx kan_waku_w1T_model[];
extern Gfx kan_waku_w2T_model[];
extern Gfx kan_waku_w3T_model[];
extern Gfx kan_waku_w4T_model[];
extern Gfx kan_win_color0_mode[];
extern Gfx kan_win_color1_mode[];

extern mMP_HousePos_c mMP_house_pos_list[];

extern Gfx kan_win_mode[];

ATTRIBUTE_ALIGN(32) static u16 kan_tizu1_pal[16] = {
    0x0000, 0xc3b0, 0x9e87, 0xd294, 0xca52, 0xbdef, 0xb5ad, 0xb9ce,
    0xa2e8, 0xb18c, 0xa705, 0xdaff, 0xab4a, 0xffff, 0xb635, 0xbe9f,
};

ATTRIBUTE_ALIGN(32) static u16 kan_tizu2_pal[16] = {
    0x0000, 0xc3b0, 0x9e87, 0xc94a, 0xe70d, 0xe1ce, 0xb5ad, 0xb195,
    0xf390, 0xb18c, 0xa705, 0xffff, 0xd54a, 0xdaff, 0xb635, 0xbe9f,
};

static u16* l_kan_tizu_pal[2] = { kan_tizu1_pal, kan_tizu2_pal };

extern u8 kan_win_suuji1_tex_rgb_ia8[];
extern u8 kan_win_suuji2_tex_rgb_ia8[];
extern u8 kan_win_suuji3_tex_rgb_ia8[];
extern u8 kan_win_suuji4_tex_rgb_ia8[];
extern u8 kan_win_suuji5_tex_rgb_ia8[];

static u8* kan_win_evw_anime_1_tex_table[FG_BLOCK_X_NUM] = {
    kan_win_suuji1_tex_rgb_ia8, kan_win_suuji2_tex_rgb_ia8, kan_win_suuji3_tex_rgb_ia8,
    kan_win_suuji4_tex_rgb_ia8, kan_win_suuji5_tex_rgb_ia8,
};

extern u8 kan_win_a_tex_rgb_ia8[];
extern u8 kan_win_b_tex_rgb_ia8[];
extern u8 kan_win_c_tex_rgb_ia8[];
extern u8 kan_win_d_tex_rgb_ia8[];
extern u8 kan_win_e_tex_rgb_ia8[];
extern u8 kan_win_f_tex_rgb_ia8[];

static u8* kan_win_evw_anime_2_tex_table[FG_BLOCK_Z_NUM] = {
    kan_win_a_tex_rgb_ia8, kan_win_b_tex_rgb_ia8, kan_win_c_tex_rgb_ia8,
    kan_win_d_tex_rgb_ia8, kan_win_e_tex_rgb_ia8, kan_win_f_tex_rgb_ia8,
};

extern Gfx kan_win_npcT_1_model[];
extern Gfx kan_win_npcT_2_model[];
extern Gfx kan_win_npcT_3_model[];

extern Gfx kan_win_npc2T_1_model[];
extern Gfx kan_win_npc2T_2_model[];
extern Gfx kan_win_npc2T_3_model[];

static Gfx* kan_win_npcT_table[] = { kan_win_npcT_1_model, kan_win_npcT_2_model, kan_win_npcT_3_model };

static Gfx* kan_win_npc2T_table[] = { kan_win_npc2T_1_model, kan_win_npc2T_2_model, kan_win_npc2T_3_model };

extern Gfx kan_win_genzaiT_model[];

extern Gfx kan_tizu_mode[];
extern Gfx kan_tizu_model[];

extern Gfx kan_win_cursorT_model[];

extern Gfx kan_win_playerT_model[];
extern Gfx kan_win_omiseT_model[];
extern Gfx kan_win_koubanT_model[];
extern Gfx kan_win_yuuT_model[];
extern Gfx kan_win_yashiroT_model[];
extern Gfx kan_win_ekiT_model[];
extern Gfx kan_win_gomiT_model[];
extern Gfx kan_win_mu_model[];
extern Gfx kan_win_ta_model[];
extern Gfx kan_win_funeT_model[];

static mMP_LabelWord_c mMP_label_word_npc = { -92.0f, -19.0f, NULL, 0 };

static mMP_Label_c mMP_label_npc = { -98.0f, -24.0f, kan_win_npcT_1_model, { &mMP_label_word_npc, NULL } };

static mMP_LabelWord_c mMP_label_word_player = { -92.0f, -21.5f, NULL, 0 };

static mMP_Label_c mMP_label_player = { -98.0f, -26.5f, kan_win_playerT_model, { &mMP_label_word_player, NULL } };

static u8 mMP_label_str_shop[4] = { CHAR_S, CHAR_h, CHAR_o, CHAR_p };

static mMP_LabelWord_c mMP_label_word_shop = { -83.0f, -25.0f, mMP_label_str_shop, 4 };

static mMP_Label_c mMP_label_shop = { -93.0f, -30.0f, kan_win_omiseT_model, { &mMP_label_word_shop, NULL } };

static u8 mMP_label_str_police[6] = { CHAR_P, CHAR_o, CHAR_l, CHAR_i, CHAR_c, CHAR_e };

static mMP_LabelWord_c mMP_label_word_police = { -83.0f, -19.0f, mMP_label_str_police, 6 };

static u8 mMP_label_str_police2[7] = { CHAR_S, CHAR_t, CHAR_a, CHAR_t, CHAR_i, CHAR_o, CHAR_n };

static mMP_LabelWord_c mMP_label_word_police2 = { -83.0f, -31.0f, mMP_label_str_police2, 7 };

static mMP_Label_c mMP_label_police = {
    -93.0f, -30.0f, kan_win_koubanT_model, { &mMP_label_word_police, &mMP_label_word_police2 }
};

static u8 mMP_label_str_post[4] = { CHAR_P, CHAR_o, CHAR_s, CHAR_t };

static mMP_LabelWord_c mMP_label_word_post = { -83.0f, -19.0f, mMP_label_str_post, 4 };

static u8 mMP_label_str_post2[6] = { CHAR_O, CHAR_f, CHAR_f, CHAR_i, CHAR_c, CHAR_e };

static mMP_LabelWord_c mMP_label_word_post2 = { -83.0f, -31.0f, mMP_label_str_post2, 6 };

static mMP_Label_c mMP_label_post = {
    -93.0f, -30.0f, kan_win_yuuT_model, { &mMP_label_word_post, &mMP_label_word_post2 }
};

static u8 mMP_label_str_shrine[7] = { CHAR_W, CHAR_i, CHAR_s, CHAR_h, CHAR_i, CHAR_n, CHAR_g };

static mMP_LabelWord_c mMP_label_word_shrine = { -83.0f, -19.0f, mMP_label_str_shrine, 7 };

static u8 mMP_label_str_shrine2[4] = { CHAR_W, CHAR_e, CHAR_l, CHAR_l };

static mMP_LabelWord_c mMP_label_word_shrine2 = { -83.0f, -31.0f, mMP_label_str_shrine2, 4 };

static mMP_Label_c mMP_label_shrine = {
    -93.0f, -30.0f, kan_win_yashiroT_model, { &mMP_label_word_shrine, &mMP_label_word_shrine2 }
};

static u8 mMP_label_str_station[5] = { CHAR_T, CHAR_r, CHAR_a, CHAR_i, CHAR_n };

static mMP_LabelWord_c mMP_label_word_station = { -83.0f, -19.0f, mMP_label_str_station, 5 };

static u8 mMP_label_str_station2[7] = { CHAR_S, CHAR_t, CHAR_a, CHAR_t, CHAR_i, CHAR_o, CHAR_n };

static mMP_LabelWord_c mMP_label_word_station2 = { -83.0f, -31.0f, mMP_label_str_station2, 7 };

static mMP_Label_c mMP_label_station = {
    -93.0f, -31.0f, kan_win_ekiT_model, { &mMP_label_word_station, &mMP_label_word_station2 }
};

static u8 mMP_label_str_junk[4] = { CHAR_D, CHAR_u, CHAR_m, CHAR_p };

static mMP_LabelWord_c mMP_label_word_junk = { -83.0f, -25.0f, mMP_label_str_junk, 4 };

static mMP_Label_c mMP_label_junk = { -93.0f, -30.0f, kan_win_gomiT_model, { &mMP_label_word_junk, NULL } };

static u8 mMP_label_str_museum[6] = { CHAR_M, CHAR_u, CHAR_s, CHAR_e, CHAR_u, CHAR_m };

static mMP_LabelWord_c mMP_label_word_museum = { -83.0f, -25.0f, mMP_label_str_museum, 6 };

static mMP_Label_c mMP_label_museum = { -93.0f, -30.0f, kan_win_mu_model, { &mMP_label_word_museum, NULL } };

static u8 mMP_label_str_needle[6] = { CHAR_T, CHAR_a, CHAR_i, CHAR_l, CHAR_o, CHAR_r };

static mMP_LabelWord_c mMP_label_word_needle = { -83.0f, -25.0f, mMP_label_str_needle, 6 };

static mMP_Label_c mMP_label_needle = { -93.0f, -30.0f, kan_win_ta_model, { &mMP_label_word_needle, NULL } };

static u8 mMP_label_str_port[4] = { CHAR_D, CHAR_o, CHAR_c, CHAR_k };

static mMP_LabelWord_c mMP_label_word_port = { -83.0f, -25.0f, mMP_label_str_port, 4 };

static mMP_Label_c mMP_label_port = { -93.0f, -30.0f, kan_win_funeT_model, { &mMP_label_word_port, NULL } };

static mMP_Label_c* mMP_label_data[mMP_LABEL_NUM] = {
    &mMP_label_npc,     &mMP_label_player, &mMP_label_shop,   &mMP_label_police, &mMP_label_post, &mMP_label_shrine,
    &mMP_label_station, &mMP_label_junk,   &mMP_label_museum, &mMP_label_needle, &mMP_label_port,
};

static int mMP_check_layer(f32 y) {
    int layer;

    switch (mCoBG_Height2GetLayer(y)) {
        case mCoBG_LAYER0:
            layer = 2;
            break;
        case mCoBG_LAYER1:
            layer = 1;
            break;
        case mCoBG_LAYER2:
            layer = 0;
            break;
        default:
            layer = 1;
            break;
    }

    if (mRF_CheckFieldStep3() == FALSE) {
        layer--;
    }

    if (layer < 0) {
        layer = 0;
    }

    return layer;
}

static int mMP_check_bg_kind(u8 kind) {
    int res = TRUE;
    if (kind <= mFM_BLOCK_TYPE_BORDER_CLIFF_CORNER_TOP_RIGHT || kind == mFM_BLOCK_TYPE_BORDER_CLIFF_LEFT_TRANSITION ||
        kind == mFM_BLOCK_TYPE_BORDER_CLIFF_RIGHT_TRANSITION || kind == mFM_BLOCK_TYPE_BORDER_CLIFF_LEFT_TUNNEL ||
        kind == mFM_BLOCK_TYPE_BORDER_CLIFF_RIGHT_TUNNEL) {
        res = FALSE;
    }

    return res;
}

static void mMP_make_max_no_table(int* max_no_table, int count) {
    int bz;
    int i;
    int j = 0;

    for (i = 0; i < count; i++) {
        max_no_table[i] = mFM_BLOCK_TYPE_FLAT;
    }

    // i = BLOCKXZ_2_BLOCKIDX(0, 1);
    for (bz = 1; bz < mMP_BLOCKZ_MAX; bz++) {
        u8 type;
        int bx;
        for (bx = 1; bx < mMP_BLOCKX_MAX; bx++) {
            type = g_block_type_p[BLOCKXZ_2_BLOCKIDX(bx, bz)];
            if (mMP_check_bg_kind(type) == TRUE) {
                max_no_table[0] = type;

                if (Save_Get(bridge.exists) && Save_Get(bridge.block_x) == bx && Save_Get(bridge.block_z) == bz &&
                    pluss_bridge[type] != 0xFF) {
                    max_no_table[0] = pluss_bridge[type];
                }

                max_no_table++;
                j++;
            }

            if (j >= count) {
                return;
            }
        }
    }
}

static void mMP_dma_texture(u8** texture_pp, int type) {
    *texture_pp = l_map_texture[type];
}

static void mMP_set_map_texture_pal(mMP_Ovl_c* map_ovl) {
    int max_no_table[FG_BLOCK_TOTAL_NUM];
    int i;

    mMP_make_max_no_table(max_no_table, FG_BLOCK_TOTAL_NUM);
    for (i = 0; i < FG_BLOCK_TOTAL_NUM; i++) {
        map_ovl->map_pal[i] = l_map_pal[max_no_table[i]];
        mMP_dma_texture(&map_ovl->map_texture[i], max_no_table[i]);
    }
}

static mActor_name_t mMP_GetFgBlockName(mMP_Ovl_c* map_ovl, int block_x, int block_z) {
    return map_ovl->combination_table[Save_Get(combi_table[block_z][block_x]).combination_type].fg_id;
}

static void mMP_set_house_data(mMP_Ovl_c* map_ovl, mSM_MenuInfo_c* menu) {
    static u8 akiya_str[PLAYER_NAME_LEN] = "free    ";

    mMP_ResidentInfo_c* resident_p;
    mMP_LabelInfo_c* block_label;
    mMP_HousePos_c* house_pos;
    mMP_HousePos_c* house_pos_top;
    mMP_HousePos_Entry_c* pos_info;
    Private_c* priv;
    Animal_c* animal;
    Anmhome_c* home;
    int i;
    int j;
    int residents;
    mActor_name_t fgblock_name;

    priv = Save_Get(private_data);
    animal = Save_Get(animals);
    resident_p = &map_ovl->player_info[0];
    block_label = &map_ovl->label_info[1][2];

    /* Process player resident info first */
    block_label->label_cnt = PLAYER_NUM;
    block_label->label_no = mMP_LABEL_PLAYER;

    residents = 0;
    for (i = 0; i < PLAYER_NUM; i++, priv++) {
        if (mPr_CheckPrivate(priv) == TRUE && (Common_Get(now_private) != priv || mEv_CheckFirstIntro() == FALSE)) {
            mPr_CopyPlayerName(resident_p->name, priv->player_ID.player_name);
            resident_p->sex = priv->gender;
            resident_p->house_layer = 0;
            resident_p->house_idx = 0;

            block_label->residents[residents] = resident_p;
            residents++;
            resident_p++;
        }
    }

    for (residents; residents < PLAYER_NUM; residents++, resident_p++) {
        mPr_CopyPlayerName(resident_p->name, akiya_str);
        resident_p->sex = -1;
        resident_p->house_layer = 0;

        block_label->residents[residents] = resident_p;
    }

    house_pos_top = mMP_house_pos_list;
    /* Process animal resident info next */
    resident_p = &map_ovl->animal_info[0];
    residents = 0;

    for (i = 0; i < ANIMAL_NUM_MAX; i++, animal++, resident_p++) {
        if (mNpc_CheckFreeAnimalInfo(animal) == FALSE) {
            home = &animal->home_info;
            mNpc_GetNpcWorldNameAnm(resident_p->name, &animal->id);
            resident_p->sex = mNpc_GetLooks2Sex(animal->id.looks);
            resident_p->house_layer = mMP_check_layer(Common_Get(npclist[i].house_position.y));

            fgblock_name = mMP_GetFgBlockName(map_ovl, home->block_x, home->block_z);
            house_pos = house_pos_top;
            pos_info = house_pos[0].entries;

            for (house_pos; house_pos->fgblock_name != 0x03B8; house_pos++) {
                if (fgblock_name == house_pos->fgblock_name) {
                    pos_info = house_pos->entries;

                    for (j = 0; j < 3; j++, pos_info++) {
                        if (pos_info->ut_x == home->ut_x && pos_info->ut_z == home->ut_z - 1) {
                            break;
                        }
                    }

                    if (j == 3) {
                        pos_info = &house_pos->entries[0]; // default
                    }

                    break;
                }
            }

            resident_p->house_idx = pos_info->idx;

            block_label = &map_ovl->label_info[home->block_z - 1][home->block_x - 1];
            block_label->residents[block_label->label_cnt] = resident_p;
            block_label->label_cnt++;
            block_label->label_no = mMP_LABEL_NPC;
        }
    }

    /* Sort villager houses by layer, with lower layers coming first */
    block_label = (mMP_LabelInfo_c*)map_ovl->label_info;
    for (i = 0; i < FG_BLOCK_TOTAL_NUM; i++, block_label++) {
        if (block_label->label_no == mMP_LABEL_NPC && block_label->label_cnt > 1) {
            for (j = 0; j < block_label->label_cnt - 1; j++) {
                if (block_label->residents[j]->house_layer > block_label->residents[j + 1]->house_layer) {
                    resident_p = block_label->residents[j];
                    block_label->residents[j] = block_label->residents[j + 1];
                    block_label->residents[j + 1] = resident_p;
                    j = -1;
                }
            }
        }
    }
}

static void mMP_set_field_data(mMP_Ovl_c* map_ovl) {
    mMP_LabelInfo_c* label_info = (mMP_LabelInfo_c*)map_ovl->label_info;
    int* block_kind_p = g_block_kind_p + BLOCKXZ_2_BLOCKIDX(1, 1); // start at the first non-border acre
    int bx;
    int bz;

    for (bz = 0; bz < FG_BLOCK_Z_NUM; bz++) {
        for (bx = 0; bx < FG_BLOCK_X_NUM; bx++) {
            if (label_info->label_cnt <= 0) {
                int kind = *block_kind_p;

                if (kind & mRF_BLOCKKIND_SHOP) {
                    label_info->label_no = mMP_LABEL_SHOP;
                    label_info->label_cnt = 2;
                } else if (kind & mRF_BLOCKKIND_POLICE) {
                    label_info->label_no = mMP_LABEL_POLICE;
                    label_info->label_cnt = 2;
                } else if (kind & mRF_BLOCKKIND_POSTOFFICE) {
                    label_info->label_no = mMP_LABEL_POST;
                    label_info->label_cnt = 2;
                } else if (kind & mRF_BLOCKKIND_SHRINE) {
                    label_info->label_no = mMP_LABEL_SHRINE;
                    label_info->label_cnt = 2;
                } else if (kind & mRF_BLOCKKIND_STATION) {
                    label_info->label_no = mMP_LABEL_STATION;
                    label_info->label_cnt = 2;
                } else if (kind & mRF_BLOCKKIND_DUMP) {
                    label_info->label_no = mMP_LABEL_JUNK;
                    label_info->label_cnt = 2;
                } else if (kind & mRF_BLOCKKIND_MUSEUM) {
                    label_info->label_no = mMP_LABEL_MUSEUM;
                    label_info->label_cnt = 2;
                } else if (kind & mRF_BLOCKKIND_TAILORS) {
                    label_info->label_no = mMP_LABEL_NEEDLE;
                    label_info->label_cnt = 2;
                } else if (kind & mRF_BLOCKKIND_DOCK) {
                    label_info->label_no = mMP_LABEL_PORT;
                    label_info->label_cnt = 2;
                }
            }

            label_info++;
            block_kind_p++;
        }

        block_kind_p += 2; // skip X border acres
    }
}

static void mMP_set_init_data(mMP_Ovl_c* map_ovl, mSM_MenuInfo_c* menu_info) {
    mMP_LabelInfo_c* label_info = (mMP_LabelInfo_c*)map_ovl->label_info;
    PLAYER_ACTOR* player = get_player_actor_withoutCheck((GAME_PLAY*)gamePT);
    int block_x;
    int block_z;
    int i;

    if (Common_Get(field_type) != mFI_FIELDTYPE2_FG && Common_Get(door_data.next_scene_id) != 0) {
        xyz_t pos;

        xyz_t_move_s_xyz(&pos, Common_GetPointer(structure_exit_door_data.exit_position));
        mFI_Wpos2BlockNum(&block_x, &block_z, pos);
    } else {
        mFI_Wpos2BlockNum(&block_x, &block_z, player->actor_class.world.position);
    }

    map_ovl->player_bx = block_x - 1;
    map_ovl->player_bz = block_z - 1;

    map_ovl->sel_bx = map_ovl->player_bx;
    map_ovl->sel_bz = map_ovl->player_bz;

    map_ovl->map_cursor_current_xpos = (f32)map_ovl->player_bx * mMP_BLOCK_SIZE_F;
    map_ovl->map_cursor_current_zpos = -(f32)map_ovl->player_bz * mMP_BLOCK_SIZE_F;

    map_ovl->cursor_frame = 0;

    map_ovl->map_cursor_target_xpos = map_ovl->map_cursor_current_xpos;
    map_ovl->map_cursor_target_zpos = map_ovl->map_cursor_current_zpos;

    mMP_set_map_texture_pal(map_ovl);

    for (i = 0; i < FG_BLOCK_TOTAL_NUM; i++, label_info++) {
        label_info->label_cnt = 0;
    }

    mMP_set_house_data(map_ovl, menu_info);
    mMP_set_field_data(map_ovl);

    map_ovl->land_name_str_len = mMl_strlen(Save_Get(land_info.name), LAND_NAME_SIZE, CHAR_SPACE);
}

static void mMP_move_Move(Submenu* submenu, mSM_MenuInfo_c* menu) {
    (*submenu->overlay->move_Move_proc)(submenu, menu);
}

static void mMP_close(Submenu* submenu, mSM_MenuInfo_c* menu) {
    (*submenu->overlay->move_chg_base_proc)(menu, mSM_MOVE_OUT_TOP);
    sAdo_SysTrgStart(0x17D);
}

#ifdef MOUSE_INPUT
static void mMP_mouse_move(Submenu* submenu, mSM_MenuInfo_c* menu) {
    mMP_Ovl_c* map_ovl = submenu->overlay->map_ovl;
    f32 mouse_x, mouse_y;
    int bx, bz;

    if (submenu->current_menu_type != mSM_OVL_MAP ||
        !pc_mouse_update_owner(FALSE, pc_mouse_pad_active()) ||
        !pc_mouse_get_ui_position(&mouse_x, &mouse_y)) {
        return;
    }

    if (pc_mouse_button_pressed() & PC_MOUSE_BUTTON_RIGHT) {
        mMP_close(submenu, menu);
        return;
    }

    mouse_x -= 160.0f + menu->position[0] + mMP_MAP_OFFSET_X - 0.5f * mMP_BLOCK_SIZE_F;
    mouse_y -= 120.0f - menu->position[1] - mMP_MAP_OFFSET_Y - 0.5f * mMP_BLOCK_SIZE_F;
    if (mouse_x < 0.0f || mouse_x >= FG_BLOCK_X_NUM * mMP_BLOCK_SIZE_F ||
        mouse_y < 0.0f || mouse_y >= FG_BLOCK_Z_NUM * mMP_BLOCK_SIZE_F) {
        return;
    }

    bx = (int)(mouse_x / mMP_BLOCK_SIZE_F);
    bz = (int)(mouse_y / mMP_BLOCK_SIZE_F);
    if (map_ovl->sel_bx != bx || map_ovl->sel_bz != bz) {
        map_ovl->sel_bx = bx;
        map_ovl->sel_bz = bz;
        sAdo_SysTrgStart(NA_SE_CURSOL);
    }

    map_ovl->map_cursor_target_xpos = bx * mMP_BLOCK_SIZE_F;
    map_ovl->map_cursor_target_zpos = -bz * mMP_BLOCK_SIZE_F;
    map_ovl->map_cursor_current_xpos = map_ovl->map_cursor_target_xpos;
    map_ovl->map_cursor_current_zpos = map_ovl->map_cursor_target_zpos;
    menu->proc_status = mSM_OVL_PROC_PLAY;
}
#endif

static void mMP_move_Play(Submenu* submenu, mSM_MenuInfo_c* menu) {
    Submenu_Overlay_c* ovl = submenu->overlay;
    int trigger = ovl->menu_control.trigger;
    mMP_Ovl_c* map_ovl = ovl->map_ovl;
    int cursor_moved = FALSE;

    if ((trigger & (BUTTON_A | BUTTON_B | BUTTON_START)) || (menu->data0 == 1 && (trigger & BUTTON_X))) {
        mMP_close(submenu, menu);
    } else if (trigger & BUTTON_CLEFT) {
        if (map_ovl->sel_bx != 0) {
            map_ovl->sel_bx--;
            map_ovl->map_cursor_target_xpos -= mMP_BLOCK_SIZE_F;
            cursor_moved = TRUE;
        }
    } else if (trigger & BUTTON_CDOWN) {
        if (map_ovl->sel_bz < FG_BLOCK_Z_NUM - 1) {
            map_ovl->sel_bz++;
            map_ovl->map_cursor_target_zpos -= mMP_BLOCK_SIZE_F;
            cursor_moved = TRUE;
        }
    } else if (trigger & BUTTON_CUP) {
        if (map_ovl->sel_bz != 0) {
            map_ovl->sel_bz--;
            map_ovl->map_cursor_target_zpos += mMP_BLOCK_SIZE_F;
            cursor_moved = TRUE;
        }
    } else if (trigger & BUTTON_CRIGHT) {
        if (map_ovl->sel_bx < FG_BLOCK_X_NUM - 1) {
            map_ovl->sel_bx++;
            map_ovl->map_cursor_target_xpos += mMP_BLOCK_SIZE_F;
            cursor_moved = TRUE;
        }
    }

    if (cursor_moved == TRUE) {
        menu->proc_status = 2; // TODO: enum & name
        sAdo_SysTrgStart(NA_SE_CURSOL);
    }

#ifdef TARGET_PC
    map_ovl->cursor_frame += (f32)gamePT->graph->dt_num_60fps_frames;
    if (map_ovl->cursor_frame >= (f32)mMP_CURSOR_FRAMES) {
        map_ovl->cursor_frame -= (f32)mMP_CURSOR_FRAMES;
    } else if (map_ovl->cursor_frame < 0.0f) {
        map_ovl->cursor_frame = 0.0f;
    }
#else
    map_ovl->cursor_frame++;
    if (map_ovl->cursor_frame >= mMP_CURSOR_FRAMES) {
        map_ovl->cursor_frame %= mMP_CURSOR_FRAMES;
    } else if (map_ovl->cursor_frame < 0) {
        map_ovl->cursor_frame = 0;
    }
#endif
}

static void mMP_move_Wait(Submenu* submenu, mSM_MenuInfo_c* menu) {
    mMP_Ovl_c* map_ovl = submenu->overlay->map_ovl;
    f32 x_remain = add_calc(&map_ovl->map_cursor_current_xpos, map_ovl->map_cursor_target_xpos, 0.7f, 19.0f, 1.8f);
    f32 z_remain = add_calc(&map_ovl->map_cursor_current_zpos, map_ovl->map_cursor_target_zpos, 0.7f, 19.0f, 1.8f);

    if (fabsf(x_remain) < 0.1f && fabsf(z_remain) < 0.1f) {
        menu->proc_status = 1;
    }
}

static void mMP_move_End(Submenu* submenu, mSM_MenuInfo_c* menu) {
    (*submenu->overlay->move_End_proc)(submenu, menu);
}

typedef void (*mMP_MOVE_PROC)(Submenu*, mSM_MenuInfo_c*);
static void mMP_map_ovl_move(Submenu* submenu) {
    static mMP_MOVE_PROC ovl_move_proc[5] = { &mMP_move_Move, &mMP_move_Play, &mMP_move_Wait,
                                              (mMP_MOVE_PROC)&none_proc1, &mMP_move_End };

    Submenu_Overlay_c* ovl = submenu->overlay;
    mSM_MenuInfo_c* menu = &ovl->menu_info[mSM_OVL_MAP];

    (*menu->pre_move_func)(submenu);
#ifdef MOUSE_INPUT
    if (menu->proc_status == mSM_OVL_PROC_PLAY || menu->proc_status == mSM_OVL_PROC_WAIT) {
        mMP_mouse_move(submenu, menu);
    }
#endif
    (*ovl_move_proc[menu->proc_status])(submenu, menu);
}

static void mMP_map_draw_init() {
    kan_win_wakuT_model_p = kan_win_wakuT_model;
    kan_win_waku1T_model_p = kan_waku_w1T_model;
    kan_win_waku2T_model_p = kan_waku_w2T_model;
    kan_win_waku3T_model_p = kan_waku_w3T_model;
    kan_win_waku4T_model_p = kan_waku_w4T_model;
    kan_win_color0_mode_p = kan_win_color0_mode;
    kan_win_color1_mode_p = kan_win_color1_mode;
}

static int mMP_get_label_cnt(mMP_LabelInfo_c* label_info) {
    int label_no = label_info->label_no;
    if (label_no == mMP_LABEL_NPC || label_no == mMP_LABEL_PLAYER) {
        return label_info->label_cnt;
    }

    return 1;
}

static void mMP_set_house_dl(GRAPH* graph, mMP_Ovl_c* map_ovl, f32 pos_x, f32 pos_y) {
    static f32 offset_x[3] = { 5.0f, 13.0f, 17.0f };
    static f32 offset_y[3] = { -4.0f, -11.0f, -18.0f };

    mMP_LabelInfo_c* label_info;
    f32 y;
    f32 base_x;
    f32 temp_x;
    f32 base_y;
    mMP_ResidentInfo_c** resident_p;
    int bz;
    int bx;
    int i;
    Gfx* gfx;

    label_info = (mMP_LabelInfo_c*)map_ovl->label_info;

    base_y = (pos_y + mMP_MAP_OFFSET_Y) + (0.5f * mMP_BLOCK_SIZE_F);
    base_x = (pos_x + mMP_MAP_OFFSET_X) - (0.5f * mMP_BLOCK_SIZE_F);

    OPEN_DISP(graph);

    gfx = NOW_POLY_OPA_DISP;
    gSPDisplayList(gfx++, kan_win_mode);

    /* draw all villager houses */

    for (bz = 0; bz < FG_BLOCK_Z_NUM; bz++) {
        temp_x = (pos_x + mMP_MAP_OFFSET_X) - (0.5f * mMP_BLOCK_SIZE_F);
        for (bx = 0; bx < FG_BLOCK_X_NUM; bx++) {
            if (label_info->label_no == mMP_LABEL_NPC) {
                resident_p = label_info->residents;

                for (i = 0; i < label_info->label_cnt; i++) {
                    Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
                    Matrix_translate(temp_x + offset_x[(*resident_p)->house_idx % 3],
                                     base_y + offset_y[(*resident_p)->house_idx / 3], 140.0f, MTX_MULT);

                    gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                    gSPDisplayList(gfx++, kan_win_npc2T_table[(*resident_p)->house_layer]);

                    resident_p++;
                }
            }

            temp_x += mMP_BLOCK_SIZE_F;
            label_info++;
        }

        base_y -= mMP_BLOCK_SIZE_F;
        // base_x = x_save;
    }

    /* draw "current acre" icon */

    Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
    Matrix_translate(
        ((pos_x + mMP_MAP_OFFSET_X) - (0.5f * mMP_BLOCK_SIZE_F) + (f32)map_ovl->player_bx * mMP_BLOCK_SIZE_F) + 3.0f + 5.0f,
        (pos_y + mMP_MAP_OFFSET_Y - (0.5f * mMP_BLOCK_SIZE_F) - (f32)map_ovl->player_bz * mMP_BLOCK_SIZE_F) + 4.0f + 5.0f, 140.0f,
        1);

    gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfx++, kan_win_genzaiT_model);

    SET_POLY_OPA_DISP(gfx);
    CLOSE_DISP(graph);
}

static void mMP_set_map_dl(GRAPH* graph, mMP_Ovl_c* map_ovl) {
    int bz;
    int bx;
    int block = 0;
    Gfx* gfx;

    OPEN_DISP(graph);

    gfx = NOW_POLY_OPA_DISP;

    gDPSetTextureAdjustMode(gfx++, G_TA_DOLPHIN);
    gSPDisplayList(gfx++, kan_tizu_mode);

    Matrix_push();
    Matrix_translate(mMP_MAP_OFFSET_X, mMP_MAP_OFFSET_Y, 0.0f, MTX_MULT);

    for (bz = 0; bz < FG_BLOCK_Z_NUM; bz++) {
        for (bx = 0; bx < FG_BLOCK_X_NUM; bx++) {
            gSPSegment(gfx++, ANIME_1_TXT_SEG, map_ovl->map_texture[block]);
            gSPSegment(gfx++, ANIME_2_TXT_SEG, l_kan_tizu_pal[map_ovl->map_pal[block]]);
            gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(gfx++, kan_tizu_model);

            /* move right one acre */
            Matrix_translate(mMP_BLOCK_SIZE_F, 0.0f, 0.0f, MTX_MULT);
            block++;
        }

        /* move left to '1' acre and down one acre */
        Matrix_translate((-mMP_BLOCK_SIZE_F) * FG_BLOCK_X_NUM, -mMP_BLOCK_SIZE_F, 0.0f, MTX_MULT);
    }

    Matrix_pull();
    gDPSetTextureAdjustMode(gfx++, G_TA_N64);

    SET_POLY_OPA_DISP(gfx);
    CLOSE_DISP(graph);
}

static void mMP_set_cursol_dl(GRAPH* graph, mMP_Ovl_c* map_ovl, f32 base_x, f32 base_y) {
    static int col_g[mMP_CURSOR_FRAMES] = { 0, 1, 2, 5, 10, 20, 50, 75, 90, 100, 90, 75, 50, 20, 10, 5, 2, 1 };

    static f32 cursol_scale[mMP_CURSOR_FRAMES] = { 1.0f, 1.015f, 1.03f, 1.04f, 1.05f, 1.06f, 1.07f, 1.08f, 1.09f,
                                                   1.1f, 1.09f,  1.08f, 1.07f, 1.06f, 1.05f, 1.04f, 1.03f, 1.015f };

    f32 x = map_ovl->map_cursor_current_xpos + base_x;
    f32 y = map_ovl->map_cursor_current_zpos + base_y;
#ifdef TARGET_PC
    int frame = (int)map_ovl->cursor_frame;
#else
    int frame = map_ovl->cursor_frame;
#endif
    Gfx* gfx;

    if (frame >= mMP_CURSOR_FRAMES) {
        frame %= mMP_CURSOR_FRAMES;
    } else if (frame < 0) {
        frame = 0;
    }

    Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
    Matrix_translate(x + mMP_MAP_OFFSET_X, y + mMP_MAP_OFFSET_Y, 140.0f, MTX_MULT);

    Matrix_scale(cursol_scale[frame], cursol_scale[frame], 1.0f, MTX_MULT);

    OPEN_DISP(graph);

    gfx = NOW_POLY_OPA_DISP;

    gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetPrimColor(gfx++, 0, 255, 255, col_g[frame], 255, 255);
    gSPDisplayList(gfx++, kan_win_cursorT_model);

    SET_POLY_OPA_DISP(gfx);

    CLOSE_DISP(graph);
}

static void mMP_set_label_dl(GAME* game, mMP_LabelInfo_c* label_info, f32 xpos, f32 ypos) {
    mMP_Label_c* label = mMP_label_data[label_info->label_no];

    if (label != NULL) {
        mMP_ResidentInfo_c** resident_p = label_info->residents;
        mMP_LabelWord_c* word;
        f32 base_x = 160.0f + xpos;
        f32 base_y = 120.0f - ypos;
        int i;

        for (i = 0; i < mMP_LABEL_WORD_NUM; i++) {
            word = label->words[i];

            if (word != NULL) {
                if (word->str == NULL) {
                    /* draw resident name label (villagers, players) */
                    int j;

                    for (j = 0; j < label_info->label_cnt; j++) {
                        int width = mFont_GetStringWidth((*resident_p)->name, PLAYER_NAME_LEN, TRUE);
                        f32 scale_x = 54.0f / width;

                        if (scale_x > 0.75f) {
                            scale_x = 0.75f;
                        }

                        if (resident_p[0]->sex != -1) {
                            mFont_SetLineStrings(game, resident_p[0]->name, PLAYER_NAME_LEN, base_x + word->ofs_x,
                                                 base_y - word->ofs_y, 255, 75, 40, 255, FALSE, TRUE, scale_x, 0.75f,
                                                 mFont_MODE_POLY);
                        } else {
                            mFont_SetLineStrings(game, resident_p[0]->name, PLAYER_NAME_LEN, base_x + word->ofs_x,
                                                 base_y - word->ofs_y, 165, 145, 140, 255, FALSE, TRUE, scale_x, 0.75f,
                                                 mFont_MODE_POLY);
                        }

                        resident_p++;
                        base_y += 12.0f;
                    }
                } else {
                    /* draw building name */
                    mFont_SetLineStrings(game, word->str, word->str_len, base_x + word->ofs_x, base_y - word->ofs_y,
                                         120, 95, 205, 255, FALSE, TRUE, 0.75f, 0.75f, mFont_MODE_POLY);
                }
            }
        }
    }
}

static void mMP_set_base_dl(GRAPH* graph, mSM_MenuInfo_c* menu) {
    Gfx* gfx;

    OPEN_DISP(graph);
    gfx = NOW_POLY_OPA_DISP;

    if (menu->data0 == 0) {
        gSPSegment(gfx++, G_MWO_SEGMENT_B, kan_win_color0_mode_p);
    } else {
        gSPSegment(gfx++, G_MWO_SEGMENT_B, kan_win_color1_mode_p);
    }

    gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfx++, kan_win_model);

    SET_POLY_OPA_DISP(gfx);
    CLOSE_DISP(graph);
}

static void mMP_set_win_dl(GRAPH* graph, mMP_Ovl_c* map_ovl, mMP_LabelInfo_c* label_info) {
    int label_count = label_info->label_cnt;
    Gfx* gfx;

    OPEN_DISP(graph);
    gfx = NOW_POLY_OPA_DISP;

    /* move X-acre number texture into segment 8 and Z-acre character texture int segment 9 */
    gSPSegment(gfx++, ANIME_1_TXT_SEG, kan_win_evw_anime_1_tex_table[map_ovl->sel_bx]);
    gSPSegment(gfx++, ANIME_2_TXT_SEG, kan_win_evw_anime_2_tex_table[map_ovl->sel_bz]);

    /* move label area texture into segment 10 based on number of labels */
    if (label_count == 4) {
        gSPSegment(gfx++, ANIME_3_TXT_SEG, kan_win_waku4T_model_p);
    } else if (label_count == 3) {
        gSPSegment(gfx++, ANIME_3_TXT_SEG, kan_win_waku3T_model_p);
    } else if (label_count == 1) {
        gSPSegment(gfx++, ANIME_3_TXT_SEG, kan_win_wakuT_model_p);
    } else if (label_count == 0) {
        gSPSegment(gfx++, ANIME_3_TXT_SEG, kan_win_waku1T_model_p);
    } else { /* label_count == 2 */
        gSPSegment(gfx++, ANIME_3_TXT_SEG, kan_win_waku2T_model_p);
    }

    gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfx++, kan_win_model2);

    SET_POLY_OPA_DISP(gfx);
    CLOSE_DISP(graph);
}

static void mMP_set_label_top_dl(GRAPH* graph, mMP_LabelInfo_c* label_info) {
    mMP_Label_c* label = mMP_label_data[label_info->label_no];
    mMP_ResidentInfo_c** resident_p;

    if (label != NULL) {
        int count = mMP_get_label_cnt(label_info);
        int i;
        Gfx* gfx;

        OPEN_DISP(graph);
        gfx = NOW_POLY_OPA_DISP;

        Matrix_push();
        Matrix_translate(label->ofs_x, label->ofs_y, 0.0f, MTX_MULT);

        if (label_info->label_no == mMP_LABEL_NPC) {
            resident_p = label_info->residents;
        } else {
            resident_p = NULL;
        }

        for (i = 0; i < count; i++) {
            gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            if (resident_p != NULL && *resident_p != NULL && (*resident_p)->house_layer != 0) {
                gSPDisplayList(gfx++, kan_win_npcT_table[(*resident_p)->house_layer]);
                resident_p++;
            } else {
                gSPDisplayList(gfx++, label->gfx);

                if (resident_p != NULL) {
                    resident_p++;
                }
            }

            Matrix_translate(0.0f, -12.0f, 0.0f, MTX_MULT);
        }

        Matrix_pull();

        SET_POLY_OPA_DISP(gfx);
        CLOSE_DISP(graph);
    }
}

static void mMP_set_dl(Submenu* submenu, GAME* game, mSM_MenuInfo_c* menu) {
    static u8 land_color[2][4] = {
        { 255, 0, 255, 255 },
        { 60, 60, 255, 255 },
    };

    GRAPH* graph = game->graph;
    mMP_Ovl_c* map_ovl = submenu->overlay->map_ovl;
    u8* col = land_color[menu->data0];
    mMP_LabelInfo_c* label_info = &map_ovl->label_info[map_ovl->sel_bz][map_ovl->sel_bx];
    u8* land_name;
    f32 xpos = menu->position[0];
    f32 ypos = menu->position[1];
    f32 str_xpos;
    f32 str_ypos;

    Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
    Matrix_translate(xpos, ypos, 140.0f, MTX_MULT);

    mMP_set_base_dl(graph, menu);
    mMP_set_map_dl(graph, map_ovl);
    mMP_set_win_dl(graph, map_ovl, label_info);
    mMP_set_label_top_dl(graph, label_info);
    mMP_set_house_dl(graph, map_ovl, xpos, ypos);
    mMP_set_cursol_dl(graph, map_ovl, xpos, ypos);

    (*submenu->overlay->set_char_matrix_proc)(graph);

    /* draw town name */
    land_name = Save_Get(land_info.name);
    str_xpos = (xpos + -136.0f) + 24.0f;
    str_ypos = (ypos + 102.0f) + -29.0f;
    mFont_SetLineStrings(game, land_name, map_ovl->land_name_str_len, str_xpos + 160.0f, 120.0f - str_ypos, col[0],
                         col[1], col[2], 255, FALSE, TRUE, 1.0f, 1.0f, mFont_MODE_POLY);

    mMP_set_label_dl(game, label_info, xpos, ypos);
}

static void mMP_map_ovl_draw(Submenu* submenu, GAME* game) {
    Submenu_Overlay_c* overlay = submenu->overlay;
    mSM_MenuInfo_c* menu = &overlay->menu_info[mSM_OVL_MAP];

    (*menu->pre_draw_func)(submenu, game);
    mMP_set_dl(submenu, game, menu);
}

extern void mMP_map_ovl_set_proc(Submenu* submenu) {
    Submenu_Overlay_c* overlay = submenu->overlay;

    overlay->menu_control.menu_move_func = &mMP_map_ovl_move;
    overlay->menu_control.menu_draw_func = &mMP_map_ovl_draw;
}

static void mMP_map_ovl_init(Submenu* submenu) {
    Submenu_Overlay_c* overlay = submenu->overlay;
    mSM_MenuInfo_c* menu = &overlay->menu_info[mSM_OVL_MAP];

    overlay->menu_control.animation_flag = FALSE;
    (*submenu->overlay->move_chg_base_proc)(menu, mSM_MOVE_IN_TOP);

    sAdo_SysTrgStart(0x17C);
    mMP_set_init_data(submenu->overlay->map_ovl, menu);
}

extern void mMP_map_ovl_construct(Submenu* submenu) {
    Submenu_Overlay_c* overlay = submenu->overlay;

    if (overlay->map_ovl == NULL) {
        overlay->map_ovl = (mMP_Ovl_c*)zelda_malloc(sizeof(mMP_Ovl_c));
        mem_clear((u8*)overlay->map_ovl, sizeof(mMP_Ovl_c), 0);
        overlay->map_ovl->combination_table = data_combi_table;
        mMP_map_draw_init();
    }

    mMP_map_ovl_init(submenu);
    mMP_map_ovl_set_proc(submenu);
}

extern void mMP_map_ovl_destruct(Submenu* submenu) {
    mMP_Ovl_c* map_ovl = submenu->overlay->map_ovl;

    if (map_ovl != NULL) {
        zelda_free(map_ovl);
    }

    submenu->overlay->map_ovl = NULL;
}
