#pragma once
#include "common.h"
#include "ColorSensor.h"

using namespace spikespi;

class ColorSense {
    public:
    void ColorSense();
    WORD getApproximateHSV_H(void);
    BYTE getApproximateHSV_S(void);
    BYTE getApproximateHSV_V(void);
    WORD getProximateHSV_H(void);
    BYTE getProximateHSV_S(void);
    BYTE getProximateHSV_V(void);
    WORD getRGB_R(void);
    WORD getRGB_G(void);
    WORD getRGB_B(void);
    
    private:
    ColorSensor::ColorSensor frontColorSense;
    RGB p_RGB;
    HSV p_approximateHSV;
    HSV p_proximateHSV;
    SDWORD p_reflection;
    SDWORD p_Ambient;
    void p_setRgb(void);
    void p_setHSV(void);
    void p_setColor(void);
    
}
