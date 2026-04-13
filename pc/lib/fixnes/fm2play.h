/* fm2play.h — stub (no movie playback needed) */
#ifndef _fm2play_h_
#define _fm2play_h_

#include <stdbool.h>

void fm2playInit(const char *fname, int start, bool pal);
bool fm2playRunning();
void fm2playUpdate();

#endif
