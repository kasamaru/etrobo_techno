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

   bool isPushed() const;

    private:
        ForceSensor &mForceSensor;
}
