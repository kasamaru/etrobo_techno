/**
 * @brief forceSense.h
 */

#pragma once 

#include "ForceSensor.h"
#include "common.h"

using namespace spikeapi;

class ForceSense {
    public:
        ForceSense();

    private:
        ForceSensor forceSense;
}
