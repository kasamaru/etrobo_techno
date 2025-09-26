
/**
 * @brief Walker
 */
#include <stdio.h>

#include "walker.h"

/* 技術教育1回目のsample01_01コピー */
Walker::Walker(Motor& leftWheel, Motor& rightWheel):               
    mLeftWheel(leftWheel),
    mRightWheel(rightWheel){

}

void Walker::stop(void) {
    /* 両ホイールを止める */
    stopRightWheel();
    stopLeftWheel();

}

void Walker::setPWMForLineTrace(SWORD nRightPWM, SWORD nLeftPWM) {
    /* ライントレース用のPWM値を設定 */
    mLeftWheel.setPower(nLeftPWM);
    mRightWheel.setPower(nRightPWM);
}

/**
 * @brief 前進
 * @note 前進する制限時間は、呼び元で管理すること
 */
void Walker::runForward(SWORD rightPWM, SWORD leftPWM) {
    mLeftWheel.setPower(leftPWM);
    mRightWheel.setPower(rightPWM);
}

/**
 * @brief 後退
 * @note 後退する制限時間は、呼び元で管理すること
 */
void Walker::runBackward(WORD rightPWM, WORD leftPWM) {
    mLeftWheel.setPower(-leftPWM);
    mRightWheel.setPower(-rightPWM);
}

/**
 * @brief 右ホイールのモータ回転速度取得
 * @return 右ホイールモータ回転速度(int32_t)
 */
DWORD Walker:: getRightSpeed(void) {
    return mRightWheel.getSpeed();
}

/**
 * @brief 左ホイールのモータ回転速度取得
 * @return 左ホイールモータ回転速度(int32_t)
 */
DWORD Walker::getLeftSpeed(void) {
    return mLeftWheel.getSpeed();
}

/**
 * @brief 右ホイールを止める
 */
void Walker::stopRightWheel(void) {
    return mRightWheel.setPower(0);
}

/**
 * @brief 左ホイールを止める
 */
void Walker::stopLeftWheel(void) {
    return mLeftWheel.setPower(0);
}

/**
 * @brief 右ホイールをブレーキをかけて止める
 */
void Walker::brakeRightWheel(void) {
    mRightWheel.brake();
}

/**
 * @brief 左ホイールをブレーキをかけて止める
 */
void Walker::brakeLeftWheel(void) {
    mLeftWheel.brake();
}
