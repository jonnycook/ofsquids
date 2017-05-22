#include "timer.h"
#include "allegro.h"

void inc_timer(void *p) {
    ++ (*(unsigned int *)p);
} END_OF_FUNCTION(inc_timer)

Timer::Timer() {
    ticks = 0;
}

bool Timer::Install() {
    LOCK_FUNCTION(inc_timer);
    LOCK_VARIABLE(tick);
    install_timer();
    install_param_int_ex(inc_timer, (void *)&ticks, BPS_TO_TIMER(60));
}

Timer &Timer::GetInstance() {
    static Timer instance;
    return instance;
}
