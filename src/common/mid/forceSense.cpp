/**
 * @brief forceSense.cpp
 */
/* TODO: ファイル名変更、よくない技術教育ならStarterになってる */
#include <stdio.h>
#include "forceSense.h"

void ForceSense::ForceSense():
    forceSense(EPort::PORT_D) {


}

/* TODO: この以下にラップした関数を作成して下さい */
/**
 * 押下中か否か
 * @retval true  押下している
 * @retval false 押下していない
 */
bool ForceSense::isPushed() const {
    return mForceSensor.isTouched();
}