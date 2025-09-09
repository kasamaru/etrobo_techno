#pragma once
#include "common.h"
#include "ColorSensor.h"

using namespace spikeapi;

class LineMonitor {
    public:
        LineMonitor(ColorSensor& colorSensor);
        SDWORD getReflection(void);
        bool isLineDetected(WORD wRGBRth_Max, WORD wRGBGth_Max, WORD wRGBBth_Max, WORD wRGBRth_Min, WORD wRGBGth_Min, WORD wRGBBth_Min);
    
    private:
        ColorSensor& mColorSensor;
        ColorSensor::RGB p_RGB; // RGB値を格納する構造体
        bool isRGBThExceeded(WORD wRGBRth_Max, WORD wRGBGth_Max, WORD wRGBBth_Max, WORD wRGBRth_Min, WORD wRGBGth_Min, WORD wRGBBth_Min);
};
