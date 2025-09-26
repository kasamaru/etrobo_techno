/**
 * @brief LineMonitor.cpp
 */
#include <stdio.h>
#include "lineMonitor.h"


LineMonitor::LineMonitor(ColorSensor& colorSensor) : 
    mColorSensor(colorSensor) {
}

SDWORD LineMonitor::getReflection(void) {
    return mColorSensor.getReflection();
}

bool LineMonitor::isRGBThExceeded(WORD wRGBRth_Max, WORD wRGBGth_Max, WORD wRGBBth_Max, WORD wRGBRth_Min, WORD wRGBGth_Min, WORD wRGBBth_Min) {
    // RGB閾値チェックの実装
    mColorSensor.getRGB(p_RGB);
    // printf("R: %d, G: %d, B: %d\n", p_RGB.r, p_RGB.g, p_RGB.b);
    // printf("Thresholds - R: %d, G: %d, B: %d\n", wRGBRth_Max, wRGBGth_Max, wRGBBth_Max);
    bool aboveMax = (p_RGB.r < wRGBRth_Max) && (p_RGB.g < wRGBGth_Max) && (p_RGB.b < wRGBBth_Max);
    bool belowMin = (p_RGB.r > wRGBRth_Min) && (p_RGB.g > wRGBGth_Min) && (p_RGB.b > wRGBBth_Min);
    if(p_RGB.b > 110) {
        printf("R: %d, G: %d, B: %d\n", p_RGB.r, p_RGB.g, p_RGB.b);
    }
    if(aboveMax && belowMin) {
        printf("Line Detected! R: %d, G: %d, B: %d\n", p_RGB.r, p_RGB.g, p_RGB.b);
    }
    return aboveMax && belowMin;
}


bool LineMonitor::isLineDetected(WORD wRGBRth_Max, WORD wRGBGth_Max, WORD wRGBBth_Max, WORD wRGBRth_Min, WORD wRGBGth_Min, WORD wRGBBth_Min) {
    // 線の検出ロジック
    return isRGBThExceeded(wRGBRth_Max, wRGBGth_Max, wRGBBth_Max, wRGBRth_Min, wRGBGth_Min, wRGBBth_Min);
}
