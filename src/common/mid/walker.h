/**
 * @brief walker.h
 */

#pragma once

#include "Motor.h"
#include "common.h"

using namespace spikeapi;
class Walker {
    public:
        Walker(Motor& leftWheel, Motor& rightWheel);
        void setPWMForLineTrace(SWORD nRightPWM, SWORD nLeftPWM);
        void runForward(WORD rightPWM, WORD leftPWM);
        void runBackward(WORD rightPWM, WORD leftPWM);
        void stop(void);
        DWORD getRightSpeed(void);
        DWORD getLeftSpeed(void);
        void stopRightWheel(void);
        void stopLeftWheel(void);
        void brakeRightWheel(void);
        void brakeLeftWheel(void);
    private:
        Motor& mLeftWheel;
        Motor& mRightWheel;
};