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
    static ColorSensor::ColorSensor frontColorSense;
    static RGB p_RGB;
    static HSV p_approximateHSV;
    static HSV p_proximateHSV;
    static SDWORD p_reflection;
    static SDWORD p_Ambient;
    static void p_setRgb(void);
    static void p_setHSV(void);
    static void p_setColor(void);
    
};
