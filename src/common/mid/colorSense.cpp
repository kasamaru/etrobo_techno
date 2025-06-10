#include <stdio.h>

#include "colorSense.h"

void ColorSense::ColorSense():
    frontColorSense(EPort::PORT_C){
}

WORD getApproximateHSV_H(void) {
    return p_ApproximateHSV.H;
}
BYTE getApproximateHSV_S(void) {
    return p_ApproximateHSV.S;
}
BYTE getApproximateHSV_V(void) {
    return p_ApproximateHSV.V;
}
WORD getProximateHSV_H(void) {
    return p_ProximateHSV.H;
}
BYTE getProximateHSV_S(void) {
    return p_ProximateHSV.S;
}
BYTE getProximateHSV_V(void) {
    return p_ProximateHSV.V;
}
WORD getRGB_R(void) {
    return p_RGB.R;
}
WORD getRGB_G(void) {
    return p_RGB.G;
}
WORD getRGB_B(void) {
    return p_RGB.B;
}

void getRGB(RGB* rgb) {
    std::memcpy(rgb, &(p_RGB), sizeof(p_RGB)/sizeof(WORD));
}

void getProximateHSV(HSV* hsv) {
    std::memcpy(hsv, &(p_ProximateHSV), sizeof(p_ProximateHSV)/sizeof(WORD));
}

void getApproximateHSV(HSV* hsv) {
    std::memcpy(hsv, &(p_ApproximateHSV), sizeof(p_ApproximateHSV)/sizeof(WORD));
}

void p_setRgb(void) {
    frontColorSense.getRGB(&p_RGB);
}
void p_setHSV(void) {
    frontColorSense.getHSV(&p_ProximateHSV);
}
void p_setColor(void) {
    frontColorSense.getColor(&p_ApproximateHSV);
}