#ifndef M_FONT_H
#define M_FONT_H

#include "types.h"
#include "m_lib.h"
#include "graph.h"
#include "game.h"
#include "libforest/gbi_extensions.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CHAR_INVERT_EXCLAMATION 0
#define CHAR_INVERT_QUESTIONMARK 1
#define CHAR_DIAERESIS_A 2
#define CHAR_GRAVE_A 3
#define CHAR_ACUTE_A 4
#define CHAR_CIRCUMFLEX_A 5
#define CHAR_TILDE_A 6
#define CHAR_ANGSTROM_A 7
#define CHAR_CEDILLA 8
#define CHAR_GRAVE_E 9
#define CHAR_ACUTE_E 10
#define CHAR_CIRCUMFLEX_E 11
#define CHAR_DIARESIS_E 12
#define CHAR_GRAVE_I 13
#define CHAR_ACUTE_I 14
#define CHAR_CIRCUMFLEX_I 15
#define CHAR_DIARESIS_I 16
#define CHAR_ETH 17
#define CHAR_TILDE_N 18
#define CHAR_GRAVE_O 19
#define CHAR_ACUTE_O 20
#define CHAR_CIRCUMFLEX_O 21
#define CHAR_TILDE_O 22
#define CHAR_DIARESIS_O 23
#define CHAR_OE 24
#define CHAR_GRAVE_U 25
#define CHAR_ACUTE_U 26
#define CHAR_CIRCUMFLEX_U 27
#define CHAR_DIARESIS_U 28
#define CHAR_LOWER_BETA 29
#define CHAR_THORN 30
#define CHAR_GRAVE_a 31
#define CHAR_SPACE 32
#define CHAR_EXCLAMATION 33
#define CHAR_QUOTATION 34
#define CHAR_ACUTE_a 35
#define CHAR_CIRCUMFLEX_a 36
#define CHAR_PERCENT 37
#define CHAR_AMPERSAND 38
#define CHAR_APOSTROPHE 39
#define CHAR_OPEN_PARENTHESIS 40
#define CHAR_CLOSE_PARENTHESIS 41
#define CHAR_TILDE 42
#define CHAR_SYMBOL_HEART 43
#define CHAR_COMMA 44
#define CHAR_DASH 45
#define CHAR_PERIOD 46
#define CHAR_SYMBOL_MUSIC_NOTE 47
#define CHAR_ZERO 48
#define CHAR_ONE 49
#define CHAR_TWO 50
#define CHAR_THREE 51
#define CHAR_FOUR 52
#define CHAR_FIVE 53
#define CHAR_SIX 54
#define CHAR_SEVEN 55
#define CHAR_EIGHT 56
#define CHAR_NINE 57
#define CHAR_COLON 58
#define CHAR_SYMBOL_DROPLET 59
#define CHAR_LESS_THAN 60
#define CHAR_EQUALS 61
#define CHAR_GREATER_THAN 62
#define CHAR_QUESTIONMARK 63
#define CHAR_AT_SIGN 64
#define CHAR_A 65
#define CHAR_B 66
#define CHAR_C 67
#define CHAR_D 68
#define CHAR_E 69
#define CHAR_F 70
#define CHAR_G 71
#define CHAR_H 72
#define CHAR_I 73
#define CHAR_J 74
#define CHAR_K 75
#define CHAR_L 76
#define CHAR_M 77
#define CHAR_N 78
#define CHAR_O 79
#define CHAR_P 80
#define CHAR_Q 81
#define CHAR_R 82
#define CHAR_S 83
#define CHAR_T 84
#define CHAR_U 85
#define CHAR_V 86
#define CHAR_W 87
#define CHAR_X 88
#define CHAR_Y 89
#define CHAR_Z 90
#define CHAR_TILDE_a 91
#define CHAR_SYMBOL_ANNOYED 92
#define CHAR_DIARESIS_a 93
#define CHAR_ANGSTROM_a 94
#define CHAR_UNDERSCORE 95
#define CHAR_LOWER_CEDILLA 96
#define CHAR_a 97
#define CHAR_b 98
#define CHAR_c 99
#define CHAR_d 100
#define CHAR_e 101
#define CHAR_f 102
#define CHAR_g 103
#define CHAR_h 104
#define CHAR_i 105
#define CHAR_j 106
#define CHAR_k 107
#define CHAR_l 108
#define CHAR_m 109
#define CHAR_n 110
#define CHAR_o 111
#define CHAR_p 112
#define CHAR_q 113
#define CHAR_r 114
#define CHAR_s 115
#define CHAR_t 116
#define CHAR_u 117
#define CHAR_v 118
#define CHAR_w 119
#define CHAR_x 120
#define CHAR_y 121
#define CHAR_z 122
#define CHAR_GRAVE_e 123
#define CHAR_ACUTE_e 124
#define CHAR_CIRCUMFLEX_e 125
#define CHAR_DIARESIS_e 126
#define CHAR_CONTROL_CODE 127
#define CHAR_MESSAGE_TAG 128
#define CHAR_GRAVE_i 129
#define CHAR_ACUTE_i 130
#define CHAR_CIRCUMFLEX_i 131
#define CHAR_DIARESIS_i 132
#define CHAR_INTERPUNCT 133
#define CHAR_LOWER_ETH 134
#define CHAR_TILDE_n 135
#define CHAR_GRAVE_o 136
#define CHAR_ACUTE_o 137
#define CHAR_CIRCUMFLEX_o 138
#define CHAR_TILDE_o 139
#define CHAR_DIARESIS_o 140
#define CHAR_oe 141
#define CHAR_GRAVE_u 142
#define CHAR_ACUTE_u 143
#define CHAR_HYPHEN 144
#define CHAR_CIRCUMFLEX_u 145
#define CHAR_DIARESIS_u 146
#define CHAR_ACUTE_y 147
#define CHAR_DIARESIS_y 148
#define CHAR_LOWER_THORN 149
#define CHAR_ACUTE_Y 150
#define CHAR_BROKEN_BAR 151
#define CHAR_SILCROW 152
#define CHAR_FEMININE_ORDINAL 153
#define CHAR_MASCULINE_ORDINAL 154
#define CHAR_DOUBLE_VERTICAL_BAR 155
#define CHAR_LATIN_MU 156
#define CHAR_SUPERSCRIPT_THREE 157
#define CHAR_SUPERSCRIPT_TWO 158
#define CHAR_SUPRESCRIPT_ONE 159
#define CHAR_MACRON_SYMBOL 160
#define CHAR_LOGICAL_NEGATION 161
#define CHAR_ASH 162
#define CHAR_LOWER_ASH 163
#define CHAR_INVERT_QUOTATION 164
#define CHAR_GUILLEMET_OPEN 165
#define CHAR_GUILLEMET_CLOSE 166
#define CHAR_SYMBOL_SUN 167
#define CHAR_SYMBOL_CLOUD 168
#define CHAR_SYMBOL_UMBRELLA 169
#define CHAR_SYMBOL_WIND 170
#define CHAR_SYMBOL_SNOWMAN 171
#define CHAR_LINES_CONVERGE_RIGHT 172
#define CHAR_LINES_CONVERGE_LEFT 173
#define CHAR_FORWARD_SLASH 174
#define CHAR_INFINITY 175
#define CHAR_CIRCLE 176
#define CHAR_CROSS 177
#define CHAR_SQUARE 178
#define CHAR_TRIANGLE 179
#define CHAR_PLUS 180
#define CHAR_SYMBOL_LIGTNING 181 // ?? maybe electric also?
#define CHAR_MARS_SYMBOL 182 // aka male symbol
#define CHAR_VENUS_SYMBOL 183 // aka female symbol
#define CHAR_SYMBOL_FLOWER 184
#define CHAR_SYMBOL_STAR 185
#define CHAR_SYMBOL_SKULL 186
#define CHAR_SYMBOL_SURPRISE 187
#define CHAR_SYMBOL_HAPPY 188
#define CHAR_SYMBOL_SAD 189
#define CHAR_SYMBOL_ANGRY 190
#define CHAR_SYMBOL_SMILE 191
#define CHAR_DIMENSION_SIGN 192 // multiplication character
#define CHAR_OBELUS_SIGN 193 // division character
#define CHAR_SYMBOL_HAMMER 194
#define CHAR_SYMBOL_RIBBON 195
#define CHAR_SYMBOL_MAIL 196
#define CHAR_SYMBOL_MONEY 197
#define CHAR_SYMBOL_PAW 198
#define CHAR_SYMBOL_SQUIRREL 199 // might be dog? would make a bit more sense ig
#define CHAR_SYMBOL_CAT 200
#define CHAR_SYMBOL_RABBIT 201
#define CHAR_SYMBOL_OCTOPUS 202 // could also be bird...?
#define CHAR_SYMBOL_COW 203
#define CHAR_SYMBOL_PIG 204
#define CHAR_NEW_LINE 205
#define CHAR_SYMBOL_FISH 206
#define CHAR_SYMBOL_BUG 207
#define CHAR_SEMICOLON 208
#define CHAR_HASHTAG 209
#define CHAR_SPACE_2 210 // Short space
#define CHAR_SPACE_3 211 // Wide space
#define CHAR_SYMBOL_KEY 212
/* Begin EU-only symbols, unused in AC */
#define CHAR_LEFT_QUOTATION 213
#define CHAR_RIGHT_QUOTATION 214
#define CHAR_LEFT_APOSTROPHE 215
#define CHAR_RIGHT_APOSTROPHE 216
#define CHAR_ETHEL 217
#define CHAR_LOWER_ETHEL 218
#define CHAR_ORDINAL_e 219
#define CHAR_ORDINAL_er 220
#define CHAR_ORDINAL_re 221
#define CHAR_BACKSLASH 222
/* Unused characters */
#define CHAR_223 223
#define CHAR_224 224
#define CHAR_225 225
#define CHAR_226 226
#define CHAR_227 227
#define CHAR_228 228
#define CHAR_229 229
#define CHAR_230 230
#define CHAR_231 231
#define CHAR_232 232
#define CHAR_233 233
#define CHAR_234 234
#define CHAR_235 235
#define CHAR_236 236
#define CHAR_237 237
#define CHAR_238 238
#define CHAR_239 239
#define CHAR_240 240
#define CHAR_241 241
#define CHAR_242 242
#define CHAR_243 243
#define CHAR_244 244
#define CHAR_245 245
#define CHAR_246 246
#define CHAR_247 247
#define CHAR_248 248
#define CHAR_249 249
#define CHAR_250 250
#define CHAR_251 251
#define CHAR_252 252
#define CHAR_253 253
#define CHAR_254 254
#define CHAR_255 255

#define TOTAL_CHARS 256

#define mFont_MARKTYPE_VERT_ARROW 0
#define mFont_MARKTYPE_HORI_ARROW 1
#define mFont_MARKTYPE_CURSOR 2
#define mFont_MARKTYPE_NEXT 3
#define mFont_MARKTYPE_CHOICE 4
#define mFont_MARKTYPE_TOTAL 5

#define mFont_MODE_POLY 0
#define mFont_MODE_FONT 1

enum {
  mFont_CONT_CODE_BEGIN = 0,
  mFont_CONT_CODE_LAST = mFont_CONT_CODE_BEGIN,
  mFont_CONT_CODE_CONTINUE,
  mFont_CONT_CODE_CLEAR,
  mFont_CONT_CODE_CURSOR_SET_TIME,
  mFont_CONT_CODE_BUTTON,
  mFont_CONT_CODE_COLOR,
  mFont_CONT_CODE_ABLE_CANCEL,
  mFont_CONT_CODE_UNABLE_CANCEL,
  mFont_CONT_CODE_SET_DEMO_ORDER_PLAYER,
  mFont_CONT_CODE_SET_DEMO_ORDER_NPC0,
  mFont_CONT_CODE_SET_DEMO_ORDER_NPC1,
  mFont_CONT_CODE_SET_DEMO_ORDER_NPC2,
  mFont_CONT_CODE_SET_DEMO_ORDER_QUEST,
  mFont_CONT_CODE_SET_SELECT_WINDOW,
  mFont_CONT_CODE_SET_NEXT_MESSAGE_F,
  mFont_CONT_CODE_SET_NEXT_MESSAGE_0,
  mFont_CONT_CODE_SET_NEXT_MESSAGE_1,
  mFont_CONT_CODE_SET_NEXT_MESSAGE_2,
  mFont_CONT_CODE_SET_NEXT_MESSAGE_3,
  mFont_CONT_CODE_SET_NEXT_MESSAGE_RANDOM_2,
  mFont_CONT_CODE_SET_NEXT_MESSAGE_RANDOM_3,
  mFont_CONT_CODE_SET_NEXT_MESSAGE_RANDOM_4,
  mFont_CONT_CODE_SET_SELECT_STRING_2,
  mFont_CONT_CODE_SET_SELECT_STRING_3,
  mFont_CONT_CODE_SET_SELECT_STRING_4,
  mFont_CONT_CODE_SET_FORCE_NEXT,
  mFont_CONT_CODE_PUT_STRING_PLAYER_NAME,
  mFont_CONT_CODE_PUT_STRING_TALK_NAME,
  mFont_CONT_CODE_PUT_STRING_TAIL,
  mFont_CONT_CODE_PUT_STRING_YEAR,
  mFont_CONT_CODE_PUT_STRING_MONTH,
  mFont_CONT_CODE_PUT_STRING_WEEK,
  mFont_CONT_CODE_PUT_STRING_DAY,
  mFont_CONT_CODE_PUT_STRING_HOUR,
  mFont_CONT_CODE_PUT_STRING_MIN,
  mFont_CONT_CODE_PUT_STRING_SEC,
  mFont_CONT_CODE_PUT_STRING_FREE0,
  mFont_CONT_CODE_PUT_STRING_FREE1,
  mFont_CONT_CODE_PUT_STRING_FREE2,
  mFont_CONT_CODE_PUT_STRING_FREE3,
  mFont_CONT_CODE_PUT_STRING_FREE4,
  mFont_CONT_CODE_PUT_STRING_FREE5,
  mFont_CONT_CODE_PUT_STRING_FREE6,
  mFont_CONT_CODE_PUT_STRING_FREE7,
  mFont_CONT_CODE_PUT_STRING_FREE8,
  mFont_CONT_CODE_PUT_STRING_FREE9,
  mFont_CONT_CODE_PUT_STRING_DETERMINATION,
  mFont_CONT_CODE_PUT_STRING_COUNTRY_NAME,
  mFont_CONT_CODE_PUT_STRING_RANDOM_NUMBER_2,
  mFont_CONT_CODE_PUT_STRING_ITEM0,
  mFont_CONT_CODE_PUT_STRING_ITEM1,
  mFont_CONT_CODE_PUT_STRING_ITEM2,
  mFont_CONT_CODE_PUT_STRING_ITEM3,
  mFont_CONT_CODE_PUT_STRING_ITEM4,
  mFont_CONT_CODE_PUT_STRING_FREE10,
  mFont_CONT_CODE_PUT_STRING_FREE11,
  mFont_CONT_CODE_PUT_STRING_FREE12,
  mFont_CONT_CODE_PUT_STRING_FREE13,
  mFont_CONT_CODE_PUT_STRING_FREE14,
  mFont_CONT_CODE_PUT_STRING_FREE15,
  mFont_CONT_CODE_PUT_STRING_FREE16,
  mFont_CONT_CODE_PUT_STRING_FREE17,
  mFont_CONT_CODE_PUT_STRING_FREE18,
  mFont_CONT_CODE_PUT_STRING_FREE19,
  mFont_CONT_CODE_PUT_STRING_MAIL,
  mFont_CONT_CODE_SET_PLAYER_DESTINY0,
  mFont_CONT_CODE_SET_PLAYER_DESTINY1,
  mFont_CONT_CODE_SET_PLAYER_DESTINY2,
  mFont_CONT_CODE_SET_PLAYER_DESTINY3,
  mFont_CONT_CODE_SET_PLAYER_DESTINY4,
  mFont_CONT_CODE_SET_PLAYER_DESTINY5,
  mFont_CONT_CODE_SET_PLAYER_DESTINY6,
  mFont_CONT_CODE_SET_PLAYER_DESTINY7,
  mFont_CONT_CODE_SET_PLAYER_DESTINY8,
  mFont_CONT_CODE_SET_PLAYER_DESTINY9,
  mFont_CONT_CODE_SET_MESSAGE_CONTENTS_NORMAL,
  mFont_CONT_CODE_SET_MESSAGE_CONTENTS_ANGRY,
  mFont_CONT_CODE_SET_MESSAGE_CONTENTS_SAD,
  mFont_CONT_CODE_SET_MESSAGE_CONTENTS_FUN,
  mFont_CONT_CODE_SET_MESSAGE_CONTENTS_SLEEPY,
  mFont_CONT_CODE_SET_COLOR_CHAR,
  mFont_CONT_CODE_SOUND_CUT,
  mFont_CONT_CODE_SET_LINE_OFFSET,
  mFont_CONT_CODE_SET_LINE_TYPE,
  mFont_CONT_CODE_SET_CHAR_SCALE,
  mFont_CONT_CODE_BUTTON2,
  mFont_CONT_CODE_BGM_MAKE,
  mFont_CONT_CODE_BGM_DELETE,
  mFont_CONT_CODE_MSG_TIME_END,
  mFont_CONT_CODE_SOUND_TRG_SYS,
  mFont_CONT_CODE_SET_LINE_SCALE,
  mFont_CONT_CODE_SOUND_NO_PAGE,
  mFont_CONT_CODE_VOICE_TRUE,
  mFont_CONT_CODE_VOICE_FALSE,
  mFont_CONT_CODE_SELECT_NO_B,
  mFont_CONT_CODE_GIVE_OPEN,
  mFont_CONT_CODE_GIVE_CLOSE,
  mFont_CONT_CODE_SET_MESSAGE_CONTENTS_GLOOMY,
  mFont_CONT_CODE_SELECT_NO_B_CLOSE,
  mFont_CONT_CODE_SET_NEXT_MESSAGE_RANDOM_SECTION,
  mFont_CONT_CODE_AGB_DUMMY0,
  mFont_CONT_CODE_AGB_DUMMY1,
  mFont_CONT_CODE_AGB_DUMMY2,
  mFont_CONT_CODE_SPACE,
  mFont_CONT_CODE_AGB_DUMMY3,
  mFont_CONT_CODE_AGB_DUMMY4,
  mFont_CONT_CODE_AGB_MALE_FEMALE_CHECK,
  mFont_CONT_CODE_AGB_DUMMY5,
  mFont_CONT_CODE_AGB_DUMMY6,
  mFont_CONT_CODE_AGB_DUMMY7,
  mFont_CONT_CODE_AGB_DUMMY8,
  mFont_CONT_CODE_AGB_DUMMY9,
  mFont_CONT_CODE_AGB_DUMMY10,
  mFont_CONT_CODE_PUT_STRING_ISLAND_NAME,
  mFont_CONT_CODE_SET_CURSOR_JUST,
  mFont_CONT_CODE_CLR_CURSOR_JUST,
  mFont_CONT_CODE_CUT_ARTICLE,
  mFont_CONT_CODE_CAPITAL_LETTER,
  mFont_CONT_CODE_PUT_STRING_AM_PM,
  mFont_CONT_CODE_SET_NEXT_MESSAGE_4,
  mFont_CONT_CODE_SET_NEXT_MESSAGE_5,
  mFont_CONT_CODE_SET_SELECT_STRING_5,
  mFont_CONT_CODE_SET_SELECT_STRING_6,

  mFont_CONT_CODE_NUM,
  mFont_CONT_CODE_END = 256
};

// TODO: figure out the other values for this
enum {
  mFont_CONT_ATTRIBUTE_0,
  mFont_CONT_ATTRIBUTE_DEMO,
  mFont_CONT_ATTRIBUTE_STRING,
  mFont_CONT_ATTRIBUTE_3,
  mFont_CONT_ATTRIBUTE_SENTENCE,
  mFont_CONT_ATTRIBUTE_CHARACTER,
  mFont_CONT_ATTRIBUTE_BGM,
  mFont_CONT_ATTRIBUTE_SE,
  mFont_CONT_ATTRIBUTE_AGB_DUMMY,

  mFont_CONT_ATTRIBUTE_END
};

enum {
  mFont_LineType_Top,
  mFont_LineType_Center,
  mFont_LineType_Bottom,

  mFont_LineType_End
};

enum {
  mFont_BGM_QUIET,

  // TODO

  mFont_BGM_NUM = 9
};

enum {
  mFont_BGM_STOP_TYPE_NORMAL,
  mFont_BGM_STOP_TYPE_QUICK,
  mFont_BGM_STOP_TYPE_RESETTI,

  mFont_BGM_STOP_TYPE_NUM
};

enum {
  mFont_SE_0,

  // TODO

  mFont_SE_NUM = 7
};

#define mFont_CHAR_FLAG_CUT 1
#define mFont_CHAR_FLAG_USE_POLY 2
#define mFont_CHAR_FLAG_SCALE 4
#define mFont_CHAR_FLAG_SCALE_RESET 8

/* sizeof(struct font_char_s) == 0x40 */
typedef struct font_char_s {
  /* 0x00 */ u8* char_p;
  /* 0x04 */ s8 len;
  /* 0x05 */ u8 flags;
  /* 0x06 */ u8 pad0[2];
  /* 0x08 */ xy_t position;
  /* 0x10 */ xy_t scale;
  /* 0x18 */ xy_t inv_scale;
  /* 0x20 */ xy_t scaled_size;
  /* 0x28 */ xy_t inv_scaled_size;
  /* 0x30 */ f32 ofs_y;
  /* 0x34 */ rgba_t color;
  /* 0x38 */ u8 color_ctr;
  /* 0x39 */ u8 pad1[3];
  /* 0x3C */ f32 width;
} mFontChar;

#define mFont_SENTENCE_FLAG_CUT 1
#define mFont_SENTENCE_FLAG_REVERT 2
#define mFont_SENTENCE_FLAG_USE_POLY 4
#define mFont_SENTENCE_FLAG_3 8
#define mFont_SENTENCE_FLAG_NO_COMBINE 16
#define mFont_SENTENCE_FLAG_NO_COLOR 32
#define mFont_SENTENCE_SKIP_DRAW_NEW_LINE 64
#define mFont_SENTENCE_FLAG_VOICE_SE 128
#define mFont_SENTENCE_FLAG_8 256

typedef struct font_sentence_s {
  u8* sentence_p;
  int len;
  u32 flags;
  xy_t position;
  int line_type;
  rgba_t color;
  xy_t scale;
  xy_t inv_scale;
  int now_idx;
  f32 offset;
  f32 width;
  f32 line_scale;
  f32 inv_line_scale;
  int se_pos;
  s16 se_character_id;
  u8 voice_idx;
  u8 voice2_idx;
  u8 voice3_idx;
  u8 pad[3];
  mFontChar character;
} mFontSentence;

#define mFont_TEX_CHAR_WIDTH 12
#define mFont_TEX_CHAR_HEIGHT 16

#define mFont_TEX_CHAR_WIDTH_F32 12.0f
#define mFont_TEX_CHAR_HEIGHT_F32 16.0f

#define mFont_SCALE_F 16.0f

typedef void (*mFont_ControlCodeCharFunc)(mFontChar*, Gfx**);
typedef void (*mFont_ControlCodeSentenceFunc)(mFontSentence*, Gfx**);

extern void mFont_ct();
extern int mFont_UnintToString(u8* str, int figure, u32 num, int figure_start, int left_cut, int fill_zero, int separator);
extern int mFont_char_save_data_check(u8 c);
extern u8 mFont_small_to_capital(u8 small);
extern int mFont_GetCodeWidth(u8 c, int cut);
extern int mFont_GetStringWidth(u8* str, int len, int cut);
extern int mFont_GetStringWidth2(u8* str, int len, int cut);
extern int mFont_CodeSize_get(u8* str);
extern int mFont_CodeSize_idx_get(u8* str, int idx);
extern int mFont_cont_attr_get(int cont_code);
extern void mFont_gppSetMode(Gfx** gfx_pp);
extern void mFont_SetMode(GRAPH* graph, int mode);
extern void mFont_SetPrimColor(GRAPH* graph, int r, int g, int b, int a, int mode);
extern void mFont_SetCombineMode(GRAPH* graph, int revert_flag, int mode);
extern f32 mFont_SetVertexRectangle(GAME* game, f32 x, f32 y, int s, int t, f32 scale_x, f32 scale_y, int mode);
extern f32 mFont_SetLineStrings_AndSpace(GAME* game, u8* str, int len, f32 x, f32 y, int r, int g, int b, int a, int flag_revert, int flag_cut, int unused, f32 scale_x, f32 scale_y, int mode);
extern f32 mFont_SetLineStrings(GAME* game, u8* str, int len, f32 x, f32 y, int r, int g, int b, int a, int flag_revert, int flag_cut, f32 scale_x, f32 scale_y, int mode);
extern void mFont_CulcOrthoMatrix(N64Mtx* m);
extern void mFont_SetMatrix(GRAPH* graph, int mode);
extern void mFont_UnSetMatrix(GRAPH* graph, int mode);
extern void mFont_Main_start(GRAPH* graph);
extern void mFontSentence_set(mFontSentence* this, u8* sentence_p, int len, u32 flags, xy_t* pos, int line_type, xy_t* scale, rgba_t* color, int se_voice_pos, u8 voice_idx, u8 voice2_idx, u8 voice3_idx, s16 voice_se_character_idx);
extern void mFontSentence_gppDraw(mFontSentence* this, GAME* game, Gfx** gfx_pp);
extern f32 mFont_SetMarkChar(GAME* game, u8 mark_type, f32 x, f32 y, int r, int g, int b, int a, int revert_flag, f32 scale_x, f32 scale_y, int mode);
extern void mFont_gppSetRectMode(Gfx** gfx_pp);

#ifdef __cplusplus
}
#endif

#endif
