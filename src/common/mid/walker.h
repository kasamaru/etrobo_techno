/**
 * @brief walker.h
 */

#pragma once

#include "Motor.h"
#include "common.h"

using namespace spikeapi;

class Walker {
    public:
        Walker();
        void runForward(WORD rightPWM, WORD leftPWM);
        void runBackward(WORD rightPWM, WORD leftPWM);
        DWORD getRightSpeed(void);
        DWORD getLeftSpeed(void);
        void stopRightWheel(void);
        void stopLeftWheel(void);
        void brakeRightWheel(void);
        void brakeLeftWheel(void);
    private:
        Motor leftWheel;
        Motor rightWheel;
};