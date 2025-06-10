
/**
 * @brief Walker
 */
#include <stdio.h>

#include "Walker.h"

/* 技術教育1回目のsample01_01コピー */
Walker::Walker():               
  leftWheel(EPort::PORT_B,Motor::EDirection::COUNTERCLOCKWISE,true), 
  rightWheel(EPort::PORT_A,Motor::EDirection::CLOCKWISE,true){

}

/**
 * @brief 前進
 * @note 前進する制限時間は、呼び元で管理すること
 */
void Walker::runForward(WORD rightPWM, WORD leftPWM) {
    leftWheel.setPower(leftWheel);
    rightWheel.setPower(rightWheel);
}

/**
 * @brief 後退
 * @note 後退する制限時間は、呼び元で管理すること
 */
void Walker::runBackward(WORD rightPWM, WORD leftPWM) {
    leftWeel.setPower(-leftPWM);
    rightWheel.setPower(-rightPWM)
}

/**
 * @brief 右ホイールのモータ回転速度取得
 * @return 右ホイールモータ回転速度(int32_t)
 */
DWORD Walker:: getRightSpeed(void) {
    return rightWheel.getSpeed();
}

/**
 * @brief 左ホイールのモータ回転速度取得
 * @return 左ホイールモータ回転速度(int32_t)
 */
DWORD Walker::getLeftSpeed(void) {
    return leftWheel.getSpeed();
}

/**
 * @brief 右ホイールを止める
 */
void Walker::stopRightWheel(void) {
    return rightWheel.stop();
}

/**
 * @brief 左ホイールを止める
 */
void Walker::stopLeftWheel(void) {
    return leftWheel.stop();
}

/**
 * @brief 右ホイールをブレーキをかけて止める
 */
void Walker::brakeRightWheel(void) {
    rightWheel.brake();
}

/**
 * @brief 左ホイールをブレーキをかけて止める
 */
void Walker::brakeLeftWheel(void) {
    leftWheel.brake();
}
