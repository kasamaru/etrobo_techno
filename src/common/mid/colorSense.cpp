#include <stdio.h>

/* TODO: ファイル名がよくないので変更、技術教育ならLineMonitorになっている */
#include "colorSense.h"

void ColorSense::ColorSense():
    frontColorSense(EPort::PORT_C){
}

/**
 * @brief 近似色相取得
 */
WORD ColorSense::getApproximateHSV_H(void) {
    return p_ApproximateHSV.H;
}

/**
 * @brief 近似彩度取得
 */
BYTE ColorSense::getApproximateHSV_S(void) {
    return p_ApproximateHSV.S;
}

/**
 * @brief 近似明度取得
 */
BYTE ColorSense::getApproximateHSV_V(void) {
    return p_ApproximateHSV.V;
}

/**
 * @brief 近似なし色相取得
 */
WORD ColorSense::getProximateHSV_H(void) {
    return p_ProximateHSV.H;
}

/**
 * @brief 近似なし彩度取得
 */
BYTE ColorSense::getProximateHSV_S(void) {
    return p_ProximateHSV.S;
}

/**
 * @brief 近似なし明度取得
 */
BYTE ColorSense::getProximateHSV_V(void) {
    return p_ProximateHSV.V;
}

/**
 * @brief R値取得
 */
WORD ColorSense::getRGB_R(void) {
    return p_RGB.R;
}

/**
 * @brief G値取得
 */
WORD ColorSense::getRGB_G(void) {
    return p_RGB.G;
}

/**
 * @brief B値取得
 */
WORD ColorSense::getRGB_B(void) {
    return p_RGB.B;
}

/**
 * @brief RGB値のコピー
 */
void cpyRGB(RGB* rgb) {
    std::memcpy(rgb, &(p_RGB), sizeof(p_RGB)/sizeof(WORD));
}

void cpyProximateHSV(HSV* hsv) {
    std::memcpy(hsv, &(p_ProximateHSV), sizeof(p_ProximateHSV)/sizeof(WORD));
}

void cpyApproximateHSV(HSV* hsv) {
    std::memcpy(hsv, &(p_ApproximateHSV), sizeof(p_ApproximateHSV)/sizeof(WORD));
}

void p_setRgb(void) {
    frontColorSense.getRGB(&p_RGB);
    cpyRGB(&p_RGB);
}
void p_setHSV(void) {
    frontColorSense.getHSV(&p_ProximateHSV);
    cpyProximateHSV(&p_ProximateHSV);
}
void p_setColor(void) {
    frontColorSense.getColor(&p_ApproximateHSV);
    cpyApproximateHSV()
}