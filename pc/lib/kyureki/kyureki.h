#ifndef KYUREKI_H
#define KYUREKI_H
/* Modern, winter-solstice-first Japanese lunisolar calendar.
 * Gregorian arithmetic is proleptic. Calendar days use modeled UT1 + 09:00.
 * This is NOT a reconstruction of the historical Tenpo calendar.
 * No calendar-date lookup tables, heap allocation, OS clock or time_t.
 */
#ifdef __cplusplus
extern "C" {
#endif

#define QK_MODEL_ID "winter-first-japan-meeus-v1"
#define QK_MIN_YEAR 1600
#define QK_MAX_YEAR 3000
#define QK_MAX_MONTHS 13

typedef enum {
    QK_OK = 0, QK_INVALID_ARGUMENT, QK_OUT_OF_RANGE,
    QK_ASTRONOMY_ERROR, QK_INVARIANT_ERROR, QK_DATE_NOT_IN_YEAR
} qk_status;

enum {
    /* Heuristic review flag, NOT a proven error bound. */
    QK_NEAR_MIDNIGHT = 1,
    /* Outside the conservative near-modern 1900..2100 labeling window.
     * All future Earth-rotation values remain forecasts, even inside it. */
    QK_EXTRAPOLATED = 2
};

typedef struct { int year, month, day; } qk_gregorian;
typedef struct { int year, month, day, leap; } qk_date;
typedef struct {
    long start_jdn; /* Integer civil-day label; NOT an astronomical instant. */
    int number;    /* 1..12, also for an intercalary month. */
    int leap;      /* 0 = regular; 1 = intercalary/repeated month. */
    int days;      /* 29 or 30 */
} qk_month;
typedef struct {
    int year, count;
    unsigned warnings;
    double min_midnight_distance_seconds;
    qk_month months[QK_MAX_MONTHS]; /* CHRONOLOGICAL, not legacy slot order. */
} qk_year;

/* Optional astronomy replacement, primarily for validation / better ephemerides.
 * All event functions return Julian dates in Terrestrial Time (TT).
 * k=0 is the new moon near 2000-01-06; k increases by one per lunation.
 * Solar longitude is apparent geocentric ecliptic longitude OF DATE, degrees.
 * delta_t_seconds returns TT-UT1, evaluated at the supplied TT Julian date.
 * Return NaN on a failed astronomical calculation.
 * NULL config selects all built-in algorithms with a 300-second review margin.
 * A non-NULL config must provide ALL callbacks, even if some are built-ins.
 * Keep config and model fixed for reproducible results; no global mutable state.
 */
typedef struct {
    double (*new_moon_tt)(long k, void *user);
    double (*solar_term_tt)(int year, int longitude, void *user);
    double (*delta_t_seconds)(double jd_tt, void *user);
    void *user;
    double midnight_review_seconds; /* [0,43200], heuristic, not confidence. */
} qk_config;

/* Build a complete LUNAR year, not a Gregorian January-to-December calendar.
 * Supported lunar years: 1600..3000 inclusive. Padding astronomical events
 * outside those endpoints are calculated internally. Output unchanged on error.
 */
qk_status qk_build_year(int lunar_year, const qk_config *config, qk_year *out);
/* Fast conversions using a caller-owned cached year. No new astronomy. */
qk_status qk_to_gregorian(const qk_year *year, int month, int day, int leap,
                         qk_gregorian *out);
qk_status qk_from_gregorian(const qk_year *year, const qk_gregorian *date,
                           qk_date *out);
/* Convenience version that builds the required lunar year. January can belong
 * to the preceding year. Supported dates are those in lunar years 1600..3000.
 */
qk_status qk_lookup_gregorian(const qk_gregorian *date, const qk_config *config,
                             qk_date *out);
qk_status qk_harvest_moon(int lunar_year, const qk_config *config,
                         qk_gregorian *out); /* REGULAR month 8, day 15 */
qk_status qk_equinox(int gregorian_year, int autumn, const qk_config *config,
                     qk_gregorian *out);

int qk_gregorian_month_days(int year, int month);
qk_status qk_gregorian_to_jdn(const qk_gregorian *date, long *out);
qk_status qk_jdn_to_gregorian(long jdn, qk_gregorian *out);
const char *qk_status_string(qk_status status);

/* Built-in ephemeris functions, exposed to enable independent testing. */
double qk_builtin_new_moon_tt(long k, void *unused);
double qk_builtin_solar_term_tt(int year, int longitude, void *unused);
double qk_builtin_delta_t_seconds(double jd_tt, void *unused);
double qk_builtin_solar_longitude(double jd_tt);

#ifdef __cplusplus
}
#endif
#endif
