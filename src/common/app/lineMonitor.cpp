/**
 * @brief LineMonitor.cpp
 */

#include "lineMonitor.h"

LineMonitor::LineMonitor(ColorSensor& colorSensor) : 
    mColorSensor(colorSensor) {
}

SDWORD LineMonitor::getReflection(void) {
    return mColorSensor.getReflection();
}

bool LineMonitor::isRGBThExceeded(WORD wRGBR, WORD wRGBG, WORD wRGBB) {
    // RGB閾値チェックの実装
    mColorSensor.getRGB(p_RGB);
    return ((wRGBR > p_RGB.r) || (wRGBG > p_RGB.g) || (wRGBB > p_RGB.b));
}


bool LineMonitor::isLineDetected(WORD wRGBR, WORD wRGBG, WORD wRGBB) {
    // 線の検出ロジック
    return isRGBThExceeded(wRGBR, wRGBG, wRGBB);
}
