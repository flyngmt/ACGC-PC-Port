/* Compact analytical astronomy for kyureki.c.
 * Mathematical models: Meeus, Astronomical Algorithms, 2nd ed., chs. 22/25/32/49;
 * truncated VSOP87D Earth longitude; Espenak/Meeus Delta-T polynomials.
 * Numerical coefficients are mathematical data, NOT calendar-date tables.
 */
#include "kyureki.h"
#include <math.h>
#include <stddef.h>

#ifdef __FAST_MATH__
#error "Do not compile the calendar with -ffast-math."
#endif

#define PI 3.14159265358979323846264338327950288
#define RAD (PI/180.0)
#define N(a) (sizeof(a)/sizeof((a)[0]))
static double norm(double x) { x=fmod(x,360.0); return x<0?x+360.0:x; }
static double sind(double x) { return sin(norm(x)*RAD); }
static double cosd(double x) { return cos(norm(x)*RAD); }
static double signed_angle(double x) { return norm(x+180.0)-180.0; }

typedef struct { double amplitude, phase, frequency; } term;
/* Truncated VSOP87D (equinox of date), amplitudes in 1e-8 radians.
 * Do NOT replace these with VSOP87's J2000-longitude coefficients. */
static const term L0[]={
 {175347046,0,0},{3341656,4.6692568,6283.07585},{34894,4.6261,12566.1517},
 {3497,2.7441,5753.3849},{3418,2.8289,3.5231},{3136,3.6277,77713.7715},
 {2676,4.4181,7860.4194},{2343,6.1352,3930.2097},{1324,.7425,11506.7698},
 {1273,2.0371,529.6910},{1199,1.1096,1577.3435},{990,5.233,5884.927},
 {902,2.045,26.298},{857,3.508,398.149},{780,1.179,5223.694},
 {753,2.533,5507.553},{505,4.583,18849.228},{492,4.205,775.523},
 {357,2.920,.067},{317,5.849,11790.629},{284,1.899,796.298},
 {271,.315,10977.079},{243,.345,5486.778},{206,4.806,2544.314},
 {205,1.869,5573.143},{202,2.458,6069.777},{156,.833,213.299},
 {132,3.411,2942.463},{126,1.083,20.775},{115,.645,.980},
 {103,.636,4694.003},{102,.976,15720.839},{102,4.267,7.114},
 {99,6.21,2146.17},{98,.68,155.42},{86,5.98,161000.69},
 {85,1.30,6275.96},{85,3.67,71430.70},{80,1.81,17260.15},
 {79,3.04,12036.46},{75,1.76,5088.63},{74,3.50,3154.69},
 {74,4.68,801.82},{70,.83,9437.76},{62,3.98,8827.39},
 {61,1.82,7084.90},{57,2.78,6286.60},{56,4.39,14143.50},
 {56,3.47,6279.55},{52,.19,12139.55},{52,1.33,1748.02},
 {51,.28,5856.48},{49,.49,1194.45},{41,5.37,8429.24},
 {41,2.40,19651.05},{39,6.17,10447.39},{37,6.04,10213.29},
 {37,2.57,1059.38},{36,1.71,2352.87},{36,1.78,6812.77},
 {33,.59,17789.85},{30,.44,83996.85},{30,2.74,1349.87},{25,3.16,4690.48}
};
static const term L1[]={
 {628331966747.491,0,0},{206059,2.678235,6283.07585},
 {4303,2.6351,12566.1517},{425,1.590,3.523},{119,5.796,26.298},
 {109,2.966,1577.344},{93,2.59,18849.23},{72,1.14,529.69},
 {68,1.87,398.15},{67,4.41,5507.55},{59,2.89,5223.69},
 {56,2.17,155.42},{45,.40,796.30},{36,.47,775.52},{29,2.65,7.11},
 {21,5.34,.98},{19,1.85,5486.78},{19,4.97,213.30},{17,2.99,6275.96},
 {16,.03,2544.31},{16,1.43,2146.17},{15,1.21,10977.08},
 {12,2.83,1748.02},{12,3.26,5088.63},{12,5.27,1194.45},
 {12,2.08,4694.00},{11,.77,553.57},{10,1.30,6286.60},
 {10,4.24,1349.87},{9,2.70,242.73},{9,5.64,951.72},
 {8,5.30,2352.87},{6,2.65,9437.76},{6,4.67,4690.48}
};
static const term L2[]={
 {52919,0,0},{8720,1.0721,6283.0758},{309,.867,12566.152},
 {27,.05,3.52},{16,5.19,26.30},{16,3.68,155.42},{10,.76,18849.23},
 {9,2.06,77713.77},{7,.83,775.52},{5,4.66,1577.34},{4,1.03,7.11},
 {4,3.44,5573.14},{3,5.14,796.30},{3,6.05,5507.55},{3,1.19,242.73},
 {3,6.12,529.69},{3,.31,398.15},{3,2.28,553.57},{2,4.38,5223.69},{2,3.75,.98}
};
static const term L3[]={
 {289.226,5.84384198723,6283.0758499914},{34.955,0,0},
 {16.819,5.48766912348,12566.1516999828},{2.962,5.19577265202,155.4203994342},
 {1.288,4.72200252235,3.523118349},{.635,5.96925937141,242.728603974},
 {.714,5.30045809128,18849.2275499742}
};
static const term L4[]={
 {114.084,PI,0},{7.717,4.13446589358,6283.0758499914},
 {.765,3.83803776214,12566.1516999828},{.420,.41925861858,155.4203994342}
};
static const term L5[]={
 {.878,PI,0},{.172,2.76579069510,6283.0758499914},
 {.050,2.01353298182,155.4203994342},{.028,2.21496423926,12566.1516999828}
};
static double series(const term *terms,size_t n,double t)
{
    double value=0; size_t i;
    for(i=0;i<n;++i) value+=terms[i].amplitude*cos(terms[i].phase+terms[i].frequency*t);
    return value;
}

double qk_builtin_solar_longitude(double jd_tt)
{
    double tau,T,longitude,omega,Lsun,Lmoon,M,e,C,v,r,nutation;
    if(!isfinite(jd_tt) || jd_tt<2200000 || jd_tt>2900000) return NAN;
    tau=(jd_tt-2451545.0)/365250.0; T=10*tau;
    longitude=series(L5,N(L5),tau);
    longitude=longitude*tau+series(L4,N(L4),tau);
    longitude=longitude*tau+series(L3,N(L3),tau);
    longitude=longitude*tau+series(L2,N(L2),tau);
    longitude=longitude*tau+series(L1,N(L1),tau);
    longitude=longitude*tau+series(L0,N(L0),tau);
    longitude=longitude*1e-8/RAD+180.0;
    omega=125.04452-1934.136261*T+.0020708*T*T+T*T*T/450000;
    Lsun=280.4665+36000.7698*T;
    Lmoon=218.3165+481267.8813*T;
    nutation=-17.20*sind(omega)-1.32*sind(2*Lsun)-.23*sind(2*Lmoon)+.21*sind(2*omega);
    /* Keplerian radius is sufficient for the small aberration correction. */
    M=357.52911+35999.05029*T-.0001537*T*T;
    e=.016708634-.000042037*T-.0000001267*T*T;
    C=(1.914602-.004817*T-.000014*T*T)*sind(M)
      +(.019993-.000101*T)*sind(2*M)+.000289*sind(3*M);
    v=M+C; r=1.000001018*(1-e*e)/(1+e*cosd(v));
    return norm(longitude+(-.09033+nutation-20.4898/r)/3600.0);
}

double qk_builtin_solar_term_tt(int year,int longitude,void *unused)
{
    qk_gregorian jan={year,1,1};
    long jdn;
    double jd0,guess,lo,hi,mid,angle;
    int i;
    (void)unused;
    if(year<1598 || year>3002 || longitude<0 || longitude>=360 || longitude%30)
        return NAN;
    if(qk_gregorian_to_jdn(&jan,&jdn)!=QK_OK) return NAN;
    jd0=jdn-.5;
    guess=jd0+norm(longitude-qk_builtin_solar_longitude(jd0))*365.2422/360;
    lo=guess-8; hi=guess+8;
    if(signed_angle(qk_builtin_solar_longitude(lo)-longitude)>0 ||
       signed_angle(qk_builtin_solar_longitude(hi)-longitude)<0) return NAN;
    for(i=0;i<40;++i) {
        mid=(lo+hi)/2;
        angle=signed_angle(qk_builtin_solar_longitude(mid)-longitude);
        if(!isfinite(angle)) return NAN;
        if(angle<0) lo=mid; else hi=mid;
        if(hi-lo<1e-8) break; /* Root tolerance, NOT ephemeris accuracy. */
    }
    return (lo+hi)/2;
}

/* A phase correction A*sin(p*M + q*Mmoon + r*F + s*Omega)*E^e. */
typedef struct { double a; int p,q,r,s,e; } moon_term;
static const moon_term moon_terms[]={
 {-.40720,0,1,0,0,0},{.17241,1,0,0,0,1},{.01608,0,2,0,0,0},
 {.01039,0,0,2,0,0},{.00739,-1,1,0,0,1},{-.00514,1,1,0,0,1},
 {.00208,2,0,0,0,2},{-.00111,0,1,-2,0,0},{-.00057,0,1,2,0,0},
 {.00056,1,2,0,0,1},{-.00042,0,3,0,0,0},{.00042,1,0,2,0,1},
 {.00038,1,0,-2,0,1},{-.00024,-1,2,0,0,1},{-.00017,0,0,0,1,0},
 {-.00007,2,1,0,0,0},{.00004,0,2,-2,0,0},{.00004,3,0,0,0,0},
 {.00003,1,1,-2,0,0},{.00003,0,2,2,0,0},{-.00003,1,1,2,0,0},
 {.00003,-1,1,2,0,0},{-.00002,-1,1,-2,0,0},{-.00002,1,3,0,0,0},
 {.00002,0,4,0,0,0}
};
/* amplitude [days], constant [degrees], coefficient of k [degrees]. */
static const term planetary[]={
 {.000325,299.77,.107408},{.000165,251.88,.016321},
 {.000164,251.83,26.651886},{.000126,349.42,36.412478},
 {.000110,84.66,18.206239},{.000062,141.74,53.303771},
 {.000060,207.14,2.453732},{.000056,154.84,7.306860},
 {.000047,34.52,27.261239},{.000042,207.19,.121824},
 {.000040,291.34,1.844379},{.000037,161.72,24.198154},
 {.000035,239.56,25.513099},{.000023,331.55,3.592518}
};

double qk_builtin_new_moon_tt(long k_index,void *unused)
{
    double k=(double)k_index,T,T2,E,M,Mp,F,O,jd,angle,factor;
    size_t i;
    (void)unused;
    if(k_index < -5000 || k_index > 12420) return NAN;
    T=k/1236.85; T2=T*T;
    jd=2451550.09766+29.530588861*k+T2*(.00015437+T*(-.000000150+.00000000073*T));
    E=1-.002516*T-.0000074*T2;
    M=norm(2.5534+29.10535670*k+T2*(-.0000014-.00000011*T));
    Mp=norm(201.5643+385.81693528*k+T2*(.0107582+T*(.00001238-.000000058*T)));
    F=norm(160.7108+390.67050284*k+T2*(-.0016118+T*(-.00000227+.000000011*T)));
    O=norm(124.7746-1.56375588*k+T2*(.0020672+.00000215*T));
    for(i=0;i<N(moon_terms);++i) {
        const moon_term *x=&moon_terms[i];
        factor=x->e==0?1:(x->e==1?E:E*E);
        angle=x->p*M+x->q*Mp+x->r*F+x->s*O;
        jd+=x->a*factor*sind(angle);
    }
    for(i=0;i<N(planetary);++i) {
        angle=planetary[i].phase+planetary[i].frequency*k;
        if(i==0) angle-=.009173*T2;
        jd+=planetary[i].amplitude*sind(angle);
    }
    return jd;
}

double qk_builtin_delta_t_seconds(double jd_tt,void *unused)
{
    qk_gregorian date,jan;
    long jdn,j0,j1;
    double y,t,u;
    (void)unused;
    if(!isfinite(jd_tt) || jd_tt<2200000 || jd_tt>2900000) return NAN;
    jdn=(long)floor(jd_tt+.5);
    if(qk_jdn_to_gregorian(jdn,&date)!=QK_OK) return NAN;
    jan.year=date.year; jan.month=jan.day=1;
    if(qk_gregorian_to_jdn(&jan,&j0)!=QK_OK) return NAN;
    ++jan.year; if(qk_gregorian_to_jdn(&jan,&j1)!=QK_OK) return NAN;
    y=date.year+(jd_tt+.5-j0)/(j1-j0);
    /* Original polynomial forecast deliberately frozen for reproducibility.
     * NOT an up-to-date measurement of the Earth's rotation. */
    if(y<1600) {
        u=(y-1000)/100;
        return 1574.2+u*(-556.01+u*(71.23472+u*(.319781+u*(-.8503463+u*(-.005050998+.0083572073*u)))));
    }
    if(y<1700) {t=y-1600; return 120+t*(-.9808+t*(-.01532+t/7129));}
    if(y<1800) {t=y-1700; return 8.83+t*(.1603+t*(-.0059285+t*(.00013336-t/1174000)));}
    if(y<1860) {t=y-1800; return 13.72+t*(-.332447+t*(.0068612+t*(.0041116+t*(-.00037436+t*(.0000121272+t*(-.0000001699+.000000000875*t))))));}
    if(y<1900) {t=y-1860; return 7.62+t*(.5737+t*(-.251754+t*(.01680668+t*(-.0004473624+t/233174))));}
    if(y<1920) {t=y-1900; return -2.79+t*(1.494119+t*(-.0598939+t*(.0061966-.000197*t)));}
    if(y<1941) {t=y-1920; return 21.20+t*(.84493+t*(-.076100+.0020936*t));}
    if(y<1961) {t=y-1950; return 29.07+t*(.407+t*(-1.0/233+t/2547));}
    if(y<1986) {t=y-1975; return 45.45+t*(1.067+t*(-1.0/260-t/718));}
    if(y<2005) {t=y-2000; return 63.86+t*(.3345+t*(-.060374+t*(.0017275+t*(.000651814+.00002373599*t))));}
    if(y<2050) {t=y-2000; return 62.92+t*(.32217+.005589*t);}
    u=(y-1820)/100;
    if(y<2150) return -20+32*u*u-.5628*(2150-y);
    return -20+32*u*u;
}
