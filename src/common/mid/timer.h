
/**
 * @brief Timer.h
 */

 #pragma once

#include "Clock.h"
#include "common.h"

using namespace spikeapi;

class Timer {
    public:
        Timer(Clock& clock);
        void start(DWORD timeoutDuration_MS);
        void stop(void);
        void reset(void);
        bool isTimeout(void);
    private:
        const Clock& mClock;
        DWORD dwStartTime_MS;
        DWORD dwTimeoutDuration;
        bool bIsTimeout;
};