/**
 * @brief starter.cpp
 */

#include "starter.h"

Starter::Starter(ForceSensor& forceSensor) :
    mForceSensor(forceSensor) {
}

/**
 * 押下中か否か
 * @retval true  押下している
 * @retval false 押下していない
 */
bool Starter::isPushed(void){
    return mForceSensor.isTouched();
}