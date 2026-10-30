#ifndef AC_BATCH_PACING_H
#define AC_BATCH_PACING_H
#include <stdint.h>
typedef struct {
    uint64_t refresh,period,next;
    unsigned int missed;
} ACBatchPacing;
/* Call at actual blank edges. Render/IO consume the period's budget instead
 * of adding another full sleep. Rebase on missed deadlines, never catch up. */
int ac_batch_pacing_reset(ACBatchPacing *,uint64_t now,uint64_t refresh,uint64_t frequency);
int ac_batch_pacing_ready(ACBatchPacing *,uint64_t now);
#endif
