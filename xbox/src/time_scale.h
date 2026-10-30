#ifndef AC_XENON_TIME_SCALE_H
#define AC_XENON_TIME_SCALE_H
#define AC_XENON_TIMEBASE_HZ 49875000ULL
#define AC_GC_TIMER_HZ 40500000ULL
static inline unsigned long long ac_scale_timebase(unsigned long long native) {
    return native / AC_XENON_TIMEBASE_HZ * AC_GC_TIMER_HZ +
           native % AC_XENON_TIMEBASE_HZ * AC_GC_TIMER_HZ / AC_XENON_TIMEBASE_HZ;
}
#endif
