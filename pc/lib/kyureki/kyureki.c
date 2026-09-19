#include "kyureki.h"
#include <math.h>
#include <float.h>
#include <stddef.h>
#include <string.h>

#define SECONDS_PER_DAY 86400.0
#define JAPAN_OFFSET_DAYS (9.0 / 24.0)
#define NEW_MOON_EPOCH 2451550.09766
#define MEAN_MONTH 29.530588861

static const qk_config default_config = {
    qk_builtin_new_moon_tt, qk_builtin_solar_term_tt,
    qk_builtin_delta_t_seconds, NULL, 300.0
};

int qk_gregorian_month_days(int year, int month)
{
    static const int days[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (year < 1 || year > 9999 || month < 1 || month > 12) return 0;
    return days[month-1] + (month == 2 &&
        year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

qk_status qk_gregorian_to_jdn(const qk_gregorian *date, long *out)
{
    long a, y, m;
    int n;
    if (!date || !out) return QK_INVALID_ARGUMENT;
    n = qk_gregorian_month_days(date->year, date->month);
    if (!n || date->day < 1 || date->day > n) return QK_INVALID_ARGUMENT;
    a = (14 - date->month) / 12;
    y = (long)date->year + 4800 - a;
    m = date->month + 12*a - 3;
    *out = date->day + (153*m+2)/5 + 365*y + y/4 - y/100 + y/400 - 32045;
    return QK_OK;
}

qk_status qk_jdn_to_gregorian(long jdn, qk_gregorian *out)
{
    long a, b, c, d, e, m;
    qk_gregorian value;
    if (!out) return QK_INVALID_ARGUMENT;
    if (jdn < 1721426L || jdn > 5373484L) return QK_OUT_OF_RANGE;
    a = jdn + 32044; b = (4*a+3)/146097; c = a - (146097*b)/4;
    d = (4*c+3)/1461; e = c - (1461*d)/4; m = (5*e+2)/153;
    value.day = (int)(e-(153*m+2)/5+1);
    value.month = (int)(m+3-12*(m/10));
    value.year = (int)(100*b+d-4800+m/10);
    *out = value;
    return QK_OK;
}

static const qk_config *get_config(const qk_config *config)
{
    if (!config) return &default_config;
    if (!config->new_moon_tt || !config->solar_term_tt ||
        !config->delta_t_seconds || !isfinite(config->midnight_review_seconds) ||
        config->midnight_review_seconds < 0 || config->midnight_review_seconds > 43200)
        return NULL;
    return config;
}

/* Convert an event instant to the JAPANESE CIVIL DATE containing it.
 * A solar term on the new-moon DATE belongs to the new month, even when the
 * solar term's instant precedes the new moon's instant on that date.
 */
static qk_status event_day(const qk_config *config, double tt,
                           long *day, double *min_distance)
{
    double dt, local, f, distance;
    if (!isfinite(tt) || tt < 2200000.0 || tt > 2900000.0)
        return QK_ASTRONOMY_ERROR;
    dt = config->delta_t_seconds(tt, config->user);
    if (!isfinite(dt) || fabs(dt) > 86400) return QK_ASTRONOMY_ERROR;
    local = tt - dt/SECONDS_PER_DAY + JAPAN_OFFSET_DAYS + 0.5;
    *day = (long)floor(local);
    f = local - floor(local);
    distance = fmin(f, 1-f) * SECONDS_PER_DAY;
    if (min_distance && distance < *min_distance) *min_distance = distance;
    return QK_OK;
}

static qk_status moon_day(const qk_config *c, long k, long *day, double *distance)
{
    return event_day(c, c->new_moon_tt(k, c->user), day, distance);
}

/* Find the month containing a winter-solstice civil date, not necessarily
 * the last conjunction BEFORE the solstice instant. Both loops are bounded.
 */
static qk_status winter_anchor(const qk_config *c, double solstice,
                               long solstice_day, long *k_out, double *distance)
{
    long k, a, b;
    int tries;
    qk_status s;
    k = (long)floor((solstice - NEW_MOON_EPOCH)/MEAN_MONTH);
    for (tries=0; tries<6; ++tries) {
        s = moon_day(c,k,&a,distance); if (s != QK_OK) return s;
        s = moon_day(c,k+1,&b,distance); if (s != QK_OK) return s;
        if (b-a < 29 || b-a > 30) return QK_INVARIANT_ERROR;
        if (a <= solstice_day && solstice_day < b) { *k_out=k; return QK_OK; }
        k += (solstice_day < a) ? -1 : 1;
    }
    return QK_INVARIANT_ERROR;
}

typedef struct {
    int count;
    qk_month month[13];
    int year[13];
} sui;

/* One solstice-to-solstice block: initial month 11 inclusive, next 11 exclusive. */
static qk_status build_sui(int year, const qk_config *c, sui *out, double *distance)
{
    double ws[2], tt, last_tt;
    long ws_day[2], k0, k1, starts[14], terms[13];
    int n, i, j, leap_index=-1, number=11, lunar_year=year;
    qk_status s;
    ws[0] = c->solar_term_tt(year,270,c->user);
    ws[1] = c->solar_term_tt(year+1,270,c->user);
    for (i=0;i<2;++i) {
        s=event_day(c,ws[i],&ws_day[i],distance); if (s != QK_OK) return s;
    }
    if (ws[1]-ws[0] < 364 || ws[1]-ws[0] > 367) return QK_INVARIANT_ERROR;
    s=winter_anchor(c,ws[0],ws_day[0],&k0,distance); if(s != QK_OK) return s;
    s=winter_anchor(c,ws[1],ws_day[1],&k1,distance); if(s != QK_OK) return s;
    n=(int)(k1-k0);
    if (n != 12 && n != 13) return QK_INVARIANT_ERROR;
    for (i=0;i<=n;++i) {
        s=moon_day(c,k0+i,&starts[i],distance); if(s != QK_OK) return s;
        if (i && (starts[i]-starts[i-1]<29 || starts[i]-starts[i-1]>30))
            return QK_INVARIANT_ERROR;
    }
    terms[0]=ws_day[0]; terms[12]=ws_day[1]; last_tt=ws[0];
    for(i=1;i<12;++i) {
        tt=c->solar_term_tt(year+1,(270+30*i)%360,c->user);
        s=event_day(c,tt,&terms[i],distance); if(s != QK_OK) return s;
        if (tt-last_tt < 28 || tt-last_tt > 33) return QK_INVARIANT_ERROR;
        last_tt=tt;
    }
    if (ws[1]-last_tt < 28 || ws[1]-last_tt > 33) return QK_INVARIANT_ERROR;
    if (n==13) {
        /* Do not turn every termless month into a leap month. Choose just the
         * FIRST termless month, and only in a 13-month solstice block. */
        for(i=1;i<n;++i) {
            int contains=0;
            for(j=0;j<13;++j)
                if(starts[i]<=terms[j] && terms[j]<starts[i+1]) contains=1;
            if(!contains) { leap_index=i; break; }
        }
        if(leap_index<0) return QK_INVARIANT_ERROR;
    }
    out->count=n;
    for(i=0;i<n;++i) {
        int leap=(i==leap_index);
        if(i && !leap) { number=number%12+1; if(number==1) ++lunar_year; }
        out->month[i].start_jdn=starts[i]; out->month[i].number=number;
        out->month[i].leap=leap; out->month[i].days=(int)(starts[i+1]-starts[i]);
        out->year[i]=lunar_year;
    }
    return QK_OK;
}

qk_status qk_build_year(int lunar_year, const qk_config *config, qk_year *out)
{
    const qk_config *c=get_config(config);
    qk_year result;
    sui block;
    int y,i,regular=0,leaps=0;
    qk_status s;
    if(!out || !c) return QK_INVALID_ARGUMENT;
    if(lunar_year<QK_MIN_YEAR || lunar_year>QK_MAX_YEAR) return QK_OUT_OF_RANGE;
    memset(&result,0,sizeof(result));
    result.year=lunar_year; result.min_midnight_distance_seconds=DBL_MAX;
    for(y=lunar_year-1;y<=lunar_year;++y) {
        s=build_sui(y,c,&block,&result.min_midnight_distance_seconds);
        if(s != QK_OK) return s;
        for(i=0;i<block.count;++i) if(block.year[i]==lunar_year) {
            if(result.count>=QK_MAX_MONTHS) return QK_INVARIANT_ERROR;
            result.months[result.count++]=block.month[i];
        }
    }
    if(result.count!=12 && result.count!=13) return QK_INVARIANT_ERROR;
    for(i=0;i<result.count;++i) {
        qk_month *m=&result.months[i];
        if(i && m->start_jdn != result.months[i-1].start_jdn+result.months[i-1].days)
            return QK_INVARIANT_ERROR;
        if(m->leap) {
            ++leaps;
            if(!i || m->number!=result.months[i-1].number || result.months[i-1].leap)
                return QK_INVARIANT_ERROR;
        } else if(m->number!=++regular) return QK_INVARIANT_ERROR;
    }
    if(regular!=12 || leaps>1) return QK_INVARIANT_ERROR;
    if(result.min_midnight_distance_seconds<=c->midnight_review_seconds)
        result.warnings|=QK_NEAR_MIDNIGHT;
    if(lunar_year<1900 || lunar_year>2100) result.warnings|=QK_EXTRAPOLATED;
    *out=result;
    return QK_OK;
}

/* Cached years must have been returned successfully by qk_build_year and not
 * modified by the caller. These are data structures, not serialized input. */
static int valid_cached_year(const qk_year *y)
{
    return y && y->year>=QK_MIN_YEAR && y->year<=QK_MAX_YEAR &&
        (y->count==12 || y->count==13);
}

qk_status qk_to_gregorian(const qk_year *year,int month,int day,int leap,qk_gregorian *out)
{
    int i;
    if(!out || !valid_cached_year(year) || month<1 || month>12 ||
       day<1 || day>30 || (leap!=0 && leap!=1)) return QK_INVALID_ARGUMENT;
    for(i=0;i<year->count;++i) {
        const qk_month *m=&year->months[i];
        if(m->number==month && m->leap==leap) {
            if(day>m->days) return QK_INVALID_ARGUMENT;
            return qk_jdn_to_gregorian(m->start_jdn+day-1,out);
        }
    }
    return QK_INVALID_ARGUMENT; /* Requested leap month does not exist. */
}

qk_status qk_from_gregorian(const qk_year *year,const qk_gregorian *date,qk_date *out)
{
    long jdn;
    int i;
    qk_status s;
    if(!out || !valid_cached_year(year)) return QK_INVALID_ARGUMENT;
    s=qk_gregorian_to_jdn(date,&jdn); if(s != QK_OK) return s;
    for(i=0;i<year->count;++i) {
        const qk_month *m=&year->months[i];
        if(m->start_jdn<=jdn && jdn<m->start_jdn+m->days) {
            qk_date result={year->year,m->number,(int)(jdn-m->start_jdn+1),m->leap};
            *out=result; return QK_OK;
        }
    }
    return QK_DATE_NOT_IN_YEAR;
}

qk_status qk_lookup_gregorian(const qk_gregorian *date,const qk_config *config,qk_date *out)
{
    qk_year y;
    int candidate;
    long ignored;
    qk_status s;
    if(!out || !get_config(config)) return QK_INVALID_ARGUMENT;
    s=qk_gregorian_to_jdn(date,&ignored); if(s != QK_OK) return s;
    for(candidate=date->year;candidate>=date->year-1;--candidate) {
        if(candidate<QK_MIN_YEAR || candidate>QK_MAX_YEAR) continue;
        s=qk_build_year(candidate,config,&y); if(s != QK_OK) return s;
        s=qk_from_gregorian(&y,date,out);
        if(s!=QK_DATE_NOT_IN_YEAR) return s;
    }
    return QK_OUT_OF_RANGE;
}

qk_status qk_harvest_moon(int lunar_year,const qk_config *config,qk_gregorian *out)
{
    qk_year y;
    qk_status s;
    if(!out) return QK_INVALID_ARGUMENT;
    s=qk_build_year(lunar_year,config,&y); if(s != QK_OK) return s;
    return qk_to_gregorian(&y,8,15,0,out);
}

qk_status qk_equinox(int year,int autumn,const qk_config *config,qk_gregorian *out)
{
    const qk_config *c=get_config(config);
    long day;
    qk_status s;
    if(!c || !out || (autumn!=0 && autumn!=1)) return QK_INVALID_ARGUMENT;
    if(year<QK_MIN_YEAR || year>QK_MAX_YEAR) return QK_OUT_OF_RANGE;
    s=event_day(c,c->solar_term_tt(year,autumn?180:0,c->user),&day,NULL);
    if(s!=QK_OK) return s;
    return qk_jdn_to_gregorian(day,out);
}

const char *qk_status_string(qk_status status)
{
    switch(status) {
    case QK_OK:return "OK";
    case QK_INVALID_ARGUMENT:return "invalid argument";
    case QK_OUT_OF_RANGE:return "outside supported lunar-year range";
    case QK_ASTRONOMY_ERROR:return "astronomical calculation failed";
    case QK_INVARIANT_ERROR:return "calendar invariant failed";
    case QK_DATE_NOT_IN_YEAR:return "date is not in the cached lunar year";
    default:return "unknown error";
    }
}
