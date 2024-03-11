#ifndef IMP_TIMER_H
#define IMP_TIMER_H

#include "baseFunc.h"

class ImpTimer {
public:
    ImpTimer();
    ~ImpTimer();

    void start();
    void stop();
    void paused();
    void unpaused();
    
    int get_ticks();

    bool is_started();
    bool is_paused();

private:
    int start_tick;
    int paused_tick;
    int is_paused_;
    int is_started_;
};





#endif //IMP_TIMER_H