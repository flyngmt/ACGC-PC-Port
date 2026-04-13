/* fm2play.c — stub (no movie playback needed) */
#include <stdbool.h>
#include "fm2play.h"

void fm2playInit(const char *fname, int start, bool pal) {
    (void)fname; (void)start; (void)pal;
}
bool fm2playRunning() { return false; }
void fm2playUpdate() { }
