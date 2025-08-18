/**
 * @file timer.cpp
 */
#include <stdio.h>
#include "timer.h"

/**
 * @brief コンストラクタ
 */
Timer::Timer(Clock& clock) : 
    mClock(clock){
    // 初期化
    dwStartTime_MS = 0;
    dwTimeoutDuration = 0;

}

/**
 * @brief タイマー開始
 * @param timeoutDuration_MS タイムアウトまでの時間（ミリ秒単位）
 */
void Timer::start(DWORD timeoutDuration_MS) {
    dwStartTime_MS = mClock.now();
    dwTimeoutDuration = timeoutDuration_MS;
}

/**
 * @brief タイマー停止
 */
void Timer::stop(void) {
    dwStartTime_MS = 0;
    dwTimeoutDuration = 0;
}

/**
 * @brief タイマーリセット
 */
void Timer::reset(void) {
    dwStartTime_MS = mClock.now();
}

/**
 * @brief タイムアウトチェック
 * @return タイムアウトしている場合はtrue、そうでない場合はfalse
 */
bool Timer::isTimeout(void) {
    
    DWORD currentTime_MS = mClock.now();
    if ((currentTime_MS - dwStartTime_MS) >= dwTimeoutDuration) {
        return true;
    }
    
    return false;
}