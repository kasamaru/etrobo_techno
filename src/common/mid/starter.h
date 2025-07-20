/**
 * @brief forceSense.h
 */

#pragma once 

#include "ForceSensor.h"
#include "common.h"

using namespace spikeapi;

class Starter {
    public:
        Starter(ForceSensor& forceSensor);

        bool isPushed(void);

    private:
        ForceSensor& mForceSensor;
};
