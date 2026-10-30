#include "batch_pacing.h"
int ac_batch_pacing_reset(ACBatchPacing *p,uint64_t now,uint64_t refresh,uint64_t frequency){
    if(!p||!refresh||!frequency||refresh>frequency||frequency>UINT64_MAX/2)return -1;
    uint64_t target=frequency/30;
    uint64_t edges=(target+refresh/2)/refresh;
    if(edges<1)edges=1;
    if(edges>4||refresh>UINT64_MAX/4)return -1;
    uint64_t period=refresh*edges;
    if(now>UINT64_MAX-period)return -1;
    *p=(ACBatchPacing){refresh,period,now+period,0};return 0;
}
int ac_batch_pacing_ready(ACBatchPacing *p,uint64_t now){
    if(!p||!p->refresh||!p->period||p->next<p->refresh/2)return -1;
    if(now<p->next-p->refresh/2)return 0;
    if(now>UINT64_MAX-p->period||p->next>UINT64_MAX-p->period)return -1;
    if(now>p->next&&now-p->next>p->refresh/2){
        ++p->missed;p->next=now+p->period;
    }else p->next+=p->period;
    return 1;
}
