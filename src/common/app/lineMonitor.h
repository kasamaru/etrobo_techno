#pragma once
#include "common.h"
#include "ColorSensor.h"

using namespace spikeapi;

class LineMonitor {
    public:
        LineMonitor(ColorSensor& colorSensor);
        SDWORD getReflection(void);
        bool isLineDetected(WORD wRGBR, WORD wRGBG, WORD wRGBB);
    
    private:
        ColorSensor& mColorSensor;
        ColorSensor::RGB p_RGB; // RGB値を格納する構造体
        bool isRGBThExceeded(WORD wRGBR, WORD wRGBG, WORD wRGBB);
};
