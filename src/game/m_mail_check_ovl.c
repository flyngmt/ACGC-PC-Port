#include "m_mail_check_ovl.h"

#include "m_mail.h"
#include "m_font.h"
#include "m_msg.h"

static int mMck_strlen(u8* str, int len) {
  u8* end_p = str + len;
  
  while (len != 0) {
    len--;

    if (*end_p != CHAR_SPACE) {
      goto end; /* Don't like this */
    }

    end_p--;
  }

  len--;

end:
  return len + 1;
}

static int mMck_cmp_sep(u8 c) {
  switch (c) {
    case CHAR_SPACE:
    case CHAR_COMMA:
    case CHAR_QUESTIONMARK:
    case CHAR_EXCLAMATION:
    case CHAR_PERIOD:
    case CHAR_INTERPUNCT:
    case CHAR_NEW_LINE:
      return TRUE;

    default:
      return FALSE;
  }
}

static u8* mMck_search_sep(u8* str, u8 len) {
  while (len-- != 0) {

    /* Only accept the separator if the next character is also not a separator */
    if (mMck_cmp_sep(str[0]) == TRUE && mMck_cmp_sep(str[1]) == FALSE) {
      break;
    }

    str++;
  }

  return str;
}

static u8* mMck_next_key(u8* str) {
  return str + 2;
}

typedef struct string_table_s {
  u8 trigger_lower;
  u8 trigger_upper;

  u8* str_table;
} mMck_cmp_str_table_c;

static u8 str_a_table[] = {
  CHAR_b, CHAR_l,
  CHAR_b, CHAR_o,
  CHAR_b, CHAR_r,
  CHAR_b, CHAR_s,
  CHAR_c, CHAR_c,
  CHAR_c, CHAR_h,
  CHAR_c, CHAR_r,
  CHAR_c, CHAR_t,
  CHAR_d, CHAR_d,
  CHAR_d, CHAR_m,
  CHAR_d, CHAR_v,
  CHAR_e, CHAR_r,
  CHAR_f, CHAR_f,
  CHAR_f, CHAR_r,
  CHAR_f, CHAR_t,
  CHAR_g, CHAR_a,
  CHAR_g, CHAR_e,
  CHAR_g, CHAR_o,
  CHAR_h, CHAR_e,
  CHAR_i, CHAR_r,
  CHAR_l, CHAR_i,
  CHAR_l, CHAR_l,
  CHAR_l, CHAR_m,
  CHAR_l, CHAR_o,
  CHAR_l, CHAR_r,
  CHAR_l, CHAR_s,
  CHAR_l, CHAR_t,
  CHAR_l, CHAR_w,
  CHAR_m, CHAR_SPACE,
  CHAR_m, CHAR_e,
  CHAR_m, CHAR_o,
  CHAR_n, CHAR_d,
  CHAR_n, CHAR_g,
  CHAR_n, CHAR_i,
  CHAR_n, CHAR_o,
  CHAR_n, CHAR_s,
  CHAR_n, CHAR_y,
  CHAR_p, CHAR_a,
  CHAR_p, CHAR_p,
  CHAR_p, CHAR_r,
  CHAR_r, CHAR_e,
  CHAR_r, CHAR_g,
  CHAR_r, CHAR_m,
  CHAR_r, CHAR_r,
  CHAR_r, CHAR_t,
  CHAR_s, CHAR_i,
  CHAR_s, CHAR_k,
  CHAR_s, CHAR_l,
  CHAR_t, CHAR_e,
  CHAR_t, CHAR_m,
  CHAR_t, CHAR_t,
  CHAR_u, CHAR_d,
  CHAR_u, CHAR_g,
  CHAR_u, CHAR_t,
  CHAR_v, CHAR_e,
  CHAR_v, CHAR_o,
  CHAR_w, CHAR_a,

  #ifndef BUGFIXES
  0, 0
  #else
  CHAR_CONTROL_CODE, 0
  #endif
};

static u8 str_b_table[] = {
  CHAR_a, CHAR_b,
  CHAR_a, CHAR_c,
  CHAR_a, CHAR_d,
  CHAR_a, CHAR_g,
  CHAR_a, CHAR_l,
  CHAR_a, CHAR_n,
  CHAR_a, CHAR_s,
  CHAR_a, CHAR_t,
  CHAR_e, CHAR_SPACE,
  CHAR_e, CHAR_a,
  CHAR_e, CHAR_c,
  CHAR_e, CHAR_d,
  CHAR_e, CHAR_e,
  CHAR_e, CHAR_f,
  CHAR_e, CHAR_g,
  CHAR_e, CHAR_h,
  CHAR_e, CHAR_l,
  CHAR_e, CHAR_s,
  CHAR_e, CHAR_t,
  CHAR_e, CHAR_y,
  CHAR_i, CHAR_c,
  CHAR_i, CHAR_g,
  CHAR_i, CHAR_k,
  CHAR_i, CHAR_l,
  CHAR_i, CHAR_r,
  CHAR_i, CHAR_t,
  CHAR_l, CHAR_a,
  CHAR_l, CHAR_e,
  CHAR_l, CHAR_o,
  CHAR_l, CHAR_u,
  CHAR_o, CHAR_a,
  CHAR_o, CHAR_d,
  CHAR_o, CHAR_n,
  CHAR_o, CHAR_o,
  CHAR_o, CHAR_r,
  CHAR_o, CHAR_t,
  CHAR_o, CHAR_u,
  CHAR_o, CHAR_x,
  CHAR_o, CHAR_y,
  CHAR_r, CHAR_a,
  CHAR_r, CHAR_e,
  CHAR_r, CHAR_i,
  CHAR_r, CHAR_o,
  CHAR_u, CHAR_i,
  CHAR_u, CHAR_r,
  CHAR_u, CHAR_s,
  CHAR_u, CHAR_t,
  CHAR_u, CHAR_y,
  CHAR_y, CHAR_SPACE,

  #ifndef BUGFIXES
  0, 0
  #else
  CHAR_CONTROL_CODE, 0
  #endif
};

static u8 str_c_table[] = {
  CHAR_a, CHAR_k,
  CHAR_a, CHAR_l,
  CHAR_a, CHAR_m,
  CHAR_a, CHAR_n,
  CHAR_a, CHAR_p,
  CHAR_a, CHAR_r,
  CHAR_a, CHAR_s,
  CHAR_a, CHAR_t,
  CHAR_a, CHAR_u,
  CHAR_e, CHAR_n,
  CHAR_e, CHAR_r,
  CHAR_h, CHAR_a,
  CHAR_h, CHAR_e,
  CHAR_h, CHAR_i,
  CHAR_h, CHAR_o,
  CHAR_h, CHAR_i,
  CHAR_h, CHAR_u,
  CHAR_i, CHAR_r,
  CHAR_i, CHAR_t,
  CHAR_l, CHAR_a,
  CHAR_l, CHAR_e,
  CHAR_l, CHAR_i,
  CHAR_l, CHAR_o,
  CHAR_o, CHAR_a,
  CHAR_o, CHAR_f,
  CHAR_o, CHAR_i,
  CHAR_o, CHAR_l,
  CHAR_o, CHAR_m,
  CHAR_o, CHAR_n,
  CHAR_o, CHAR_o,
  CHAR_o, CHAR_p,
  CHAR_o, CHAR_r,
  CHAR_o, CHAR_s,
  CHAR_o, CHAR_u,
  CHAR_o, CHAR_v,
  CHAR_o, CHAR_w,
  CHAR_r, CHAR_e,
  CHAR_r, CHAR_i,
  CHAR_r, CHAR_o,
  CHAR_r, CHAR_y,
  CHAR_u, CHAR_p,
  CHAR_u, CHAR_r,
  CHAR_u, CHAR_s,
  CHAR_u, CHAR_t,

  #ifdef BUGFIXES
  CHAR_CONTROL_CODE, 0
  #endif
};

static u8 str_d_table[] = {
  CHAR_a, CHAR_d,
  CHAR_a, CHAR_i,
  CHAR_a, CHAR_m,
  CHAR_a, CHAR_n,
  CHAR_a, CHAR_r,
  CHAR_a, CHAR_t,
  CHAR_a, CHAR_u,
  CHAR_a, CHAR_y,
  CHAR_e, CHAR_a,
  CHAR_e, CHAR_c,
  CHAR_e, CHAR_e,
  CHAR_e, CHAR_f,
  CHAR_e, CHAR_g,
  CHAR_e, CHAR_l,
  CHAR_e, CHAR_m,
  CHAR_e, CHAR_n,
  CHAR_e, CHAR_p,
  CHAR_e, CHAR_s,
  CHAR_e, CHAR_t,
  CHAR_e, CHAR_v,
  CHAR_i, CHAR_c,
  CHAR_i, CHAR_d,
  CHAR_i, CHAR_e,
  CHAR_i, CHAR_f,
  CHAR_i, CHAR_g,
  CHAR_i, CHAR_n,
  CHAR_i, CHAR_r,
  CHAR_i, CHAR_s,
  CHAR_i, CHAR_v,
  CHAR_o, CHAR_SPACE,
  CHAR_o, CHAR_c,
  CHAR_o, CHAR_e,
  CHAR_o, CHAR_g,
  CHAR_o, CHAR_l,
  CHAR_o, CHAR_n,
  CHAR_o, CHAR_o,
  CHAR_o, CHAR_u,
  CHAR_o, CHAR_w,
  CHAR_o, CHAR_z,
  CHAR_r, CHAR_a,
  CHAR_r, CHAR_e,
  CHAR_r, CHAR_i,
  CHAR_r, CHAR_o,
  CHAR_r, CHAR_u,
  CHAR_r, CHAR_y,
  CHAR_u, CHAR_e,
  CHAR_u, CHAR_r,
  CHAR_u, CHAR_s,
  CHAR_u, CHAR_t,

  #ifndef BUGFIXES
  0, 0
  #else
  CHAR_CONTROL_CODE, 0
  #endif
};

static u8 str_e_table[] = {
  CHAR_a, CHAR_c,
  CHAR_a, CHAR_r,
  CHAR_a, CHAR_s,
  CHAR_a, CHAR_t,
  CHAR_d, CHAR_u,
  CHAR_f, CHAR_f,
  CHAR_g, CHAR_g,
  CHAR_i, CHAR_g,
  CHAR_i, CHAR_t,
  CHAR_l, CHAR_e,
  CHAR_l, CHAR_s,
  CHAR_m, CHAR_p,
  CHAR_n, CHAR_d,
  CHAR_n, CHAR_e,
  CHAR_n, CHAR_g,
  CHAR_n, CHAR_j,
  CHAR_n, CHAR_o,
  CHAR_n, CHAR_t,
  CHAR_q, CHAR_u,
  CHAR_r, CHAR_r,
  CHAR_s, CHAR_p,
  CHAR_u, CHAR_r,
  CHAR_v, CHAR_e,
  CHAR_x, CHAR_a,
  CHAR_x, CHAR_c,
  CHAR_x, CHAR_e,
  CHAR_x, CHAR_p,
  CHAR_y, CHAR_e,

  #ifdef BUGFIXES
  CHAR_CONTROL_CODE, 0
  #endif
};

static u8 str_f_table[] = {
  CHAR_a, CHAR_c,
  CHAR_a, CHAR_i,
  CHAR_a, CHAR_l,
  CHAR_a, CHAR_m,
  CHAR_a, CHAR_r,
  CHAR_a, CHAR_s,
  CHAR_a, CHAR_t,
  CHAR_e, CHAR_a,
  CHAR_e, CHAR_b,
  CHAR_e, CHAR_d,
  CHAR_e, CHAR_e,
  CHAR_e, CHAR_l,
  CHAR_e, CHAR_w,
  CHAR_i, CHAR_e,
  CHAR_i, CHAR_f,
  CHAR_i, CHAR_g,
  CHAR_i, CHAR_l,
  CHAR_i, CHAR_n,
  CHAR_i, CHAR_r,
  CHAR_i, CHAR_s,
  CHAR_i, CHAR_v,
  CHAR_i, CHAR_x,
  CHAR_l, CHAR_a,
  CHAR_l, CHAR_e,
  CHAR_l, CHAR_i,
  CHAR_l, CHAR_o,
  CHAR_l, CHAR_y,
  CHAR_o, CHAR_l,
  CHAR_o, CHAR_o,
  CHAR_o, CHAR_r,
  CHAR_o, CHAR_u,
  CHAR_r, CHAR_a,
  CHAR_r, CHAR_e,
  CHAR_r, CHAR_i,
  CHAR_r, CHAR_o,
  CHAR_r, CHAR_u,
  CHAR_u, CHAR_l,
  CHAR_u, CHAR_n,
  CHAR_u, CHAR_t,

  #ifndef BUGFIXES
  0, 0
  #else
  CHAR_CONTROL_CODE, 0
  #endif
};

static u8 str_g_table[] = {
  CHAR_a, CHAR_i,
  CHAR_a, CHAR_m,
  CHAR_a, CHAR_r,
  CHAR_a, CHAR_s,
  CHAR_a, CHAR_t,
  CHAR_a, CHAR_v,
  CHAR_e, CHAR_n,
  CHAR_e, CHAR_r,
  CHAR_e, CHAR_t,
  CHAR_i, CHAR_r,
  CHAR_i, CHAR_v,
  CHAR_l, CHAR_a,
  CHAR_o, CHAR_SPACE,
  CHAR_o, CHAR_d,
  CHAR_o, CHAR_i,
  CHAR_o, CHAR_n,
  CHAR_o, CHAR_o,
  CHAR_o, CHAR_t,
  CHAR_o, CHAR_v,
  CHAR_r, CHAR_a,
  CHAR_r, CHAR_e,
  CHAR_r, CHAR_o,
  CHAR_u, CHAR_a,
  CHAR_u, CHAR_e,
  CHAR_u, CHAR_i,
  CHAR_u, CHAR_n,

  #ifdef BUGFIXES
  CHAR_CONTROL_CODE, 0
  #endif
};

static u8 str_h_table[] = {
  CHAR_a, CHAR_b,
  CHAR_a, CHAR_d,
  CHAR_a, CHAR_i,
  CHAR_a, CHAR_l,
  CHAR_a, CHAR_n,
  CHAR_a, CHAR_p,
  CHAR_a, CHAR_r,
  CHAR_a, CHAR_s,
  CHAR_a, CHAR_t,
  CHAR_a, CHAR_v,
  CHAR_e, CHAR_SPACE,
  CHAR_e, CHAR_a,
  CHAR_e, CHAR_i,
  CHAR_e, CHAR_l,
  CHAR_e, CHAR_r,
  CHAR_i, CHAR_SPACE,
  CHAR_i, CHAR_d,
  CHAR_i, CHAR_g,
  CHAR_i, CHAR_l,
  CHAR_i, CHAR_m,
  CHAR_i, CHAR_r,
  CHAR_i, CHAR_s,
  CHAR_i, CHAR_t,
  CHAR_o, CHAR_l,
  CHAR_o, CHAR_m,
  CHAR_o, CHAR_n,
  CHAR_o, CHAR_p,
  CHAR_o, CHAR_r,
  CHAR_o, CHAR_s,
  CHAR_o, CHAR_t,
  CHAR_o, CHAR_u,
  CHAR_o, CHAR_w,
  CHAR_u, CHAR_m,
  CHAR_u, CHAR_n,
  CHAR_u, CHAR_r,
  CHAR_u, CHAR_s,

  #ifdef BUGFIXES
  CHAR_CONTROL_CODE, 0
  #endif
};

static u8 str_i_table[] = {
  CHAR_SPACE, CHAR_SPACE,
  CHAR_c, CHAR_e,
  CHAR_d, CHAR_e,
  CHAR_f, CHAR_SPACE,
  CHAR_m, CHAR_a,
  CHAR_m, CHAR_m,
  CHAR_m, CHAR_p,
  CHAR_n, CHAR_SPACE,
  CHAR_n, CHAR_c,
  CHAR_n, CHAR_d,
  CHAR_n, CHAR_f,
  CHAR_n, CHAR_s,
  CHAR_n, CHAR_t,
  CHAR_n, CHAR_v,
  CHAR_r, CHAR_o,
  CHAR_s, CHAR_SPACE,
  CHAR_s, CHAR_l,
  CHAR_t, CHAR_SPACE,
  CHAR_t, CHAR_s,

  #ifndef BUGFIXES
  0, 0
  #else
  CHAR_CONTROL_CODE, 0
  #endif
};

static u8 str_j_table[] = {
  CHAR_a, CHAR_n,
  CHAR_a, CHAR_p,
  CHAR_o, CHAR_b,
  CHAR_o, CHAR_i,
  CHAR_u, CHAR_d,
  CHAR_u, CHAR_l,
  CHAR_u, CHAR_m,
  CHAR_u, CHAR_n,
  CHAR_u, CHAR_s,

  #ifndef BUGFIXES
  0, 0
  #else
  CHAR_CONTROL_CODE, 0
  #endif
};

static u8 str_k_table[] = {
  CHAR_e, CHAR_e,
  CHAR_e, CHAR_p,
  CHAR_e, CHAR_y,
  CHAR_i, CHAR_c,
  CHAR_i, CHAR_l,
  CHAR_i, CHAR_n,
  CHAR_i, CHAR_t,
  CHAR_n, CHAR_e,
  CHAR_n, CHAR_i,
  CHAR_n, CHAR_o,

  #ifdef BUGFIXES
  CHAR_CONTROL_CODE, 0
  #endif
};

static u8 str_l_table[] = {
  CHAR_a, CHAR_b,
  CHAR_a, CHAR_d,
  CHAR_a, CHAR_i,
  CHAR_a, CHAR_k,
  CHAR_a, CHAR_n,
  CHAR_a, CHAR_r,
  CHAR_a, CHAR_s,
  CHAR_a, CHAR_t,
  CHAR_a, CHAR_u,
  CHAR_a, CHAR_w,
  CHAR_a, CHAR_y,
  CHAR_a, CHAR_z,
  CHAR_e, CHAR_a,
  CHAR_e, CHAR_d,
  CHAR_e, CHAR_f,
  CHAR_e, CHAR_g,
  CHAR_e, CHAR_n,
  CHAR_e, CHAR_s,
  CHAR_e, CHAR_t,
  CHAR_e, CHAR_v,
  CHAR_i, CHAR_b,
  CHAR_i, CHAR_e,
  CHAR_i, CHAR_f,
  CHAR_i, CHAR_g,
  CHAR_i, CHAR_k,
  CHAR_i, CHAR_m,
  CHAR_i, CHAR_n,
  CHAR_i, CHAR_s,
  CHAR_i, CHAR_t,
  CHAR_i, CHAR_v,
  CHAR_o, CHAR_c,
  CHAR_o, CHAR_n,
  CHAR_o, CHAR_o,
  CHAR_o, CHAR_s,
  CHAR_o, CHAR_t,
  CHAR_o, CHAR_u,
  CHAR_o, CHAR_v,
  CHAR_o, CHAR_w,
  CHAR_u, CHAR_n,
  CHAR_y, CHAR_i,

  #ifdef BUGFIXES
  CHAR_CONTROL_CODE, 0
  #endif
};

static u8 str_m_table[] = {
  CHAR_a, CHAR_c,
  CHAR_a, CHAR_d,
  CHAR_a, CHAR_g,
  CHAR_a, CHAR_i,
  CHAR_a, CHAR_j,
  CHAR_a, CHAR_k,
  CHAR_a, CHAR_n,
  CHAR_a, CHAR_p,
  CHAR_a, CHAR_r,
  CHAR_a, CHAR_t,
  CHAR_a, CHAR_y,
  CHAR_e, CHAR_SPACE,
  CHAR_e, CHAR_a,
  CHAR_e, CHAR_d,
  CHAR_e, CHAR_e,
  CHAR_e, CHAR_m,
  CHAR_e, CHAR_n,
  CHAR_e, CHAR_s,
  CHAR_e, CHAR_t,
  CHAR_i, CHAR_d,
  CHAR_i, CHAR_g,
  CHAR_i, CHAR_l,
  CHAR_i, CHAR_n,
  CHAR_i, CHAR_s,
  CHAR_o, CHAR_d,
  CHAR_o, CHAR_m,
  CHAR_o, CHAR_n,
  CHAR_o, CHAR_o,
  CHAR_o, CHAR_r,
  CHAR_o, CHAR_s,
  CHAR_o, CHAR_t,
  CHAR_o, CHAR_u,
  CHAR_o, CHAR_v,
  CHAR_u, CHAR_c,
  CHAR_u, CHAR_m,
  CHAR_u, CHAR_s,
  CHAR_y, CHAR_SPACE,
  CHAR_y, CHAR_s,

  #ifdef BUGFIXES
  CHAR_CONTROL_CODE, 0
  #endif
};

static u8 str_n_table[] = {
  CHAR_a, CHAR_m,
  CHAR_a, CHAR_r,
  CHAR_a, CHAR_t,
  CHAR_e, CHAR_a,
  CHAR_e, CHAR_c,
  CHAR_e, CHAR_e,
  CHAR_e, CHAR_i,
  CHAR_e, CHAR_v,
  CHAR_e, CHAR_w,
  CHAR_e, CHAR_x,
  CHAR_i, CHAR_c,
  CHAR_i, CHAR_g,
  CHAR_i, CHAR_n,
  CHAR_o, CHAR_SPACE,
  CHAR_o, CHAR_b,
  CHAR_o, CHAR_i,
  CHAR_o, CHAR_n,
  CHAR_o, CHAR_o,
  CHAR_o, CHAR_r,
  CHAR_o, CHAR_s,
  CHAR_o, CHAR_t,
  CHAR_o, CHAR_v,
  CHAR_o, CHAR_w,
  CHAR_u, CHAR_m,

  #ifdef BUGFIXES
  CHAR_CONTROL_CODE, 0
  #endif
};

static u8 str_o_table[] = {
  CHAR_b, CHAR_j,
  CHAR_APOSTROPHE, CHAR_c,
  CHAR_c, CHAR_t,
  CHAR_f, CHAR_SPACE,
  CHAR_f, CHAR_f,
  CHAR_f, CHAR_t,
  CHAR_h, CHAR_SPACE,
  CHAR_i, CHAR_l,
  CHAR_k, CHAR_a,
  CHAR_l, CHAR_d,
  CHAR_n, CHAR_SPACE,
  CHAR_n, CHAR_c,
  CHAR_n, CHAR_e,
  CHAR_n, CHAR_l,
  CHAR_p, CHAR_e,
  CHAR_p, CHAR_i,
  CHAR_p, CHAR_p,
  CHAR_r, CHAR_SPACE,
  CHAR_r, CHAR_a,
  CHAR_r, CHAR_d,
  CHAR_t, CHAR_h,
  CHAR_u, CHAR_r,
  CHAR_u, CHAR_t,
  CHAR_v, CHAR_e,
  CHAR_w, CHAR_n,

  #ifndef BUGFIXES
  0, 0
  #else
  CHAR_CONTROL_CODE, 0
  #endif
};

static u8 str_p_table[] = {
  CHAR_a, CHAR_c,
  CHAR_a, CHAR_g,
  CHAR_a, CHAR_i,
  CHAR_a, CHAR_p,
  CHAR_a, CHAR_r,
  CHAR_a, CHAR_s,
  CHAR_a, CHAR_t,
  CHAR_a, CHAR_y,
  CHAR_e, CHAR_a,
  CHAR_e, CHAR_n,
  CHAR_e, CHAR_o,
  CHAR_e, CHAR_r,
  CHAR_h, CHAR_o,
  CHAR_i, CHAR_c,
  CHAR_i, CHAR_e,
  CHAR_i, CHAR_n,
  CHAR_i, CHAR_p,
  CHAR_l, CHAR_a,
  CHAR_l, CHAR_e,
  CHAR_o, CHAR_c,
  CHAR_o, CHAR_i,
  CHAR_o, CHAR_l,
  CHAR_o, CHAR_o,
  CHAR_o, CHAR_p,
  CHAR_o, CHAR_s,
  CHAR_o, CHAR_t,
  CHAR_o, CHAR_u,
  CHAR_o, CHAR_w,
  CHAR_r, CHAR_a,
  CHAR_r, CHAR_e,
  CHAR_r, CHAR_i,
  CHAR_r, CHAR_o,
  CHAR_u, CHAR_b,
  CHAR_u, CHAR_l,
  CHAR_u, CHAR_p,
  CHAR_u, CHAR_r,
  CHAR_u, CHAR_s,
  CHAR_u, CHAR_t,

  #ifdef BUGFIXES
  CHAR_CONTROL_CODE, 0
  #endif
};

static u8 str_q_table[] = {
  CHAR_u, CHAR_a,
  CHAR_u, CHAR_e,
  CHAR_u, CHAR_i,

  #ifndef BUGFIXES
  0, 0
  #else
  CHAR_CONTROL_CODE, 0
  #endif
};

static u8 str_r_table[] = {
  CHAR_a, CHAR_c,
  CHAR_a, CHAR_d,
  CHAR_a, CHAR_i,
  CHAR_a, CHAR_n,
  CHAR_a, CHAR_p,
  CHAR_a, CHAR_t,
  CHAR_e, CHAR_a,
  CHAR_e, CHAR_c,
  CHAR_e, CHAR_d,
  CHAR_e, CHAR_f,
  CHAR_e, CHAR_g,
  CHAR_e, CHAR_l,
  CHAR_e, CHAR_m,
  CHAR_e, CHAR_p,
  CHAR_e, CHAR_q,
  CHAR_e, CHAR_s,
  CHAR_e, CHAR_t,
  CHAR_i, CHAR_c,
  CHAR_i, CHAR_d,
  CHAR_i, CHAR_g,
  CHAR_i, CHAR_n,
  CHAR_i, CHAR_s,
  CHAR_i, CHAR_v,
  CHAR_o, CHAR_a,
  CHAR_o, CHAR_c,
  CHAR_o, CHAR_d,
  CHAR_o, CHAR_l,
  CHAR_o, CHAR_o,
  CHAR_o, CHAR_s,
  CHAR_o, CHAR_u,
  CHAR_o, CHAR_w,
  CHAR_u, CHAR_l,
  CHAR_u, CHAR_n,
  CHAR_u, CHAR_s,

  #ifdef BUGFIXES
  CHAR_CONTROL_CODE, 0
  #endif
};

static u8 str_s_table[] = {
  CHAR_a, CHAR_d,
  CHAR_a, CHAR_f,
  CHAR_a, CHAR_i,
  CHAR_a, CHAR_l,
  CHAR_a, CHAR_m,
  CHAR_a, CHAR_n,
  CHAR_a, CHAR_t,
  CHAR_a, CHAR_v,
  CHAR_a, CHAR_w,
  CHAR_a, CHAR_y,
  CHAR_c, CHAR_e,
  CHAR_c, CHAR_h,
  CHAR_c, CHAR_i,
  CHAR_c, CHAR_o,
  CHAR_e, CHAR_a,
  CHAR_e, CHAR_c,
  CHAR_e, CHAR_e,
  CHAR_e, CHAR_l,
  CHAR_e, CHAR_n,
  CHAR_e, CHAR_p,
  CHAR_e, CHAR_r,
  CHAR_e, CHAR_t,
  CHAR_e, CHAR_v,
  CHAR_e, CHAR_x,
  CHAR_h, CHAR_a,
  CHAR_h, CHAR_e,
  CHAR_h, CHAR_i,
  CHAR_h, CHAR_o,
  CHAR_h, CHAR_u,
  CHAR_i, CHAR_c,
  CHAR_i, CHAR_d,
  CHAR_i, CHAR_g,
  CHAR_i, CHAR_l,
  CHAR_i, CHAR_m,
  CHAR_i, CHAR_n,
  CHAR_i, CHAR_s,
  CHAR_i, CHAR_t,
  CHAR_i, CHAR_x,
  CHAR_i, CHAR_z,
  CHAR_k, CHAR_i,
  CHAR_k, CHAR_y,
  CHAR_l, CHAR_e,
  CHAR_l, CHAR_i,
  CHAR_l, CHAR_o,
  CHAR_m, CHAR_a,
  CHAR_m, CHAR_e,
  CHAR_m, CHAR_i,
  CHAR_m, CHAR_o,
  CHAR_n, CHAR_o,
  CHAR_o, CHAR_SPACE,
  CHAR_o, CHAR_a,
  CHAR_o, CHAR_c,
  CHAR_o, CHAR_f,
  CHAR_o, CHAR_i,
  CHAR_o, CHAR_l,
  CHAR_o, CHAR_m,
  CHAR_o, CHAR_n,
  CHAR_o, CHAR_o,
  CHAR_o, CHAR_r,
  CHAR_o, CHAR_u,
  CHAR_p, CHAR_a,
  CHAR_p, CHAR_e,
  CHAR_p, CHAR_i,
  CHAR_p, CHAR_o,
  CHAR_p, CHAR_r,
  CHAR_q, CHAR_u,
  CHAR_t, CHAR_a,
  CHAR_t, CHAR_e,
  CHAR_t, CHAR_i,
  CHAR_t, CHAR_o,
  CHAR_t, CHAR_r,
  CHAR_t, CHAR_u,
  CHAR_t, CHAR_y,
  CHAR_u, CHAR_b,
  CHAR_u, CHAR_c,
  CHAR_u, CHAR_d,
  CHAR_u, CHAR_f,
  CHAR_u, CHAR_g,
  CHAR_u, CHAR_m,
  CHAR_u, CHAR_n,
  CHAR_u, CHAR_p,
  CHAR_u, CHAR_r,
  CHAR_w, CHAR_a,
  CHAR_w, CHAR_e,
  CHAR_w, CHAR_i,
  CHAR_w, CHAR_u,
  CHAR_y, CHAR_s,

  #ifndef BUGFIXES
  0, 0
  #else
  CHAR_CONTROL_CODE, 0
  #endif
};

static u8 str_t_table[] = {
  CHAR_a, CHAR_b,
  CHAR_a, CHAR_k,
  CHAR_a, CHAR_l,
  CHAR_a, CHAR_s,
  CHAR_a, CHAR_u,
  CHAR_a, CHAR_x,
  CHAR_e, CHAR_a,
  CHAR_e, CHAR_e,
  CHAR_e, CHAR_l,
  CHAR_e, CHAR_m,
  CHAR_e, CHAR_n,
  CHAR_e, CHAR_r,
  CHAR_e, CHAR_s,
  CHAR_h, CHAR_a,
  CHAR_h, CHAR_e,
  CHAR_h, CHAR_i,
  CHAR_h, CHAR_o,
  CHAR_h, CHAR_r,
  CHAR_h, CHAR_u,
  CHAR_i, CHAR_c,
  CHAR_i, CHAR_e,
  CHAR_i, CHAR_l,
  CHAR_i, CHAR_m,
  CHAR_i, CHAR_r,
  CHAR_i, CHAR_t,
  CHAR_o, CHAR_SPACE,
  CHAR_o, CHAR_d,
  CHAR_o, CHAR_g,
  CHAR_o, CHAR_l,
  CHAR_o, CHAR_m,
  CHAR_o, CHAR_n,
  CHAR_o, CHAR_o,
  CHAR_o, CHAR_p,
  CHAR_o, CHAR_r,
  CHAR_o, CHAR_t,
  CHAR_o, CHAR_u,
  CHAR_o, CHAR_w,
  CHAR_r, CHAR_a,
  CHAR_r, CHAR_e,
  CHAR_r, CHAR_i,
  CHAR_r, CHAR_o,
  CHAR_r, CHAR_u,
  CHAR_r, CHAR_y,
  CHAR_u, CHAR_e,
  CHAR_u, CHAR_r,
  CHAR_v, CHAR_SPACE,
  CHAR_w, CHAR_e,
  CHAR_w, CHAR_i,
  CHAR_w, CHAR_o,
  CHAR_y, CHAR_i,
  CHAR_y, CHAR_p,

  #ifndef BUGFIXES
  0, 0
  #else
  CHAR_CONTROL_CODE, 0
  #endif
};

static u8 str_u_table[] = {
  CHAR_n, CHAR_a,
  CHAR_n, CHAR_c,
  CHAR_n, CHAR_d,
  CHAR_n, CHAR_i,
  CHAR_n, CHAR_l,
  CHAR_n, CHAR_t,
  CHAR_p, CHAR_SPACE,
  CHAR_p, CHAR_o,
  CHAR_s, CHAR_SPACE,
  CHAR_s, CHAR_e,
  CHAR_s, CHAR_u,

  #ifndef BUGFIXES
  0, 0
  #else
  CHAR_CONTROL_CODE, 0
  #endif
};

static u8 str_v_table[] = {
  CHAR_a, CHAR_l,
  CHAR_a, CHAR_r,
  CHAR_e, CHAR_g,
  CHAR_e, CHAR_r,
  CHAR_i, CHAR_e,
  CHAR_i, CHAR_l,
  CHAR_i, CHAR_s,
  CHAR_o, CHAR_i,
  CHAR_o, CHAR_l,
  CHAR_o, CHAR_t,

  #ifdef BUGFIXES
  CHAR_CONTROL_CODE, 0
  #endif
};

static u8 str_w_table[] = {
  CHAR_a, CHAR_i,
  CHAR_a, CHAR_k,
  CHAR_a, CHAR_l,
  CHAR_a, CHAR_n,
  CHAR_a, CHAR_r,
  CHAR_a, CHAR_s,
  CHAR_a, CHAR_t,
  CHAR_a, CHAR_v,
  CHAR_a, CHAR_y,
  CHAR_e, CHAR_SPACE,
  CHAR_e, CHAR_a,
  CHAR_e, CHAR_d,
  CHAR_e, CHAR_e,
  CHAR_e, CHAR_i,
  CHAR_e, CHAR_l,
  CHAR_e, CHAR_n,
  CHAR_e, CHAR_r,
  CHAR_e, CHAR_s,
  CHAR_e, CHAR_t,
  CHAR_h, CHAR_a,
  CHAR_h, CHAR_e,
  CHAR_h, CHAR_i,
  CHAR_h, CHAR_o,
  CHAR_h, CHAR_y,
  CHAR_i, CHAR_d,
  CHAR_i, CHAR_f,
  CHAR_i, CHAR_l,
  CHAR_i, CHAR_n,
  CHAR_i, CHAR_r,
  CHAR_i, CHAR_s,
  CHAR_i, CHAR_t,
  CHAR_i, CHAR_v,
  CHAR_o, CHAR_k,
  CHAR_o, CHAR_m,
  CHAR_o, CHAR_n,
  CHAR_o, CHAR_o,
  CHAR_o, CHAR_r,
  CHAR_o, CHAR_u,
  CHAR_r, CHAR_i,
  CHAR_r, CHAR_o,

  #ifdef BUGFIXES
  CHAR_CONTROL_CODE, 0
  #endif
};

static u8 str_x_table[] = {
  CHAR_m, CHAR_a,
};

static u8 str_y_table[] = {
  CHAR_a, CHAR_r,
  CHAR_e, CHAR_a,
  CHAR_e, CHAR_l,
  CHAR_e, CHAR_n,
  CHAR_e, CHAR_s,
  CHAR_e, CHAR_t,
  CHAR_o, CHAR_u,

  #ifndef BUGFIXES
  0, 0
  #else
  CHAR_CONTROL_CODE, 0
  #endif
};

static u8 str_z_table[] = {
  CHAR_e, CHAR_r,

  #ifdef BUGFIXES
  CHAR_CONTROL_CODE, 0
  #endif
};

static mMck_cmp_str_table_c cmp_str_table_c[26] = {
  { CHAR_a, CHAR_A, str_a_table },
  { CHAR_b, CHAR_B, str_b_table },
  { CHAR_c, CHAR_C, str_c_table },
  { CHAR_d, CHAR_D, str_d_table },
  { CHAR_e, CHAR_E, str_e_table },
  { CHAR_f, CHAR_F, str_f_table },
  { CHAR_g, CHAR_G, str_g_table },
  { CHAR_h, CHAR_H, str_h_table },
  { CHAR_i, CHAR_I, str_i_table },
  { CHAR_j, CHAR_J, str_j_table },
  { CHAR_k, CHAR_K, str_k_table },
  { CHAR_l, CHAR_L, str_l_table },
  { CHAR_m, CHAR_M, str_m_table },
  { CHAR_n, CHAR_N, str_n_table },
  { CHAR_o, CHAR_O, str_o_table },
  { CHAR_p, CHAR_P, str_p_table },
  { CHAR_q, CHAR_Q, str_q_table },
  { CHAR_r, CHAR_R, str_r_table },
  { CHAR_s, CHAR_S, str_s_table },
  { CHAR_t, CHAR_T, str_t_table },
  { CHAR_u, CHAR_U, str_u_table },
  { CHAR_v, CHAR_V, str_v_table },
  { CHAR_w, CHAR_W, str_w_table },
  { CHAR_x, CHAR_X, str_x_table },
  { CHAR_y, CHAR_Y, str_y_table },
  { CHAR_z, CHAR_Z, str_z_table }
};

static int mMck_cmp_key(u8* str) {
  u8 char0 = str[0];
  u8 char1 = str[1];
  u8 char2 = str[2];
  int i;

  for (i = 0; i < 26; i++) {
    u8* str_table = cmp_str_table_c[i].str_table;

    if (char0 == cmp_str_table_c[i].trigger_lower || char0 == cmp_str_table_c[i].trigger_upper) {

      /* 
      BUG: in the NTSC-U (US version) of AC, the string tables are missing the control code character (0x7F).
      The game will continue processing data as syllable values until it either reaches an unrelated 0x7F byte,
      or it finds two consecutive bytes which satisfies the current syllable pair.
      */
     
      for (str_table; str_table[0] != CHAR_CONTROL_CODE; str_table = mMck_next_key(str_table)) {
        if (char1 == str_table[0] && char2 == str_table[1]) {
          return TRUE; /* Valid 3-letter (syllable?) match found */
        }
      }
    }
  }

  return FALSE; /* No match found */
}

extern int mMck_check_key_hit(int* len, u8* str) {
  u8* sep = str;
  int i;
  int str_len;
  int matches;
  int chars;

  *len = 0;
  i = 0;
  matches = 0;
  chars = 0;
  str_len = mMck_strlen(str, MAIL_BODY_LEN - 3);

  if (str_len == 0) {
    return 0;
  }
  else {
    /* There might be a goto here? */

    while (i <= str_len) {
      sep = str;
      chars++;
      if (mMck_cmp_key(sep)) {
        matches++;
      }

      str = mMck_search_sep(sep, str_len - i) + 1;
      i += (int)(str - sep); /* track current position */
    }

    *len = chars;
    return (matches * 10000) / (chars * 100);
  }
}

static int mMck_cmp_sep_nes(u8 c) {
  switch (c) {
    case CHAR_PERIOD:
    case CHAR_QUESTIONMARK:
    case CHAR_EXCLAMATION:
      return TRUE;

    default:
    return FALSE;
  }
}

static int mMck_strlen_new(u8* str, int len) {
  if (len > 0) {
    u8* end_p = str + len - 1;

    for (len; len != 0; len--) {
      if (*end_p != CHAR_SPACE) {
        break;
      }
      end_p--;
    }
  }

  return len;
}

static int mMck_check_alpha(u8 c, int alpha_case) {
  static u8 offset[mMck_CASE_NUM] = { CHAR_a, CHAR_A };

  int res = FALSE;

  if (alpha_case < mMck_CASE_NUM) {
    u8 ofs = offset[alpha_case];
    if (c >= ofs && c <= ofs + 25) {
      res = TRUE;
    }
  }

  return res;
}

static int mMck_check_eof(u8* str, int pos) {
  int points = 0;

  if (pos < MAIL_BODY_LEN && mMck_cmp_sep_nes(str[pos - 1]) == TRUE) {
    points = 20;
  }

  return points;
}

static int mMck_check_key_get_hit_count(u8* str) {
  u8* sep;
  int i;
  int hit_count;
  int str_len;

  i = 0;
  hit_count = 0;
  str_len = mMck_strlen_new(str, MAIL_BODY_LEN - 3);

  if (str_len <= 0) {
    return 0;
  }
  else {
    /* There might be a goto here? */

    while (i <= str_len) {
      sep = str;
      if (mMck_cmp_key(sep)) {
        hit_count++;
      }

      str = mMck_search_sep(sep, str_len - i) + 1;
      i += (int)(str - sep); /* track current position */
    }

    return hit_count;
  }
}

/* Scores each "sentence" for correct capitalization.
   An uppercase character must appear within 3 characters after separators.
*/
static int mMck_check_key_type_A(u8* str, int pos) {
  int sz;
  int points = mMck_check_eof(str, pos);

  while (str != NULL && pos > 3) {
    /* Find the next separator (.?!) */
    while (mMck_cmp_sep_nes(*str) == FALSE && pos > 3) {
      str++;
      pos--;
    }

    /* Must be three characters or more remaining */
    if (pos > 3) {
      sz = 3;
      str++;
      pos--;

      /* Check that at least one of the characters after the separator is uppercase */
      while (TRUE) {
        if (mMck_check_alpha(*str, mMck_CASE_UPPER) == TRUE) {
          break;
        }
        
        sz--;
        str++;
        pos--;

        if (sz <= 0) {
          break;
        }
      }

      /* Add or subtract 10 points depending on whether uppercase letters were found */
      if (sz == 0) {
        points -= 10;
      }
      else {
        points += 10;
      }
    }
  }

  return points;
}

/* Add three points for each "valid" three-character groupings */
static int mMck_check_key_type_B(u8* str, int len) {
  return mMck_check_key_get_hit_count(str) * 3;
}

/* 
  Add 20 points if the non-space character following a separator is correctly
  capitalized. If it is not, subtract 10 points. 0 points if no non-space
  characters are left following the separator.
*/
static int mMck_check_key_type_C(u8* str, int len) {
  int points = 0;

  for (len; len != 0; len--) {
    if (*str != CHAR_SPACE) {
      if (mMck_check_alpha(*str, mMck_CASE_UPPER) == TRUE) {
        points = 20;
      }
      else {
        points = -10;
      }

      break;
    }

    str++;
  }

  return points;
}

/*
  If three characters in a row are the same alpha (a-z/A-Z) character,
  subtract 50 points.
*/
static int mMck_check_key_type_D(u8* str, int len) {
  int points = 0;

  while (len > 2) {
    /* Check if the next character is alpha range (A-Za-z) */
    if (mMck_check_alpha(*str, mMck_CASE_LOWER) == TRUE || mMck_check_alpha(*str, mMck_CASE_UPPER) == TRUE) {
      if (str[0] == str[1] && str[0] == str[2]) {
        points = -50;
        break;
      }
    }

    len--;
    str++;
  }

  return points;
}

/*
  If the string is 20% or more spaces, add 20 points.
  Otherwise, subtract 20 points.
*/
static int mMck_check_key_type_E(u8* str, int len) {
  int spaces = 0;
  int non_spaces;
  int i;
  int points;

  for (i = len; i != 0; i--) {
    if (*str == CHAR_SPACE) {
      spaces++;
    }

    str++;
  }

  len = len - spaces;
  if (len > 0) {
    if ((spaces * 100) / len >= 20) {
      points = 20;
    }
    else {
      points = -20;
    }
  } else {
      points = -20;
  }

  return points;
}

/*
  Search for any run-on sentences. Run-on sentences are
  75 or more characters in a row without a separator (.?!).
  If a run-on sentence is found, subtract 150 points.
*/
static int mMck_check_key_type_F(u8* str, int len) {
  int sentence_len;
  int points = 0;

  while (len > 76) {
    if (mMck_cmp_sep_nes(*str) == TRUE) {
      sentence_len = 0;
      
      len--;
      str++;

      while (mMck_cmp_sep_nes(*str) == FALSE) {
        sentence_len++;

        if (sentence_len >= 75) {
          break;
        }
        
        str++;
        len--;
      }

      if (sentence_len >= 75) {
        points = -150;
        break;
      }
    }

    len--;
    str++;
  }

  return points;
}

/*
  Subtract 20 points for every 32 characters in a row
  for which a space is not present.
*/
static int mMck_check_key_type_G(u8* str, int len) {
  int r_len = 32;
  u8 no_space = TRUE;
  int points = 0;

  for (len; len > 0; len--) {
    r_len--;

    if (no_space == TRUE) {
      if (*str == CHAR_SPACE) {
        no_space = FALSE;
      }
      else if (r_len == 0) {
        points += -20;
      }
    }

    if (r_len == 0) {
      r_len = 32;
      no_space = TRUE;
    }

    str++;
  }

  return points;
}

typedef int (*mMck_CHECK_PROC)(u8*, int);

extern int mMck_check_key_hit_nes(u8* str) {
  static mMck_CHECK_PROC check_proc[mMck_CHECK_KEY_TYPE_NUM] = {
    &mMck_check_key_type_A,
    &mMck_check_key_type_B,
    &mMck_check_key_type_C,
    &mMck_check_key_type_D,
    &mMck_check_key_type_E,
    &mMck_check_key_type_F,
    &mMck_check_key_type_G
  };

  int len;
  int points = 0;
  int i;

  if (str != NULL) {
    len = mMck_strlen_new(str, MAIL_BODY_LEN);

    for (i = 0; i < mMck_CHECK_KEY_TYPE_NUM; i++) {
      points += (*check_proc[i])(str, len);
    }
  }

  return points;
}
